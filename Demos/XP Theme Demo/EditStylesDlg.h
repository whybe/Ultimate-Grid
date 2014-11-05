#if !defined(AFX_EDITSTYLESDLG_H__CECA644C_5B38_4994_AC8F_7A076F739ECF__INCLUDED_)
#define AFX_EDITSTYLESDLG_H__CECA644C_5B38_4994_AC8F_7A076F739ECF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditStylesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditStylesDlg dialog

#include <map>
#include <vector>

using std::map;
using std::vector;

class CEditStylesDlg : public CDialog
{
// Construction
public:
	CEditStylesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditStylesDlg)
	enum { IDD = IDD_EDITSTYLESDLG_DIALOG };
	CComboBox	m_cbPartStart;
	CComboBox	m_cbGridPart;
	CComboBox	m_cbState;
	CComboBox	m_cbPart;
	CComboBox	m_cbControl;
	CButton	m_DrawArea;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditStylesDlg)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditStylesDlg)
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnPaint();
	afx_msg void OnSelchangeCombo2();
	afx_msg void OnSelchangeCombo3();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	map<CString, vector<CString> > m_themeToParts;
	map<CString, vector<CString> > m_themeAndPartToStates;
	map<CString, std::pair<int, int> > m_themePartStateToIDs;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITSTYLESDLG_H__CECA644C_5B38_4994_AC8F_7A076F739ECF__INCLUDED_)
