/***********************************************
	Ultimate Grid
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.


	class 
		CUGCRealTimeGrid
	Purpose
		General purpose derived grid class.
		This class can be used as a starting 
		point for any grid project.
************************************************/
#include "ugctrl.h"
#include "UGCTbutn.h"
#include "ugctpro1.h"

#define TIMERID	1000
#define CT_NEGATIVE  64
#define CT_POSITIVE  128

class CRealTimeGrid:public CUGCtrl
{

public:
	CUGButtonType m_button;
	int m_buttonIndex;
		
	CUGAdvProgressType	m_pro1;
	int m_pro1Index;

	CFont m_font1;
	CFont m_font2;
					
	CRealTimeGrid();
	~CRealTimeGrid();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealTimeGrid)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(CRealTimeGrid)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual void OnSetup();
	virtual void OnGetCell(int col,long row,CUGCell *cell);
	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);
	virtual void OnRowSizing(long row,int *height);

	void QuickRedrawCell( int col, long row );
};
