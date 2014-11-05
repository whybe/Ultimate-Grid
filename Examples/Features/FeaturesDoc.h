// FeaturesDoc.h : interface of the CFeaturesDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FEATURESDOC_H__737DCA5D_B2AE_11D1_BF3F_0020359647BF__INCLUDED_)
#define AFX_FEATURESDOC_H__737DCA5D_B2AE_11D1_BF3F_0020359647BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CFeaturesDoc : public CDocument
{
protected: // create from serialization only
	CFeaturesDoc();
	DECLARE_DYNCREATE(CFeaturesDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFeaturesDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFeaturesDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFeaturesDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FEATURESDOC_H__737DCA5D_B2AE_11D1_BF3F_0020359647BF__INCLUDED_)
