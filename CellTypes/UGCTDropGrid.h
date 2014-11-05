/*************************************************************************
				Class Declaration : CUGCTDropGrid, CDropDownCug
**************************************************************************
	Source file : UGCTDropGrid.cpp
	Header file : UGCTDropGrid.h
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Purpose:
		The CUGCTDropGrid celltype was created to provide users with ability
		to show a popup window containing a grid, just like a drop list.
		By default an instance of the CDropDownCug will be created and used
		as the grid control within the popup window, but it can be replaced
		with any CDropDownCug derived class through the OnCellTypeNotify
		notification.

		We require for the grid control (that will be shown within the popup)
		to be derived from the CDropDownCug because it contains number of
		member variables which are set (pointer to parent CUGCtrl, pointer
		to the celltype, etc).
	
	Helper structures:
		CreateDropDownGrid structure stores information about the drop down grid
			window.  A pointer to this structure is passed in to the
			CUGCtrl::OnCellTypeNotify notification allowing for adjustments
			to what will be displayed.  You can change the size and postion,
			the control class (ie. MyCug), as well as setup of the grid object.

		SelectedGridItem structure stores information about user selection within
			the 'DropDown' grid, a pointer to this structure is passed to the
			CUGCtrl::OnCellTypeNotify notification allowing the developer to
			make final adjustments to the 'selectedCell' object.  The content
			of this object will be set to the cell that initiated the drop down.
			A pointer to the CUGCtrl derived class is also included just in
			case more information about the selection is required.

	Extended celltype styles:
		UGCT_SHOWASPOPUPWND	- extended celltype style which toggles showing of the
							  'popup grid' windows as a popup or child window.
							  The m_popupWnd is always created with WS_POPUP style set,
							  but if this flag is not set then the ShowPopupGridWnd
							  will adjust the size and position of the popup to always
							  fit the client area.

	Notifications sent to the OnCellTypeNotify:
		UGCT_SHOWDROPGRID	- called when the user clicked on the dropdown button
							  and the popup window is about to be displayed.
							  In this notification a pointer to the CreateDropDownGrid
							  structure is passed in as the 'param', this structure
							  shoud be used to customize the grid that will be displayed.
		UGCT_CLOSEDROPGRID	- called when user decided to close the 'DropDown' window
							  that contains the grid, it should be used to clean up
							  all additional memory allocated for the grid.
		UGCT_SELECTEDITEM	- called when user makes a selection in the 'DropDown' grid
							  object.  This notificaton provides a pointer to the
							  SelectedGridItem structure which allow to make final
							  adjustments to the string that will be displayed.
*************************************************************************/
#ifndef _UGCTDropGrid_H_
#define _UGCTDropGrid_H_

class CDropDownCug;

// Dropdown grid extended styles
#define UGCT_SHOWASPOPUPWND	BIT1
// Dropdown grid OnCellTypeNotify notifications
#define UGCT_SHOWDROPGRID	100
#define UGCT_CLOSEDROPGRID	101
#define UGCT_SELECTEDITEM	102

// Dropdown grid stuctures
// CreateDropDownGrid structure is used when the drop down was just
// started, but before anywindow was made visible.  This structure
// contains all of the information required for the popup window to
// display properly (the position, size, grid object, and the window)
// All of these objects can be modified through the OnCellTypeNotify
struct UG_CLASS_DECL CreateDropDownGrid
{
	CRect popUpWndRect;
	CDropDownCug *pGridCtrl;
	CWnd *pPopupWnd;
};

// SelectedGridItem structure is used to store all relative information
// about the selection that the user made.  Default implementation of the
// OnSelectedGridItem function will create an instance of this structure
// if it was not provided.
struct UG_CLASS_DECL SelectedGridItem
{
	int selectedCol;
	long selectedRow;
	CUGCell *selectedCell;
	CDropDownCug *pGridCtrl;
};

// Dafault CUGCtrl class that will be displayed in the dropdown.
class UG_CLASS_DECL CUGCTDropGrid: public CUGCellType
{
protected:
	// member variaobles that define drop button attributes
	int		m_btnWidth;
	int		m_btnDown;
	CRect	m_btnRect;
	// Location of the cell that started the drop down
	int		m_btnCol;
	long	m_btnRow;
	// Dropdown button colors
	CPen	m_pen;
	CBrush	m_brush;

	CreateDropDownGrid* m_pDropGridStruct;
	CDropDownCug* m_pGridCtrl;
	CWnd m_popupWnd;
	// Protected function responsible for showing the dropdown grid
	int ShowPopupGridWnd();

public:
	CUGCTDropGrid();
	~CUGCTDropGrid();
	// member function that handles user selection
	virtual int OnSelectedGridItem( SelectedGridItem *pSelectedInfo = NULL );
	virtual void OnClosePopup();

public:
	// Overrides
	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();

	virtual int GetEditArea(RECT *rect);
	virtual void GetBestSize(CDC *dc,CSize *size,CUGCell *cell);
	virtual BOOL OnLClicked(int col,long row,int updn,RECT *rect,POINT *point);
	virtual BOOL OnKeyDown(int col,long row,UINT *vcKey);
	virtual BOOL OnCharDown(int col,long row,UINT *vcKey);
	virtual BOOL OnMouseMove(int col,long row,POINT *point,UINT flags);
	virtual void OnKillFocus(int col,long row,CUGCell *cell);
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current);
};

/*************************************************************************
				Class Declaration : CDropDownCug
**************************************************************************
	Source file : UGCTDropGrid.cpp
	Header file : UGCTDropGrid.h
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Purpose:
		The CDropDownCug is the default CUGCtrl control that will be displayed
		in the dropdown.  This class contains code for the standard behavior
		(select, close wnd), and all other grid controls that will be used
		in the dropdown window should be derived from this class.

		The CUGCTDropGrid provides two functions that should be used when the
		user makes a selection or decides to close the popup window:

		OnSelectedGridItem	- the user made a selection and it should be
							  saved to the cell that started the dropdown.
							  This function takes a pointer to the SelectedGridItem
							  structure, but if it is not provided than
							  a new object will be created and populated
							  with standard information.

		OnClosePopup		- use this function to close the popup window,
							  it will reset the focus and the state of the
							  drop button.

		When the selection is made the code should look like following:

		if ( m_cellType != NULL )
		{
			// call the default implementation for the selection
			((CUGCTDropGrid*)m_cellType)->OnSelectedGridItem();
			// close the popup window
			((CUGCTDropGrid*)m_cellType)->OnClosePopup();
		}
*************************************************************************/
class UG_CLASS_DECL CDropDownCug :public CUGCtrl
{
public:
	CDropDownCug();
	~CDropDownCug();

	// member variables that deal with the parent grid control
	CUGCtrl *m_parentCtrl;
	CUGCellType *m_cellType;

public:
	// Overrides
	// for the CUGCtrl virtual functions/notifications
	virtual void OnKillFocus(int section);
	virtual void OnKeyDown(UINT *vcKey,BOOL processed);
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
};

#endif // _UGCTDropGrid_H_