// ChecklistGrid.cpp: implementation of the CChecklistGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChecklistGrid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//
// Number of columns this control has
// 
#define SET_NUMBER_COLS				(1)

//
// Message IDs of popup menu commands
//
#define IDM_CHECK_ALL				(WM_USER + 600)
#define IDM_UNCHECK_ALL				(WM_USER + 601)
#define IDM_TOGGLE_CHECK			(WM_USER + 602)

//
// Popup menu text strings
//
static LPCTSTR STRING_CHECK_ALL		= _T("&Check All");
static LPCTSTR STRING_UNCHECK_ALL	= _T("&Uncheck All");
static LPCTSTR STRING_TOGGLE_CHECK	= _T("&Toggle Check");


BEGIN_MESSAGE_MAP(CChecklistGrid, CUGCtrl)
	//{{AFX_MSG_MAP(CChecklistGrid)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChecklistGrid::CChecklistGrid()
{
	m_bAutoSetWidth = FALSE;
}

CChecklistGrid::~CChecklistGrid()
{
	UGXPThemes::CleanUp();
}

void CChecklistGrid::OnSetup()
{
	//
	// virutal void OnSetup()
	//
	// overrides the base class OnSetup function which
	// performs initial setup for the control
	//
	// IN     - none
	//
	// OUT    - none
	//
	// RETURN - void
	//
	
	
	// set the number columns
	SetNumberCols(SET_NUMBER_COLS);
	SetNumberRows(1);
	QuickSetText( 0, 0, "" );

	// Remove the grid lines
	EnableExcelBorders(FALSE);

	// Remove the top and side headings
	SetSH_Width(0);
	SetTH_Height(0);

	// Always use background highlight
	SetCurrentCellMode(2);

	AutoSetWidth(TRUE);

	if (SetMultiSelectMode(TRUE) != UG_SUCCESS)
	{
		TRACE("CChecklistGrid::OnSetup() - Unable to set multi-select mode.\n");
	}

	// enable the popup menu and populate it
	EnableMenu(TRUE);

	AddMenuItem(IDM_CHECK_ALL, STRING_CHECK_ALL);
	AddMenuItem(IDM_UNCHECK_ALL, STRING_UNCHECK_ALL);
	AddMenuItem(IDM_TOGGLE_CHECK, STRING_TOGGLE_CHECK);

	CUGCell cell;
	GetColDefault(0,&cell);
	cell.SetHBackColor(RGB(120,120,120));
	SetColDefault(0,&cell);

	UseHints(TRUE);

}

BOOL CChecklistGrid::IsItemChecked(long lIndex)
{
	//
	// BOOL IsItemCheck(long lIndex)
	//
	// Call this function to determine if the item at lIndex
	// is checked or not.
	//
	// IN     - lIndex: the zero based index of the item to check
	//
	// OUT    - none
	//
	// RETURN - TRUE if the item at lIndex is checked;
	//          FALSE otherwise
	//

	CUGCell cell;

	GetCell(0, lIndex, &cell);
	return cell.GetBool();
}

BOOL CChecklistGrid::SetItemCheck(long lIndex, BOOL bChecked)
{
	//
	// BOOL SetItemCheck(long lIndex, BOOL bChecked)
	//
	// Call this function to check or uncheck a particular item.
	//
	// IN     - lIndex   : the zero based index of the item to check
	//
	//          bChecked : if TRUE the item will be checked
	//                     if FALSE the item will be unchecked.
	//
	// OUT    - none
	//
	// RETURN - TRUE if the item at lIndex is checked/unchecked;
	//          FALSE otherwise
	//

	CUGCell cell;
	if (GetCell(0, lIndex, &cell) != UG_SUCCESS)
		return FALSE;

	cell.SetBool(bChecked);
	if (SetCell(0, lIndex, &cell) != UG_SUCCESS)
		return FALSE;

	return TRUE;
}

