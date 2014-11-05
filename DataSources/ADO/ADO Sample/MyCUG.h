// MyCUG.h : interface of the MyCug class
//
/////////////////////////////////////////////////////////////////////////////
#include "ugctrl.h"
// include the sort arrow celltype
#include "UGCTsarw.h"

class MyCug:public CUGCtrl
{
public:
	MyCug();
	~MyCug();

protected:
	CFont	m_defFont;
	// member variables required for the sort feedback
	CUGSortArrowType m_sortArrow;
	int m_curSortCol;
	int m_sortDir;

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
	virtual void OnSheetSetup( int nIndex );
	//movement and sizing
	virtual void OnHitBottom(long numrows,long rowspast,long rowsfound);
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnCharDown(UINT *vcKey,BOOL processed);
	//GetCellIndirect notification
	virtual void OnGetCell(int col,long row,CUGCell *cell);
	//menu notifications
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int  OnMenuStart(int col,long row,int section);

	virtual void OnTabSelected(int ID);
};
