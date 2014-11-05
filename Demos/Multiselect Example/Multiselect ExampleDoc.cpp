// Multiselect ExampleDoc.cpp : implementation of the CMultiselectExampleDoc class
//

#include "stdafx.h"
#include "Multiselect Example.h"

#include "Multiselect ExampleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiselectExampleDoc

IMPLEMENT_DYNCREATE(CMultiselectExampleDoc, CDocument)

BEGIN_MESSAGE_MAP(CMultiselectExampleDoc, CDocument)
	//{{AFX_MSG_MAP(CMultiselectExampleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiselectExampleDoc construction/destruction

CMultiselectExampleDoc::CMultiselectExampleDoc()
{
	// TODO: add one-time construction code here

}

CMultiselectExampleDoc::~CMultiselectExampleDoc()
{
}

BOOL CMultiselectExampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMultiselectExampleDoc serialization

void CMultiselectExampleDoc::Serialize(CArchive& ar)
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
// CMultiselectExampleDoc diagnostics

#ifdef _DEBUG
void CMultiselectExampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMultiselectExampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMultiselectExampleDoc commands
