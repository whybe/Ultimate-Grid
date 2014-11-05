/*************************************************************************
				Class Implementation : CUGCTAutoSize
**************************************************************************
	Source file : UGCTButn.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTAutoSize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***************************************************
CUGCTAutoSize - Contstructor
	Initialize member variables
****************************************************/
CUGCTAutoSize::CUGCTAutoSize()
{
}

/***************************************************
~CUGCTAutoSize - Destructor
	Clean up all allocated resources
****************************************************/
CUGCTAutoSize::~CUGCTAutoSize()
{
}

/***************************************************
OnDraw
	The Ultimate Grid calls this vistual function
	every time it is drawing a cell.  It is upto
	the individual cell type to properly draw itself.
Params:
	dc		- device context to draw the cell with
	rect	- rectangle to draw the cell in
	col		- column that is being drawn
	row		- row that is being drawn
	cell	- cell that is being drawn
	selected- TRUE if the cell is selected, otherwise FALSE
	current - TRUE if the cell is the current cell, otherwise FALSE
Return
	<none>
****************************************************/
void CUGCTAutoSize::OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current)
{
	if (!m_drawThemesSet)
		m_useThemes = cell->UseThemes();

	// before drawing of the cell check if it's content will fuly fit
	CSize size( 0, 0 );
	GetBestSize( dc, &size, cell );

	if ( size.cx > m_ctrl->GetColWidth( col ))
	{
		m_ctrl->SetColWidth( col, size.cx );
		m_ctrl->Invalidate();
	}
	else if ( size.cy > m_ctrl->GetRowHeight( row ))
	{
		m_ctrl->SetRowHeight( row, size.cy );
		m_ctrl->Invalidate();
	}
	else
		// call the default implementation
		CUGCellType::OnDraw( dc, rect, col, row, cell, selected, current );
}

/***************************************************
OnChangedCellWidth
	This notification is sent to all visible
	cells is affected column when the user has
	changed width of a column.
Params:
	col - column that the mouse is over
	row - row that the mouse is over
	width - pointer to new column width
Return:
	<none>
****************************************************/
void CUGCTAutoSize::OnChangedCellWidth(int col, long row, int* width)
{
	CClientDC dc( m_ctrl );
	CUGCell cell;
	CSize size;

	m_ctrl->GetCellIndirect( col, row, &cell );
	GetBestSize( &dc, &size, &cell );

	if ( size.cx > *width )
		*width = size.cy;
}

/***************************************************
OnChangedCellHeight
	This notification is sent to all visible
	cells is affected row when the user has
	changed height of a column.
Params:
	col - column that the mouse is over
	row - row that the mouse is over
	height - pointer to new row height
Return:
	<none>
****************************************************/
void CUGCTAutoSize::OnChangedCellHeight(int col, long row, int* height) 
{
	CClientDC dc( m_ctrl );
	CUGCell cell;
	CSize size;

	m_ctrl->GetCellIndirect( col, row, &cell );
	GetBestSize( &dc, &size, &cell );

	if ( size.cy > *height )
		*height = size.cy;
}
