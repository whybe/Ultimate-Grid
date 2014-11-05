// AppointmentBookDoc.h : interface of the CAppointmentBookDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPOINTMENTBOOKDOC_H__AEC37B24_CE5A_4D7E_B21E_45A03E5355B8__INCLUDED_)
#define AFX_APPOINTMENTBOOKDOC_H__AEC37B24_CE5A_4D7E_B21E_45A03E5355B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAppointmentBookDoc : public CDocument
{
protected: // create from serialization only
	CAppointmentBookDoc();
	DECLARE_DYNCREATE(CAppointmentBookDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppointmentBookDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAppointmentBookDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAppointmentBookDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPOINTMENTBOOKDOC_H__AEC37B24_CE5A_4D7E_B21E_45A03E5355B8__INCLUDED_)
