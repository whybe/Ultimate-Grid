/***********************************************
	Ultimate Grid
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.


	class 
		CUGMyCug
	Purpose
		General purpose derived grid class.
		This class can be used as a starting 
		point for any grid project.
************************************************/
#include "ugctrl.h"

class MyCug:public CUGCtrl
{

public:

	BOOL m_arrowCursor;

	CFont m_font;
	CPen m_pen;
					
	MyCug();
	~MyCug();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyCug)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(MyCug)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	virtual void OnHitBottom(long numrows,long rowspast,long rowsfound);
	
	//data source notifications
	virtual void OnDataSourceNotify(int ID,long msg,long param);


};
