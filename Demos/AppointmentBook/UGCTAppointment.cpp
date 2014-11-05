// UGCTAppointment.cpp: implementation of the CUGCTAppointment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UGCTAppointment.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUGCTAppointment::CUGCTAppointment()
{

}

CUGCTAppointment::~CUGCTAppointment()
{

}

void CUGCTAppointment::OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current)
{
	// take care of the left margin area
	if (( cell->GetPropertyFlags()&UGCELL_STRING_SET ) && ( CString( cell->GetText()) != "" ))
	{
		dc->FillSolidRect( rect->left, rect->top, APP_MARGIN, rect->bottom - rect->top, RGB(0,0,200));
	}
	else
	{
		dc->FillSolidRect( rect->left, rect->top, APP_MARGIN, rect->bottom - rect->top, RGB(255,255,255));
	}

	// rest of the drawing can use default drawing routine
	rect->left = rect->left + APP_MARGIN;

	CUGCellType::OnDraw( dc, rect, col, row, cell, selected, current );
}

int CUGCTAppointment::GetEditArea(RECT *rect)
{
	rect->left = rect->left + APP_MARGIN;

	return UG_SUCCESS;
}