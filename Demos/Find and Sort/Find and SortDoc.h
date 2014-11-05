// Find and SortDoc.h : interface of the CFindandSortDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FINDANDSORTDOC_H__E0E19B97_6406_4422_A375_D6C833FE1851__INCLUDED_)
#define AFX_FINDANDSORTDOC_H__E0E19B97_6406_4422_A375_D6C833FE1851__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFindandSortDoc : public CDocument
{
protected: // create from serialization only
	CFindandSortDoc();
	DECLARE_DYNCREATE(CFindandSortDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindandSortDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFindandSortDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFindandSortDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDANDSORTDOC_H__E0E19B97_6406_4422_A375_D6C833FE1851__INCLUDED_)
