// RealTimeDoc.cpp : implementation of the CRealTimeDoc class
//

#include "stdafx.h"
#include "RealTime.h"

#include "RealTimeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRealTimeDoc

IMPLEMENT_DYNCREATE(CRealTimeDoc, CDocument)

BEGIN_MESSAGE_MAP(CRealTimeDoc, CDocument)
	//{{AFX_MSG_MAP(CRealTimeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRealTimeDoc construction/destruction

CRealTimeDoc::CRealTimeDoc()
{
	// TODO: add one-time construction code here

}

CRealTimeDoc::~CRealTimeDoc()
{
}

BOOL CRealTimeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRealTimeDoc serialization

void CRealTimeDoc::Serialize(CArchive& ar)
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
// CRealTimeDoc diagnostics

#ifdef _DEBUG
void CRealTimeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRealTimeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRealTimeDoc commands
