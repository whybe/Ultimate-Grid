// ADODataSourceView.h : interface of the CADODataSourceView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADODATASOURCEVIEW_H__0CB22F09_4A3B_4542_AF76_02DA803ED181__INCLUDED_)
#define AFX_ADODATASOURCEVIEW_H__0CB22F09_4A3B_4542_AF76_02DA803ED181__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyCug.h"

class CADODataSourceView : public CView
{
protected: // create from serialization only
	CADODataSourceView();
	DECLARE_DYNCREATE(CADODataSourceView)

// Attributes
public:
	CADODataSourceDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADODataSourceView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CADODataSourceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	MyCug m_grid;

// Generated message map functions
protected:
	//{{AFX_MSG(CADODataSourceView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ADODataSourceView.cpp
inline CADODataSourceDoc* CADODataSourceView::GetDocument()
   { return (CADODataSourceDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADODATASOURCEVIEW_H__0CB22F09_4A3B_4542_AF76_02DA803ED181__INCLUDED_)
