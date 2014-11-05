// OutlookStyleDoc.cpp : implementation of the COutlookStyleDoc class
//

#include "stdafx.h"
#include "OutlookStyle.h"

#include "OutlookStyleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutlookStyleDoc

IMPLEMENT_DYNCREATE(COutlookStyleDoc, CDocument)

BEGIN_MESSAGE_MAP(COutlookStyleDoc, CDocument)
	//{{AFX_MSG_MAP(COutlookStyleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutlookStyleDoc construction/destruction

COutlookStyleDoc::COutlookStyleDoc()
{
	// TODO: add one-time construction code here

}

COutlookStyleDoc::~COutlookStyleDoc()
{
}

BOOL COutlookStyleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COutlookStyleDoc serialization

void COutlookStyleDoc::Serialize(CArchive& ar)
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
// COutlookStyleDoc diagnostics

#ifdef _DEBUG
void COutlookStyleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COutlookStyleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutlookStyleDoc commands
