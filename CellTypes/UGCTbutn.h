/*************************************************************************
				Class Declaration : CUGButtonType
**************************************************************************
	Source file : UGCTButn.cpp
	Header file : UGCTButn.h
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Purpose
		This celltype simulates a standard windows
		push button control.
	
	Details
		CellTypeEx:
			UGCT_BUTTONNOFOCUS - dont show focus rect in the cell
			UGCT_BUTTONTOGGLE  - toggle button

		Notifications (OnCellTypeNotify)
			UGCT_BUTTONCLICK - sent when the mouse button goes up
				and the mouse was over the button
			UGCT_BUTTONDOWN - sent when the mouse button is pressed
				over the button.
			UGCT_BUTTONUP - sent when the mouse button is released.		
*************************************************************************/

#ifndef _UGCTbutn_H_
#define _UGCTbutn_H_

//notifications
#define UGCT_BUTTONCLICK	1	
#define UGCT_BUTTONDOWN		2	
#define UGCT_BUTTONUP		3	


//celltype EX styles
#define UGCT_BUTTONNOFOCUS	16


//CUGButtonType class definition
class UG_CLASS_DECL CUGButtonType: public CUGCellType
{
protected:

	int		m_btnDown;
	int		m_btnDownCol;
	long	m_btnDownRow;
	int		m_mode;
	RECT	m_btnDownRect;

public:

	CUGButtonType();
	~CUGButtonType();
	
	virtual BOOL OnDClicked(int col,long row,RECT *rect,POINT *point);
	virtual BOOL OnLClicked(int col,long row,int updn,RECT *rect,POINT *point);
	virtual BOOL OnKeyDown(int col,long row,UINT *vcKey);
	virtual BOOL OnMouseMove(int col,long row,POINT *point,UINT flags);

	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,
		CUGCell *cell,int selected,int current);

	virtual void OnKillFocus(int col,long row,CUGCell *cell);

};

#endif //#ifndef _UGCTbutn_H_