// ExampleDoc.h : interface of the CExampleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXAMPLEDOC_H__A1619E72_291D_11D1_A911_0080C85A0F46__INCLUDED_)
#define AFX_EXAMPLEDOC_H__A1619E72_291D_11D1_A911_0080C85A0F46__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CExampleDoc : public CDocument
{
protected: // create from serialization only
	CExampleDoc();
	DECLARE_DYNCREATE(CExampleDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExampleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExampleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExampleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLEDOC_H__A1619E72_291D_11D1_A911_0080C85A0F46__INCLUDED_)
