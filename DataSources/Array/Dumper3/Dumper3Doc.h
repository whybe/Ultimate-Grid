// Dumper3Doc.h : interface of the CDumper3Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUMPER3DOC_H__B82266B1_500D_11D2_8957_0080C86AC2FB__INCLUDED_)
#define AFX_DUMPER3DOC_H__B82266B1_500D_11D2_8957_0080C86AC2FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CDumper3Doc : public CDocument
{
protected: // create from serialization only
	CDumper3Doc();
	DECLARE_DYNCREATE(CDumper3Doc)


// Attributes
public:
	CByteArray		m_byteArray;	// load file  -  datasource will read this...	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDumper3Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDumper3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDumper3Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUMPER3DOC_H__B82266B1_500D_11D2_8957_0080C86AC2FB__INCLUDED_)
