// MyCUG.h : interface of the MyCug class
//
/////////////////////////////////////////////////////////////////////////////
#include "ugctrl.h"
#include "UGCTDropGrid.h"
#include "DropMonthCug.h"
#include "DropDayCug.h"
#include "ADOImpDatasource.h"

class MyCug:public CUGCtrl
{
public:
	MyCug();
	~MyCug();

protected:
	int m_nBellBmpIndex;
	int m_nCurrMonth;
	int m_nCurrYear;
	int m_nMonthDispFont;
	COleDateTime m_tempDateTime;
	CUGCTDropGrid m_dropGridCT;
	CDropMonthCug m_dropMonthGrid;
	CDropDayCug m_dropDayGrid;
	CPen m_borderPen;
	CADOImpDatasource m_adoRecordSet;

	void PopulateMonthInfo();
	void GetMonthInfo( int &nMinDay, int &nDaysInMonth );
	int GetAppCount( int nDayOfMonth );

private:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(MyCug)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed=0);
	//GetCellIndirect notification
	virtual void OnGetCell(int col,long row,CUGCell *cell);
	//cell type notifications
	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
};
