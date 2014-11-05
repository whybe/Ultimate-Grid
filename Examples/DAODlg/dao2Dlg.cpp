/***********************************************************
Ultimate Grid Demo - DAO Query
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
************************************************************/

#include "stdafx.h"

#include "mycug.h"
#include "ugdao.h"

#include "dao2.h"
#include "dao2Dlg.h"
#include "aboutdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***********************************************************
************************************************************/
CDao2Dlg::CDao2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDao2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDao2Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_SQL	= "";
	m_path	= "";
	

}

/***********************************************************
************************************************************/
void CDao2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDao2Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

/***********************************************************
************************************************************/
BEGIN_MESSAGE_MAP(CDao2Dlg, CDialog)
	//{{AFX_MSG_MAP(CDao2Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/***********************************************************
************************************************************/
BOOL CDao2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	
	CAboutDlg splash;
	// only show splash if not embedded
		splash.Create(NULL);
		CWnd *pWnd = splash.GetDlgItem( IDOK );	// Hide the Ok button 
		pWnd->ShowWindow( FALSE );
		splash.ShowWindow(SW_SHOW);
		splash.UpdateWindow();
	
	Sleep(4000);	// Delay two seconds for splash
	splash.DestroyWindow();

	// make sure that we can open Access 2000 files (using DAO 3.6).
	AfxGetModuleState()->m_dwVersion = 0x0601;

	//set up the grid
	m_ctrl.AttachGrid(this,IDC_GRID);
	m_dataIndex = m_ctrl.AddDataSource(&m_dao);
	m_ctrl.SetDefDataSource(m_dataIndex);
	m_ctrl.SetNumberRows(0);
	m_ctrl.SetNumberCols(0);
	
	m_ctrl.SetTH_Height(0);
	m_ctrl.SetSH_Width(0);
	m_hideHeadings = TRUE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

/***********************************************************
************************************************************/
void CDao2Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

/***********************************************************
************************************************************/
HCURSOR CDao2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/***********************************************************
************************************************************/
void CDao2Dlg::OnOK() 
{
	// TODO: Add extra validation here
	
	GetDlgItemText(IDC_LIST,m_SQL);

	if(m_path.GetLength() <1){
		MessageBox("No Database Specified","Can not continue",MB_OK);
		return;
	}
	if(m_SQL.GetLength() <1){
		MessageBox("No Query Specified","Can not continue",MB_OK);
		return;
	}

	m_dao.SetOption(UGDAO_OPT_GHOSTROWMODE,FALSE,FALSE);

	if(m_dao.OpenSQL(m_path,m_SQL) == UG_SUCCESS){
		if(m_hideHeadings){
			m_hideHeadings = FALSE;
			m_ctrl.SetTH_Height(20);
			m_ctrl.SetSH_Width(30);
		}
		m_ctrl.SetGridUsingDataSource(m_dataIndex);
		m_ctrl.GotoRow(0);
		m_ctrl.RedrawAll();
	}
	else{
		MessageBox("Unable To create record set","Can not continue",MB_OK);
		m_ctrl.SetNumberCols(0,0);
		m_ctrl.SetNumberRows(0);
		m_ctrl.SetTH_Height(0);
		m_ctrl.SetSH_Width(0);
		m_hideHeadings = TRUE;
	}
}

/***********************************************************
************************************************************/
void CDao2Dlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RECT dRect,gRect;

	GetClientRect(&dRect);

	CWnd *grd = GetDlgItem(IDC_GRID);
	if(grd != NULL){
		grd->GetWindowRect(&gRect);
		ScreenToClient(&gRect);
		gRect.bottom = dRect.bottom;
		gRect.right = dRect.right;
		grd->MoveWindow(&gRect,TRUE);
	}
}

/***********************************************************
************************************************************/
void CDao2Dlg::OnBrowse() 
{
	// TODO: Add your control notification handler code here
	CFileDialog fd(TRUE,"*.mdb",m_path,OFN_HIDEREADONLY,"Access Databases  *.mdb|*.mdb||",this);
	if(fd.DoModal()==IDOK){
		CString s = fd.GetPathName();
		SetDlgItemText(IDC_PATH,s);
		OnOpen();
	}
}

/***********************************************************
************************************************************/
void CDao2Dlg::OnOpen() 
{
	
	GetDlgItemText(IDC_PATH,m_path);
	int open;
	char buf[255];

	if(m_path.GetLength()==0){
		MessageBox("Please enter in a database file name, or browse for a database",
			"Cannot Open",MB_OK);
		return;
	}

	SetCursor(LoadCursor(NULL,IDC_WAIT));

	//open the database
	CDaoDatabase Db(NULL);
	try{
		Db.Open(m_path,FALSE,FALSE,"");
		open = TRUE;
	}
	catch(...){
		open = FALSE;
	}
	
	//get the table list
	int count  = Db.GetTableDefCount();
	CComboBox *cb = (CComboBox *)GetDlgItem(IDC_LIST);
	cb->ResetContent( );
	CDaoTableDefInfo ti;
	for(int loop =0;loop <count;loop++){
		try{
			Db.GetTableDefInfo(loop,ti,AFX_DAO_PRIMARY_INFO);
			if(!(ti.m_lAttributes&dbSystemObject)){
				wsprintf(buf,"SELECT * FROM [%s]",ti.m_strName);
				cb->AddString(buf);
			}
		}
		catch(...){
		}
	}

	cb->SetCurSel(0);

	//close the database
	if(open)
		Db.Close();

	SetCursor(LoadCursor(NULL,IDC_ARROW));
}

/***********************************************************
************************************************************/
void CDao2Dlg::OnAbout() 
{
	//show the about dialog
	CAboutDlg about;
	about.DoModal();
}

void CDao2Dlg::OnCheck1() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	Invalidate();
}
