// ADODataSourceDoc.h : interface of the CADODataSourceDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADODATASOURCEDOC_H__DF53A47F_39F7_4163_A9D8_F1F3289D3E16__INCLUDED_)
#define AFX_ADODATASOURCEDOC_H__DF53A47F_39F7_4163_A9D8_F1F3289D3E16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CADODataSourceDoc : public CDocument
{
protected: // create from serialization only
	CADODataSourceDoc();
	DECLARE_DYNCREATE(CADODataSourceDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADODataSourceDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CADODataSourceDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CADODataSourceDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADODATASOURCEDOC_H__DF53A47F_39F7_4163_A9D8_F1F3289D3E16__INCLUDED_)
