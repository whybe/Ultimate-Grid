// MyCug.h : interface of the MyCug class
//
/////////////////////////////////////////////////////////////////////////////
#include "ugctrl.h"
#include "DataMatrix.h"

#define UPDATE_EVENT 10023
#define REDRAW_EVENT 10024

class MyCug:public CUGCtrl
{
public:
	MyCug();
	~MyCug();

protected:
	CDataMatrix m_data;
	int m_nUpdateInterval;
	int m_nRedrawDelay;
	// draw hints list
	UGDrwHintVList *m_head;

	void DrawCached();
	void AddToCache( int col, long row );
	int RedrawCell_WCache( int col, long row );

private:
	CString m_tmpStr;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(MyCug)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	//GetCellIndirect notification
	virtual void OnGetCell(int col,long row,CUGCell *cell);
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
};
