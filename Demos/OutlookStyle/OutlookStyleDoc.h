// OutlookStyleDoc.h : interface of the COutlookStyleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTLOOKSTYLEDOC_H__A83EBF29_7800_4A63_B91C_18CC58272886__INCLUDED_)
#define AFX_OUTLOOKSTYLEDOC_H__A83EBF29_7800_4A63_B91C_18CC58272886__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COutlookStyleDoc : public CDocument
{
protected: // create from serialization only
	COutlookStyleDoc();
	DECLARE_DYNCREATE(COutlookStyleDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutlookStyleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutlookStyleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COutlookStyleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTLOOKSTYLEDOC_H__A83EBF29_7800_4A63_B91C_18CC58272886__INCLUDED_)
