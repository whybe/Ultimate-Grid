// Calendar DemoDoc.cpp : implementation of the CCalendarDemoDoc class
//

#include "stdafx.h"
#include "Calendar Demo.h"

#include "Calendar DemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoDoc

IMPLEMENT_DYNCREATE(CCalendarDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CCalendarDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CCalendarDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoDoc construction/destruction

CCalendarDemoDoc::CCalendarDemoDoc()
{
	// TODO: add one-time construction code here

}

CCalendarDemoDoc::~CCalendarDemoDoc()
{
}

BOOL CCalendarDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoDoc serialization

void CCalendarDemoDoc::Serialize(CArchive& ar)
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
// CCalendarDemoDoc diagnostics

#ifdef _DEBUG
void CCalendarDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCalendarDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoDoc commands
