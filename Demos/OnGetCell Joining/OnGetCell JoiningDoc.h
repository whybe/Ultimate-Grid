// OnGetCell JoiningDoc.h : interface of the COnGetCellJoiningDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ONGETCELLJOININGDOC_H__9B87811D_1D0C_11D3_844D_0020359647BF__INCLUDED_)
#define AFX_ONGETCELLJOININGDOC_H__9B87811D_1D0C_11D3_844D_0020359647BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COnGetCellJoiningDoc : public CDocument
{
protected: // create from serialization only
	COnGetCellJoiningDoc();
	DECLARE_DYNCREATE(COnGetCellJoiningDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnGetCellJoiningDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COnGetCellJoiningDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COnGetCellJoiningDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONGETCELLJOININGDOC_H__9B87811D_1D0C_11D3_844D_0020359647BF__INCLUDED_)
