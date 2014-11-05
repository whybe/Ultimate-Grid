// DAO sortingView.h : interface of the CDAOsortingView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DAOSORTINGVIEW_H__7879430F_9240_11D3_9B43_0020359647BF__INCLUDED_)
#define AFX_DAOSORTINGVIEW_H__7879430F_9240_11D3_9B43_0020359647BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyCug.h"
#include "ugdao.h"

class CDAOsortingView : public CView
{
protected: // create from serialization only
	CDAOsortingView();
	DECLARE_DYNCREATE(CDAOsortingView)

// Attributes
public:
	CDAOsortingDoc* GetDocument();

// Operations
public:

protected:
	MyCug m_grid;
	CUGDAODataSource m_data;
	int m_dataIndex;
	int m_printPage;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDAOsortingView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDAOsortingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDAOsortingView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DAO sortingView.cpp
inline CDAOsortingDoc* CDAOsortingView::GetDocument()
   { return (CDAOsortingDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DAOSORTINGVIEW_H__7879430F_9240_11D3_9B43_0020359647BF__INCLUDED_)
