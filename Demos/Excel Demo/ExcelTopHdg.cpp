// ExcelTopHdg.cpp : implementation file
//

#include "stdafx.h"
#include "ExcelTopHdg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExcelTopHdg

CExcelTopHdg::CExcelTopHdg()
{
	m_isSelecting = FALSE;
	m_iLastColSelected = -1;
}

CExcelTopHdg::~CExcelTopHdg()
{
}


BEGIN_MESSAGE_MAP(CExcelTopHdg, CUGTopHdg)
	//{{AFX_MSG_MAP(CExcelTopHdg)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CExcelTopHdg message handlers
void CExcelTopHdg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// if the user decided to select cols ...
	if ( m_isSelecting == TRUE )
	{
		//find the col
		long xIndex;
		long nWidth = 0;

		for ( xIndex = 0; xIndex < m_GI->m_numberCols; xIndex++ )
		{	
			if ( xIndex == m_GI->m_numLockCols )
				xIndex = m_GI->m_leftCol;
		
			nWidth += m_ctrl->GetColWidth( xIndex );

			if( nWidth > point.x )
			{	// col found, check if the selection has also changed
				if ( m_iLastColSelected == xIndex )
					return;

				m_GI->m_multiSelect->EndBlock( xIndex, m_GI->m_numberRows - 1 );
				m_iLastColSelected = xIndex;
				m_ctrl->RedrawAll();
				return;
			}
		}
	}
	//check to see if the mouse is over a cell separation 
	//if the mouse is not currently sizing
	if(m_isSizing == FALSE && (nFlags&MK_LBUTTON) == 0 && m_GI->m_userSizingMode >0)
	{
		//check for user resize position
		CheckForUserResize(&point);		
	}
	else if(m_isSizing)
	{
		if(m_colOrRowSizing == 0){	//col sizing
			
			if(point.x < m_sizingStartPos - m_sizingStartSize)
				point.x = m_sizingStartPos - m_sizingStartSize;

			int width = m_sizingStartSize + (point.x - m_sizingStartPos);

			//send notifications to cell types
			for(int nIndex=m_ctrl->GetTopRow(); nIndex<m_ctrl->GetBottomRow(); nIndex++)
			{
				CUGCellType* pCellType=m_ctrl->GetCellType(m_sizingColRow,nIndex);
				if(pCellType!=NULL)
				{
					pCellType->OnChangingCellWidth(m_sizingColRow,nIndex,&width);
				}
			}
			//send notification to control
			m_ctrl->OnColSizing(m_sizingColRow,&width);

			//just draw a focus rect
			if(m_GI->m_userSizingMode == 1){
				m_ctrl->SetColWidth(m_sizingColRow,width);
				Update();
				
				CDC* dc = m_ctrl->m_CUGGrid->GetDC();
				dc->DrawFocusRect(&m_focusRect);
				m_focusRect.top = 0;
				m_focusRect.bottom = m_GI->m_gridHeight;
				m_focusRect.left = point.x-1;
				m_focusRect.right = point.x+1;
				dc->DrawFocusRect(&m_focusRect);
				m_ctrl->m_CUGGrid->ReleaseDC(dc);

			}
			//update on the fly
			else{
				m_ctrl->SetColWidth(m_sizingColRow,width);
				m_ctrl->RedrawAll();
			}
		}
		else
		{	//row sizing
			int height = m_sizingStartSize + (point.y - m_sizingStartPos);
			if(height <0)
				height = 0;
			m_GI->m_topHdgHeights[m_sizingColRow] = height;

			height = m_sizingStartHeight + (point.y - m_sizingStartPos);
			if(height <0)
				height = 0;

			m_ctrl->OnTopHdgSizing(&height);

			m_GI->m_topHdgHeight = height;
			m_ctrl->AdjustComponentSizes();
		}
	}
	//check for column swapping
	else if(m_GI->m_enableColSwapping && m_swapStartCol >= 0)
	{	
		MSG msg;
		
		//while column swapping enable mouse scrolling of the grid
		if(point.x < 0 || point.x > m_GI->m_gridWidth){
			
			//remove the focus rectangle
			CDC* dc = m_ctrl->m_CUGGrid->GetDC();
			dc->DrawFocusRect(&m_focusRect);
			m_focusRect.left	= -1;
			m_focusRect.right	= -1;
			m_ctrl->m_CUGGrid->ReleaseDC(dc);		

			while(1){
				if(point.x < 0){
					m_ctrl->MoveLeftCol(UG_LINEUP);
				}
				else if(point.x > m_GI->m_gridWidth){
					m_ctrl->MoveLeftCol(UG_LINEDOWN);
				}
				//check for messages, if ther are none then scroll some more
				while(PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)){
					if(msg.message == WM_MOUSEMOVE || msg.message == WM_LBUTTONUP){
						return;
					}			
					GetMessage(&msg,NULL,0,0);
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
		else
		{
			int col,row;
			RECT rect;
			point.y = 1;

			//find the column that the mouse is over
			if(GetCellFromPoint(&point,&col,&row,&rect) != UG_SUCCESS)
				return;

			//only start swapping if the mouse has moved over
			//a different column since the mouse button was pressed
			if(col != m_swapStartCol || m_swapEndCol >=0){
				
				if(( point.x - rect.left) > ((rect.right - rect.left)/2)){
					col ++;
					rect.left = rect.right;
				}

				if(col > m_GI->m_numberCols)
					col = m_GI->m_numberCols;

				//the firt time this is called redraw the top heading
				//so that the startswap cell is updated
				if(m_swapEndCol < 0){
					m_swapEndCol = col;
					Update();
				}

				//store the current col number
				m_swapEndCol = col;

				//draw a focus rect showing where the swap will
				//take place
				CDC* dc = m_ctrl->m_CUGGrid->GetDC();
				dc->DrawFocusRect(&m_focusRect);
				m_focusRect.top = 0;
				m_focusRect.bottom = m_GI->m_gridHeight;
				m_focusRect.left = rect.left;
				m_focusRect.right = rect.left+2;
				dc->DrawFocusRect(&m_focusRect);
				m_ctrl->m_CUGGrid->ReleaseDC(dc);		
			}
		}
	}
}

void CExcelTopHdg::OnLButtonDown(UINT nFlags, CPoint point) 
{	
	UNREFERENCED_PARAMETER(nFlags);

	int col;
	int row;
	RECT rect;

	if(GetFocus() != m_ctrl->m_CUGGrid)
		m_ctrl->m_CUGGrid->SetFocus();

	if(m_canSize)
	{
		m_isSizing = TRUE;
		SetCapture();
	}
	else if ( m_isSelecting == FALSE && m_GI->m_multiSelectFlag != FALSE &&
			  m_GI->m_enableColSwapping == FALSE )
	{	// if the multiselect is enabled allow the user to select the cols
		m_isSelecting = TRUE;

		SetCapture();

		//find the col
		long xIndex;
		long nWidth = 0;

		for ( xIndex = 0; xIndex < m_GI->m_numberCols; xIndex++ )
		{	
			if ( xIndex == m_GI->m_numLockCols )
				xIndex = m_GI->m_leftCol;
			
			nWidth += m_ctrl->GetColWidth( xIndex );

			if( nWidth > point.x )
			{	// col found
				if ( GetKeyState( VK_SHIFT ) < 0 )
				{
					int stCol, edCol;
					long stRow, edRow;

					m_GI->m_multiSelect->GetCurrentBlock( &stCol, &stRow, &edCol, &edRow );
					if ( stRow != 0 )
						m_GI->m_multiSelect->StartBlock( stCol, 0 );

				}
				else if ( GetKeyState( VK_CONTROL ) < 0 )
				{
					m_GI->m_currentCol = xIndex;
					m_GI->m_currentRow = 0;
					m_GI->m_multiSelect->StartBlock( xIndex, 0 );
				}
				else
				{
					m_GI->m_currentCol = xIndex;
					m_GI->m_currentRow = 0;
					m_GI->m_multiSelect->ClearAll();
					m_GI->m_multiSelect->StartBlock( xIndex, 0 );
				}
				m_GI->m_multiSelect->EndBlock( xIndex, m_GI->m_numberRows - 1 );
				m_iLastColSelected = xIndex;
				m_ctrl->RedrawAll();

				return;
			}
		}
	}
	else if(GetCellFromPoint(&point,&col,&row,&rect) == UG_SUCCESS)
	{
		//store the column where the button was pressed
		//just in case a swap is to take place
		if(m_ctrl->OnColSwapStart(col) != FALSE)
			m_swapStartCol = col;

		//send a notification to the cell type	
		BOOL processed = m_ctrl->GetCellType(col,row)->OnLClicked(col,row,1,&rect,&point);
		//send a notification to the main grid class
		m_ctrl->OnTH_LClicked(col,row,1,&rect,&point,processed);

	}
	
	//SetCapture();
}

void CExcelTopHdg::OnLButtonUp(UINT nFlags, CPoint point) 
{	
	UNREFERENCED_PARAMETER(nFlags);

	int col;
	int row;
	RECT rect;

	if ( m_isSelecting )
	{
		m_isSelecting = FALSE;
		m_iLastColSelected = -1;
		ReleaseCapture();

		//find the col
		long xIndex;
		long nWidth = 0;

		for ( xIndex = 0; xIndex < m_GI->m_numberCols; xIndex++ )
		{	
			if ( xIndex == m_GI->m_numLockCols )
				xIndex = m_GI->m_leftCol;
			
			nWidth += m_ctrl->GetColWidth( xIndex );

			if( nWidth > point.x )
			{	// col found
				m_GI->m_dragCol = xIndex;
				m_GI->m_dragRow = m_GI->m_numberRows - 1;
				return;
			}
		}
	}
	else if(m_isSizing)
	{
		if(m_colOrRowSizing == 0){	//col sizing
			//send notifications
			int width = m_ctrl->GetColWidth(m_sizingColRow);
			// if the uniform row height is enabled than only send col sized
			// notification to visible cells, else send it to all cells in column
			long startRow,
				 endRow; 

			if ( m_GI->m_uniformRowHeightFlag == TRUE )
			{
				startRow = m_ctrl->GetTopRow();
				endRow = m_ctrl->GetBottomRow();
			}
			else
			{
				startRow = 0;
				endRow = m_GI->m_numberRows;
			}

			//send notifications to individual cell types
			for ( long nIndex = startRow; nIndex < endRow; nIndex++ )
			{
				CUGCellType* pCellType=m_ctrl->GetCellType(m_sizingColRow,nIndex);
				if(pCellType!=NULL)
				{
					pCellType->OnChangedCellWidth(m_sizingColRow,nIndex,&width);
				}
			}
			m_ctrl->OnColSized(m_sizingColRow,&width);
			if(width != m_ctrl->GetColWidth(m_sizingColRow))
				m_ctrl->SetColWidth(m_sizingColRow,width);
		}
		else{
			m_ctrl->OnTopHdgSized(&m_GI->m_topHdgHeight);
		}
		m_isSizing = FALSE;

		//send notification
		m_ctrl->m_CUGGrid->InvalidateRect(NULL);
		m_ctrl->AdjustComponentSizes();
	}	

	else if(GetCellFromPoint(&point,&col,&row,&rect) == UG_SUCCESS){

		//send a notification to the cell type	
		BOOL processed = m_ctrl->GetCellType(col,row)->OnLClicked(col,row,0,&rect,&point);
		//send a notification to the main grid class
		m_ctrl->OnTH_LClicked(col,row,0,&rect,&point,processed);

	}

	//column swapping
	if(m_GI->m_enableColSwapping && m_swapStartCol >= 0){
		
		int end = m_swapEndCol;
		if(m_swapStartCol < end) // this needs to be done since the internal
			end --;				 // calc. does not take into account that the 
								 // start col will be removed and all the cols
								 // are going to slide over one position
		if(m_ctrl->OnCanColSwap(m_swapStartCol,end) != FALSE){
			m_ctrl->MoveColPosition(m_swapStartCol,m_swapEndCol,TRUE);

			//only redraw if swapping or a potential swap took place
			if(m_swapEndCol >=0){
				m_swapEndCol = -1;	
				m_ctrl->RedrawAll();
			}
			else{
				Invalidate();
			}
		}
		else{
			m_ctrl->RedrawAll();
		}
	}

	//reset variables
	m_swapStartCol		= -1;
	m_swapEndCol		= -1;	
	m_focusRect.left	= -1;
	m_focusRect.right	= -1;

	ReleaseCapture();
}
