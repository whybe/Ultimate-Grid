#include "ugctrl.h"

#include "..\ugoledb.h"

class MyCug:public CUGCtrl
{
protected:
	CUG_OLEDB_DataSource  m_oleDBdata;
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

	virtual void OnSetup();

	//menu notifications
	virtual void OnHitBottom(long numrows,long rowspast,long rowsfound);
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
};
