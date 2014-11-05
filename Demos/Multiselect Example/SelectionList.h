#if !defined(AFX_SELECTIONLIST_H__9E95222B_D32B_11D2_83E4_0020359647BF__INCLUDED_)
#define AFX_SELECTIONLIST_H__9E95222B_D32B_11D2_83E4_0020359647BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectionList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectionList view

class CSelectionList : public CListView
{
protected:
	CSelectionList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSelectionList)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectionList)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSelectionList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSelectionList)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTIONLIST_H__9E95222B_D32B_11D2_83E4_0020359647BF__INCLUDED_)
