// BindingToArrayDoc.cpp : implementation of the CBindingToArrayDoc class
//

#include "stdafx.h"
#include "BindingToArray.h"

#include "BindingToArrayDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBindingToArrayDoc

IMPLEMENT_DYNCREATE(CBindingToArrayDoc, CDocument)

BEGIN_MESSAGE_MAP(CBindingToArrayDoc, CDocument)
	//{{AFX_MSG_MAP(CBindingToArrayDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBindingToArrayDoc construction/destruction

CBindingToArrayDoc::CBindingToArrayDoc()
{
	// TODO: add one-time construction code here

}

CBindingToArrayDoc::~CBindingToArrayDoc()
{
}

BOOL CBindingToArrayDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBindingToArrayDoc serialization

void CBindingToArrayDoc::Serialize(CArchive& ar)
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
// CBindingToArrayDoc diagnostics

#ifdef _DEBUG
void CBindingToArrayDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBindingToArrayDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBindingToArrayDoc commands
