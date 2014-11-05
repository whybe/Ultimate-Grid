// Ex7View.h : interface of the CEx7View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX7VIEW_H__58B8FCED_0939_11D1_B1EB_002035964AAA__INCLUDED_)
#define AFX_EX7VIEW_H__58B8FCED_0939_11D1_B1EB_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx7View : public CView
{
protected: // create from serialization only
	CEx7View();
	DECLARE_DYNCREATE(CEx7View)

// Attributes
public:

	// here is the instance of Ultimate Grid for the view
	MyCug	m_ctrl;

	CEx7Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx7View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx7View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx7View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewUsexpthemes();
	afx_msg void OnUpdateViewUsexpthemes(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex7View.cpp
inline CEx7Doc* CEx7View::GetDocument()
   { return (CEx7Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX7VIEW_H__58B8FCED_0939_11D1_B1EB_002035964AAA__INCLUDED_)
