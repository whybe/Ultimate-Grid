// EX25Doc.cpp : implementation of the CEX25Doc class
//

#include "stdafx.h"
#include "EX25.h"

#include "EX25Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEX25Doc

IMPLEMENT_DYNCREATE(CEX25Doc, CDocument)

BEGIN_MESSAGE_MAP(CEX25Doc, CDocument)
	//{{AFX_MSG_MAP(CEX25Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEX25Doc construction/destruction

CEX25Doc::CEX25Doc()
{
	// TODO: add one-time construction code here

}

CEX25Doc::~CEX25Doc()
{
}

BOOL CEX25Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEX25Doc serialization

void CEX25Doc::Serialize(CArchive& ar)
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
// CEX25Doc diagnostics

#ifdef _DEBUG
void CEX25Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEX25Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEX25Doc commands
