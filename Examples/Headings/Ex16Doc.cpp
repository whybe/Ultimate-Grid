// Ex16Doc.cpp : implementation of the CEx16Doc class
//

#include "stdafx.h"
#include "Ex16.h"

#include "Ex16Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx16Doc

IMPLEMENT_DYNCREATE(CEx16Doc, CDocument)

BEGIN_MESSAGE_MAP(CEx16Doc, CDocument)
	//{{AFX_MSG_MAP(CEx16Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx16Doc construction/destruction

CEx16Doc::CEx16Doc()
{
	// TODO: add one-time construction code here

}

CEx16Doc::~CEx16Doc()
{
}

BOOL CEx16Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx16Doc serialization

void CEx16Doc::Serialize(CArchive& ar)
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
// CEx16Doc diagnostics

#ifdef _DEBUG
void CEx16Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx16Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx16Doc commands
