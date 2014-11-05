// Ex13Doc.cpp : implementation of the CEx13Doc class
//

#include "stdafx.h"
#include "Ex13.h"

#include "Ex13Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx13Doc

IMPLEMENT_DYNCREATE(CEx13Doc, CDocument)

BEGIN_MESSAGE_MAP(CEx13Doc, CDocument)
	//{{AFX_MSG_MAP(CEx13Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx13Doc construction/destruction

CEx13Doc::CEx13Doc()
{
	// TODO: add one-time construction code here

}

CEx13Doc::~CEx13Doc()
{
}

BOOL CEx13Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx13Doc serialization

void CEx13Doc::Serialize(CArchive& ar)
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
// CEx13Doc diagnostics

#ifdef _DEBUG
void CEx13Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx13Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx13Doc commands
