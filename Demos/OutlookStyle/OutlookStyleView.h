// OutlookStyleView.h : interface of the COutlookStyleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTLOOKSTYLEVIEW_H__14EC109A_019A_4613_B2CC_438D1C10EDA6__INCLUDED_)
#define AFX_OUTLOOKSTYLEVIEW_H__14EC109A_019A_4613_B2CC_438D1C10EDA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include  "OutlookStyleDoc.h"
#include "CellTypeOutlook.h"
#include "OXSkinnedView.h"

enum flagColor { clear = 0, red = 1, blue = 2, yellow = 3, green = 4, orange = 5, purple = 6, check = 7 };

#define BASEVIEW CView
class COutlookStyleView : public COXSkinnedView<BASEVIEW>
{
protected: // create from serialization only
	COutlookStyleView();
	DECLARE_DYNCREATE(COutlookStyleView)

// Attributes
public:
	COutlookStyleDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutlookStyleView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutlookStyleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void ChangeReadFlag();
	void SetFlag(flagColor f);
	void SetDefaultFlag(flagColor f);
	
protected:
	CCellTypeOutlook m_grid;
	CRichEditCtrl    m_edit;
	int				 m_gridWidth;
	CPoint			 m_oldMousePos;
	bool			 m_isMoving;
	HCURSOR			 m_moveCursor; 
	HCURSOR			 m_defaultCursor; 

	void SetControlPos();

// Generated message map functions
protected:
	//{{AFX_MSG(COutlookStyleView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRedFlag();
	afx_msg void OnBlueFlag();
	afx_msg void OnYellowFlag();
	afx_msg void OnGreenFlag();
	afx_msg void OnOrangeFlag();
	afx_msg void OnPurpleFlag();
	afx_msg void OnClearFlag();
	afx_msg void OnFlagComplete();
	afx_msg void OnDefRedFlag();
	afx_msg void OnDefBlueFlag();
	afx_msg void OnDefYellowFlag();
	afx_msg void OnDefGreenFlag();
	afx_msg void OnDefOrangeFlag();
	afx_msg void OnDefPurpleFlag();
	afx_msg void OnChangeRead();
	afx_msg void OnChangeShowGroups();
	afx_msg void OnUpdateShowgroups(CCmdUI* pCmdUI);
	afx_msg void OnSortByDate();
	afx_msg void OnUpdateSortByDate(CCmdUI* pCmdUI);
	afx_msg void OnSortByFrom();
	afx_msg void OnUpdateSortByFrom(CCmdUI* pCmdUI);
	afx_msg void OnSortBySize();
	afx_msg void OnUpdateSortBySize(CCmdUI* pCmdUI);
	afx_msg void OnSortBySubject();
	afx_msg void OnUpdateSortBySubject(CCmdUI* pCmdUI);
	afx_msg void OnSortByFlag();
	afx_msg void OnUpdateSortByFlag(CCmdUI* pCmdUI);
	afx_msg void OnSortByAttachments();
	afx_msg void OnUpdateSortByAttachments(CCmdUI* pCmdUI);
	afx_msg void OnExpandAll();
	afx_msg void OnCollapseAll();
	afx_msg void OnMarkReadAll();
	afx_msg void OnMarkUnreadAll();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OutlookStyleView.cpp
inline COutlookStyleDoc* COutlookStyleView::GetDocument()
   { return (COutlookStyleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTLOOKSTYLEVIEW_H__14EC109A_019A_4613_B2CC_438D1C10EDA6__INCLUDED_)
