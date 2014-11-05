// OnGetCell JoiningDoc.cpp : implementation of the COnGetCellJoiningDoc class
//

#include "stdafx.h"
#include "OnGetCell Joining.h"

#include "OnGetCell JoiningDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COnGetCellJoiningDoc

IMPLEMENT_DYNCREATE(COnGetCellJoiningDoc, CDocument)

BEGIN_MESSAGE_MAP(COnGetCellJoiningDoc, CDocument)
	//{{AFX_MSG_MAP(COnGetCellJoiningDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnGetCellJoiningDoc construction/destruction

COnGetCellJoiningDoc::COnGetCellJoiningDoc()
{
	// TODO: add one-time construction code here

}

COnGetCellJoiningDoc::~COnGetCellJoiningDoc()
{
}

BOOL COnGetCellJoiningDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COnGetCellJoiningDoc serialization

void COnGetCellJoiningDoc::Serialize(CArchive& ar)
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
// COnGetCellJoiningDoc diagnostics

#ifdef _DEBUG
void COnGetCellJoiningDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COnGetCellJoiningDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COnGetCellJoiningDoc commands
