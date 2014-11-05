// MyCUG.h : interface of the MyCug class
//
//	The Cell Properties sample demonstrates the flexibility of a grid's cell.
//	Right click on a corner button cell, or a top heading cell, or grid's cell
//	to show a CPropertyDlg dialog. 
//
/////////////////////////////////////////////////////////////////////////////
#include "ugctrl.h"

class MyCug:public CUGCtrl
{
public:
	MyCug();
	~MyCug();

protected:

private:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(MyCug)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	//GetCellIndirect notification
	virtual void OnGetCell(int col,long row,CUGCell *cell);
	//cell type notifications
	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	//menu notifications
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int  OnMenuStart(int col,long row,int section);
};
