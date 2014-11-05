// CDropDayCug.h : interface of the CDropDayCug class
//
/////////////////////////////////////////////////////////////////////////////
#include "ugctrl.h"
#include "UGCTDropGrid.h"
#include "ADOImpDatasource.h"

class CDropDayCug:public CDropDownCug
{
public:
	CDropDayCug();
	~CDropDayCug();

	void SetDate( int nYear, int nMonth, int nDay );
	BOOL IsUpdated() { return m_bIsUpdated; }

protected:
	BOOL m_bIsUpdated;
	CFont m_crossedFont;
	COleDateTime m_appDate;
	CADOImpDatasource m_adoDatasource;

private:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(CDropDayCug)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	//GetCellIndirect notification
	virtual void OnGetCell(int col,long row,CUGCell *cell);
	//SetCell notification
	virtual void OnSetCell(int col,long row,CUGCell *cell);

	virtual void OnHitBottom(long numrows,long rowspast,long rowsfound);
	virtual int OnEditStart(int col, long row,CWnd **edit);
	virtual int OnEditFinish(int col, long row,CWnd* edit,LPCTSTR string,BOOL cancelFlag);
	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	virtual void OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed);
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	virtual void OnCharDown(UINT *vcKey,BOOL processed);
	virtual void OnKeyDown(UINT *vcKey,BOOL processed);
	virtual void OnKillFocus(int section, CWnd *pNewWnd);
	//menu notifications
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int  OnMenuStart(int col,long row,int section);
};
