// AppointmentBookDoc.cpp : implementation of the CAppointmentBookDoc class
//

#include "stdafx.h"
#include "AppointmentBook.h"

#include "AppointmentBookDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppointmentBookDoc

IMPLEMENT_DYNCREATE(CAppointmentBookDoc, CDocument)

BEGIN_MESSAGE_MAP(CAppointmentBookDoc, CDocument)
	//{{AFX_MSG_MAP(CAppointmentBookDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppointmentBookDoc construction/destruction

CAppointmentBookDoc::CAppointmentBookDoc()
{
	// TODO: add one-time construction code here

}

CAppointmentBookDoc::~CAppointmentBookDoc()
{
}

BOOL CAppointmentBookDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAppointmentBookDoc serialization

void CAppointmentBookDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAppointmentBookDoc diagnostics

#ifdef _DEBUG
void CAppointmentBookDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAppointmentBookDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAppointmentBookDoc commands
