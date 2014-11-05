// CDropMonthCug.h : interface of the CDropMonthCug class
//
/////////////////////////////////////////////////////////////////////////////
#include "ugctrl.h"
#include "UGCTDropGrid.h"

class CDropMonthCug:public CDropDownCug
{
public:
	CDropMonthCug();
	~CDropMonthCug();

	inline void SetCurrentYear( long nYear ) { m_nYear = nYear; }
	inline long GetCurrentYear() { return m_nYear; }

protected:
	long m_nYear;

private:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(CDropMonthCug)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	virtual void OnGetCell(int col,long row,CUGCell *cell);
	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	virtual void OnCB_LClicked(int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnCB_DClicked(RECT *rect,POINT *point,BOOL processed);
};
