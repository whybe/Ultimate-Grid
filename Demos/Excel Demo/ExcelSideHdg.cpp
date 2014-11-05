// ExcelSideHdg.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include "ExcelSideHdg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExcelSideHdg

CExcelSideHdg::CExcelSideHdg()
{
	m_isSelecting = FALSE;
}

CExcelSideHdg::~CExcelSideHdg()
{
}


BEGIN_MESSAGE_MAP(CExcelSideHdg, CUGSideHdg)
	//{{AFX_MSG_MAP(CExcelSideHdg)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CExcelSideHdg message handlers

void CExcelSideHdg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// if the user decided to select rows ...
	if ( m_isSelecting == TRUE )
	{
		//find the row
		long yIndex;
		long nHeight = 0;

		// loop through all visible rows to determine which mouse cusror is above
		for ( yIndex = m_ctrl->GetTopRow(); yIndex < m_ctrl->GetBottomRow(); yIndex++ )
		{	
			if ( yIndex == m_GI->m_numLockRows )
				yIndex = m_GI->m_topRow;
			
			nHeight += m_ctrl->GetRowHeight( yIndex );

			if( nHeight > point.y )
			{	// row found
				if ( m_iLastRowSelected == yIndex )
					return;

				m_GI->m_multiSelect->EndBlock( m_GI->m_numberCols - 1, yIndex );
				m_iLastRowSelected = yIndex;
				m_ctrl->RedrawAll();
				return;
			}
		}
	}
	// check to see if the mouse is over a cell separation
	// but only if the mouse is not currently sizing 
	else if ( m_isSizing == FALSE && (nFlags&MK_LBUTTON) == 0 &&
			  m_GI->m_userSizingMode > 0 )
	{
		m_canSize = FALSE;

		//side heading column width sizing
		int width = m_GI->m_sideHdgWidth;
		for(int col = 0; col < m_GI->m_numberSideHdgCols ;col++)
		{
			if(point.x < width+3 && point.x > width-3)
			{
				if(m_ctrl->OnCanSizeSideHdg() == FALSE)
					return;

				m_canSize = TRUE;
				m_colOrRowSizing = 0;
				m_sizingColRow = col;
				m_sizingStartSize = m_GI->m_sideHdgWidths[col];
				m_sizingStartPos = point.x;
				m_sizingStartWidth = m_GI->m_sideHdgWidth;

				SetCursor(m_GI->m_WEResizseCursor);
				return;
			}
			width -= m_GI->m_sideHdgWidths[col];
		}

		//side heading row height sizing
		int height = 0;
		for(long row = 0;row < m_GI->m_numberRows;row++){
			if(row == m_GI->m_numLockRows)
				row = m_GI->m_topRow;

			height += m_ctrl->GetRowHeight(row);
			if(height > m_GI->m_gridHeight)
				break;

			if(point.y < height+3 && point.y > height-3){

				if(m_ctrl->GetRowHeight(row+1) == 0 && (row+1) < m_GI->m_numberRows)
					row++;

				if(m_ctrl->OnCanSizeRow(row) == FALSE)
					return;

				m_canSize = TRUE;
				m_colOrRowSizing = 1;
				m_sizingColRow = row;
				m_sizingStartSize = m_ctrl->GetRowHeight(row);
				m_sizingStartPos = point.y;
				if(m_GI->m_uniformRowHeightFlag){
					if( 0 != m_GI->m_defRowHeight )	// Bug fix --- Minghai Mar.17,2000
						m_sizingNumRowsDown =  point.y / m_GI->m_defRowHeight;
				}	
				SetCursor(m_GI->m_NSResizseCursor);
				return;
			}
		}

	}

	//perform the sizing
	else if(m_isSizing){
		if(m_colOrRowSizing == 0){	//col sizing
			int width = m_sizingStartSize +( point.x - m_sizingStartPos);
			if(width <0)
				width = 0;
			m_GI->m_sideHdgWidths[m_sizingColRow] = width;
			width = m_sizingStartWidth + (point.x - m_sizingStartPos);
			if(width <0)
				width = 0;

			m_ctrl->OnSideHdgSizing(&width);

			m_GI->m_sideHdgWidth = width;
			m_ctrl->AdjustComponentSizes();

		}
		else{						//row sizing
			int height;
			if(m_GI->m_uniformRowHeightFlag){		
				if(point.y <1)
					point.y = 1;
				if(m_sizingNumRowsDown>0)
					height = point.y / m_sizingNumRowsDown;
				else
					height = point.y;
			}
			else{
				height = m_sizingStartSize+(point.y - m_sizingStartPos);
			}

			if(height < 0)
				height = 0 ;

			for(int nIndex=m_ctrl->GetLeftCol(); nIndex<m_ctrl->GetRightCol(); nIndex++)
			{
				CUGCellType* pCellType=m_ctrl->GetCellType(nIndex,m_sizingColRow);
				if(pCellType!=NULL)
				{
					pCellType->OnChangingCellHeight(nIndex,m_sizingColRow,&height);
				}
			}

			m_ctrl->OnRowSizing(m_sizingColRow,&height);

			m_ctrl->SetRowHeight(m_sizingColRow,height);

			if(m_GI->m_userSizingMode == 1){ // focus rect
				Update();
				CDC* dc = m_ctrl->m_CUGGrid->GetDC();
				dc->DrawFocusRect(&m_focusRect);
				m_focusRect.top = point.y-1;
				m_focusRect.bottom = point.y+1;
				m_focusRect.left = 0;
				m_focusRect.right = m_GI->m_gridWidth;
				dc->DrawFocusRect(&m_focusRect);
				m_ctrl->m_CUGGrid->ReleaseDC(dc);

			}
			else{
				m_ctrl->RedrawAll();
			}
		}
	}
}

