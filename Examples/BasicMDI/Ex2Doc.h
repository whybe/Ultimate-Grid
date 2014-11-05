// Ex2Doc.h : interface of the CEx2Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX2DOC_H__58B8FCA4_0939_11D1_B1EB_002035964AAA__INCLUDED_)
#define AFX_EX2DOC_H__58B8FCA4_0939_11D1_B1EB_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx2Doc : public CDocument
{
protected: // create from serialization only
	CEx2Doc();
	DECLARE_DYNCREATE(CEx2Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx2Doc)
	afx_msg void OnViewUsexpthemes();
	afx_msg void OnUpdateViewUsexpthemes(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX2DOC_H__58B8FCA4_0939_11D1_B1EB_002035964AAA__INCLUDED_)
