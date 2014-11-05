// Ex27Doc.cpp : implementation of the CEx27Doc class
//

#include "stdafx.h"
#include "Ex27.h"

#include "Ex27Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx27Doc

IMPLEMENT_DYNCREATE(CEx27Doc, CDocument)

BEGIN_MESSAGE_MAP(CEx27Doc, CDocument)
	//{{AFX_MSG_MAP(CEx27Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx27Doc construction/destruction

CEx27Doc::CEx27Doc()
{
	// TODO: add one-time construction code here

}

CEx27Doc::~CEx27Doc()
{
}

BOOL CEx27Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx27Doc serialization

void CEx27Doc::Serialize(CArchive& ar)
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
// CEx27Doc diagnostics

#ifdef _DEBUG
void CEx27Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx27Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx27Doc commands
