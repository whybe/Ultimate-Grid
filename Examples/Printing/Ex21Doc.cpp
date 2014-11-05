// Ex21Doc.cpp : implementation of the CEx21Doc class
//

#include "stdafx.h"
#include "Ex21.h"

#include "Ex21Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx21Doc

IMPLEMENT_DYNCREATE(CEx21Doc, CDocument)

BEGIN_MESSAGE_MAP(CEx21Doc, CDocument)
	//{{AFX_MSG_MAP(CEx21Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx21Doc construction/destruction

CEx21Doc::CEx21Doc()
{
	// TODO: add one-time construction code here

}

CEx21Doc::~CEx21Doc()
{
}

BOOL CEx21Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx21Doc serialization

void CEx21Doc::Serialize(CArchive& ar)
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
// CEx21Doc diagnostics

#ifdef _DEBUG
void CEx21Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx21Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx21Doc commands
