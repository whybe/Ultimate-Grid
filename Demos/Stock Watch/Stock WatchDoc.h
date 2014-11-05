// Stock WatchDoc.h : interface of the CStockWatchDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STOCKWATCHDOC_H__5DF4A90A_92F9_4DCA_9627_BE0DEB0FFF32__INCLUDED_)
#define AFX_STOCKWATCHDOC_H__5DF4A90A_92F9_4DCA_9627_BE0DEB0FFF32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CStockWatchDoc : public CDocument
{
protected: // create from serialization only
	CStockWatchDoc();
	DECLARE_DYNCREATE(CStockWatchDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStockWatchDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStockWatchDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CStockWatchDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STOCKWATCHDOC_H__5DF4A90A_92F9_4DCA_9627_BE0DEB0FFF32__INCLUDED_)
