// Excel DemoDoc.cpp : implementation of the CExcelDemoDoc class
//

#include "stdafx.h"
#include "Excel Demo.h"

#include "Excel DemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExcelDemoDoc

IMPLEMENT_DYNCREATE(CExcelDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CExcelDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CExcelDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExcelDemoDoc construction/destruction

CExcelDemoDoc::CExcelDemoDoc()
{
	// TODO: add one-time construction code here

}

CExcelDemoDoc::~CExcelDemoDoc()
{
}

BOOL CExcelDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExcelDemoDoc serialization

void CExcelDemoDoc::Serialize(CArchive& ar)
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
// CExcelDemoDoc diagnostics

#ifdef _DEBUG
void CExcelDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExcelDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExcelDemoDoc commands

BOOL CExcelDemoDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  Add your specialized creation code here
	m_sOpenFilename = lpszPathName;

	return TRUE;
}
