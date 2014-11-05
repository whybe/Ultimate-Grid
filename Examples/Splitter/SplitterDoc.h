// SplitterDoc.h : interface of the CSplitterDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLITTERDOC_H__1D63AE1D_0461_11D2_88AF_0080C859A484__INCLUDED_)
#define AFX_SPLITTERDOC_H__1D63AE1D_0461_11D2_88AF_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "MyCUG.h"

class CSplitterDoc : public CDocument
{
protected: // create from serialization only
	CSplitterDoc();
	DECLARE_DYNCREATE(CSplitterDoc)

// Attributes
public:
	// m_memMan is the DataSource that is shared by all the grids
	// We could have derived another class from CUGDataSource 
	// but instead we use the CUGMem class which holds data in
	// a linked list.
	CUGMem m_memMan;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitterDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSplitterDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CSplitterDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITTERDOC_H__1D63AE1D_0461_11D2_88AF_0080C859A484__INCLUDED_)
