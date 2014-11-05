// RTLandLTRDoc.cpp : implementation of the CRTLandLTRDoc class
//

#include "stdafx.h"
#include "RTLandLTR.h"

#include "RTLandLTRDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRTLandLTRDoc

IMPLEMENT_DYNCREATE(CRTLandLTRDoc, CDocument)

BEGIN_MESSAGE_MAP(CRTLandLTRDoc, CDocument)
	//{{AFX_MSG_MAP(CRTLandLTRDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRTLandLTRDoc construction/destruction

CRTLandLTRDoc::CRTLandLTRDoc()
{
	// TODO: add one-time construction code here

}

CRTLandLTRDoc::~CRTLandLTRDoc()
{
}

BOOL CRTLandLTRDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRTLandLTRDoc serialization

void CRTLandLTRDoc::Serialize(CArchive& ar)
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
// CRTLandLTRDoc diagnostics

#ifdef _DEBUG
void CRTLandLTRDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRTLandLTRDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRTLandLTRDoc commands
