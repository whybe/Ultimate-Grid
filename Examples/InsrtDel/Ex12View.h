// Ex12View.h : interface of the CEx12View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX12VIEW_H__CF04F2FB_0EB5_11D1_B1F1_002035964AAA__INCLUDED_)
#define AFX_EX12VIEW_H__CF04F2FB_0EB5_11D1_B1F1_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx12View : public CView
{
protected: // create from serialization only
	CEx12View();
	DECLARE_DYNCREATE(CEx12View)

// Attributes
public:

	// here is the instance of Ultimate Grid for the view
	MyCug	m_ctrl;

	CEx12Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx12View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx12View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx12View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewUsexpthemes();
	afx_msg void OnUpdateViewUsexpthemes(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex12View.cpp
inline CEx12Doc* CEx12View::GetDocument()
   { return (CEx12Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX12VIEW_H__CF04F2FB_0EB5_11D1_B1F1_002035964AAA__INCLUDED_)
