#if !defined(AFX_MYCUG_H__1D63AE27_0461_11D2_88AF_0080C859A484__INCLUDED_)
#define AFX_MYCUG_H__1D63AE27_0461_11D2_88AF_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MyCUG.h : header file
//

#include "ugctrl.h"

/////////////////////////////////////////////////////////////////////////////
// CMyCUG window

class CMyCUG : public CUGCtrl
{
// Construction
public:
	CMyCUG();

// Attributes
public:

// Operations
public:
	virtual void OnSetup();
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,int processed);
	virtual int OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCUG)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyCUG();

protected:
	CFont m_font;

// Generated message map functions
protected:
	//{{AFX_MSG(CMyCUG)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCUG_H__1D63AE27_0461_11D2_88AF_0080C859A484__INCLUDED_)
