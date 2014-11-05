// SplitterView.h : interface of the CSplitterView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLITTERVIEW_H__1D63AE1F_0461_11D2_88AF_0080C859A484__INCLUDED_)
#define AFX_SPLITTERVIEW_H__1D63AE1F_0461_11D2_88AF_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMyCUG;
class CSplitterDoc;

class CSplitterView : public CView
{
protected: // create from serialization only
	CSplitterView();
	DECLARE_DYNCREATE(CSplitterView)

// Attributes
public:
	CSplitterDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitterView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSplitterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CMyCUG* m_pGrid;

// Generated message map functions
protected:
	//{{AFX_MSG(CSplitterView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewUsexpthees();
	afx_msg void OnUpdateViewUsexpthees(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SplitterView.cpp
inline CSplitterDoc* CSplitterView::GetDocument()
   { return (CSplitterDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITTERVIEW_H__1D63AE1F_0461_11D2_88AF_0080C859A484__INCLUDED_)
