// ChecklistDoc.cpp : implementation of the CChecklistDoc class
//

#include "stdafx.h"
#include "Checklist.h"

#include "ChecklistDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChecklistDoc

IMPLEMENT_DYNCREATE(CChecklistDoc, CDocument)

BEGIN_MESSAGE_MAP(CChecklistDoc, CDocument)
	//{{AFX_MSG_MAP(CChecklistDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChecklistDoc construction/destruction

CChecklistDoc::CChecklistDoc()
{
	// TODO: add one-time construction code here

}

CChecklistDoc::~CChecklistDoc()
{
}

BOOL CChecklistDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChecklistDoc serialization

void CChecklistDoc::Serialize(CArchive& ar)
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
// CChecklistDoc diagnostics

#ifdef _DEBUG
void CChecklistDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CChecklistDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChecklistDoc commands
