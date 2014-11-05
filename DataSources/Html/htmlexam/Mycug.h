#include "ugctrl.h"
#include "openHTML.h"
#include "..\ughtml.h"

class MyCug:public CUGCtrl
{
protected:
	CUG_HTML_DataSource m_data;
public:

	OpenHTML m_dlg;

	BOOL Open();

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
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int  OnMenuStart(int col,long row,int section);

};
