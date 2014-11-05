// UGCTAppointment.h: interface for the CUGCTAppointment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGCTAPPOINTMENT_H__8EF1E30B_E442_481F_9756_E3F44CFEDAC0__INCLUDED_)
#define AFX_UGCTAPPOINTMENT_H__8EF1E30B_E442_481F_9756_E3F44CFEDAC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UGCtrl.h"

#define APP_MARGIN 5

class CUGCTAppointment : public CUGCellType
{
public:
	CUGCTAppointment();
	virtual ~CUGCTAppointment();

	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current);
	virtual int GetEditArea(RECT *rect);
};

#endif // !defined(AFX_UGCTAPPOINTMENT_H__8EF1E30B_E442_481F_9756_E3F44CFEDAC0__INCLUDED_)
