// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__A18EF576_64C6_4D29_B314_D9FA0A2188DB__INCLUDED_)
#define AFX_MAINFRM_H__A18EF576_64C6_4D29_B314_D9FA0A2188DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXFrameWndDock.h"
#include "OXTabClientWnd.h"
#include "XStatus4.h"

#include "OXSkinnedComboBox.h"
/*#include "WorkspaceBar.h"
#include "FoldersBar.h"
#include "PropertiesBar.h"
*/

#include "OXBitmapMenuOrganizer.h"
#include "OXCoolToolBar.h"
#include "OXMenuBar.h"
#include "OXSizeDockBar.h"

class CMainFrame : public COXMenuBarFrame<CFrameWnd, COXSizeDockBar>// public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	COXCoolToolBar    m_wndToolBar;
	COXCoolToolBar	m_wndToolBar2;
	COXCoolToolBar	m_wndToolBar3;
	CImageList		m_toolbar2Images;
	CImageList		m_toolbar3Images;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	COXBitmapMenuOrganizer m_BMO;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__A18EF576_64C6_4D29_B314_D9FA0A2188DB__INCLUDED_)
