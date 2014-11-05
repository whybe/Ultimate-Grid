// Ex12Doc.cpp : implementation of the CEx12Doc class
//

#include "stdafx.h"
#include "Ex12.h"

#include "Ex12Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx12Doc

IMPLEMENT_DYNCREATE(CEx12Doc, CDocument)

BEGIN_MESSAGE_MAP(CEx12Doc, CDocument)
	//{{AFX_MSG_MAP(CEx12Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx12Doc construction/destruction

CEx12Doc::CEx12Doc()
{
	// TODO: add one-time construction code here

}

CEx12Doc::~CEx12Doc()
{
}

BOOL CEx12Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx12Doc serialization

void CEx12Doc::Serialize(CArchive& ar)
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
// CEx12Doc diagnostics

#ifdef _DEBUG
void CEx12Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx12Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx12Doc commands
