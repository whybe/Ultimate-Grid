// XMLSampleDoc.h : interface of the CXMLSampleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLSAMPLEDOC_H__F69F88C0_E8CB_4ECF_9396_14D1A8A4F434__INCLUDED_)
#define AFX_XMLSAMPLEDOC_H__F69F88C0_E8CB_4ECF_9396_14D1A8A4F434__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CXMLSampleDoc : public CDocument
{
protected: // create from serialization only
	CXMLSampleDoc();
	DECLARE_DYNCREATE(CXMLSampleDoc)

// Attributes
public:
	CString GetOpenFilename() { return m_sOpenFilename; }
	void SetOpenFilename( CString openFile ) { m_sOpenFilename = openFile; }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMLSampleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXMLSampleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString m_sOpenFilename;

// Generated message map functions
protected:
	//{{AFX_MSG(CXMLSampleDoc)
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

#endif // !defined(AFX_XMLSAMPLEDOC_H__F69F88C0_E8CB_4ECF_9396_14D1A8A4F434__INCLUDED_)
