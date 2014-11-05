// Excel DemoView.h : interface of the CExcelDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCELDEMOVIEW_H__FE46C8CF_C5AA_4AF0_960B_65058F325040__INCLUDED_)
#define AFX_EXCELDEMOVIEW_H__FE46C8CF_C5AA_4AF0_960B_65058F325040__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyCug.h"

class CExcelDemoView : public CView
{
protected: // create from serialization only
	CExcelDemoView();
	DECLARE_DYNCREATE(CExcelDemoView)

// Attributes
public:
	CExcelDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExcelDemoView)
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
	virtual ~CExcelDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	MyCug m_grid;

// Generated message map functions
protected:
	//{{AFX_MSG(CExcelDemoView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnThemesNone();
	afx_msg void OnUpdateThemesNone(CCmdUI *pCmdUI);
	afx_msg void OnThemesStyle1();
	afx_msg void OnUpdateThemesStyle1(CCmdUI *pCmdUI);
	afx_msg void OnThemesStyle2();
	afx_msg void OnUpdateThemesStyle2(CCmdUI *pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileClose();
	virtual void OnInitialUpdate();
public:
	afx_msg void OnViewReset();
};

#ifndef _DEBUG  // debug version in Excel DemoView.cpp
inline CExcelDemoDoc* CExcelDemoView::GetDocument()
   { return (CExcelDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXCELDEMOVIEW_H__FE46C8CF_C5AA_4AF0_960B_65058F325040__INCLUDED_)
