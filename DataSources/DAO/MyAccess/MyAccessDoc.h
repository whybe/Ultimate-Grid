// MyAccessDoc.h : interface of the CMyAccessDoc class
//
/////////////////////////////////////////////////////////////////////////////
#include "mysqldlg.h"


#if !defined(AFX_MYACCESSDOC_H__6E6BFE7F_5152_11D1_B265_002035964AAA__INCLUDED_)
#define AFX_MYACCESSDOC_H__6E6BFE7F_5152_11D1_B265_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CMyAccessDoc : public CDocument
{
protected: // create from serialization only
	CMyAccessDoc();
	DECLARE_DYNCREATE(CMyAccessDoc)

// Attributes
public:
	CUGDAODataSource	m_data;
	CMySQLDlg			m_sqlDlg;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyAccessDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyAccessDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyAccessDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYACCESSDOC_H__6E6BFE7F_5152_11D1_B265_002035964AAA__INCLUDED_)
