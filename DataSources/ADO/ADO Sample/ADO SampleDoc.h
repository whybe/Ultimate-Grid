// ADO SampleDoc.h : interface of the CADOSampleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOSAMPLEDOC_H__5C5DE34E_D553_4332_AAE3_F5EC23CAF5A2__INCLUDED_)
#define AFX_ADOSAMPLEDOC_H__5C5DE34E_D553_4332_AAE3_F5EC23CAF5A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CADOSampleDoc : public CDocument
{
protected: // create from serialization only
	CADOSampleDoc();
	DECLARE_DYNCREATE(CADOSampleDoc)

// Attributes
public:

// Operations
public:
	CString GetConnectionString() { return m_szConnection; }
	CString GetSQLString( int nIndex = 0 );
	void SetSQLString( CString szSql, int nIndex = 0 );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADOSampleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CADOSampleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString m_szConnection;
	CStringList m_szSQL;

// Generated message map functions
protected:
	//{{AFX_MSG(CADOSampleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADOSAMPLEDOC_H__5C5DE34E_D553_4332_AAE3_F5EC23CAF5A2__INCLUDED_)
