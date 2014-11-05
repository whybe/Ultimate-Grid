/*************************************************************************
				Class Implementation : CUGAutoFontType
**************************************************************************
	Source file : UGCTafnt.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTAfnt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***************************************************
CUGAutoFontType - Constructor
	Initialize all member data
****************************************************/
CUGAutoFontType::CUGAutoFontType(){
	m_canOverLap = FALSE;
}

/***************************************************
~CUGAutoFontType - Destructor
	Clean up all allocated resources
****************************************************/
CUGAutoFontType::~CUGAutoFontType(){
}

/***************************************************
GetName  - overloaded CUGCellType::GetName
	Returns a readable name for the cell type.
	Returned value is used to help end-users
	to see what cell type are available.

    **See CUGCellType::GetName for more details
	about this function

Params:
	<none>
Return:
	cell type name
****************************************************/
LPCTSTR CUGAutoFontType::GetName()
{
	return _T("Auto Font");
}

/***************************************************
GetUGID  - overloaded CUGCellType::GetUGID
	Returns a GUID for the cell type, this number
	is unique for each cell type and never changes.
	This number can be used to find the cell types
	added to this instance of the Ultimate Grid.

    **See CUGCellType::GetUGID for more details
	about this function

Params:
	<none>
Returns:
	UGID (which is actually a GUID)
****************************************************/
LPCUGID CUGAutoFontType::GetUGID()
{
	static const UGID ugid = 
	{ 0x45858880, 0xd9eb, 0x11d5, { 0x9b, 0x37, 0x0, 0x50, 0xba, 0xd4, 0x4b, 0xcd } };

	return &ugid;
}

/***************************************************
OnDraw - overloaded CUGCellType::OnDraw
	This function will adjust the font size used for
	drawing the text for the given cell based on the
	length of the text, in an attempt to display the
	entire text string

    **See CUGCellType::OnDraw for more details
	about this function
****************************************************/
void CUGAutoFontType::OnDraw(CDC *dc,RECT *rect,int col,long row,
							 CUGCell *cell,int selected,int current)
{
	if (!m_drawThemesSet)
		m_useThemes = cell->UseThemes();

	DrawBorder(dc,rect,rect,cell);

	HFONT oldFont = NULL;

	//create the font needed
	if(cell->IsPropertySet(UGCELL_FONT_SET))
		oldFont = (HFONT) ::SelectObject(dc->m_hDC, (HFONT)(cell->GetFont()->m_hObject));

	HFONT newFont = NULL;

	float fScale = 1.0;
#ifdef UG_ENABLE_PRINTING
	fScale = m_ctrl->GetUGPrint()->GetPrintVScale(dc);
#endif

	if(cell->IsPropertySet(UGCELL_TEXT_SET)){
		int oldLeft = rect->left;
		rect->left += (int) (m_ctrl->m_GI->m_margin * fScale);
		newFont = CreateAutoSizeFont(dc->m_hDC,rect,cell->GetText());
		if (NULL != oldFont)
			oldFont = (HFONT) ::SelectObject(dc->m_hDC, newFont);
		else
			dc->SelectObject(newFont);
		cell->ClearPropertySetFlag(UGCELL_FONT_SET);
		rect->left = oldLeft;
	}

	//draw the text in using the default drawing routine
	DrawText(dc,rect,0,col,row,cell,selected,current);

	if( NULL != oldFont ) SelectObject(dc->m_hDC, oldFont);
	if( NULL != newFont ) DeleteObject(newFont);
}

/***************************************************
CreateAutoSizeFont
	Determines the size of the font required to
	draw the text with. The font is then created
	and returned.
Params
	hdc - device context
	rect - rectagle of the cell to be drawn
	string - string to be drawn within the cell rectangle
Return
	HFONT - handle to the newly created font object
****************************************************/
HFONT CUGAutoFontType::CreateAutoSizeFont(HDC hdc, RECT *rect,LPCTSTR string)
{
	HFONT	font;
	int		Height = 1;
	int		Width = rect->right - rect->left;

	SIZE	size;
	float   ratio;
	TEXTMETRIC tm;
	TCHAR	fontFace[60];
	int		rt;
	int saveID = SaveDC(hdc);
	
	GetTextFace(hdc,60,fontFace);
	GetTextMetrics(hdc,&tm);

	Height = Width/(int)_tcslen(string);
	if(Height < 1)
		Height = 1;
	Height = Height + Height/2;

	font =  CreateFont(Height, 0, 0, 0, 600, 0,0,0,0,0,0,0,0,fontFace);
	SelectObject(hdc,font);

	GetTextExtentPoint(hdc,string,(int)_tcslen(string),&size);
	ratio = (float)size.cy/(float)size.cx;
	Height = (int)((float)Width*ratio);
	rt = RestoreDC(hdc,saveID);
	rt = DeleteObject(font);
	font = CreateFont(Height, 0, 0, 0, 600, 0,0,0,0,0,0,0,0,fontFace);
	SelectObject(hdc,font);
	GetTextExtentPoint(hdc,string,(int)_tcslen(string),&size);

	if (Width >size.cx)
	{
		while (Width > size.cx && Height < 500)
		{
			rt = RestoreDC(hdc,saveID);
			rt = DeleteObject(font);
			Height++;
			font = CreateFont(Height, 0, 0, 0, 600, 0,0,0,0,0,0,0,0,fontFace);
			SelectObject(hdc,font);
			GetTextExtentPoint(hdc,string,(int)_tcslen(string),&size);

		}
		rt = RestoreDC(hdc,saveID);
		rt = DeleteObject(font);
		Height--;
		if(Height > 0)
			font = CreateFont(Height, 0, 0, 0, 600, 0,0,0,0,0,0,0,0,fontFace);

	}
	else if (Width < size.cx)
	{
		while (Width < size.cx  && Height > 1)
		{
			rt = RestoreDC(hdc,saveID);
			rt = DeleteObject(font);
			Height--;
			font = CreateFont(Height, 0, 0, 0, 600, 0,0,0,0,0,0,0,0,fontFace);
			SelectObject(hdc,font);
			GetTextExtentPoint(hdc,string,(int)_tcslen(string),&size);
			if(Height<1)
				break;
		}

		rt = RestoreDC(hdc,saveID);
		rt = DeleteObject(font);
		Height--;
		if(Height < 1)
			Height = 1;
		font = CreateFont(Height, 0, 0, 0, 600, 0,0,0,0,0,0,0,0,fontFace);
	}
	if (Height >(rect->bottom - rect->top))
	{
		Height = rect->bottom - rect->top;
		if(Height <2)
			Height = 2;
		rt = RestoreDC(hdc,saveID);
		rt = DeleteObject(font);
		font = CreateFont(Height, 0, 0, 0, 600, 0,0,0,0,0,0,0,0,fontFace);
	}
	
	rt = RestoreDC(hdc,saveID);

	return font;
}
