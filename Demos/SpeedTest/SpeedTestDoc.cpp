// SpeedTestDoc.cpp : implementation of the CSpeedTestDoc class
//

#include "stdafx.h"
#include "SpeedTest.h"

#include "SpeedTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpeedTestDoc

IMPLEMENT_DYNCREATE(CSpeedTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CSpeedTestDoc, CDocument)
	//{{AFX_MSG_MAP(CSpeedTestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpeedTestDoc construction/destruction

CSpeedTestDoc::CSpeedTestDoc()
{
	// TODO: add one-time construction code here

}

CSpeedTestDoc::~CSpeedTestDoc()
{
}

BOOL CSpeedTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSpeedTestDoc serialization

void CSpeedTestDoc::Serialize(CArchive& ar)
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
// CSpeedTestDoc diagnostics

#ifdef _DEBUG
void CSpeedTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSpeedTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSpeedTestDoc commands
