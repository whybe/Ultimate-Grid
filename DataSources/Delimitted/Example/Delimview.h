// ComView.h : interface of the CDelimView class
//
/////////////////////////////////////////////////////////////////////////////

class CDelimView : public CView
{
protected: // create from serialization only
	CDelimView();
	DECLARE_DYNCREATE(CDelimView)

// Attributes
public:
	CDelimDoc* GetDocument();

	MyCug		m_grid;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDelimView)
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
	virtual ~CDelimView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDelimView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ComView.cpp
inline CDelimDoc* CDelimView::GetDocument()
   { return (CDelimDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
