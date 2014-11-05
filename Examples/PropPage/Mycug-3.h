#include "ugctrl.h"

class MyCug3:public CUGCtrl
{

public:
	MyCug3();
	~MyCug3();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(MyCug3)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	
	virtual int  OnCanSizeCol(int col);
	virtual int  OnCanSizeRow(long row);
	virtual int  OnCanSizeTopHdg();
	virtual int  OnCanSizeSideHdg();

	//GetCellIndirect notification
	virtual void OnGetCell(int col,long row,CUGCell *cell);
};
