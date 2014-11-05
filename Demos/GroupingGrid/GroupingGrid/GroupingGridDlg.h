// GroupingGridDlg.h : header file
//

#pragma once

#include "MyCug.h"

// CGroupingGridDlg dialog
class CGroupingGridDlg : public CDialog
{
// Construction
public:
	CGroupingGridDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_GROUPINGGRID_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	MyCug m_Grid;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