void CExcelSideHdg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER(nFlags);

	int col;
	long row;
	RECT rect;

	if(GetFocus() != m_ctrl->m_CUGGrid)
		m_ctrl->m_CUGGrid->SetFocus();

	if ( m_canSize )
	{
		m_isSizing = TRUE;
		SetCapture();
	}
	else if ( m_isSelecting == FALSE && m_GI->m_multiSelectFlag != FALSE )
	{	// if the multiselect is enabled allow the user to select the rows
		m_isSelecting = TRUE;
		SetCapture();

		//find the row
		long yIndex;
		long nHeight = 0;

		for ( yIndex = 0; yIndex < m_GI->m_numberRows; yIndex++ )
		{	
			if ( yIndex == m_GI->m_numLockRows )
				yIndex = m_GI->m_topRow;
			
			nHeight += m_ctrl->GetRowHeight( yIndex );

			if( nHeight > point.y )
			{	// row found
				if ( GetKeyState( VK_SHIFT ) < 0 )
				{
					int stCol, edCol;
					long stRow, edRow;

					m_GI->m_multiSelect->GetCurrentBlock( &stCol, &stRow, &edCol, &edRow );
					if ( stCol != 0 )
						m_GI->m_multiSelect->StartBlock( 0, stRow );

				}
				else if ( GetKeyState( VK_CONTROL ) < 0 )
				{
					m_GI->m_currentCol = 0;
					m_GI->m_currentRow = yIndex;
					m_GI->m_multiSelect->StartBlock( 0, yIndex );
				}
				else
				{
					m_GI->m_currentCol = 0;
					m_GI->m_currentRow = yIndex;
					m_GI->m_multiSelect->ClearAll();
					m_GI->m_multiSelect->StartBlock( 0, yIndex );
				}
				m_GI->m_multiSelect->EndBlock( m_GI->m_numberCols - 1, yIndex );
				m_iLastRowSelected = yIndex;
				m_ctrl->RedrawAll();

				return;
			}
		}
	}
	else if(GetCellFromPoint(&point,&col,&row,&rect) == UG_SUCCESS)
	{
		//send a notification to the cell type	
		BOOL processed = m_ctrl->GetCellType(col,row)->OnLClicked(col,row,1,&rect,&point);
		//send a notification to the main grid class
		m_ctrl->OnSH_LClicked(col,row,1,&rect,&point,processed);
	}
}

void CExcelSideHdg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER(nFlags);

	int col;
	long row;
	RECT rect;

	if ( m_isSelecting )
	{
		m_isSelecting = FALSE;
		m_iLastRowSelected = -1;
		ReleaseCapture();

		//find the row
		long yIndex;
		long nHeight = 0;

		for ( yIndex = 0; yIndex < m_GI->m_numberRows; yIndex++ )
		{	
			if ( yIndex == m_GI->m_numLockRows )
				yIndex = m_GI->m_topRow;
			
			nHeight += m_ctrl->GetRowHeight( yIndex );

			if( nHeight > point.y )
			{	// row found
				m_GI->m_dragCol = m_GI->m_numberCols - 1;
				m_GI->m_dragRow = yIndex;
				return;
			}
		}
	}
	else if(m_isSizing)
	{
		m_isSizing = FALSE;
		m_focusRect.top = -1;
		m_focusRect.bottom = -1;		
		ReleaseCapture();

		if(m_colOrRowSizing == 0){	//col sizing
			m_ctrl->OnSideHdgSized(&m_GI->m_sideHdgWidth);
		}
		else{
			int height = m_ctrl->GetRowHeight(m_sizingColRow);
			for(int nIndex=m_ctrl->GetLeftCol(); nIndex<m_ctrl->GetRightCol(); nIndex++)
			{
				CUGCellType* pCellType=m_ctrl->GetCellType(nIndex,m_sizingColRow);
				if(pCellType!=NULL)
				{
					pCellType->OnChangedCellHeight(nIndex,m_sizingColRow,&height);
				}
			}
			m_ctrl->OnRowSized(m_sizingColRow,&height);
			m_ctrl->SetRowHeight(m_sizingColRow,height);

		}
		m_ctrl->AdjustComponentSizes();

	}
	else if(GetCellFromPoint(&point,&col,&row,&rect) == UG_SUCCESS){

		//send a notification to the cell type	
		BOOL processed = m_ctrl->GetCellType(col,row)->OnLClicked(col,row,0,&rect,&point);
		//send a notification to the main grid class
		m_ctrl->OnSH_LClicked(col,row,0,&rect,&point,processed);
	}	
}
