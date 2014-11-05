// Ex21Doc.h : interface of the CEx21Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX21DOC_H__49810E90_B43D_11D1_8F89_0020359646CF__INCLUDED_)
#define AFX_EX21DOC_H__49810E90_B43D_11D1_8F89_0020359646CF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx21Doc : public CDocument
{
protected: // create from serialization only
	CEx21Doc();
	DECLARE_DYNCREATE(CEx21Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx21Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx21Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx21Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX21DOC_H__49810E90_B43D_11D1_8F89_0020359646CF__INCLUDED_)
