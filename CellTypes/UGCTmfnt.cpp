/*************************************************************************
				Class Implementation : CUGMultiFontType
**************************************************************************
	Source file : UGCTmfnt.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTmfnt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{

	int gcd(int x, int y)
	{
		while(x!=y)
		{
			if (x>y) x -= y;
			else y -=x;
		}

		return x;
	}

	void SetExtents(CDC * dc, int wx, int wy, int vx, int vy)
	{
		int gx = gcd(wx, vx);
		int gy = gcd(wy, vy);

		dc->SetWindowExt(wx/gx, wy/gy);
		dc->SetViewportExt(vx/gx, vy/gy);
	}
}

/***************************************************
****************************************************/
CUGMultiFontType::CUGMultiFontType(){
	m_font = NULL;
	m_oldFont = NULL;
	m_canOverLap = FALSE;
	m_fHScale = 1.0;
	m_fVScale = 1.0;
}

/***************************************************
****************************************************/
CUGMultiFontType::~CUGMultiFontType(){
	if(m_font != NULL)
		delete m_font;

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
LPCTSTR CUGMultiFontType::GetName()
{
	return _T("Multi-Font");
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
LPCUGID CUGMultiFontType::GetUGID()
{
	static const UGID ugid = 
	{ 0x45858888, 0xd9eb, 0x11d5, { 0x9b, 0x37, 0x0, 0x50, 0xba, 0xd4, 0x4b, 0xcd } };

	return &ugid;
}

/***************************************************
OnDraw - overloaded CUGCellType::OnDraw
	Draws the text using the inline formating information
	to determine the font and colors to use.

    **See CUGCellType::OnDraw for more details
	about this function
****************************************************/
void CUGMultiFontType::OnDraw(CDC *dc,RECT *rect,int col,long row,
							  CUGCell *cell,int selected,int current){

	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);

	CSize size;
	COLORREF backcolor;
	int left,top;
	int len,x,y;
	CString param;
	int oldleft = rect->left;
	CString string;
	short alignment;

	//store the current state of the DC so that it can be restored again
	int dcSaveID = dc->SaveDC();

	long properties = cell->GetPropertyFlags();

	if(properties&UGCELL_TEXT_SET)
		string = cell->GetText();

	m_fHScale = 1.0;
	m_fVScale = 1.0;
	
	if (dc->IsPrinting())
	{
#ifdef UG_ENABLE_PRINTING
		m_fHScale = m_ctrl->GetUGPrint()->GetPrintHScale(dc);
		m_fVScale = m_ctrl->GetUGPrint()->GetPrintVScale(dc);
#endif	
	}

	DrawBorder(dc,rect,rect,cell);

	//check the selected and current states
	if(selected || (current && m_ctrl->m_GI->m_currentCellMode&2))
	{
		dc->SetTextColor(cell->GetHTextColor());
		backcolor = cell->GetHBackColor();
	}
	else
	{
		dc->SetTextColor(cell->GetTextColor());
		backcolor = cell->GetBackColor();
	}

	DrawBackground( dc, rect, backcolor );

	
	//check for bitmaps
	if(properties&UGCELL_BITMAP_SET)
	{
		oldleft = rect->left;
		rect->left += DrawBitmap(dc,cell->GetBitmap(),rect,backcolor);
	}

	//text alignment
	if(properties&UGCELL_ALIGNMENT_SET)
		alignment = cell->GetAlignment();
	else
		alignment = 0;

	if(alignment & UG_ALIGNCENTER)
	{
		GetBestSize( dc, &size, cell );
		left = rect->left + (rect->right - rect->left - size.cx) /2;
	}
	else if(alignment & UG_ALIGNRIGHT)
	{
		GetBestSize( dc, &size, cell );
		left = rect->right - size.cx - 3;
	}
	else
	{
		left = rect->left+3;
	}	

	if(alignment & UG_ALIGNVCENTER)
	{
		GetTextExtentPoint(dc->m_hDC,string,string.GetLength(),&size);
		top = rect->top + (rect->bottom - rect->top - size.cy) /2;
	}
	else if(alignment & UG_ALIGNBOTTOM)
	{
		GetTextExtentPoint(dc->m_hDC,string,string.GetLength(),&size);
		top = rect->bottom - 6;
		dc->SetTextAlign(TA_BASELINE);
	}
	else
	{
		top = rect->top+1;
	}

	len = string.GetLength();

	for(x=0;x<len;x++)
	{
		//check for the beginning of a format option
		if(string.GetAt(x) =='<' && string.GetAt(x+1) ==':')
		{
			//get the format option string
			y = x+2;
			while(string.GetAt(x) !='>' && x <len)
			{
				x++;
			}
			ParseCommand(dc,&string.Mid(y,x-y));
			x++;
			if(x >= len)
				break;
		}

		//***draw the text*** 
		dc->ExtTextOut(left,top,ETO_CLIPPED,rect,string.Mid(x,1),1,NULL);

		size = dc->GetTextExtent(string.Mid(x,1));
		left += size.cx;
		rect->left = left;
	}

	//reset the rect
	rect->left = oldleft;

	//restore the device context to its original state - to prevent resource leaks
	if(m_oldFont != NULL && ::GetObjectType(m_oldFont))
	{
		dc->SelectObject(m_oldFont);
		m_oldFont = NULL;
	}

	dc->RestoreDC(dcSaveID);
}


/***************************************************
ParseCommand
	Parses an inline formating tag to see if the
	tag contains font or color formating information.
	Once the tag is parsed the formating is applied
	to the device context.
Params
	dc - device context
	command - pointer to the command string to parse
Return
	UG_SUCCESS - success
	UG_ERROR - error
****************************************************/
int CUGMultiFontType::ParseCommand(CDC *dc,CString *command)
{
	int x;
	int pos[30];
	int len = command->GetLength();
	int count =0;
	CString fontName;
	CString string;
	int r,g,b,p,w;

	//make into upper case
	command->MakeUpper();
	
	if ( m_oldFont != NULL && ::GetObjectType(m_oldFont))
	{
		dc->SelectObject( m_oldFont );
		m_oldFont = NULL;
	}

	//get all the position params
	for(x=0;x<len && count <29;x++){
		if(command->GetAt(x) ==_T(',')){
			pos[count] = x;
			count++;
		}
	}
	pos[count] = x;
	
	//see if it is a font command
	if(command->GetAt(0)==_T('F')){
		fontName = command->Mid(pos[0]+1,pos[1]-pos[0]-1);
		p = 12;
		if(count >= 2){
			string = command->Mid(pos[1]+1,pos[2]-pos[1]-1);
			p = _ttoi(string);
		}
		w = 400;
		if(count >= 3){
			string = command->Mid(pos[2]+1,pos[3]-pos[2]-1);
			w = _ttoi(string);
		}

		if(m_font != NULL){
			dc->SelectObject(m_font);
			delete m_font;
		}
		m_font = new CFont;
		m_font->CreateFont((int)(p * m_fVScale),0,0,0,w,0,0,0,0,0,0,0,0,fontName);
		m_oldFont = dc->SelectObject(m_font);

		// This is here because the print preview DC seems to return an invalid font, causing a crash.
		if (!::GetObjectType(m_oldFont))
			m_oldFont = NULL;
	}
	else if(command->GetAt(0)==_T('C')){
		r = 255;
		g = 255;
		b = 255;
		if(count >= 1){
			string = command->Mid(pos[0]+1,pos[1]-pos[0]-1);
			r = _ttoi(string);
		}
		if(count >= 2){
			string = command->Mid(pos[1]+1,pos[2]-pos[1]-1);
			g = _ttoi(string);
		}
		if(count >= 3){
			string = command->Mid(pos[2]+1,pos[3]-pos[2]-1);
			b = _ttoi(string);
		}
		dc->SetTextColor(RGB(r,g,b));
	}
	else{
		return UG_ERROR;
	}

	return UG_SUCCESS;
}

/****************************************************
GetBestSize
	Returns the best (nominal) size for a cell using
	this cell type, with the given cell properties.
Params:
	dc		- device context to use to calc the size on	
	size	- return the best size in this param
	cell	- pointer to a cell object to use for the calc.
Return:
	<none>
*****************************************************/
void CUGMultiFontType::GetBestSize(CDC *dc,CSize *size,CUGCell *cell)
{
	//store the current state of the DC so that it can be restored again
	int dcSaveID = dc->SaveDC();

	CString string = cell->GetText();
	int len = string.GetLength();
	int contentWidth = 0;
	CRect rect(0,0,0,0);
	int bitmapWidth = 0;
	double yin = 0, ratio = 0;

	size->cx = 3;
	size->cy = 3;

	if ( cell->IsPropertySet( UGCELL_BITMAP_SET ))
	{
		BITMAP bitmap;
		cell->GetBitmap()->GetBitmap( &bitmap );
		// calculate the size of the bitmap
		yin = bitmap.bmHeight;
		ratio = ( size->cy + 4 ) / yin;
		bitmapWidth = (int)( bitmap.bmWidth * ratio ) + 6;
	}

	for( int inStrPos = 0; inStrPos < len; inStrPos++ )
	{
		//check for the beginning of a format option
		if( string.GetAt( inStrPos ) =='<' && string.GetAt( inStrPos + 1 ) ==':' )
		{
			//get the format option string
			int tempStrPos = inStrPos + 2;
			while ( string.GetAt( inStrPos ) != '>' && inStrPos < len )
				inStrPos++;

			ParseCommand( dc, &string.Mid( tempStrPos, inStrPos - tempStrPos ));
			inStrPos++;

			if ( inStrPos >= len )
				break;
		}
		rect.top = rect.left = rect.right = rect.bottom = 0;
		// calculate width of individual portion of the string
		dc->DrawText( string.Mid(inStrPos, 1 ), rect, DT_CALCRECT|DT_SINGLELINE );
		contentWidth += rect.Width();
	}

	//use margins
	size->cx = contentWidth + bitmapWidth + 6;
	size->cy = 2;

	//restore the device context to its original state - to prevent resource leaks
	if(m_oldFont != NULL && ::GetObjectType(m_oldFont))
	{
		dc->SelectObject(m_oldFont);
		m_oldFont = NULL;
	}

	dc->RestoreDC(dcSaveID);
}