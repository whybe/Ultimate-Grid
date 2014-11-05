// AppInfo.cpp : implementation file
//

#include "stdafx.h"
#include "AppointmentBook.h"
#include "AppInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppInfo dialog


CAppInfo::CAppInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CAppInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAppInfo)
	m_appointmentStr = _T("");
	m_startTime = -1;
	m_hours = 0;
	m_minutes = 1;
	//}}AFX_DATA_INIT
}


void CAppInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppInfo)
	DDX_Text(pDX, IDC_APP_INFO, m_appointmentStr);
	DDX_CBIndex(pDX, IDC_START_TIME, m_startTime);
	DDX_Text(pDX, IDC_HOURS, m_hours);
	DDV_MinMaxInt(pDX, m_hours, 0, 23);
	DDX_CBIndex(pDX, IDC_MINUTES, m_minutes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppInfo, CDialog)
	//{{AFX_MSG_MAP(CAppInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppInfo message handlers
BOOL CAppInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString tempStr;
	CComboBox* startTime = ((CComboBox*)GetDlgItem( IDC_START_TIME ));

	for ( int yIndex = 0; yIndex < 48; yIndex ++ )
	{	// the hour indicator
		if (!( yIndex % 2 ))
		{
			if ( yIndex == 0 )
				tempStr.Format( "12:00 AM" );
			else if ( yIndex == 24 )
				tempStr.Format( "12:00 PM" );
			else if (( yIndex/2 ) > 12 )
				tempStr.Format( "%d:00 PM", yIndex/2 - 12 );
			else
				tempStr.Format( "%d:00 AM", yIndex/2 );
		}
		else
		{
			if ( yIndex == 1 )
				tempStr.Format( "12:30 AM" );
			else if ( yIndex == 25 )
				tempStr.Format( "12:30 PM" );
			else if (( yIndex/2 ) > 12 )
				tempStr.Format( "%d:30 PM", yIndex/2 - 12 );
			else
				tempStr.Format( "%d:30 AM", yIndex/2 );
		}

		startTime->AddString( tempStr );
	}

	startTime->EnableWindow( FALSE );
	
	UpdateData( FALSE );
	GetDlgItem( IDC_APP_INFO )->SetFocus();

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// 
void CAppInfo::SetStartTime( int timeSelection )
{
	m_startTime = timeSelection;
}

/////////////////////////////////////////////////////////////////////////////
// 
void CAppInfo::SetDuration( int duration )
{
	m_hours = 0;

	if ( duration > 0 )
	{
		m_hours = ( duration + 1 ) / 2;
	}

	m_minutes = !(duration % 2);
}

/////////////////////////////////////////////////////////////////////////////
// 
void CAppInfo::SetAppointmentStr( CString appStr )
{
	m_appointmentStr = appStr;
}

/////////////////////////////////////////////////////////////////////////////
// 
int CAppInfo::GetStartTime()
{
	return m_startTime;
}

/////////////////////////////////////////////////////////////////////////////
// 
int CAppInfo::GetDuration()
{
	return (( m_hours * 2 ) + m_minutes ) - 1;
}

/////////////////////////////////////////////////////////////////////////////
// 
CString CAppInfo::GetAppointmentStr()
{
	return m_appointmentStr;
}
