// ADO SampleView.h : interface of the CADOSampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOSAMPLEVIEW_H__C1C8BD97_60B6_4E32_9E52_9F53FEBBE984__INCLUDED_)
#define AFX_ADOSAMPLEVIEW_H__C1C8BD97_60B6_4E32_9E52_9F53FEBBE984__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyCug.h"
// include ADO datasource
#include "ADOImpDatasource.h"

class CADOSampleView : public CView
{
protected: // create from serialization only
	CADOSampleView();
	DECLARE_DYNCREATE(CADOSampleView)

// Attributes
public:
	CADOSampleDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADOSampleView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CADOSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	MyCug m_grid;

	struct _tagDSList
	{
		CADOImpDatasource *m_dsADO;
		_tagDSList *next;

		_tagDSList()
		{
			m_dsADO = NULL;
			next = NULL;
		}
	} *m_pDSList;

// Generated message map functions
protected:
	//{{AFX_MSG(CADOSampleView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRefreshData();
	afx_msg void OnShowSql();
	afx_msg void OnAppendRow();
	afx_msg void OnDeleteRecord();
	afx_msg void OnAddTable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ADO SampleView.cpp
inline CADOSampleDoc* CADOSampleView::GetDocument()
   { return (CADOSampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADOSAMPLEVIEW_H__C1C8BD97_60B6_4E32_9E52_9F53FEBBE984__INCLUDED_)
