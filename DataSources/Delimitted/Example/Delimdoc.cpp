// DelimDoc.cpp : implementation of the CDelimDoc class
//

#include "stdafx.h"
#include "Delim.h"

#include "DelimDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDelimDoc

IMPLEMENT_DYNCREATE(CDelimDoc, CDocument)

BEGIN_MESSAGE_MAP(CDelimDoc, CDocument)
	//{{AFX_MSG_MAP(CDelimDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDelimDoc construction/destruction

CDelimDoc::CDelimDoc()
{
	// TODO: add one-time construction code here

}

CDelimDoc::~CDelimDoc()
{
}

BOOL CDelimDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDelimDoc serialization

void CDelimDoc::Serialize(CArchive& ar)
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
// CDelimDoc diagnostics

#ifdef _DEBUG
void CDelimDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDelimDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDelimDoc commands
