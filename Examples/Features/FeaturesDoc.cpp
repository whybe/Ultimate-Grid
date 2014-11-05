// FeaturesDoc.cpp : implementation of the CFeaturesDoc class
//

#include "stdafx.h"
#include "Features.h"

#include "FeaturesDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFeaturesDoc

IMPLEMENT_DYNCREATE(CFeaturesDoc, CDocument)

BEGIN_MESSAGE_MAP(CFeaturesDoc, CDocument)
	//{{AFX_MSG_MAP(CFeaturesDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFeaturesDoc construction/destruction

CFeaturesDoc::CFeaturesDoc()
{
	// TODO: add one-time construction code here

}

CFeaturesDoc::~CFeaturesDoc()
{
}

BOOL CFeaturesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFeaturesDoc serialization

void CFeaturesDoc::Serialize(CArchive& ar)
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
// CFeaturesDoc diagnostics

#ifdef _DEBUG
void CFeaturesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFeaturesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFeaturesDoc commands
