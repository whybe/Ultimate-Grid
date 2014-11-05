#include "ugctrl.h"


class MyCug:public CUGCtrl
{
protected:
	CFont m_font1;
	CFont m_font2;
	CFont m_font3;

	CBitmap m_bitmap1;
	CBitmap m_bitmap2;

	CArray <int, int> m_originalCols;

	int StoreOriginalCols ( void );

public:
	MyCug();
	~MyCug();

	int FitToWindow ( int startCol, int endCol );

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(MyCug)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	virtual void OnSetup();

	//menu notifications
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int  OnMenuStart(int col,long row,int section);
	virtual COLORREF OnGetDefBackColor(int section);
	virtual void OnColSized(int col,int *width);
};
