// Use UG LibDoc.h : interface of the CUseUGLibDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_USEUGLIBDOC_H__53C17BBD_A312_4F07_85C9_02CD34014A81__INCLUDED_)
#define AFX_USEUGLIBDOC_H__53C17BBD_A312_4F07_85C9_02CD34014A81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CUseUGLibDoc : public CDocument
{
protected: // create from serialization only
	CUseUGLibDoc();
	DECLARE_DYNCREATE(CUseUGLibDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseUGLibDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUseUGLibDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CUseUGLibDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USEUGLIBDOC_H__53C17BBD_A312_4F07_85C9_02CD34014A81__INCLUDED_)
