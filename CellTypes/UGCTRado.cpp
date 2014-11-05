/*************************************************************************
				Class Implementation : CUGRadioType
**************************************************************************
	Source file : UGCTrado.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTRado.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***************************************************
CUGRadioType - Constructor
****************************************************/
CUGRadioType::CUGRadioType(){

	m_canOverLap = FALSE;
	SetTextEditMode(FALSE);
}
/***************************************************
~CUGRadioType - Destructor
****************************************************/
CUGRadioType::~CUGRadioType(){
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
LPCTSTR CUGRadioType::GetName()
{
	return _T("Radio Button");
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
LPCUGID CUGRadioType::GetUGID()
{
	static const UGID ugid = 
	{ 0x4585888f, 0xd9eb, 0x11d5, { 0x9b, 0x37, 0x0, 0x50, 0xba, 0xd4, 0x4b, 0xcd } };

	return &ugid;
}

/***************************************************
OnLClicked - overloaded CUGCellType::OnLClicked
	Checks to see if the area where the radio button 
	is drawn within the cell has been clicked.
	If so then the state of the 

    **See CUGCellType::OnLClicked for more details
	about this function
****************************************************/
BOOL CUGRadioType::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point)
{
	if(updn)
	{
		//get the height of the font
		int itemHeight;
		CDC * dc = m_ctrl->GetDC();
		
		m_ctrl->GetCellIndirect(col,row,&m_cell);

		if ( m_cell.GetReadOnly() == TRUE )
			return FALSE;

		if(m_cell.IsPropertySet(UGCELL_FONT_SET) == FALSE)
			if(m_ctrl->m_GI->m_defFont != NULL)
			dc->SelectObject(m_ctrl->m_GI->m_defFont);
		else
			dc->SelectObject(m_cell.GetFont());

		CSize size = dc->GetTextExtent(_T("X"),1);
		m_ctrl->ReleaseDC(dc);
		itemHeight = size.cy;

		//check the x -co-ord
		//int x = point->x - rect->left;
		//if(x <3 || x > itemHeight)
			//return FALSE;

		//find which item was selected
		int y = point->y - rect->top;
		int select = y / itemHeight;

		//get the old selection
		int oldSelect = (int)m_cell.GetNumber();

		//get the number of items
		CString label = m_cell.GetLabelText();
		int itemCount = 0;
		int t;
		int len = label.GetLength();
		for(t = 0;t<len;t++){
			if(label.GetAt(t) == _T('\n')){
				itemCount++;
			}
		}
		if(select >= itemCount)
			return FALSE;
		
		//check to see if they are the same
		if(select != oldSelect){
			m_cell.SetNumber(select);
			m_ctrl->SetCell(col,row,&m_cell);
			m_ctrl->RedrawCell(col,row);
		}
	
		OnCellTypeNotify(m_ID, col, row, UGCT_RADIOBUTTON_SELECTED, select);
		
		return TRUE;
	}
	return FALSE;
}
/***************************************************
OnKeyDown - overloaded CUGCellType::OnKeyDown

    **See CUGCellType::OnKeyDown for more details
	about this function
****************************************************/
BOOL CUGRadioType::OnKeyDown(int col,long row,UINT *vcKey)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);

	if ( *vcKey == VK_SPACE )
	{	
		int select,col,itemHeight,itemCount;
		long row;
		CString label;
		CDC * dc;
				
		col = m_ctrl->GetCurrentCol();
		row= m_ctrl->GetCurrentRow();

		dc = m_ctrl->GetDC();
		
		m_ctrl->GetCellIndirect(col,row,&m_cell);

		if ( m_cell.GetReadOnly() == TRUE )
			return FALSE;

		if(m_cell.IsPropertySet(UGCELL_FONT_SET) == FALSE){
			if(m_ctrl->m_GI->m_defFont != NULL)
				dc->SelectObject(m_ctrl->m_GI->m_defFont);
		}
		else
			dc->SelectObject(m_cell.GetFont());

		CSize size = dc->GetTextExtent(_T("X"),1);
		m_ctrl->ReleaseDC(dc);
		itemHeight = size.cy;

		select = (int)m_cell.GetNumber();

		//get the number of items
		label = m_cell.GetLabelText();
		itemCount = 0;
		int len = label.GetLength();
		for(int t = 0; t < len ;t++){
			if(label.GetAt(t) == _T('\n')){
				itemCount++;
			}
		}
		if(select >= itemCount - 1)
			select = 0;
		else
			select++;
		
		//check to see if they are the same
		m_cell.SetNumber(select);
		m_ctrl->SetCell(col,row,&m_cell);
		m_ctrl->RedrawCell(col,row);
			
		OnCellTypeNotify(m_ID, col, row, UGCT_RADIOBUTTON_SELECTED, select);
		
		return TRUE;
	}
	return FALSE;
}
/***************************************************
OnDraw - overloaded CUGCellType::OnDraw
	Draws the list of radio button in the cell based
	on the \n separated list of items (located in the
	cells label field).

    **See CUGCellType::OnDraw for more details
	about this function
****************************************************/
void CUGRadioType::OnDraw(CDC *dc,RECT *rect,int col,long row,
						 CUGCell *cell,int selected,int current)
{
	if (!m_drawThemesSet)
		m_useThemes = cell->UseThemes();

	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(selected);
	UNREFERENCED_PARAMETER(current);
	
	DrawBorder(dc,rect,rect,cell);

	long properties = cell->GetPropertyFlags();

	int saveID = dc->SaveDC();
	
	CRgn rgn;
	rgn.CreateRectRgnIndirect(rect);
	dc->SelectClipRgn(&rgn);

	int alignment;
	if(properties&UGCELL_ALIGNMENT_SET)
		alignment = cell->GetAlignment();
	else
		alignment = 0;

	//select the font
	if(properties&UGCELL_FONT_SET )
		dc->SelectObject(cell->GetFont());

	//check the selected and current states
	if(selected || (current && m_ctrl->m_GI->m_currentCellMode&2))
	{
		dc->SetTextColor(cell->GetHTextColor());
		DrawBackground( dc, rect, cell->GetHBackColor(), row, col, cell, selected > 0, current > 0);
	}
	else
	{
		dc->SetTextColor(cell->GetTextColor());
		DrawBackground( dc, rect, cell->GetBackColor(), row, col, cell, selected > 0, current > 0);
	}
		
	//get the height of the font
	int itemHeight;
	CSize size = dc->GetTextExtent(_T("X"),1);
	itemHeight = size.cy;

	//get the number of items
	CString label;
	if(properties&UGCELL_LABEL_SET)
		label = cell->GetLabelText();

	int itemCount = 0;
	int t;
	int len = label.GetLength();
	for(t = 0;t<len;t++){
		if(label.GetAt(t) == _T('\n')){
			itemCount++;
		}
	}
	//get the pointers to each
	int *positions = new int[itemCount+1];
	positions[0] = 0;
	int count =1;
	for(t = 0;t<len;t++){
		if(label.GetAt(t) == _T('\n')){
			positions[count] = t+1;
			count++;
		}
	}

	//get the selected item
	int selectNum = (int)cell->GetNumber();

	//draw the items
	RECT itemRect;
	CopyRect(&itemRect,rect);
	itemRect.left +=3;
	itemRect.top ++;
	for(t=0;t<itemCount;t++){
		//draw the circle
		itemRect.bottom = itemRect.top+itemHeight;
		itemRect.right = itemRect.left+itemHeight;
		itemRect.top+=2;
		itemRect.bottom-=2;
		itemRect.right-=3;
		//dc->SelectObject(GetStockObject(WHITE_BRUSH));

		if (m_useThemes && UGXPThemes::IsThemed())
		{
			UGXPThemes::DrawBackground(NULL, *dc, (selectNum == t) ? XPCellTypeRadioYes : XPCellTypeRadio, UGXPThemes::GetState(selected > 0, current > 0), &itemRect, NULL);
		}
		else
		{
			dc->SelectObject((CBrush*)CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
			dc->Ellipse(&itemRect);
			
			//draw the selected button
			if(selectNum == t){
				itemRect.left+=2;
				itemRect.top+=2;
				itemRect.bottom-=2;
				itemRect.right-=2;
				//dc->SelectObject(GetStockObject(BLACK_BRUSH));
				dc->SelectObject((CBrush*)CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
				dc->Ellipse(&itemRect);
				itemRect.left-=2;
    			itemRect.top-=2;
	    		itemRect.bottom+=2;
				itemRect.right+=2;
			}
		}


		//draw the label text
		itemRect.top-=2;
		itemRect.bottom+=2;
		itemRect.right+=3;
		itemRect.right = rect->right;
		itemRect.left += itemHeight;
	
		//text alignment
		CString label = cell->GetLabelText();
		CString string = label.Mid(positions[t],positions[t+1] - positions[t]-1);
		int left;
		if(alignment & UG_ALIGNCENTER){
			GetTextExtentPoint(dc->m_hDC,string,lstrlen(string),&size);
			left = itemRect.left + (itemRect.right - itemRect.left - size.cx) /2;
		}
		else if(alignment & UG_ALIGNRIGHT){
			GetTextExtentPoint(dc->m_hDC,string,lstrlen(string),&size);
			left = itemRect.right - size.cx - 3;
		}
		else{
			left = itemRect.left+3;
		}	

		CString drawText = label.Mid(positions[t],positions[t+1] - positions[t]-1);

		if (!m_useThemes || !UGXPThemes::WriteText(NULL, *dc, XPCellTypeRadio, UGXPThemes::GetState(selected > 0, current > 0), drawText, drawText.GetLength(), DT_LEFT, &itemRect)) 
		{
			//draw
			dc->ExtTextOut(left,itemRect.top,ETO_CLIPPED,
				&itemRect,
				drawText 
				,NULL);
		}
		itemRect.left -= itemHeight;
		itemRect.top = itemRect.bottom;
	}
	
	delete positions;
	dc->RestoreDC(saveID);

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
void CUGRadioType::GetBestSize(CDC *dc,CSize *size,CUGCell *cell)
{
	CRect rect(0,0,0,0);
	CFont* oldFont = NULL;

	if( cell->IsPropertySet( UGCELL_FONT_SET ))
		oldFont = dc->SelectObject( cell->GetFont());
	// get height of each item
	CSize itemSize = dc->GetTextExtent(_T("X"),1);
	// calculate the rect needed to draw the text
	dc->DrawText( cell->GetLabelText(), rect, DT_CALCRECT );
	dc->SelectObject( oldFont );
	// combine the results
	size->cx = rect.Width() + itemSize.cx + 8;
}