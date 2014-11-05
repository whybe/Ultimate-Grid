// Ex7Doc.cpp : implementation of the CEx7Doc class
//

#include "stdafx.h"
#include "Ex7.h"

#include "Ex7Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx7Doc

IMPLEMENT_DYNCREATE(CEx7Doc, CDocument)

BEGIN_MESSAGE_MAP(CEx7Doc, CDocument)
	//{{AFX_MSG_MAP(CEx7Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx7Doc construction/destruction

CEx7Doc::CEx7Doc()
{
	// TODO: add one-time construction code here

}

CEx7Doc::~CEx7Doc()
{
}

BOOL CEx7Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx7Doc serialization

void CEx7Doc::Serialize(CArchive& ar)
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
// CEx7Doc diagnostics

#ifdef _DEBUG
void CEx7Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx7Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx7Doc commands
