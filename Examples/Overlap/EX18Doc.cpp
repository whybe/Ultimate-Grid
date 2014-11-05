// EX18Doc.cpp : implementation of the CEX18Doc class
//

#include "stdafx.h"
#include "EX18.h"

#include "EX18Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEX18Doc

IMPLEMENT_DYNCREATE(CEX18Doc, CDocument)

BEGIN_MESSAGE_MAP(CEX18Doc, CDocument)
	//{{AFX_MSG_MAP(CEX18Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEX18Doc construction/destruction

CEX18Doc::CEX18Doc()
{
	// TODO: add one-time construction code here

}

CEX18Doc::~CEX18Doc()
{
}

BOOL CEX18Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEX18Doc serialization

void CEX18Doc::Serialize(CArchive& ar)
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
// CEX18Doc diagnostics

#ifdef _DEBUG
void CEX18Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEX18Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEX18Doc commands
