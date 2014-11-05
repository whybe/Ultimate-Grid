// db7Doc.h : interface of the CDb7Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB7DOC_H__B20EBE91_F00B_11D1_88D1_0080C86AC2FB__INCLUDED_)
#define AFX_DB7DOC_H__B20EBE91_F00B_11D1_88D1_0080C86AC2FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CDb7Doc : public CDocument
{
protected: // create from serialization only
	CDb7Doc();
	DECLARE_DYNCREATE(CDb7Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDb7Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void SetTitle(LPCTSTR lpszTitle);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDb7Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDb7Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DB7DOC_H__B20EBE91_F00B_11D1_88D1_0080C86AC2FB__INCLUDED_)
