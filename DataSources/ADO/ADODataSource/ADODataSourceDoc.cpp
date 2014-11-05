// ADODataSourceDoc.cpp : implementation of the CADODataSourceDoc class
//

#include "stdafx.h"
#include "ADODataSource.h"

#include "ADODataSourceDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CADODataSourceDoc

IMPLEMENT_DYNCREATE(CADODataSourceDoc, CDocument)

BEGIN_MESSAGE_MAP(CADODataSourceDoc, CDocument)
	//{{AFX_MSG_MAP(CADODataSourceDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADODataSourceDoc construction/destruction

CADODataSourceDoc::CADODataSourceDoc()
{
	// TODO: add one-time construction code here

}

CADODataSourceDoc::~CADODataSourceDoc()
{
}

BOOL CADODataSourceDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CADODataSourceDoc serialization

void CADODataSourceDoc::Serialize(CArchive& ar)
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
// CADODataSourceDoc diagnostics

#ifdef _DEBUG
void CADODataSourceDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CADODataSourceDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CADODataSourceDoc commands
