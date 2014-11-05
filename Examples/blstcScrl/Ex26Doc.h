// Ex26Doc.h : interface of the CEx26Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX26DOC_H__DC52CADD_15B2_11D1_A903_0080C85A0F46__INCLUDED_)
#define AFX_EX26DOC_H__DC52CADD_15B2_11D1_A903_0080C85A0F46__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx26Doc : public CDocument
{
protected: // create from serialization only
	CEx26Doc();
	DECLARE_DYNCREATE(CEx26Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx26Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx26Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx26Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX26DOC_H__DC52CADD_15B2_11D1_A903_0080C85A0F46__INCLUDED_)
