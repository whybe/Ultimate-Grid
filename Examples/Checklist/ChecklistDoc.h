// ChecklistDoc.h : interface of the CChecklistDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKLISTDOC_H__C2D71BAF_006D_11D2_88A6_0080C859A484__INCLUDED_)
#define AFX_CHECKLISTDOC_H__C2D71BAF_006D_11D2_88A6_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CChecklistDoc : public CDocument
{
protected: // create from serialization only
	CChecklistDoc();
	DECLARE_DYNCREATE(CChecklistDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChecklistDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChecklistDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CChecklistDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKLISTDOC_H__C2D71BAF_006D_11D2_88A6_0080C859A484__INCLUDED_)
