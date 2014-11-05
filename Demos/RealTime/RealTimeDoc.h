// RealTimeDoc.h : interface of the CRealTimeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REALTIMEDOC_H__82D2A07E_B2B7_4383_90C7_998AE427C5B0__INCLUDED_)
#define AFX_REALTIMEDOC_H__82D2A07E_B2B7_4383_90C7_998AE427C5B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRealTimeDoc : public CDocument
{
protected: // create from serialization only
	CRealTimeDoc();
	DECLARE_DYNCREATE(CRealTimeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealTimeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRealTimeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRealTimeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REALTIMEDOC_H__82D2A07E_B2B7_4383_90C7_998AE427C5B0__INCLUDED_)
