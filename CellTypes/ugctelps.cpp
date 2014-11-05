/*************************************************************************
				Class Implementation : CUGEllipsisType
**************************************************************************
	Source file : UGCTelps.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTelps.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/********************************************
CUGEllipsisType - Constructor
*********************************************/
CUGEllipsisType::CUGEllipsisType(){

	m_btnWidth =	GetSystemMetrics(SM_CXVSCROLL);
	m_btnDown =		FALSE;

	m_pen.CreatePen(PS_SOLID,1,GetSysColor(COLOR_BTNFACE));
	m_brush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));

	m_canOverLap = FALSE;
}
/********************************************
~CUGEllipsisType - Destructor
*********************************************/
CUGEllipsisType::~CUGEllipsisType(){
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
LPCTSTR CUGEllipsisType::GetName()
{
	return _T("Ellipsis Text");
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
LPCUGID CUGEllipsisType::GetUGID()
{
	static const UGID ugid =
	{ 0x45858885, 0xd9eb, 0x11d5, { 0x9b, 0x37, 0x0, 0x50, 0xba, 0xd4, 0x4b, 0xcd } };


	return &ugid;
}
/********************************************
OnLClicked - overloaded CUGCellType::OnLClicked
	Checks to see if the ellipsis button has
	been clicked. If the mouse button is pressed,
	then the button is redrawn as depressed. Once
	the button is released (and is still over the
	ellipsis button) then the ellipsis button is 
	redrawn as raised and the UGCT_ELLIPSISBUTTONCLICK
	notification is fired.

    **See CUGCellType::OnLClicked for more details
	about this function
*********************************************/
BOOL CUGEllipsisType::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point){

	if(updn){
		if(point->x > (rect->right -m_btnWidth)){			
			
			//copy the button co-ords
			CopyRect(&m_btnRect,rect);
			m_btnRect.left = rect->right - m_btnWidth;
			
			//redraw the button
			m_btnDown = TRUE;
			m_btnCol = col;
			m_btnRow = row;
			m_ctrl->RedrawCell(m_btnCol,m_btnRow);
			return TRUE;
		}

		m_btnCol = -1;
		m_btnRow = -1;			
		return FALSE;
	}
	else if(m_btnDown){		

		//notify the user that the button has been clicked
		OnCellTypeNotify(m_ID,col,row,UGCT_ELLIPSISBUTTONCLICK,0);
		m_btnDown = FALSE;
		m_btnCol = -1;
		m_btnRow = -1;			

		m_ctrl->RedrawCell(col,row);
		return TRUE;
	}
	return FALSE;
}
/********************************************
OnDClicked - overloaded CUGCellType::OnDClicked
	Redirects all double click events to the
	OnLClicked function (see OnLClicked)

    **See CUGCellType::OnDClicked for more details
	about this function
*********************************************/
BOOL CUGEllipsisType::OnDClicked(int col,long row,RECT *rect,POINT *point){
	
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(point);

	return TRUE;
}
/********************************************
OnMouseMove - overloaded CUGCellType::OnMouseMove
	If the ellipsis button is depressed and the
	mouse button is down, then this function checks
	to see if the mouse has been moved outside of
	the button area. If so then the button is drawn
	as raised. Once the mouse re-enters the button
	area the button is then drawn as depressed.
	
    **See CUGCellType::OnMouseMove for more details
	about this function
*********************************************/
BOOL CUGEllipsisType::OnMouseMove(int col,long row,POINT *point,UINT flags){

	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);

	if((flags&MK_LBUTTON) == FALSE)
		return FALSE;

	if(point->x >= m_btnRect.left && point->x <= m_btnRect.right){
		if(point->y >= m_btnRect.top && point->y <= m_btnRect.bottom){
			if(!m_btnDown){
				m_btnDown = TRUE;
				m_ctrl->RedrawCell(m_btnCol,m_btnRow);
			}
			return TRUE;
		}
	}
	if(m_btnDown){
		m_btnDown = FALSE;
		m_ctrl->RedrawCell(m_btnCol,m_btnRow);
	}
	return FALSE;
}
/********************************************
GetEditArea - overloaded CUGCellType::GetEditArea
	Returns the valid edit area within the cell,
	which is the entire area of the cell minus
	the ellipsis button.

    **See CUGCellType::GetEditArea for more details
	about this function
*********************************************/
int CUGEllipsisType::GetEditArea(RECT *rect)
{
	rect->right -= m_btnWidth + 1;

	return UG_SUCCESS;
}
/********************************************
OnDraw - overloaded CUGCellType::OnDraw
	Draws the context of the cell. All text
	drawing is handled by the CUGCellType::DrawText
	routine, therefore it inherits all of the
	default text drawing capabilities.
	This function is also responsible for drawing
	the ellipsis button portion of the cell.

    **See CUGCellType::OnDraw for more details
	about this function
*********************************************/
void CUGEllipsisType::OnDraw(CDC *dc,RECT *rect,int col,long row,
							 CUGCell *cell,int selected,int current)
{
	if (!m_drawThemesSet)
		m_useThemes = cell->UseThemes();

	float fScale = 1.0;
#ifdef UG_ENABLE_PRINTING
	fScale = m_ctrl->GetUGPrint()->GetPrintVScale(dc);
#endif

	int style = 0;
	if( cell->IsPropertySet( UGCELL_CELLTYPEEX_SET ) )
		style = cell->GetCellTypeEx();

	//if the cell is not current and hide button is on
	//then don't draw the button
	if( style & UGCT_ELLIPSISHIDEBUTTON && !current)
	{
		CUGCellType::OnDraw(dc,rect,col,row,cell,selected,current);
		return;
	}

	DrawBorder(dc,rect,rect,cell);

	int left = rect->left;
	RECT rectout;
	CPen * oldpen;

	//draw the 3D border
	rect->left = rect->right - (int) (m_btnWidth * fScale);


#ifdef UG_ENABLE_PRINTING
	if (dc->IsPrinting())
	{
		rect->left += (int) fScale;
		rect->right -= (int) fScale;
		rect->top += (int) fScale;
		rect->bottom -= (int) fScale;
	}
#endif
	UGXPThemeState state = UGXPThemes::GetState(selected > 0, current > 0);

	if(m_btnDown && current){
		cell->SetBorder(UG_BDR_RECESSED);
		DrawBorder(dc,rect,&rectout,cell);
		state = ThemeStatePressed;
	}
	else{
		cell->SetBorder(UG_BDR_RAISED);
		DrawBorder(dc,rect,&rectout,cell);
	}

	if (m_useThemes && UGXPThemes::IsThemed())
	{
		UGXPThemes::DrawBackground(NULL, *dc, XPCellTypeButton, state, &rectout, NULL);
		UGXPThemes::WriteText(NULL, *dc, XPCellTypeButton, state, _T("..."), 3, DT_CENTER, &rectout);
	}
	else
	{
		//fill the border in
		dc->SetBkColor(GetSysColor(COLOR_BTNFACE));
		dc->FillRect(&rectout,&m_brush);
	
		//make a line to separate the border from the rest ofthe cell
		oldpen = (CPen *)dc->SelectObject((CPen *)&m_pen);
		dc->MoveTo(rect->left-1,rect->top);
		dc->LineTo(rect->left-1,rect->bottom);

		//draw the three ...
		int x= rect->left + (((int) (m_btnWidth * fScale) - (int) (7 * fScale))/2);
		int y = rect->top + ((rect->bottom - rect->top)/4)*3;

		dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(BLACK_PEN)));
		dc->MoveTo(x, y);
		dc->LineTo(x, y + (int) (2 * fScale));
		dc->MoveTo(x + (int) (3 * fScale), y);
		dc->LineTo(x + (int) (3 * fScale), y + (int) (2 * fScale));
		dc->MoveTo(x + (int) (6 * fScale), y);
		dc->LineTo(x + (int) (6 * fScale), y + (int) (2 * fScale));
		
		dc->SelectObject(oldpen);

	}
	

	//draw the text in using the default drawing routine
	rect->left =left;
	rect->right -=((int) (m_btnWidth * fScale) + (int) fScale);

	DrawText(dc,rect,0,col,row,cell,selected,current);

	return;
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
void CUGEllipsisType::GetBestSize(CDC *dc,CSize *size,CUGCell *cell)
{
	CUGCellType::GetBestSize( dc, size, cell );
	// in the case of the drop list celltype we will take the normal
	// width of the text selected, and if the drop button is vible,
	// we will increate the width by the width of the button.
	if (!( cell->GetCellTypeEx()&UGCT_DROPLISTHIDEBUTTON ))
	{
		size->cx += m_btnWidth;
	}
}
