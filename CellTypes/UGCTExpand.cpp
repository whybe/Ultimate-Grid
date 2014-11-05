/*************************************************************************
				Class Implementation : CUGExpandType
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
#include "UGCTExpand.h"

#ifdef UGEXPANDUSEMAIL
// This is needed for the mark all read/unread functionality
#include "UGCTMail.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***************************************************
CUGExpandType - Constructor
****************************************************/
CUGExpandType::CUGExpandType()
{

	m_canOverLap = TRUE;
	SetTextEditMode(FALSE);
	m_font.CreateFont(13, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS,   DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Tahoma"));

}
/***************************************************
~CUGExpandType - Destructor
****************************************************/
CUGExpandType::~CUGExpandType()
{
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
LPCTSTR CUGExpandType::GetName()
{
	return _T("Expand Button");
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
LPCUGID CUGExpandType::GetUGID()
{
	static const UGID ugid = 
	{ 0x3ED578E, 0xBE0C, 0x11DA, { 0xB0, 0x12, 0xB6, 0x22, 0xA1, 0xEF, 0x54, 0x92 } };

	return &ugid;
}

/***************************************************
ExpandOrContract  - This method toggles the cell at
	the selected position to expand or contract, 
	which basically means walking from that cell until 
	we find one that is of the Expand cell type and 
	either hiding or showing the cells

Params:
	col - the column of the cell to expand from
	row	- the row of the cell to expand from
Return:
	none
****************************************************/
// v7.2 - update 03 - added OnCellTypeNotify call.
void CUGExpandType::ExpandOrContract(int col, int row)
{
    CUGCtrl * ctrl = this->m_ctrl;

    CUGCell thisCell;
    ctrl->GetCell(col, row, &thisCell);

    CellData * cellData = GetCellData(col, row);

    int numberOfRows = cellData->numberOfRows;

	// v7.2 - update 03 - incorporate OnCellTypeNotify callback to allow ID
	// of operation - param indicates current state - if TRUE, expanded 
	// and about to collapse, FALSE collapsed and about to expand.
	// Return FALSE from derived CUGCtrl::OnCellTypeNotify to abort action.
    if(m_ctrl->OnCellTypeNotify(m_ID, col, row, UGCT_EXPANDCONTRACT, cellData->isOpen) == FALSE) {
        return;
    }

	bool isOpen = !cellData->isOpen;

	if (cellData->isSelected)
	{
		cellData->isOpen = isOpen;
	}
	else
	{
		m_ctrl->Invalidate();
		return;
	}

	int initialRow = row;

	CUGCell cell;
	while(true)
	{
		if (row >= ctrl->GetNumberRows())
			break;

		if (numberOfRows > 0 && row - initialRow == numberOfRows)
			break;

		// UG_ERROR is returned in cases where we don't mind, 
		// specifically, if the grid can't work out the cell type.
		// So, we don't do anything in that case, and we don't check 
		// the return type.
		ctrl->GetCell(col, ++row, &cell);

		if (cell.GetCellType() == thisCell.GetCellType())
		{
			break;
		}

        if (!isOpen)
        {
            int height = ctrl->GetRowHeight(row);;

            // v7.2 - update 03 - 0 row height was not stored, causing
			//        rows that were hidden to 'reappear' on collapse/expand.
			//		  Reported by atillaselem
//			if (height > 0)
            if (height >= 0)
            {
                m_mapColumnHeights[row] = height;
                height = 0;
                ctrl->OnRowSizing(row,&height);
                ctrl->SetRowHeight(row,height);
            }				
        }
        else
        {
			int height = m_mapColumnHeights[row];
			ctrl->OnRowSizing(row,&height);
			ctrl->SetRowHeight(row,height);
		}

		ctrl->Invalidate();
	}
}

/***************************************************
OnLClicked - overloaded CUGCellType::OnLClicked
	Checks to see if the area where the radio button 
	is drawn within the cell has been clicked.
	If so then the state of the 

    **See CUGCellType::OnLClicked for more details
	about this function
****************************************************/
BOOL CUGExpandType::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point)
{
	if(updn)
	{
		// Work out if the user clicked on the box, and if so,
		// set the property to true so that it will expand/contract
		RECT rcBox = *rect;
		SIZE sz;

		if (!UGXPThemes::GetThemePartSize(L"TREEVIEW", NULL, 2, 1, &rcBox, 2, &sz))
		{
			sz.cx = sz.cy = 11;
		}

		const int height = rect->bottom - rect->top;
		const int offset = (height - sz.cy) /2;

		rcBox.top = rect->top + offset;
		rcBox.bottom = rcBox.top + sz.cy;
		rcBox.left = rect->left + offset;
		rcBox.right = rcBox.left + sz.cx;

		if (PtInRect(&rcBox, *point))
		{
			CellData * cellData = GetCellData(col, row);

			cellData->isSelected = cellData->wasSelected = true;
//			m_mapSelectedColumns[row].first = m_mapSelectedColumns[row].second = true;
		}
			
		ExpandOrContract(col, row);
			
		return TRUE;
	}
	return FALSE;
}

/***************************************************
OnRClicked - overloaded CUGCellType::OnRClicked
	Checks to see if the area where the radio button 
	is drawn within the cell has been clicked.
	If so then the state of the 

    **See CUGCellType::OnRClicked for more details
	about this function
****************************************************/
BOOL CUGExpandType::OnRClicked(int col,long row,int updn,RECT *rect,POINT *point)
{
	BOOL retval = FALSE;

	if(updn)
	{
		m_ctrl->OnCellTypeNotify(m_ID, col, row, 0, (LONG_PTR)point);

		retval = TRUE;
	}

	return retval;
}

/***************************************************
OnKeyDown - overloaded CUGCellType::OnKeyDown

    **See CUGCellType::OnKeyDown for more details
	about this function
****************************************************/
BOOL CUGExpandType::OnKeyDown(int col,long row,UINT *vcKey)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);

	if ( *vcKey == VK_SPACE )
	{	
		ExpandOrContract(col, row);

		return TRUE;
	}
	return FALSE;
}

