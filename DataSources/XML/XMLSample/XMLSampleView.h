// XMLSampleView.h : interface of the CXMLSampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLSAMPLEVIEW_H__EE494B63_91FC_42AD_A53A_4E3397B929EA__INCLUDED_)
#define AFX_XMLSAMPLEVIEW_H__EE494B63_91FC_42AD_A53A_4E3397B929EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyCug.h"

class CXMLSampleView : public CView
{
protected: // create from serialization only
	CXMLSampleView();
	DECLARE_DYNCREATE(CXMLSampleView)

// Attributes
public:
	CXMLSampleDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMLSampleView)
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
	virtual ~CXMLSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	MyCug m_grid;

// Generated message map functions
protected:
	//{{AFX_MSG(CXMLSampleView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileClose();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in XMLSampleView.cpp
inline CXMLSampleDoc* CXMLSampleView::GetDocument()
   { return (CXMLSampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMLSAMPLEVIEW_H__EE494B63_91FC_42AD_A53A_4E3397B929EA__INCLUDED_)
