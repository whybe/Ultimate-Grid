// Ex30Doc.h : interface of the CEx30Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX30DOC_H__0D55287F_1D57_11D1_B28B_444553540000__INCLUDED_)
#define AFX_EX30DOC_H__0D55287F_1D57_11D1_B28B_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx30Doc : public CDocument
{
protected: // create from serialization only
	CEx30Doc();
	DECLARE_DYNCREATE(CEx30Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx30Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx30Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx30Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX30DOC_H__0D55287F_1D57_11D1_B28B_444553540000__INCLUDED_)
