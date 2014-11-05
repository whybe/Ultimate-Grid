// Ex6Doc.cpp : implementation of the CEx6Doc class
//

#include "stdafx.h"
#include "Ex6.h"

#include "Ex6Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx6Doc

IMPLEMENT_DYNCREATE(CEx6Doc, CDocument)

BEGIN_MESSAGE_MAP(CEx6Doc, CDocument)
	//{{AFX_MSG_MAP(CEx6Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx6Doc construction/destruction

CEx6Doc::CEx6Doc()
{
	// TODO: add one-time construction code here

}

CEx6Doc::~CEx6Doc()
{
}

BOOL CEx6Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx6Doc serialization

void CEx6Doc::Serialize(CArchive& ar)
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
// CEx6Doc diagnostics

#ifdef _DEBUG
void CEx6Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx6Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx6Doc commands
