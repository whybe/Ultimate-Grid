// Ex14Doc.cpp : implementation of the CEx14Doc class
//

#include "stdafx.h"
#include "Ex14.h"

#include "Ex14Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx14Doc

IMPLEMENT_DYNCREATE(CEx14Doc, CDocument)

BEGIN_MESSAGE_MAP(CEx14Doc, CDocument)
	//{{AFX_MSG_MAP(CEx14Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx14Doc construction/destruction

CEx14Doc::CEx14Doc()
{
	// TODO: add one-time construction code here

}

CEx14Doc::~CEx14Doc()
{
}

BOOL CEx14Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx14Doc serialization

void CEx14Doc::Serialize(CArchive& ar)
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
// CEx14Doc diagnostics

#ifdef _DEBUG
void CEx14Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx14Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx14Doc commands
