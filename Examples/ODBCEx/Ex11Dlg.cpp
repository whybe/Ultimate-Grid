// Ex11Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ex11.h"
#include "Ex11Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	BOOL Create (CWnd *pParent);
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx11Dlg dialog

CEx11Dlg::CEx11Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEx11Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEx11Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEx11Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEx11Dlg)
	DDX_Control(pDX, IDC_SQL_EDIT, m_sql2);
	DDX_Control(pDX, IDC_CONNECT, m_control2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEx11Dlg, CDialog)
	//{{AFX_MSG_MAP(CEx11Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_SQL, OnSql)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx11Dlg message handlers

BOOL CEx11Dlg::OnInitDialog()
{
	// invoke About Dialog on startup
	CAboutDlg splash;
	splash.Create(NULL);
	CWnd *pWnd = splash.GetDlgItem( IDOK );
	pWnd->ShowWindow( FALSE );
	splash.ShowWindow(SW_SHOW);
	splash.UpdateWindow();
	Sleep(3000);
	splash.DestroyWindow();

	CDialog::OnInitDialog();

	// place grid on the dialog
	m_dialog.AttachGrid (this, IDC_GRID);
	// This line of code is responsible for creating the datasource index
	// which will supply the grid with data. 
	m_index = m_dialog.AddDataSource (&m_dialog.m_odbc);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEx11Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEx11Dlg::OnPaint() 
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEx11Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEx11Dlg::OnBrowse() 
{
	//initialize local variables
	CString	sqlString, connectstr ;
	SQLDatasourceInfo* dbI;
	char buf[255] ;
	int i = 0, ans = m_dialog.m_odbc.Browse(this->m_hWnd);
	
	if (ans == UG_SUCCESS){
		m_sql2.SetWindowText(*m_dialog.m_odbc.GetConnectString());
		MessageBox("You have successfully connected to the database" , "OK", MB_OK) ;
		// place 'select' statements into the 'SQL statement' combo box
		while(dbI = m_dialog.m_odbc.GetTableInfo(i++)){
			sqlString.Format("Select * FROM [%s]",dbI->tableName);
			m_control2.AddString(sqlString);
		}
	}
// select first item into edit portion
	m_control2.GetLBText(0,buf);
	m_control2.SetWindowText(buf);	
}

void CEx11Dlg::OnSql() 
{
	// initialize local variables
	int ret = 1;
	CString	db, sql;

	// reset the grid control
	m_dialog.SetDefDataSource(0);
	m_dialog.SetNumberRows(0);
	m_dialog.SetNumberCols(0);
	m_dialog.SetTH_Height(0);
	m_dialog.SetSH_Width(0);
	m_dialog.RedrawAll();

	m_sql2.GetWindowText(db);
	m_control2.GetWindowText(sql);

	if (db == "")			// is connect string present?
		MessageBox("Invalid connect string");
	else if (sql == "")		// is SQL statement present?
		MessageBox("Invalid SQL string");
	else {
		// open datasource
		AfxGetApp()->BeginWaitCursor();
		ret = m_dialog.m_odbc.OpenSQL(db,sql);	
		AfxGetApp()->EndWaitCursor();
	}

	if (ret == UG_SUCCESS) {	// if connected, fill-in grid cells with data from DB
		m_dialog.EnableUpdate(FALSE);
		m_dialog.SetTH_Height(20);
		m_dialog.SetSH_Width(30);
		
		m_dialog.SetDefDataSource(m_index);			// set datasource to selected DB
		m_dialog.SetGridUsingDataSource(m_index);	// read data

		m_dialog.BestFit(0,m_dialog.GetNumberCols()-1,0,UG_BESTFIT_TOPHEADINGS);
		for (int i= 0; i < m_dialog.GetNumberCols(); i++)
			if (m_dialog.GetColWidth(i) > 300){
				m_dialog.SetColWidth(i,300);
			}		
//		m_dialog.SetSH_Width(31);
		m_dialog.GotoRow(0);
		m_dialog.EnableUpdate(TRUE);
	}
}

BOOL CAboutDlg::Create(CWnd * pParent)
{
	if (!CDialog::Create(CAboutDlg::IDD, pParent))
	{
		TRACE0("Warning: creation of CAboutDlg dialog failed\n");
		return FALSE;
	}

	return TRUE;
}

void CEx11Dlg::OnCheck1() 
{
	
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
	Invalidate();
}

