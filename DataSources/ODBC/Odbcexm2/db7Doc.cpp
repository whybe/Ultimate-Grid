// db7Doc.cpp : implementation of the CDb7Doc class
//

#include "stdafx.h"
#include "db7.h"

#include "db7Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDb7Doc

IMPLEMENT_DYNCREATE(CDb7Doc, CDocument)

BEGIN_MESSAGE_MAP(CDb7Doc, CDocument)
	//{{AFX_MSG_MAP(CDb7Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDb7Doc construction/destruction

CDb7Doc::CDb7Doc()
{
	// TODO: add one-time construction code here

}

CDb7Doc::~CDb7Doc()
{
}

BOOL CDb7Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDb7Doc serialization

void CDb7Doc::Serialize(CArchive& ar)
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
// CDb7Doc diagnostics

#ifdef _DEBUG
void CDb7Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDb7Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDb7Doc commands

void CDb7Doc::SetTitle(LPCTSTR lpszTitle) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDocument::SetTitle(lpszTitle);
}
