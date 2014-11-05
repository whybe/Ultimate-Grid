#include "ugctrl.h"


class MyCug1:public CUGCtrl
{

public:


	MyCug1();
	~MyCug1();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(MyCug1)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	
	//movement and sizing
	virtual int  OnCanSizeCol(int col);
	virtual int  OnCanSizeTopHdg();
};
