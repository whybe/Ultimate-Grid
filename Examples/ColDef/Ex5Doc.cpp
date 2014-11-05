// Ex5Doc.cpp : implementation of the CEx5Doc class
//

#include "stdafx.h"
#include "Ex5.h"

#include "Ex5Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx5Doc

IMPLEMENT_DYNCREATE(CEx5Doc, CDocument)

BEGIN_MESSAGE_MAP(CEx5Doc, CDocument)
	//{{AFX_MSG_MAP(CEx5Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx5Doc construction/destruction

CEx5Doc::CEx5Doc()
{
	// TODO: add one-time construction code here

}

CEx5Doc::~CEx5Doc()
{
}

BOOL CEx5Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx5Doc serialization

void CEx5Doc::Serialize(CArchive& ar)
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
// CEx5Doc diagnostics

#ifdef _DEBUG
void CEx5Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx5Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx5Doc commands
