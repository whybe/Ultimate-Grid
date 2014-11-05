// XP Theme DemoDoc.cpp : implementation of the CXPThemeDemoDoc class
//

#include "stdafx.h"
#include "XP Theme Demo.h"

#include "XP Theme DemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXPThemeDemoDoc

IMPLEMENT_DYNCREATE(CXPThemeDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CXPThemeDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CXPThemeDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXPThemeDemoDoc construction/destruction

CXPThemeDemoDoc::CXPThemeDemoDoc()
{
	// TODO: add one-time construction code here

}

CXPThemeDemoDoc::~CXPThemeDemoDoc()
{
}

BOOL CXPThemeDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CXPThemeDemoDoc serialization

void CXPThemeDemoDoc::Serialize(CArchive& ar)
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
// CXPThemeDemoDoc diagnostics

#ifdef _DEBUG
void CXPThemeDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXPThemeDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXPThemeDemoDoc commands
