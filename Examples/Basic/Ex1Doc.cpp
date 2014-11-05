// Ex1Doc.cpp : implementation of the CEx1Doc class
//

#include "stdafx.h"
#include "Ex1.h"

#include "Ex1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx1Doc

IMPLEMENT_DYNCREATE(CEx1Doc, CDocument)

BEGIN_MESSAGE_MAP(CEx1Doc, CDocument)
	//{{AFX_MSG_MAP(CEx1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx1Doc construction/destruction

CEx1Doc::CEx1Doc()
{
	// TODO: add one-time construction code here

}

CEx1Doc::~CEx1Doc()
{
}

BOOL CEx1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx1Doc serialization

void CEx1Doc::Serialize(CArchive& ar)
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
// CEx1Doc diagnostics

#ifdef _DEBUG
void CEx1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx1Doc commands
