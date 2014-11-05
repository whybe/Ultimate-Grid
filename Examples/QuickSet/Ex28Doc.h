// Ex28Doc.h : interface of the CEx28Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX28DOC_H__DC52CAF0_15B2_11D1_A903_0080C85A0F46__INCLUDED_)
#define AFX_EX28DOC_H__DC52CAF0_15B2_11D1_A903_0080C85A0F46__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx28Doc : public CDocument
{
protected: // create from serialization only
	CEx28Doc();
	DECLARE_DYNCREATE(CEx28Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx28Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx28Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx28Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX28DOC_H__DC52CAF0_15B2_11D1_A903_0080C85A0F46__INCLUDED_)
