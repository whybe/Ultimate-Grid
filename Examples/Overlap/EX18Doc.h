// EX18Doc.h : interface of the CEX18Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX18DOC_H__B91C6C1D_1405_11D1_A901_0080C85A0F46__INCLUDED_)
#define AFX_EX18DOC_H__B91C6C1D_1405_11D1_A901_0080C85A0F46__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEX18Doc : public CDocument
{
protected: // create from serialization only
	CEX18Doc();
	DECLARE_DYNCREATE(CEX18Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEX18Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEX18Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEX18Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX18DOC_H__B91C6C1D_1405_11D1_A901_0080C85A0F46__INCLUDED_)
