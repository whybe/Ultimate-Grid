#include "ugctrl.h"
#include "..\UGdelim.h"

class MyCug:public CUGCtrl
{
protected:
	CUG_Delimitted	m_data;

public:


	MyCug();
	~MyCug();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyCug)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(MyCug)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	virtual void OnMenuCommand(int col,long row,int section,int item);

	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);

};
