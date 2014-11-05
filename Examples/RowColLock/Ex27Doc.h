// Ex27Doc.h : interface of the CEx27Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX27DOC_H__CF04F2AB_0EB5_11D1_B1F1_002035964AAA__INCLUDED_)
#define AFX_EX27DOC_H__CF04F2AB_0EB5_11D1_B1F1_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx27Doc : public CDocument
{
protected: // create from serialization only
	CEx27Doc();
	DECLARE_DYNCREATE(CEx27Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx27Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx27Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx27Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX27DOC_H__CF04F2AB_0EB5_11D1_B1F1_002035964AAA__INCLUDED_)
