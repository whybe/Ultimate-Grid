#include "ugctrl.h"


class MyCug2:public CUGCtrl
{

public:


	MyCug2();
	~MyCug2();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(MyCug2)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	
	//GetCellIndirect notification
	virtual void OnGetCell(int col,long row,CUGCell *cell);
};
