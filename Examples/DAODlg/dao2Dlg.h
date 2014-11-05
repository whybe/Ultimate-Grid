// dao2Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDao2Dlg dialog

class CDao2Dlg : public CDialog
{
// Construction
public:
	CDao2Dlg(CWnd* pParent = NULL);	// standard constructor

	MyCug				m_ctrl;
	CUGDAODataSource	m_dao;
	int					m_dataIndex;
	CString				m_SQL;
	CString				m_path;
	BOOL				m_hideHeadings;

// Dialog Data
	//{{AFX_DATA(CDao2Dlg)
	enum { IDD = IDD_DAO2_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDao2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDao2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBrowse();
	afx_msg void OnOpen();
	afx_msg void OnAbout();
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
