// ChecklistGrid.h: interface for the CChecklistGrid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKLISTGRID_H__C2D71BB9_006D_11D2_88A6_0080C859A484__INCLUDED_)
#define AFX_CHECKLISTGRID_H__C2D71BB9_006D_11D2_88A6_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "UGCtrl.h"

//
//
// class CChecklistGrid
//
//
// This class wraps the CUGCtrl class to create the functionality of a 
// check list box.  Instead of adding rows (or columns) you add Items.
// Add items by using the CChecklistGrid::AddItem function.
//
//
//

class CChecklistGrid : public CUGCtrl
{
public:
	CChecklistGrid();
	virtual ~CChecklistGrid();

private:
	typedef enum tagMODIFYTYPE{ CHECK_ALL, UNCHECK_ALL, TOGGLE_CHECK } MODIFYTYPE;

	long EnumerateSelectedAnd(MODIFYTYPE modify);


protected:
	//{{AFX_VIRTUAL(CChecklistGrid)
	//}}AFX_VIRTUAL

public:
	// Item state
	virtual BOOL IsItemChecked(long lIndex);
	virtual BOOL SetItemCheck(long lIndex, BOOL bChecked);
	virtual BOOL ToggleItemCheck(long lIndex) { return SetItemCheck(lIndex, !IsItemChecked(lIndex)); }
	
	// Add/Remove items
	virtual BOOL AddItem(long lIndex, LPCTSTR pszText, BOOL bChecked, CFont* pFont = NULL, long lStyle = UGCT_CHECKBOXCHECKMARK);
	virtual BOOL RemoveItem(long lIndex, BOOL bRedrawAll = TRUE);
	
	// Get/Set Item Style
	virtual BOOL SetItemStyle(long lIndex, long lStyle);
	virtual long GetItemStyle(long lIndex);

	// Get/Set Row width
	virtual void SetWidth(int iWidth);
	virtual int GetWidth();
	virtual void AutoSetWidth(BOOL bEnable = TRUE);
	virtual BOOL GetAutoSetWidth() const { return m_bAutoSetWidth; }

protected:
	BOOL m_bAutoSetWidth;

protected:
	virtual void OnSetup();
	virtual void OnMenuCommand(int nColumn,long lRow,int nSection,int nItem);
	virtual int OnMenuStart(int nColumn,long lRow,int nSection);
	virtual int OnHint(int col,long row,int section,CString *string);


protected:
	//{{AFX_MSG(CChecklistGrid)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_CHECKLISTGRID_H__C2D71BB9_006D_11D2_88A6_0080C859A484__INCLUDED_)