/***************************************************
OnDraw - overloaded CUGCellType::OnDraw

    **See CUGCellType::OnDraw for more details
	about this function
****************************************************/
void CUGExpandType::OnDraw(CDC *dc,RECT *rect,int col,long row,
						 CUGCell *cell,int selected,int current)
{
	COLORREF foreCol = RGB(49,106,197);
	COLORREF textCol = RGB(55, 104, 185);

	if (!m_drawThemesSet)
		m_useThemes = cell->UseThemes();

	CellData * cellData = GetCellData(col, row);

	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(selected);
	UNREFERENCED_PARAMETER(current);
	
	cellData->isSelected = (cellData->wasSelected && current > 0);
	cellData->wasSelected = (current>0);

	bool isOpen = cellData->isOpen;

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

	CFont * pFont = NULL;
	//select the font
	if(properties&UGCELL_FONT_SET )
		pFont = dc->SelectObject(cell->GetFont());

	RECT rcBox = *rect;
	SIZE sz;

	if (!UGXPThemes::GetThemePartSize(L"TREEVIEW", NULL, 2, ((isOpen) ? 2 : 1), &rcBox, 2, &sz))
	{
		sz.cx = sz.cy = 11;
	}

	const int height = rect->bottom - rect->top;
	const int offset = height - (int)(sz.cy * 1.5);
	rcBox.top = rect->top + offset;
	rcBox.bottom = rcBox.top + sz.cy;
	rcBox.left = rect->left + 3;
	rcBox.right = rcBox.left + sz.cx;

	RECT rcText = rcBox;
	rcText.top -= 3;
	rcText.right = rect->right;
	rcText.left = rcBox.right + 8;

	//check the selected and current states
	if(selected || current)
	{
		dc->SetTextColor(RGB(255, 255, 255));
	}
	else
	{
		dc->SetTextColor(textCol);
	}

	// Try drawing with themes first
	// This will just fail if themes are turned off.
	bool xpThemeSucceeded = UGXPThemes::DrawBackground(NULL, *dc, L"HEADER", 1, 2, rect, rect);
	xpThemeSucceeded &= UGXPThemes::DrawBackground(NULL, *dc, L"TREEVIEW", 2, ((isOpen) ? 2 : 1), &rcBox, &rcBox);
	xpThemeSucceeded &= UGXPThemes::WriteText(NULL, *dc, _T("TREEVIEW"), 2, ((isOpen) ? 2 : 1), cell->GetText(),
		cell->GetTextLength(), DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS, &rcText);

	if (!xpThemeSucceeded)
	{
		dc->FillSolidRect(rect, (selected >0 || current > 0) ? foreCol : RGB(255, 255, 255));

		if (!m_buttonBack.m_hObject)
		{
			MakeBitmap(dc, rcBox);
		}

		CDC dcButton;
		dcButton.CreateCompatibleDC(dc);
		CBitmap * pOldBitmap = dcButton.SelectObject(&m_buttonBack);
		dc->BitBlt(rcBox.left, rcBox.top, rcBox.right - rcBox.left, rcBox.bottom - rcBox.top, &dcButton, 0, 0, SRCCOPY);

		dcButton.SelectObject(pOldBitmap);

		CGdiObject * oldPen = dc->SelectStockObject(BLACK_PEN);
		dc->MoveTo(rcBox.left + 3, rcBox.top + sz.cy / 2);
		dc->LineTo(rcBox.right - 3, rcBox.top + sz.cy / 2);

		if (!isOpen)
		{
			const int middleX = rcBox.left + (rcBox.right - rcBox.left) / 2;
			dc->MoveTo(middleX, rcBox.top + 3);
			dc->LineTo(middleX, rcBox.bottom - 3);
		}

		dc->SelectObject(oldPen);

		CPen lowerPen(PS_SOLID, 2, RGB(123,163,224));

		oldPen = dc->SelectObject(&lowerPen);
		dc->MoveTo(rect->left, rect->bottom-1);
		dc->LineTo(rect->right, rect->bottom-1);
		dc->SelectObject(oldPen);

		CFont * pOldFont = dc->SelectObject(&m_font);
		dc->DrawText(cell->GetText(), &rcText, DT_END_ELLIPSIS);
		dc->SelectObject(pOldFont);
	}

	if (pFont)
		dc->SelectObject(pFont);

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
void CUGExpandType::GetBestSize(CDC *dc,CSize *size,CUGCell *cell)
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

/****************************************************
MakeBitmap
	This method draws the background for the expand/
	contract button, so we don't have the hand draw it
	every time a paint event occurs.
Params:
	dc		- device context to draw bitmap onto
	rc		- rect to draw bitmap onto
Return:
	<none>
*****************************************************/

void CUGExpandType::MakeBitmap(CDC * source, RECT rc)
{
	int r1=255,g1=255,b1=255;
	int r2=176,g2=200,b2=240;

	int x1=1,y1=1;
	int x2=0,y2=0;

	CRect rect(0, 0, rc.right - rc.left, rc.bottom - rc.top);

	CDC dc;
	dc.CreateCompatibleDC(source);

	m_buttonBack.CreateCompatibleBitmap(source, rect.Width(), rect.Height());

	CBitmap *oldbmap = dc.SelectObject(&m_buttonBack);

	CPen p(PS_SOLID,1,RGB(r1,g1, b1));
	CPen *oldpen = dc.SelectObject(&p); 

	dc.MoveTo(0,0);
	dc.LineTo(rect.Width(), 0);

	dc.SelectObject(oldpen);

	while(x1 < rect.Width()-1 && y1 < rect.Height())
	{
		if(y1 < rect.Height()-1)
			y1++;
		else
			x1++;

		if(x2 < rect.Width()-1)
			x2++;
		else
			y2++;

		int i = x1+y1;
		int r = r1 + (i * (r2-r1) / (rect.Width()+rect.Height()-2));
		int g = g1 + (i * (g2-g1) / (rect.Width()+rect.Height()-2));
		int b = b1 + (i * (b2-b1) / (rect.Width()+rect.Height()-2));

		CPen p(PS_SOLID,1,RGB(r,g,b));

		CPen *oldpen = dc.SelectObject(&p); 

		dc.MoveTo(x1,y1);
		dc.LineTo(x2,y2);


		dc.SelectObject(oldpen);
	} 

	const int stepX = (rect.Width() - 2)/3;
	const int stepY = (rect.Height() - 2)/3;

	int x = 1;
	int y = 1;

	CPen p1(PS_SOLID, 1, RGB(160, 176, 192));

	CPen * oldPen = dc.SelectObject(&p1);
	dc.MoveTo(x, 0);
	dc.LineTo(x+stepX, 0);
	dc.MoveTo(0, y);
	dc.LineTo(0, y+stepY);
	x+=stepX;
	y+=stepY;

	dc.SelectObject(oldPen);

	CPen p2(PS_SOLID, 1, RGB(160, 168, 192));

	oldPen = dc.SelectObject(&p2);
	dc.MoveTo(x, 0);
	dc.LineTo(x+stepX, 0);
	dc.MoveTo(0, y);
	dc.LineTo(0, y+stepY);
	x+=stepX;
	y+=stepY;

	dc.SelectObject(oldPen);

	CPen p3(PS_SOLID, 1, RGB(144, 160, 192));

	oldPen = dc.SelectObject(&p3);
	dc.MoveTo(x, 0);
	dc.LineTo(x+stepX, 0);
	dc.MoveTo(0, y);
	dc.LineTo(0, y+stepY);

	dc.SelectObject(oldPen);

	CPen p4(PS_SOLID, 1, RGB(48, 72, 96));
	oldPen = dc.SelectObject(&p3);
	dc.MoveTo(rect.Width()-1, 1);
	dc.LineTo(rect.Width()-1, rect.Height() - 1);
	dc.LineTo(0, rect.Height() - 1);
	dc.SelectObject(oldPen);

	dc.SetPixel(0, 0, RGB(231, 235, 239));
	dc.SetPixel(0, rect.Height() - 1, RGB(203, 209, 215));
	dc.SetPixel(rect.Width()-1, rect.Height() - 1, RGB(203, 209, 215));
	dc.SetPixel(rect.Width()-1, 0, RGB(203, 209, 215));

	dc.SelectObject(oldbmap);
}

/****************************************************
ExpandAll
	Expands all rows using the column we specify to 
	to search for CUGCTExpand cells.
Params:
	col - the column which contains the expand cells
Return:
	<none>
*****************************************************/

void CUGExpandType::ExpandAll(int col)
{
	if (col >=0 && col < m_ctrl->GetNumberCols())
	{
		const int rowCount = m_ctrl->GetNumberRows();

		for(int row = 0; row < rowCount; ++row)
		{
			if (m_ctrl->GetCellType(col, row)->GetID() == this->GetID())
			{
				CellData * cellData = GetCellData(col, row);
				if (!cellData->isOpen)
				{
					CellData * cellData = GetCellData(col, row);
					cellData->isSelected = true;
					ExpandOrContract(col, row);
				}
			}
		}
		m_ctrl->Invalidate();
	}
}

/****************************************************
CollapseAll
	Collapses all rows using the column we specify to 
	to search for CUGCTExpand cells.
Params:
	col - the column which contains the expand cells
Return:
	<none>
*****************************************************/
void CUGExpandType::CollapseAll(int col)
{
	if (col >=0 && col < m_ctrl->GetNumberCols())
	{
		const int rowCount = m_ctrl->GetNumberRows();

		for(int row = 0; row < rowCount; ++row)
		{
			if (m_ctrl->GetCellType(col, row)->GetID() == this->GetID())
			{
				CellData * cellData = GetCellData(col, row);
				if (!cellData->isOpen)
				{
					cellData->isSelected = true;
					ExpandOrContract(col, row);
				}
			}
		}
		m_ctrl->Invalidate();
	}
}

/****************************************************
MarkAllRead
	Walks through the column specified, starting at 
	the row specified, looking for all mail cells in 
	the group, in order to mark them all as read.
	This function and MarkAllUnread make this class
	tightly coupled to the mail cell type, they would
	need to be removed to use this class without that
	dependancy
Params:
	col - the column which contains the expand cells
	row - the first row from which to mark mail cells 
	      as read.
Return:
	<none>
*****************************************************/
#ifdef UGEXPANDUSEMAIL
void CUGExpandType::MarkAllRead(int col, int row)
{
	if (col >=0 && col < m_ctrl->GetNumberCols())
	{
		const int rowCount = m_ctrl->GetNumberRows();

		// Make sure we're starting from a expanding cell
		if (m_ctrl->GetCellType(col, row)->GetID() == this->GetID())
		{
			CUGCell cell;

			for(++row;row < rowCount; ++row)
			{
				// Stop when we get to the next one
				if (m_ctrl->GetCellType(col, row)->GetID() == this->GetID()) 
					break;

				m_ctrl->GetCell(col, row, &cell);

				CUGCTMail::mailItem item = CUGCTMail::ParseString(&cell);
				
				if (item.didParseOK)
					item.isRead = true;

				CUGCTMail::SetString(item, col, row, &cell, m_ctrl);
			}
		}
		m_ctrl->Invalidate();
	}

}

/****************************************************
MarkAllUnread
	Walks through the column specified, starting at 
	the row specified, looking for all mail cells in 
	the group, in order to mark them all as unread.
	This function and MarkAllRead make this class
	tightly coupled to the mail cell type, they would
	need to be removed to use this class without that
	dependancy
Params:
	col - the column which contains the expand cells
	row - the first row from which to mark mail cells 
		  as unread.
Return:
	<none>
*****************************************************/

void CUGExpandType::MarkAllUnread(int col, int row)
{
	if (col >=0 && col < m_ctrl->GetNumberCols())
	{
		const int rowCount = m_ctrl->GetNumberRows();

		// Make sure we're starting from a expanding cell
		if (m_ctrl->GetCellType(col, row)->GetID() == this->GetID())
		{
			CUGCell cell;

			for(++row;row < rowCount; ++row)
			{
				// Stop when we get to the next one
				if (m_ctrl->GetCellType(col, row)->GetID() == this->GetID()) 
					break;

				m_ctrl->GetCell(col, row, &cell);

				CUGCTMail::mailItem item = CUGCTMail::ParseString(&cell);
				
				if (item.didParseOK)
					item.isRead = false;

				CUGCTMail::SetString(item, col, row, &cell, m_ctrl);
			}
		}
		m_ctrl->Invalidate();
	}
}
#endif // defined UGEXPANDUSEMAIL

/****************************************************
ShowGroups
	Walks through all columns and rows, looking for 
	this cell type, and either hides ( by contraction)
	or shows the grouping cells.  As a result, in a grid
	that has more than one column, it will hide entire rows
	as there is no other way to hide a cell.
	We use a map to store the old row heights in order to 
	be able to restore them correctly when asked to.
Params:
	show - sets if we show or hide the cells.
Return:
	<none>
*****************************************************/
void CUGExpandType::ShowGroups(bool show)
{
	const int rowCount = m_ctrl->GetNumberRows();
	const int colCount = m_ctrl->GetNumberCols();

	for(int col=0;col<colCount;++col)
	{
		for(int row=0;row<rowCount;++row)
		{
			if (m_ctrl->GetCellType(col, row)->GetID() == this->GetID()) 
			{
				int height = m_ctrl->GetRowHeight(row);

				// If we're contracting, first store the height
				if (height) m_mapColumnHeights[row] = height;

				m_ctrl->SetRowHeight(row, (show) ? m_mapColumnHeights[row] : 0);
			}
		}
	}
}

/****************************************************
ResetCache
	When we change the sort order, we call this method 
	in order to reset all our caches, otherwise these 
	maps may contain values that are no longer valid, as
	they all store values by row number, which will have 
	changed.
Params:
	<none>
Return:
	<none>
*****************************************************/
void CUGExpandType::ResetCache()
{
	m_mapColumnHeights.clear();
}

/****************************************************
SetNumberOfRows
	Information about the state of the cell is stored 
	in the base cell class, via the ExtraMemory functionality.
	This struct includes a number of rows to expand/contract,
	which defaults to zero, but can be set with this function.
	When it is zero, the cells expand or contract to the next 
	cell of the expanding type.
Params:
	row - The row the expanding cell is on
	col - The column the expanding cell is on
	rows - The number of rows to expand or contract
Return:
	<none>
*****************************************************/
void CUGExpandType::SetNumberOfRows(int col, int row, int rows)
{
	CUGCell cell;

	// Make sure we're setting the number of rows on an expanding cell
	ASSERT(m_ctrl->GetCellType(col, row)->GetID() == this->GetID());

	CellData * ptr = GetCellData(col, row);
	
	ptr->numberOfRows = rows;
}

/****************************************************
GetCellData
	Information about the state of the cell is stored 
	in the base cell class, via the ExtraMemory functionality.
	This method encapsulates ensuring that this memory has been
	set ( or initialising it if necessary ), and casting the 
	return value to our CellData struct, which is internal to 
	this class.
Params:
	row - The row the expanding cell is on
	col - The column the expanding cell is on
Return:
	<none>
*****************************************************/
CUGExpandType::CellData* CUGExpandType::GetCellData(int col, int row)
{
	CUGCell cell;
	m_ctrl->GetCell(col, row, &cell);

	if (!cell.GetExtraMemPtr())
	{
		cell.AllocExtraMem(sizeof(CellData));
		::memset(cell.GetExtraMemPtr(), 0, sizeof(CellData));
		CellData* ptr = (CellData*)cell.GetExtraMemPtr();
		ptr->isOpen = true;
		ptr->isSelected = ptr->wasSelected = false;
		m_ctrl->SetCell(col, row, &cell);
	}

	return (CellData*)cell.GetExtraMemPtr();
}