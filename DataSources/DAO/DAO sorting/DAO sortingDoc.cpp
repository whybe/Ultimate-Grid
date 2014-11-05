// DAO sortingDoc.cpp : implementation of the CDAOsortingDoc class
//

#include "stdafx.h"
#include "DAO sorting.h"

#include "DAO sortingDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDAOsortingDoc

IMPLEMENT_DYNCREATE(CDAOsortingDoc, CDocument)

BEGIN_MESSAGE_MAP(CDAOsortingDoc, CDocument)
	//{{AFX_MSG_MAP(CDAOsortingDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDAOsortingDoc construction/destruction

CDAOsortingDoc::CDAOsortingDoc()
{
	// TODO: add one-time construction code here

}

CDAOsortingDoc::~CDAOsortingDoc()
{
}

BOOL CDAOsortingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDAOsortingDoc serialization

void CDAOsortingDoc::Serialize(CArchive& ar)
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
// CDAOsortingDoc diagnostics

#ifdef _DEBUG
void CDAOsortingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDAOsortingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDAOsortingDoc commands
