// Code3Doc.cpp : implementation of the CCode3Doc class
//

#include "stdafx.h"
#include "Code3.h"

#include "Code3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCode3Doc

IMPLEMENT_DYNCREATE(CCode3Doc, CDocument)

BEGIN_MESSAGE_MAP(CCode3Doc, CDocument)
	//{{AFX_MSG_MAP(CCode3Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCode3Doc construction/destruction

CCode3Doc::CCode3Doc()
{
	// TODO: add one-time construction code here

}

CCode3Doc::~CCode3Doc()
{
}

BOOL CCode3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCode3Doc serialization

void CCode3Doc::Serialize(CArchive& ar)
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
// CCode3Doc diagnostics

#ifdef _DEBUG
void CCode3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCode3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCode3Doc commands
