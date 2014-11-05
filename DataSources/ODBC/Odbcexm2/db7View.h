// db7View.h : interface of the CDb7View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB7VIEW_H__B20EBE93_F00B_11D1_88D1_0080C86AC2FB__INCLUDED_)
#define AFX_DB7VIEW_H__B20EBE93_F00B_11D1_88D1_0080C86AC2FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MyCug.h"
#include "ugodbc.h"

class CDb7View : public CView
{
protected: // create from serialization only
	CDb7View();
	DECLARE_DYNCREATE(CDb7View)

// Attributes
public:

	MyCug	            m_ctrl;
	CUGODBCDatasource	m_odbc;

	CDb7Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDb7View)
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
	virtual ~CDb7View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDb7View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in db7View.cpp
inline CDb7Doc* CDb7View::GetDocument()
   { return (CDb7Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DB7VIEW_H__B20EBE93_F00B_11D1_88D1_0080C86AC2FB__INCLUDED_)
