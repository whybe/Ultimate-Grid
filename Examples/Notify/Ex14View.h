// Ex14View.h : interface of the CEx14View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX14VIEW_H__1E2EF4EF_1504_11D1_A901_0080C85A0F46__INCLUDED_)
#define AFX_EX14VIEW_H__1E2EF4EF_1504_11D1_A901_0080C85A0F46__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx14View : public CFormView
{
protected: // create from serialization only
	CEx14View();
	DECLARE_DYNCREATE(CEx14View)

	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_FORMVIEW };
	CListBox	m_output;
	//}}AFX_DATA


	// here is the instance of Ultimate Grid for the view
	MyCug	m_ctrl;

// Attributes
public:
	CEx14Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx14View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx14View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void AddNotificationMessage(LPCSTR message);
protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx14View)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewUsexpthemes();
	afx_msg void OnUpdateViewUsexpthemes(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Ex14View.cpp
inline CEx14Doc* CEx14View::GetDocument()
   { return (CEx14Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX14VIEW_H__1E2EF4EF_1504_11D1_A901_0080C85A0F46__INCLUDED_)
