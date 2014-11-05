// Ex5View.h : interface of the CEx5View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX5VIEW_H__58B8FCDA_0939_11D1_B1EB_002035964AAA__INCLUDED_)
#define AFX_EX5VIEW_H__58B8FCDA_0939_11D1_B1EB_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx5View : public CView
{
protected: // create from serialization only
	CEx5View();
	DECLARE_DYNCREATE(CEx5View)

// Attributes
public:

	// here is the instance of Ultimate Grid for the view
	MyCug	m_ctrl;

	CEx5Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx5View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx5View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx5View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewUsexpthemes();
	afx_msg void OnUpdateViewUsexpthemes(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex5View.cpp
inline CEx5Doc* CEx5View::GetDocument()
   { return (CEx5Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX5VIEW_H__58B8FCDA_0939_11D1_B1EB_002035964AAA__INCLUDED_)
