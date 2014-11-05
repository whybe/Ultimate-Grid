// ChecklistView.h : interface of the CChecklistView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKLISTVIEW_H__C2D71BB1_006D_11D2_88A6_0080C859A484__INCLUDED_)
#define AFX_CHECKLISTVIEW_H__C2D71BB1_006D_11D2_88A6_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CChecklistGrid;

class CChecklistView : public CView
{
protected: // create from serialization only
	CChecklistView();
	DECLARE_DYNCREATE(CChecklistView)

// Attributes
public:
	CChecklistDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChecklistView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChecklistView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CChecklistGrid* m_pChecklistGrid;
	CFont m_font;

// Generated message map functions
protected:
	//{{AFX_MSG(CChecklistView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewUsexpthemes();
	afx_msg void OnUpdateViewUsexpthemes(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ChecklistView.cpp
inline CChecklistDoc* CChecklistView::GetDocument()
   { return (CChecklistDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKLISTVIEW_H__C2D71BB1_006D_11D2_88A6_0080C859A484__INCLUDED_)
