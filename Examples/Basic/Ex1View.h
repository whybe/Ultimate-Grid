// Ex1View.h : interface of the CEx1View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX1VIEW_H__220475DF_0751_11D1_B1E8_002035964AAA__INCLUDED_)
#define AFX_EX1VIEW_H__220475DF_0751_11D1_B1E8_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx1View : public CView
{
protected: // create from serialization only
	CEx1View();
	DECLARE_DYNCREATE(CEx1View)

// Attributes
public:
	
	MyCug	m_ctrl;
	
	CEx1Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx1View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx1View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewUsexpthemes();
	afx_msg void OnUpdateViewUsexpthemes(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex1View.cpp
inline CEx1Doc* CEx1View::GetDocument()
   { return (CEx1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX1VIEW_H__220475DF_0751_11D1_B1E8_002035964AAA__INCLUDED_)
