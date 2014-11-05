#include "ugctrl.h"
#include "ugctspin.h"

class MyCug:public CUGCtrl
{
protected:
	CBitmap m_bitmap1;
	CBitmap m_bitmap2;
	CBitmap m_bitmap3;
	CBitmap m_bitmap4;
	CBitmap m_bitmap5;
	CBitmap m_bitmap6;
	CBitmap m_bitmap7;
	CBitmap m_bitmap8;
	CBitmap m_bitmap9;
	CFont m_font1;
	CUGSpinButtonType	m_spin;

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
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int  OnMenuStart(int col,long row,int section);
	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL  processed);
	virtual void OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL  processed);
	virtual COLORREF OnGetDefBackColor(int section);
};
