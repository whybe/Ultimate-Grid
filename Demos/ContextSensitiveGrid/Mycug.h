// MyCug97.h : interface of the MyCug class
//
/////////////////////////////////////////////////////////////////////////////
#include "ugctrl.h"

class MyCug:public CUGCtrl
{
public:
	MyCug();
	~MyCug();

protected:
	CFont m_hdgFont;
	CFont m_bodyFont;

private:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(MyCug)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	virtual void OnGetCell( int col, long row, CUGCell *cell );
	virtual COLORREF OnGetDefBackColor(int section);
	// Context help 
	virtual DWORD OnGetContextHelpID( int col, long row, int section );
};
