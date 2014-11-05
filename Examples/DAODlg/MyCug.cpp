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

#include "stdafx.h"
#include "resource.h"
#include "MyCug.h"
#include "ugdao.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(MyCug,CUGCtrl)
	//{{AFX_MSG_MAP(MyCug)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/***************************************************
****************************************************/
MyCug::MyCug()
{
	m_arrowCursor = FALSE;
}
/***************************************************
****************************************************/
MyCug::~MyCug()
{
	UGXPThemes::CleanUp();
}

/***************************************************
OnSetup
	This function is called just after the grid window 
	is created or attached to a dialog item.
	It can be used to initially setup the grid
****************************************************/
void MyCug::OnSetup(){
	
	SetUniformRowHeight(TRUE);
}


/***************************************************
****************************************************/
void MyCug::OnHitBottom(long numrows,long rowspast,long rowsfound){
	if(rowsfound >0){
		SetNumberRows(numrows+rowsfound,FALSE);
	}
}
void MyCug::OnDataSourceNotify(int ID,long msg,long param){
	if ( ID == UGDS_ID_DAO){
		switch (msg) {
		case UGDSM_DAO_EOF:
			break;
		case UGDSM_DAO_UPDATEFAILED:
				break;
		case UGDSM_DAO_KILLEXTRAROW:
				break;
		case UGDSM_DAO_ADJUSTROWS:
			SetNumberRows(param);
			break;
		default:
			break;
		}

	}
}
