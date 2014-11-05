// Ex2Doc.cpp : implementation of the CEx2Doc class
//

#include "stdafx.h"
#include "Ex2.h"

#include "Ex2Doc.h"

#include "UGCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx2Doc

IMPLEMENT_DYNCREATE(CEx2Doc, CDocument)

BEGIN_MESSAGE_MAP(CEx2Doc, CDocument)
	//{{AFX_MSG_MAP(CEx2Doc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx2Doc construction/destruction

CEx2Doc::CEx2Doc()
{
	// TODO: add one-time construction code here

}

CEx2Doc::~CEx2Doc()
{
}

BOOL CEx2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx2Doc serialization

void CEx2Doc::Serialize(CArchive& ar)
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
// CEx2Doc diagnostics

#ifdef _DEBUG
void CEx2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx2Doc commands
	// TODO: Add your command update UI handler code here
	

