// DAO sortingDoc.h : interface of the CDAOsortingDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DAOSORTINGDOC_H__7879430D_9240_11D3_9B43_0020359647BF__INCLUDED_)
#define AFX_DAOSORTINGDOC_H__7879430D_9240_11D3_9B43_0020359647BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDAOsortingDoc : public CDocument
{
protected: // create from serialization only
	CDAOsortingDoc();
	DECLARE_DYNCREATE(CDAOsortingDoc)

// Attributes
public:
	CString m_sDBName;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDAOsortingDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDAOsortingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDAOsortingDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DAOSORTINGDOC_H__7879430D_9240_11D3_9B43_0020359647BF__INCLUDED_)
