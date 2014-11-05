#include "ugctrl.h"
#include "ugodbc.h"

class MyCug:public CUGCtrl
{
public:
	MyCug();
	~MyCug();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(MyCug)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	virtual void OnHitBottom(long numrows,long rowspast,long rowsfound);
};
