// ExampleDoc.cpp : implementation of the CExampleDoc class
//

#include "stdafx.h"
#include "Example.h"

#include "ExampleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExampleDoc

IMPLEMENT_DYNCREATE(CExampleDoc, CDocument)

BEGIN_MESSAGE_MAP(CExampleDoc, CDocument)
	//{{AFX_MSG_MAP(CExampleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExampleDoc construction/destruction

CExampleDoc::CExampleDoc()
{
	// TODO: add one-time construction code here

}

CExampleDoc::~CExampleDoc()
{
}

BOOL CExampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExampleDoc serialization

void CExampleDoc::Serialize(CArchive& ar)
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
// CExampleDoc diagnostics

#ifdef _DEBUG
void CExampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExampleDoc commands
