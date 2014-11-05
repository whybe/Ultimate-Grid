// DB4Dlg.cpp : implementation file
//

#include "stdafx.h"

#include "MyCug.h"

#include "DB4.h"
#include "DB4Dlg.h"

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
// CDB4Dlg dialog

CDB4Dlg::CDB4Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDB4Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDB4Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDB4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDB4Dlg)
	DDX_Control(pDX, IDC_EDITCONNECT, m_eConnect);
	DDX_Control(pDX, IDC_COMBOSQL, m_cbSQL);
	DDX_Control(pDX, IDC_OPEN, m_buttonOpen);
	DDX_Control(pDX, IDC_BROWSE, m_buttonBrowse);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDB4Dlg, CDialog)
	//{{AFX_MSG_MAP(CDB4Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDB4Dlg message handlers

BOOL CDB4Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

    // setup the grid
    m_ctrl.AttachGrid(this,IDC_GRID);

    m_ctrl.SetNumberRows(0);
    m_ctrl.SetNumberCols(0);

    m_ctrl.SetTH_Height(0);
    m_ctrl.SetSH_Width(0);

	m_index = m_ctrl.AddDataSource(&m_ctrl.m_odbc);
    // add the datasource, but don't yet make it the default


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

void CDB4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDB4Dlg::OnPaint() 
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
HCURSOR CDB4Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDB4Dlg::OnOpen() 
{
	
    int ret = 1;
	CString	db;
	CString sql;

	m_ctrl.m_odbc.Close();	// close first...
    
	m_ctrl.SetDefDataSource(0);
	m_ctrl.SetNumberRows(0);
	m_ctrl.SetNumberCols(0);
	m_ctrl.SetTH_Height(0);
	m_ctrl.SetSH_Width(0);
	m_ctrl.RedrawAll();
	
	m_eConnect.GetWindowText(db);
	m_cbSQL.GetWindowText(sql);

	if (db == _T(""))
		MessageBox(_T("Invalid connect string"));
	else if (sql == "")
		MessageBox(_T("Invalid SQL string"));
	else {
		AfxGetApp()->BeginWaitCursor();
		ret = m_ctrl.m_odbc.OpenSQL(db,sql);	
		AfxGetApp()->EndWaitCursor();
	}
	

	if (ret == UG_SUCCESS) {

		m_ctrl.EnableUpdate(FALSE);
		m_ctrl.SetTH_Height(20);
		m_ctrl.SetSH_Width(30);
		
		m_ctrl.SetDefDataSource(m_index);
		m_ctrl.SetGridUsingDataSource(m_index);

		long rr = m_ctrl.GetNumberRows();
		

		m_ctrl.BestFit(0,m_ctrl.GetNumberCols()-1,0,UG_BESTFIT_TOPHEADINGS);
		for (int i= 0; i < m_ctrl.GetNumberCols(); i++)
			if (m_ctrl.GetColWidth(i) > 300)
				m_ctrl.SetColWidth(i,300);
		m_ctrl.SetSH_Width(31);
		m_ctrl.GotoRow(0);
		m_ctrl.EnableUpdate(TRUE);
		
	}	
}

void CDB4Dlg::OnBrowse() 
{
  SWORD	retcode;
	SQLDatasourceInfo*	dbI;
	TCHAR buf[255];
	int i = 0;
	CString	sqlString;

	m_ctrl.m_odbc.Close();	// close first...

 
	m_ctrl.SetDefDataSource(0);
	m_ctrl.SetNumberRows(0);
	m_ctrl.SetNumberCols(0);
	m_ctrl.SetTH_Height(0);
	m_ctrl.SetSH_Width(0);
	m_ctrl.RedrawAll();


	m_eConnect.SetWindowText(_T(""));

	i = m_cbSQL.GetCount();

	while(m_cbSQL.DeleteString(--i) != CB_ERR);
	m_cbSQL.Clear();


	// call this to invoke the ODBC connection dialogs
	retcode = m_ctrl.m_odbc.Browse(this->m_hWnd);	
	
	if (retcode == UG_SUCCESS) {
		
		// retrieve the connect string ...
		m_eConnect.SetWindowText(*m_ctrl.m_odbc.GetConnectString());
	
		// ... and get the table names from the datasource.
		i = 0;
		while(dbI = m_ctrl.m_odbc.GetTableInfo(i++)){
			sqlString.Format(_T("Select * FROM [%s]"),dbI->tableName);
			m_cbSQL.AddString(sqlString);
		}

		// select first item into edit portion
		m_cbSQL.GetLBText(0,buf);
		m_cbSQL.SetWindowText(buf);
		
	}
	
}

void CDB4Dlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
    if(m_ctrl.GetSafeHwnd() == NULL)
        return;

	
    RECT rect, clientRect;
    m_ctrl.GetWindowRect(&rect);
    ScreenToClient(&rect);
    
    GetClientRect(&clientRect);

    rect.right = clientRect.right - rect.left;
    rect.bottom = clientRect.bottom - rect.left;

    m_ctrl.MoveWindow(&rect);
	m_ctrl.RedrawAll();
	
}
