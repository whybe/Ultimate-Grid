// ExampleView.h : interface of the CExampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXAMPLEVIEW_H__A1619E74_291D_11D1_A911_0080C85A0F46__INCLUDED_)
#define AFX_EXAMPLEVIEW_H__A1619E74_291D_11D1_A911_0080C85A0F46__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// include the header file for the Ultimate Grid derived class
#include "MyCug.h"

class CExampleView : public CView
{
protected: // create from serialization only
	// here is the instance of Ultimate Grid for the view
	MyCug	m_ctrl;

	CExampleView();
	DECLARE_DYNCREATE(CExampleView)

// Attributes
public:
	CExampleDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExampleView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExampleView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ExampleView.cpp
inline CExampleDoc* CExampleView::GetDocument()
   { return (CExampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLEVIEW_H__A1619E74_291D_11D1_A911_0080C85A0F46__INCLUDED_)
