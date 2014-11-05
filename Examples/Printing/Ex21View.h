// Ex21View.h : interface of the CEx21View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX21VIEW_H__49810E92_B43D_11D1_8F89_0020359646CF__INCLUDED_)
#define AFX_EX21VIEW_H__49810E92_B43D_11D1_8F89_0020359646CF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx21View : public CView
{
protected: // create from serialization only
	CEx21View();
	DECLARE_DYNCREATE(CEx21View)

// Attributes
public:
	CEx21Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx21View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx21View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	int m_printPage;
	BOOL m_isPrinting;
	CRect m_drawRect;
	MyCug m_ctrl;
	//{{AFX_MSG(CEx21View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewUsexpthemes();
	afx_msg void OnUpdateViewUsexpthemes(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex21View.cpp
inline CEx21Doc* CEx21View::GetDocument()
   { return (CEx21Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX21VIEW_H__49810E92_B43D_11D1_8F89_0020359646CF__INCLUDED_)
