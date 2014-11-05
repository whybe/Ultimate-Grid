// Multiselect ExampleDoc.h : interface of the CMultiselectExampleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTISELECTEXAMPLEDOC_H__9E95221B_D32B_11D2_83E4_0020359647BF__INCLUDED_)
#define AFX_MULTISELECTEXAMPLEDOC_H__9E95221B_D32B_11D2_83E4_0020359647BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMultiselectExampleDoc : public CDocument
{
protected: // create from serialization only
	CMultiselectExampleDoc();
	DECLARE_DYNCREATE(CMultiselectExampleDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiselectExampleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMultiselectExampleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMultiselectExampleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTISELECTEXAMPLEDOC_H__9E95221B_D32B_11D2_83E4_0020359647BF__INCLUDED_)
