// Dumper3View.h : interface of the CDumper3View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUMPER3VIEW_H__B82266B3_500D_11D2_8957_0080C86AC2FB__INCLUDED_)
#define AFX_DUMPER3VIEW_H__B82266B3_500D_11D2_8957_0080C86AC2FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDumper3View : public CView
{
protected: // create from serialization only
	CDumper3View();
	DECLARE_DYNCREATE(CDumper3View)

// Attributes
public:

	MyCug	*m_ctrl;
	CRect	m_drawRect;
	BOOL	m_isPrinting;
	int		m_printPage;


	CDumper3Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDumper3View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDumper3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDumper3View)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEditFind();
	afx_msg void OnUpdateEditFind(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Dumper3View.cpp
inline CDumper3Doc* CDumper3View::GetDocument()
   { return (CDumper3Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUMPER3VIEW_H__B82266B3_500D_11D2_8957_0080C86AC2FB__INCLUDED_)
