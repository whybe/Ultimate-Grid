// ADO SampleDoc.cpp : implementation of the CADOSampleDoc class
//

#include "stdafx.h"
#include "ADO Sample.h"

#include "ADO SampleDoc.h"
#include "ConnectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CADOSampleDoc

IMPLEMENT_DYNCREATE(CADOSampleDoc, CDocument)

BEGIN_MESSAGE_MAP(CADOSampleDoc, CDocument)
	//{{AFX_MSG_MAP(CADOSampleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADOSampleDoc construction/destruction

CADOSampleDoc::CADOSampleDoc()
{
	// TODO: add one-time construction code here

}

CADOSampleDoc::~CADOSampleDoc()
{
}

BOOL CADOSampleDoc::OnNewDocument()
{
	CConnectDlg conDlg;

	if ( conDlg.DoModal() != IDOK  )
		return FALSE;

	if (!CDocument::OnNewDocument())
		return FALSE;

	m_szConnection = conDlg.GetConnectionString();
	SetSQLString( conDlg.GetSQLString());

	if ( m_szConnection == _T("") || GetSQLString() == _T(""))
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CADOSampleDoc serialization

void CADOSampleDoc::Serialize(CArchive& ar)
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
// CADOSampleDoc diagnostics

#ifdef _DEBUG
void CADOSampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CADOSampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CADOSampleDoc commands
CString CADOSampleDoc::GetSQLString( int nIndex /*= 0*/ )
{
	POSITION pos = m_szSQL.FindIndex( nIndex );

	if ( pos == NULL )
		return "";
		
	return m_szSQL.GetAt( pos );
}

void CADOSampleDoc::SetSQLString( CString szSql, int nIndex /*= 0*/ )
{
	POSITION pos = m_szSQL.FindIndex( nIndex );

	if ( pos == NULL )
		m_szSQL.AddTail( szSql );
	else
		m_szSQL.SetAt( m_szSQL.FindIndex( nIndex ), szSql );
}
