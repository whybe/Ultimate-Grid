// ContextSensitiveGridDoc.cpp : implementation of the CContextSensitiveGridDoc class
//

#include "stdafx.h"
#include "ContextSensitiveGrid.h"

#include "ContextSensitiveGridDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContextSensitiveGridDoc

IMPLEMENT_DYNCREATE(CContextSensitiveGridDoc, CDocument)

BEGIN_MESSAGE_MAP(CContextSensitiveGridDoc, CDocument)
	//{{AFX_MSG_MAP(CContextSensitiveGridDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContextSensitiveGridDoc construction/destruction

CContextSensitiveGridDoc::CContextSensitiveGridDoc()
{
	// TODO: add one-time construction code here

}

CContextSensitiveGridDoc::~CContextSensitiveGridDoc()
{
}

BOOL CContextSensitiveGridDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CContextSensitiveGridDoc serialization

void CContextSensitiveGridDoc::Serialize(CArchive& ar)
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
// CContextSensitiveGridDoc diagnostics

#ifdef _DEBUG
void CContextSensitiveGridDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CContextSensitiveGridDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CContextSensitiveGridDoc commands