BOOL CChecklistGrid::AddItem(long lIndex, LPCTSTR pszText, BOOL bChecked, CFont* pFont, long lStyle)
{
	//
	// BOOL AddItem(long lIndex, LPCTSTR pszText, BOOL bChecked, CFont* pFont, long lStyle)
	//
	// Call this function to add an Item into the control.
	//
	// IN     - lIndex   : the zero based index of the item
	//
	//          pszText  : the item text
	//
	//          bChecked : if TRUE the item will be checked
	//                     if FALSE the item will be unchecked.
	//
	//          pFont    : a pointer to a CFont object with the
	//                     font to draw the text with. (can be NULL)
	//
	//          lStyle   : the style of the item (see UGDEFINE.H or CChecklistGrid::SetItemStyle)
	//
	//
	// OUT    - none
	//
	// RETURN - TRUE if the item at was successfully inserted
	//          FALSE otherwise
	//

	CUGCell cell;	
	
	if (cell.SetCellType(UGCT_CHECKBOX) != UG_SUCCESS)
		return FALSE;

	if (cell.SetCellTypeEx(lStyle) != UG_SUCCESS)
		return FALSE;

	if (cell.SetLabelText(pszText) != UG_SUCCESS)
		return FALSE;

	if (cell.SetBool(bChecked) != UG_SUCCESS)
		return FALSE;

	if (pFont != NULL && cell.SetFont(pFont) != UG_SUCCESS)
		return FALSE;

	if (InsertRow(lIndex) != UG_SUCCESS)
		return FALSE;

	if (SetCell(0, lIndex, &cell) != UG_SUCCESS)
		return FALSE;

	if (RedrawCell(0, lIndex) != UG_SUCCESS)
		return FALSE;

	return TRUE;
}

BOOL CChecklistGrid::RemoveItem(long lIndex, BOOL bRedrawAll)
{
	//
	// BOOL RemoveItem(long lIndex, BOOL bRedrawAll)
	//
	// Call this function to remove an item from the control
	//
	// IN     - lIndex    : the zero based index of the item to remove
	//
	//          bRedrawAll: if TRUE the entire control will redraw
	//                      if FALSE the control won't update and it is
	//                      the responsiblity of the user to redraw
	//
	// OUT    - none
	//
	// RETURN - TRUE if the item at was successfully deleted
	//          FALSE otherwise
	//

	if (DeleteRow(lIndex) != UG_SUCCESS)
		return FALSE;

	if (bRedrawAll && RedrawAll() != UG_SUCCESS)
		return FALSE;;

	return TRUE;
}

	
BOOL CChecklistGrid::SetItemStyle(long lIndex, long lStyle)
{
	//
	// BOOL SetItemStyle(long lIndex, long lStyle)
	//
	// Call this function to set the style of a particular item
	//
	// IN     - lIndex   : the zero based index of the item
	//
	//          lStyle   : the style of the item this can be a
	//                     combination of the UGCT_* styles
	//
	//
	//			#define UGCT_CHECKBOX			2
	//			#define UGCT_CHECKBOXFLAT		0
	//			#define UGCT_CHECKBOXCROSS		0
	//			#define UGCT_CHECKBOX3DRECESS	BIT8
	//			#define UGCT_CHECKBOX3DRAISED	BIT9
	//			#define UGCT_CHECKBOXCHECKMARK	BIT12
	//
	//			#define UGCT_CHECKBOXSET		53
	//
	// OUT    - none
	//
	// RETURN - TRUE if the style at lIndex was successfully modified
	//          FALSE otherwise
	//

	CUGCell cell;

	if (GetCell(0, lIndex, &cell) != UG_SUCCESS)
		return FALSE;

	if (cell.SetCellTypeEx(lStyle) != UG_SUCCESS)
		return FALSE;

	if (SetCell(0, lIndex, &cell) != UG_SUCCESS)
		return FALSE;

	return TRUE;
}

long CChecklistGrid::GetItemStyle(long lIndex)
{
	//
	// long GetItemStyle(long lIndex)
	//
	// Call this function to Get the style of a particular item
	//
	// IN     - lIndex   : the zero based index of the item
	//
	// OUT    - none
	//
	// RETURN - the style of the item if successful
	//          otherwise -1
	//

	CUGCell cell;

	if (GetCell(0, lIndex, &cell) != UG_SUCCESS)
		return -1;

	return cell.GetCellTypeEx();
}

void CChecklistGrid::SetWidth(int iWidth)
{
	//
	// void SetWidth(int iWidth)
	//
	// Call this function to set the width of all the rows
	// in the control
	//
	// IN     - none
	//
	// OUT    - none
	//
	// RETURN - none
	//
	
	SetColWidth(0, iWidth);
}

int CChecklistGrid::GetWidth()
{
	//
	// int GetWidth()
	//
	// Call this function to get the width of the rows in
	// the control
	//
	// IN     - none
	//
	// OUT    - none
	//
	// RETURN - The width of the rows if successful
	//          -1 otherwise (NOTE: 0 is a vaild width)
	//

	int nWidth;
	if (GetColWidth(0, &nWidth) != UG_SUCCESS)
		return -1;
	
	return nWidth;
}

