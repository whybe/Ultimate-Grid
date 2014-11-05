// Ex16View.h : interface of the CEx16View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX16VIEW_H__0FFAF162_08EC_11D1_B1EB_002035964AAA__INCLUDED_)
#define AFX_EX16VIEW_H__0FFAF162_08EC_11D1_B1EB_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx16View : public CView
{
protected: // create from serialization only
	CEx16View();
	DECLARE_DYNCREATE(CEx16View)

// Attributes
public:
	
	MyCug	m_ctrl;

	CEx16Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx16View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx16View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx16View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewUsexpthemes();
	afx_msg void OnUpdateViewUsexpthemes(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex16View.cpp
inline CEx16Doc* CEx16View::GetDocument()
   { return (CEx16Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX16VIEW_H__0FFAF162_08EC_11D1_B1EB_002035964AAA__INCLUDED_)
