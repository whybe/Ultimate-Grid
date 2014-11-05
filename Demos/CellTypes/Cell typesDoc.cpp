// Cell typesDoc.cpp : implementation of the CCelltypesDoc class
//

#include "stdafx.h"
#include "Cell types.h"

#include "Cell typesDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCelltypesDoc

IMPLEMENT_DYNCREATE(CCelltypesDoc, CDocument)

BEGIN_MESSAGE_MAP(CCelltypesDoc, CDocument)
	//{{AFX_MSG_MAP(CCelltypesDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCelltypesDoc construction/destruction

CCelltypesDoc::CCelltypesDoc()
{
	// TODO: add one-time construction code here

}

CCelltypesDoc::~CCelltypesDoc()
{
}

BOOL CCelltypesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCelltypesDoc serialization

void CCelltypesDoc::Serialize(CArchive& ar)
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
// CCelltypesDoc diagnostics

#ifdef _DEBUG
void CCelltypesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCelltypesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCelltypesDoc commands
