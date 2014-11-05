// Ex30Doc.cpp : implementation of the CEx30Doc class
//

#include "stdafx.h"
#include "Ex30.h"

#include "Ex30Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx30Doc

IMPLEMENT_DYNCREATE(CEx30Doc, CDocument)

BEGIN_MESSAGE_MAP(CEx30Doc, CDocument)
	//{{AFX_MSG_MAP(CEx30Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx30Doc construction/destruction

CEx30Doc::CEx30Doc()
{
	// TODO: add one-time construction code here

}

CEx30Doc::~CEx30Doc()
{
}

BOOL CEx30Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx30Doc serialization

void CEx30Doc::Serialize(CArchive& ar)
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
// CEx30Doc diagnostics

#ifdef _DEBUG
void CEx30Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx30Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx30Doc commands
