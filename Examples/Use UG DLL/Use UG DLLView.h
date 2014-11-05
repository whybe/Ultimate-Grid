// Use UG DLLView.h : interface of the CUseUGDLLView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_USEUGDLLVIEW_H__2D788E67_E655_4DC5_BDCE_8C766ECF9F9E__INCLUDED_)
#define AFX_USEUGDLLVIEW_H__2D788E67_E655_4DC5_BDCE_8C766ECF9F9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyCug.h"
class CUseUGDLLView : public CView
{
protected: // create from serialization only
	CUseUGDLLView();
	DECLARE_DYNCREATE(CUseUGDLLView)

// Attributes
public:
	CUseUGDLLDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseUGDLLView)
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
	virtual ~CUseUGDLLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	MyCug m_grid;

// Generated message map functions
protected:
	//{{AFX_MSG(CUseUGDLLView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Use UG DLLView.cpp
inline CUseUGDLLDoc* CUseUGDLLView::GetDocument()
   { return (CUseUGDLLDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USEUGDLLVIEW_H__2D788E67_E655_4DC5_BDCE_8C766ECF9F9E__INCLUDED_)
