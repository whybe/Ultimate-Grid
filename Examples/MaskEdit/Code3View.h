// Code3View.h : interface of the CCode3View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODE3VIEW_H__ECDE36C1_511B_11D1_A491_0020359647BF__INCLUDED_)
#define AFX_CODE3VIEW_H__ECDE36C1_511B_11D1_A491_0020359647BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CCode3View : public CView
{
protected: // create from serialization only
	CCode3View();
	DECLARE_DYNCREATE(CCode3View)

// Attributes
public:
	CCode3Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCode3View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL
	MyCug m_ctrl;
// Implementation
public:
	virtual ~CCode3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCode3View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnViewUsexpthemes();
	afx_msg void OnUpdateViewUsexpthemes(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Code3View.cpp
inline CCode3Doc* CCode3View::GetDocument()
   { return (CCode3Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CODE3VIEW_H__ECDE36C1_511B_11D1_A491_0020359647BF__INCLUDED_)
