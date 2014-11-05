// EX25Doc.h : interface of the CEX25Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX25DOC_H__391E9729_157A_11D1_A902_0080C85A0F46__INCLUDED_)
#define AFX_EX25DOC_H__391E9729_157A_11D1_A902_0080C85A0F46__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEX25Doc : public CDocument
{
protected: // create from serialization only
	CEX25Doc();
	DECLARE_DYNCREATE(CEX25Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEX25Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEX25Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEX25Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX25DOC_H__391E9729_157A_11D1_A902_0080C85A0F46__INCLUDED_)
