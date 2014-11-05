// FeaturesView.h : interface of the CFeaturesView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FEATURESVIEW_H__737DCA5F_B2AE_11D1_BF3F_0020359647BF__INCLUDED_)
#define AFX_FEATURESVIEW_H__737DCA5F_B2AE_11D1_BF3F_0020359647BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CFeaturesView : public CView
{
protected: // create from serialization only
	CFeaturesView();
	DECLARE_DYNCREATE(CFeaturesView)

// Attributes
public:
	CFeaturesDoc* GetDocument();
	MyCug m_grid;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFeaturesView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFeaturesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFeaturesView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewUsexpthemes();
	afx_msg void OnUpdateViewUsexpthemes(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FeaturesView.cpp
inline CFeaturesDoc* CFeaturesView::GetDocument()
   { return (CFeaturesDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FEATURESVIEW_H__737DCA5F_B2AE_11D1_BF3F_0020359647BF__INCLUDED_)
