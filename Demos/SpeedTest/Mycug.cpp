/////////////////////////////////////////////////////////////////////////////
//	Skeleton Class for a Derived MyCug

#include "stdafx.h"
#include "resource.h"
#include "MyCug.h"

#include "SetupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(MyCug,CUGCtrl)
	//{{AFX_MSG_MAP(MyCug)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Standard MyCug construction/destruction
MyCug::MyCug()
{
	UGXPThemes::UseThemes(true);
	m_head = NULL;
}

MyCug::~MyCug()
{
	UGXPThemes::CleanUp();
	// clean up ...
	if ( m_head != NULL )
	{
		UGDrwHintVList *pTemp = m_head;
		UGDrwHintVList *pDelTemp = NULL;

		while( pTemp != NULL )
		{
			pDelTemp = pTemp;
			pTemp = pTemp->next;
			delete pDelTemp;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
//	OnSetup
//		This function is called just after the grid window 
//		is created or attached to a dialog item.
//		It can be used to initially setup the grid
void MyCug::OnSetup()
{
	// customize the display
	CSetupDlg dlg;
	dlg.DoModal();
	m_nUpdateInterval = dlg.GetInterval();
	m_nRedrawDelay = dlg.GetRedrawDelay();

	// the slowest portion of this application is population of the Virtual
	// data matrix with random data
	m_data.PopulateMatrix( dlg.GetNumberCols(), dlg.GetNumberRows());

	SetDefColWidth( 60 );

	SetNumberRows( m_data.GetNumberRows());
	SetNumberCols( m_data.GetNumberCols());

	// start the timer that will update random cells
	SetTimer( UPDATE_EVENT, m_nUpdateInterval, 0 );
	// and redraw cashed cells
	SetTimer( REDRAW_EVENT, m_nRedrawDelay, 0 );
}
	
/////////////////////////////////////////////////////////////////////////////
//	OnGetCell
//		This message is sent everytime the grid needs to
//		draw a cell in the grid. At this point the cell
//		class has been filled with the information to be
//		used to draw the cell. The information can now be
//		changed before it is used for drawing
//
//	Warning:
//		This notification is called for each cell that needs to be painted
//		Placing complicated calculations here will slowdown the refresh speed.
//	Params:
//		col, row	- coordinates of cell currently drawing
//		cell		- pointer to the cell object that is being drawn
//	Return:
//		<none>
void MyCug::OnGetCell(int col,long row,CUGCell *cell)
{
	if ( col >= 0 && row == -1 )
	{	// set default values to the top heading
		cell->SetNumberDecimals( 0 );
		cell->SetNumber( col );
	}
	else if ( row >= 0 && col == -1 )
	{	// set default values to the side heading (row numbers)
		cell->SetNumberDecimals( 0 );
		cell->SetNumber( row );
	}
	else if ( col >= 0 && row >= 0 )
	{
		cell->SetNumberDecimals( 0 );
		cell->SetNumber( m_data.GetValue( col, row ));
		cell->SetAlignment( UG_ALIGNRIGHT );
	}
}

void MyCug::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	StartEdit();
}

void MyCug::OnTimer(UINT nIDEvent) 
{
	if ( nIDEvent == UPDATE_EVENT )
	{
		// update cell's content
		KillTimer( UPDATE_EVENT );

		int col = rand()%m_data.GetNumberCols();
		int row = rand()%m_data.GetNumberRows();
		int newVal = rand()%100;

		m_data.UpdateValue( col, row, newVal );
		RedrawCell_WCache( col, row );

		SetTimer( UPDATE_EVENT, m_nUpdateInterval, 0 );
	}
	else if ( nIDEvent == REDRAW_EVENT )
	{
		// redraw all cashed cells
		KillTimer( REDRAW_EVENT );
		DrawCached();
		SetTimer( REDRAW_EVENT, m_nRedrawDelay, 0 );
	}

	CUGCtrl::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////////////
//	RedrawCell_WCache
//		This version of RedrawCell will use redraw batching functionality
int MyCug::RedrawCell_WCache( int col, long row )
{
	if ( m_nRedrawDelay > 0 )
	{
		AddToCache( col, row );
	}
	else
	{	// pass the redraw message without delay for this you can use:
		// 1. PaintDrawHintsNow function, which is a better way for frequent updates
		CRect rect;
		GetCellRect(col,row,&rect);
		m_CUGGrid->m_drawHint.AddHint( col, row, col, row );

		if( GetCurrentRow() != row && GetCurrentCol() != col )
			TempDisableFocusRect();

		m_CUGGrid->PaintDrawHintsNow(&rect);

		// 2. or standard RedrawCell
		// RedrawCell( col, row );
	}

	return UG_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////
//	Cached drawing
//		Purpose of this function is to create a list of redraw requests.
//		This list will then be passed to the grid for painting.
void MyCug::AddToCache( int col, long row )
{
	// m_CUGGrid->m_drawHint.AddHint( col, row );
	// do not call AddHint directly, instead create a queue that will
	// temporarly hold coordinates of all cells marked for redraw
	// and then make calls to AddHint when ready to redraw

	UGDrwHintVList *pTemp = m_head;
	UGDrwHintVList *pNewItem = new UGDrwHintVList;

	// populate the structure
	pNewItem->Col = col;
	pNewItem->Row = row;
	pNewItem->next = NULL;

	// add new element to the list
	if ( m_head == NULL )
	{
		m_head = pNewItem;
	}
	else
	{
		while ( pTemp->next != NULL )
		{
			pTemp = pTemp->next;
		}
		pTemp->next = pNewItem;
	}
}

/////////////////////////////////////////////////////////////////////////////
//	DrawCached
//		This function will draw all cashed redraw requests in one sweep
void MyCug::DrawCached()
{
	UGDrwHintVList *pTemp = m_head;
	UGDrwHintVList *pDelTemp = NULL;

	// prevent new items from being added to the draw list
	m_head = NULL;

	// copy all of the cached draw hints, and
	// clear them as we go
	while( pTemp != NULL )
	{
		RECT rect;
		GetCellRect(pTemp->Col,pTemp->Row,&rect);
		m_CUGGrid->m_drawHint.AddHint(pTemp->Col,pTemp->Row,pTemp->Col,pTemp->Row);

		if(GetCurrentRow() != pTemp->Row || GetCurrentCol() != pTemp->Col)
			TempDisableFocusRect();

		m_CUGGrid->PaintDrawHintsNow(&rect);

		// delete cached draw hint
		pDelTemp = pTemp;
		pTemp = pTemp->next;
		delete pDelTemp;
	}
}
