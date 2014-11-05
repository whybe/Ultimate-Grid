// Ex26Doc.cpp : implementation of the CEx26Doc class
//

#include "stdafx.h"
#include "Ex26.h"

#include "Ex26Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx26Doc

IMPLEMENT_DYNCREATE(CEx26Doc, CDocument)

BEGIN_MESSAGE_MAP(CEx26Doc, CDocument)
	//{{AFX_MSG_MAP(CEx26Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx26Doc construction/destruction

CEx26Doc::CEx26Doc()
{
	// TODO: add one-time construction code here

}

CEx26Doc::~CEx26Doc()
{
}

BOOL CEx26Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx26Doc serialization

void CEx26Doc::Serialize(CArchive& ar)
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
// CEx26Doc diagnostics

#ifdef _DEBUG
void CEx26Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx26Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx26Doc commands
