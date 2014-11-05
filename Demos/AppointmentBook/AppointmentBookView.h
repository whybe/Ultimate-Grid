// AppointmentBookView.h : interface of the CAppointmentBookView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPOINTMENTBOOKVIEW_H__DF1D1C85_F207_4B5F_A140_1770C9DA9861__INCLUDED_)
#define AFX_APPOINTMENTBOOKVIEW_H__DF1D1C85_F207_4B5F_A140_1770C9DA9861__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyCug.h"

class CAppointmentBookView : public CView
{
protected: // create from serialization only
	CAppointmentBookView();
	DECLARE_DYNCREATE(CAppointmentBookView)

// Attributes
public:
	CAppointmentBookDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppointmentBookView)
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
	virtual ~CAppointmentBookView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	MyCug m_grid;

// Generated message map functions
protected:
	//{{AFX_MSG(CAppointmentBookView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnViewUsexpthemes1();
	afx_msg void OnViewUsexpthemes2();
	afx_msg void OnViewUsexpthemesNone();
	afx_msg void OnUpdateViewUsexpthemes1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewUsexpthemes2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewUsexpthemesNone(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AppointmentBookView.cpp
inline CAppointmentBookDoc* CAppointmentBookView::GetDocument()
   { return (CAppointmentBookDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPOINTMENTBOOKVIEW_H__DF1D1C85_F207_4B5F_A140_1770C9DA9861__INCLUDED_)
