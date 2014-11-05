// Find and SortDoc.cpp : implementation of the CFindandSortDoc class
//

#include "stdafx.h"
#include "Find and Sort.h"

#include "Find and SortDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindandSortDoc

IMPLEMENT_DYNCREATE(CFindandSortDoc, CDocument)

BEGIN_MESSAGE_MAP(CFindandSortDoc, CDocument)
	//{{AFX_MSG_MAP(CFindandSortDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindandSortDoc construction/destruction

CFindandSortDoc::CFindandSortDoc()
{
	// TODO: add one-time construction code here

}

CFindandSortDoc::~CFindandSortDoc()
{
}

BOOL CFindandSortDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFindandSortDoc serialization

void CFindandSortDoc::Serialize(CArchive& ar)
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
// CFindandSortDoc diagnostics

#ifdef _DEBUG
void CFindandSortDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFindandSortDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFindandSortDoc commands
