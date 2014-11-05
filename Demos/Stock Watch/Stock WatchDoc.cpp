// Stock WatchDoc.cpp : implementation of the CStockWatchDoc class
//

#include "stdafx.h"
#include "Stock Watch.h"

#include "Stock WatchDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStockWatchDoc

IMPLEMENT_DYNCREATE(CStockWatchDoc, CDocument)

BEGIN_MESSAGE_MAP(CStockWatchDoc, CDocument)
	//{{AFX_MSG_MAP(CStockWatchDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStockWatchDoc construction/destruction

CStockWatchDoc::CStockWatchDoc()
{
	// TODO: add one-time construction code here

}

CStockWatchDoc::~CStockWatchDoc()
{
}

BOOL CStockWatchDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CStockWatchDoc serialization

void CStockWatchDoc::Serialize(CArchive& ar)
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
// CStockWatchDoc diagnostics

#ifdef _DEBUG
void CStockWatchDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStockWatchDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStockWatchDoc commands
