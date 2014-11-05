// Code3Doc.h : interface of the CCode3Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODE3DOC_H__ECDE36BF_511B_11D1_A491_0020359647BF__INCLUDED_)
#define AFX_CODE3DOC_H__ECDE36BF_511B_11D1_A491_0020359647BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CCode3Doc : public CDocument
{
protected: // create from serialization only
	CCode3Doc();
	DECLARE_DYNCREATE(CCode3Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCode3Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCode3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCode3Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CODE3DOC_H__ECDE36BF_511B_11D1_A491_0020359647BF__INCLUDED_)
