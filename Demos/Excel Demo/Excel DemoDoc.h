// Excel DemoDoc.h : interface of the CExcelDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCELDEMODOC_H__7D5157B0_3ACB_46A7_99A6_43B7060BAC00__INCLUDED_)
#define AFX_EXCELDEMODOC_H__7D5157B0_3ACB_46A7_99A6_43B7060BAC00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExcelDemoDoc : public CDocument
{
protected: // create from serialization only
	CExcelDemoDoc();
	DECLARE_DYNCREATE(CExcelDemoDoc)

// Attributes
public:
	CString GetOpenFilename() { return m_sOpenFilename; }
	void SetOpenFilename( CString openFile ) { m_sOpenFilename = openFile; }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExcelDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExcelDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString m_sOpenFilename;

// Generated message map functions
protected:
	//{{AFX_MSG(CExcelDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXCELDEMODOC_H__7D5157B0_3ACB_46A7_99A6_43B7060BAC00__INCLUDED_)
