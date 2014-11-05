// XP Theme DemoDoc.h : interface of the CXPThemeDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XPTHEMEDEMODOC_H__262F5919_2059_4218_8E40_DDCBF7BCFF85__INCLUDED_)
#define AFX_XPTHEMEDEMODOC_H__262F5919_2059_4218_8E40_DDCBF7BCFF85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CXPThemeDemoDoc : public CDocument
{
protected: // create from serialization only
	CXPThemeDemoDoc();
	DECLARE_DYNCREATE(CXPThemeDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXPThemeDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXPThemeDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXPThemeDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XPTHEMEDEMODOC_H__262F5919_2059_4218_8E40_DDCBF7BCFF85__INCLUDED_)
