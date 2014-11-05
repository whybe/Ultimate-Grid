// Cell typesDoc.h : interface of the CCelltypesDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CELLTYPESDOC_H__4D6D872D_BFF4_4ABD_A4E2_E64C97E31C70__INCLUDED_)
#define AFX_CELLTYPESDOC_H__4D6D872D_BFF4_4ABD_A4E2_E64C97E31C70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCelltypesDoc : public CDocument
{
protected: // create from serialization only
	CCelltypesDoc();
	DECLARE_DYNCREATE(CCelltypesDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCelltypesDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCelltypesDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCelltypesDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CELLTYPESDOC_H__4D6D872D_BFF4_4ABD_A4E2_E64C97E31C70__INCLUDED_)
