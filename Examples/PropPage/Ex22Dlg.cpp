// Ex22Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ex22.h"
#include "Ex22Dlg.h"

#include "UGCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx22Dlg dialog

CEx22Dlg::CEx22Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEx22Dlg::IDD, pParent)
{

	//{{AFX_DATA_INIT(CEx22Dlg)
	m_wiz = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CEx22Dlg::~CEx22Dlg()
{
	UGXPThemes::CleanUp();
}

void CEx22Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEx22Dlg)
	DDX_Check(pDX, IDC_CHECK2, m_wiz);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEx22Dlg, CDialog)
	//{{AFX_MSG_MAP(CEx22Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INVOKE, OnInvoke)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx22Dlg message handlers

BOOL CEx22Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CEx22Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	
		CDialog::OnSysCommand(nID, lParam);
	
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEx22Dlg::OnPaint() 
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
HCURSOR CEx22Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEx22Dlg::OnInvoke() 
{
	UpdateData();
	// TODO: Add your control notification handler code here

	CPropertySheet proSheet(IDS_PSHTCAPTION,this,0);

	CPPage1 page1;
	CPPage2 page2;
	CPPage3 page3;

	proSheet.AddPage(&page1);
	proSheet.AddPage(&page2);
	proSheet.AddPage(&page3);


	if (m_wiz){
		proSheet.SetWizardMode();
	}
	
	proSheet.DoModal();
}

void CEx22Dlg::OnCheck1() 
{
	UGXPThemes::UseThemes(!UGXPThemes::UseThemes());
}
