// MyAccessView.h : interface of the CMyAccessView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYACCESSVIEW_H__6E6BFE81_5152_11D1_B265_002035964AAA__INCLUDED_)
#define AFX_MYACCESSVIEW_H__6E6BFE81_5152_11D1_B265_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMyAccessView : public CView
{
protected: // create from serialization only
	CMyAccessView();
	DECLARE_DYNCREATE(CMyAccessView)

// Attributes
public:

	CRect			m_drawRect;
	BOOL			m_isPrinting;
	int				m_printPage;

	CUGAccessCtrl	m_ctrl;
	CMyAccessDoc*	GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyAccessView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyAccessView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyAccessView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyAccessView.cpp
inline CMyAccessDoc* CMyAccessView::GetDocument()
   { return (CMyAccessDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYACCESSVIEW_H__6E6BFE81_5152_11D1_B265_002035964AAA__INCLUDED_)