void CChecklistGrid::OnMenuCommand(int nColumn,long lRow,int nSection,int nItem)
{
	//
	// void OnMenuCommand(int nColumn, long lRow, int nSection, int nItem)
	//
	// OnMenuCommand is overridden here to add custom menu commands to the
	// popup menu in the grid
	//
	//

	if (nSection == UG_GRID)
	{
		ASSERT(nColumn == 0);

		switch (nItem)
		{
			case IDM_CHECK_ALL:
				EnumerateSelectedAnd(CHECK_ALL);
				break;

			case IDM_UNCHECK_ALL:
				EnumerateSelectedAnd(UNCHECK_ALL);
				break;

			case IDM_TOGGLE_CHECK:
				EnumerateSelectedAnd(TOGGLE_CHECK);
				break;

#ifdef _DEBUG		
			default:
				ASSERT(FALSE);
				TRACE("Unexpected nItem in CChecklistGrid::OnMenuCommand()\n");
				break;
#endif // _DEBUG
		}
	}
}

int CChecklistGrid::OnMenuStart(int nColumn,long lRow,int nSection)
{
	//
	// int OnMenuStart(int nColumn, long lRow, int nSection)
	//
	// Return TRUE here to allow the popup menu to show. This is an
	// override of the base class function.
	//

	return TRUE;
}

long CChecklistGrid::EnumerateSelectedAnd(MODIFYTYPE modify)
{
	//
	// long EnumerateSelectedAnd(MODIFYTYPE modify)
	//
	// This function is called in response to a menu item option of
	// either Check All, Uncheck All or Toggle Check. It will perform
	// these tasks on the selected items
	//
	// IN     - modify    : a MODIFYTYPE which tells us what change to make
	//
	// OUT    - none
	//
	// RETURN - the number of items modified
	//

	long lCount = 0;
	long lRow;
	int nColumn;
	CUGCell cell;

	if (EnumFirstSelected(&nColumn, &lRow) == UG_SUCCESS)
	{
		ASSERT(nColumn == 0);
		++lCount;
		
		if (GetCell(0, lRow, &cell) != UG_SUCCESS)
			return lCount;

		if (modify == TOGGLE_CHECK)
			cell.SetBool(!cell.GetBool());
		else
			cell.SetBool(modify == CHECK_ALL);

		if (SetCell(nColumn, lRow, &cell) != UG_SUCCESS)
			return lCount;

		RedrawCell(nColumn, lRow);
		
		while (EnumNextSelected(&nColumn, &lRow) == UG_SUCCESS)
		{
			ASSERT(nColumn == 0);
			++lCount;

			if (GetCell(0, lRow, &cell) != UG_SUCCESS)
				return lCount;

			if (modify == TOGGLE_CHECK)
				cell.SetBool(!cell.GetBool());
			else
				cell.SetBool(modify == CHECK_ALL);

			if (SetCell(nColumn, lRow, &cell) != UG_SUCCESS)
				return lCount;

			RedrawCell(nColumn, lRow);
		}
	}

	return lCount;
}

void CChecklistGrid::AutoSetWidth(BOOL bEnable)
{
	//
	// BOOL RemoveItem(long lIndex, BOOL bRedrawAll)
	//
	// Call this function to enable automatic resizing of the
	// control's column on reciept of the WM_SIZE message
	//
	// IN     - bEnable   : TRUE if automatic width setting should be
	//                      enabled. FALSE otherwise
	//
	// OUT    - none
	//
	// RETURN - none
	//

	m_bAutoSetWidth = bEnable;
}

void CChecklistGrid::OnSize(UINT nType, int cx, int cy) 
{
	//
	// void OnSize(UINT nType, int cx, int cy)
	//
	// Responds to the WM_SIZE message. If automatic width
	// setting is enable the control will resize the 0 column.
	//

	CUGCtrl::OnSize(nType, cx, cy);
	
	if (::IsWindow(GetSafeHwnd()) && m_bAutoSetWidth)
	{
		ASSERT_VALID(this);

		RECT rect;
		GetClientRect(&rect);
		VERIFY(SetColWidth(0, rect.right - 1) == UG_SUCCESS);
	}
}

int CChecklistGrid::OnHint(int col,long row,int section,CString *string) {
	CString str;
	CUGCell cell;
	if(UG_SUCCESS == GetCell(col,row,&cell)) {
		cell.GetLabelText(&str);
		*string = "This is " + str;
	}
	return 1;
}
	
