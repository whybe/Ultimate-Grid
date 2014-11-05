#if !defined(AFX_APPINFO_H__728B692A_9AB4_4AD0_878A_F3023115392B__INCLUDED_)
#define AFX_APPINFO_H__728B692A_9AB4_4AD0_878A_F3023115392B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAppInfo dialog

class CAppInfo : public CDialog
{
// Construction
public:
	void SetStartTime( int timeSelection );
	void SetDuration( int duration );
	void SetAppointmentStr( CString appStr );

	int GetStartTime();
	int GetDuration();
	CString GetAppointmentStr();

	CAppInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAppInfo)
	enum { IDD = IDD_APP_DLG };
	CString	m_appointmentStr;
	int		m_startTime;
	int		m_hours;
	int		m_minutes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAppInfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPINFO_H__728B692A_9AB4_4AD0_878A_F3023115392B__INCLUDED_)
