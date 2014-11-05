// Ex28Doc.cpp : implementation of the CEx28Doc class
//

#include "stdafx.h"
#include "Ex28.h"

#include "Ex28Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx28Doc

IMPLEMENT_DYNCREATE(CEx28Doc, CDocument)

BEGIN_MESSAGE_MAP(CEx28Doc, CDocument)
	//{{AFX_MSG_MAP(CEx28Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx28Doc construction/destruction

CEx28Doc::CEx28Doc()
{
	// TODO: add one-time construction code here

}

CEx28Doc::~CEx28Doc()
{
}

BOOL CEx28Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx28Doc serialization

void CEx28Doc::Serialize(CArchive& ar)
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
// CEx28Doc diagnostics

#ifdef _DEBUG
void CEx28Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx28Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx28Doc commands
