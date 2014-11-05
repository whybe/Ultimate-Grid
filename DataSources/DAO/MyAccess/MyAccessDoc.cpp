// MyAccessDoc.cpp : implementation of the CMyAccessDoc class
//

#include "stdafx.h"
#include "mysqldlg.h"

#include "MyAccess.h"
#include "ugaccess.h"

#include "ugdao.h"

#include "MyAccessDoc.h"
#include "MyAccessView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyAccessDoc

IMPLEMENT_DYNCREATE(CMyAccessDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyAccessDoc, CDocument)
	//{{AFX_MSG_MAP(CMyAccessDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyAccessDoc construction/destruction

CMyAccessDoc::CMyAccessDoc()
{
	// TODO: add one-time construction code here

}

CMyAccessDoc::~CMyAccessDoc()
{
}

BOOL CMyAccessDoc::OnNewDocument()
{
//	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMyAccessDoc serialization

void CMyAccessDoc::Serialize(CArchive& ar)
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
// CMyAccessDoc diagnostics

#ifdef _DEBUG
void CMyAccessDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyAccessDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyAccessDoc commands

BOOL CMyAccessDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	LPTSTR	 buf;
	INT	     ret;
	INT		 openType;

	// TODO: Add your specialized code here and/or call the base class
	
	CDaoDatabase Db(NULL);
	try{
		Db.Open(lpszPathName,FALSE,FALSE,_T(""));
	}
	catch(CException * e){
		e->ReportError();
		e->Delete();
		return FALSE;
	}
	
	m_sqlDlg.SetDatabase(&Db);
	m_sqlDlg.m_csPath = lpszPathName;


	if(m_sqlDlg.DoModal()!= IDOK) {
		return FALSE;
	}

	openType = m_sqlDlg.GetOpenType();
	
	m_data.SetOption(UGDAO_OPT_GHOSTROWMODE,m_sqlDlg.m_bUseGhost,0L);
	m_data.SetOption(UGDAO_OPT_ALLOWEDITS,m_sqlDlg.m_bAllowEdit,0L);
	m_data.SetOption(UGDAO_OPT_NUMBERSIDEHDG, m_sqlDlg.m_bNumSH, m_sqlDlg.m_bBase1);

	if( dbOpenTable != openType) {
		buf = m_sqlDlg.GetSQLString();
		ret = m_data.Open(lpszPathName,NULL,openType,buf,0);
	}
	else {
		buf = m_sqlDlg.GetTableName();
		ret = m_data.Open(lpszPathName,buf, openType,NULL,0);
	}	



	if(UG_SUCCESS == ret || 3021 == ret)
		return TRUE;
	else
		return FALSE;
}

