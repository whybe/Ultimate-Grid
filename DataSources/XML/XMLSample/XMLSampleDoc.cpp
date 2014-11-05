// XMLSampleDoc.cpp : implementation of the CXMLSampleDoc class
//

#include "stdafx.h"
#include "XMLSample.h"

#include "XMLSampleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXMLSampleDoc

IMPLEMENT_DYNCREATE(CXMLSampleDoc, CDocument)

BEGIN_MESSAGE_MAP(CXMLSampleDoc, CDocument)
	//{{AFX_MSG_MAP(CXMLSampleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXMLSampleDoc construction/destruction

CXMLSampleDoc::CXMLSampleDoc()
{
	// TODO: add one-time construction code here
	m_sOpenFilename = _T("");
}

CXMLSampleDoc::~CXMLSampleDoc()
{
}

BOOL CXMLSampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CXMLSampleDoc serialization

void CXMLSampleDoc::Serialize(CArchive& ar)
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
// CXMLSampleDoc diagnostics

#ifdef _DEBUG
void CXMLSampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXMLSampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXMLSampleDoc commands

BOOL CXMLSampleDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  Add your specialized creation code here
	m_sOpenFilename = lpszPathName;

	return TRUE;
}
