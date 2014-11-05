// Use UG DLLDoc.h : interface of the CUseUGDLLDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_USEUGDLLDOC_H__CEA9F556_FADA_495F_A1F8_88BCA19A8D11__INCLUDED_)
#define AFX_USEUGDLLDOC_H__CEA9F556_FADA_495F_A1F8_88BCA19A8D11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CUseUGDLLDoc : public CDocument
{
protected: // create from serialization only
	CUseUGDLLDoc();
	DECLARE_DYNCREATE(CUseUGDLLDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseUGDLLDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUseUGDLLDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CUseUGDLLDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USEUGDLLDOC_H__CEA9F556_FADA_495F_A1F8_88BCA19A8D11__INCLUDED_)
