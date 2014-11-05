// Ex12Doc.h : interface of the CEx12Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX12DOC_H__CF04F2F9_0EB5_11D1_B1F1_002035964AAA__INCLUDED_)
#define AFX_EX12DOC_H__CF04F2F9_0EB5_11D1_B1F1_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx12Doc : public CDocument
{
protected: // create from serialization only
	CEx12Doc();
	DECLARE_DYNCREATE(CEx12Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx12Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx12Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx12Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX12DOC_H__CF04F2F9_0EB5_11D1_B1F1_002035964AAA__INCLUDED_)
