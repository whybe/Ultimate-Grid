// Use UG LibDoc.cpp : implementation of the CUseUGLibDoc class
//

#include "stdafx.h"
#include "Use UG Lib.h"

#include "Use UG LibDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUseUGLibDoc

IMPLEMENT_DYNCREATE(CUseUGLibDoc, CDocument)

BEGIN_MESSAGE_MAP(CUseUGLibDoc, CDocument)
	//{{AFX_MSG_MAP(CUseUGLibDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUseUGLibDoc construction/destruction

CUseUGLibDoc::CUseUGLibDoc()
{
	// TODO: add one-time construction code here

}

CUseUGLibDoc::~CUseUGLibDoc()
{
}

BOOL CUseUGLibDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CUseUGLibDoc serialization

void CUseUGLibDoc::Serialize(CArchive& ar)
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
// CUseUGLibDoc diagnostics

#ifdef _DEBUG
void CUseUGLibDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUseUGLibDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUseUGLibDoc commands
