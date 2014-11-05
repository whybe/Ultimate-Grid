#include "ugctrl.h"
#include "UGCTsarw.h"	// Added by ClassView

#ifndef _FindGrid_H_
#define _FindGrid_H_

class CFindGrid:public CUGCtrl
{

public:
	CFindGrid();
	~CFindGrid();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(CFindGrid)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	virtual void OnTH_LClicked( int iCol, long lRow, int iUpdn, RECT* pRect, POINT* pPoint, BOOL bProcessed = 0 );
	virtual void OnGetCell( int iCol, long lRow, CUGCell* pCell );
	virtual void OnMenuCommand( int iCol, long lRow, int iSection, int iItem );
	virtual int  OnMenuStart( int iCol, long lRow, int iSection );
	virtual int OnHint( int iCol, long lRow, int iSection, CString* pString );
	virtual int OnSortEvaluate( CUGCell* pCell1, CUGCell* pCell2, int iFlags );
	virtual void OnCellChange(int oldcol,int newcol,long oldrow,long newrow);
	
protected:
	BOOL m_bSortedAscending;
	int m_iArrowIndex;
	CUGSortArrowType m_sortArrow;
	int m_iSortCol;
	void InitMenu();
	CFont m_font;
};

#endif //_FindGrid_H_