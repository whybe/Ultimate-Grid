// Cell PropertiesView.h : interface of the CCellPropertiesView class
//


#pragma once
#include "MyCug.h"

class CCellPropertiesView : public CView
{
protected: // create from serialization only
	CCellPropertiesView();
	DECLARE_DYNCREATE(CCellPropertiesView)

// Attributes
public:
	CCellPropertiesDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCellPropertiesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	MyCug m_grid;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnViewUsexpthemes();
	afx_msg void OnUpdateViewUsexpthemes(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // debug version in Cell PropertiesView.cpp
inline CCellPropertiesDoc* CCellPropertiesView::GetDocument() const
   { return reinterpret_cast<CCellPropertiesDoc*>(m_pDocument); }
#endif

