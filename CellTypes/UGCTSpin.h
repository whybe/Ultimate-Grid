/*************************************************************************
				Class Declaration : CUGSpinButtonType
**************************************************************************
	Source file : UGCTSpin.cpp
	Header file : UGCTSpin.h
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

  Details
		Cell type extended style
			UGCT_SPINBUTTONHIDEBUTTON - when set the spin button will not
				be shown unless the cell has focus

		Notifications (OnCellTypeNotify)
			UGCT_SPINBUTTONUP - sent when the up arrow is pressed
			UGCT_SPINBUTTONDOWN - sent when the down arrow is pressed

*************************************************************************/

#ifndef _UGCTSpin_H_
#define _UGCTSpin_H_

//CUGSpinButtonType declaration
class UG_CLASS_DECL CUGSpinButtonType: public CUGCellType
{
protected:

	CPen	pen;
	CBrush	brush;

	int		btnBottomDown;
	int		btnTopDown;
	int		btnTopBottom;	//1-top button in progress 2-bottom in progress

	int		btnWidth;
	RECT	btnRect;
	int		btnCol;
	long	btnRow;

public:

	CUGSpinButtonType();
	~CUGSpinButtonType();

	//overloaded CUGCellType functions
	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();
	virtual int GetEditArea(RECT *rect);
	virtual BOOL OnDClicked(int col,long row,RECT *rect,POINT *point);
	virtual BOOL OnLClicked(int col,long row,int updn,RECT *rect,POINT *point);
	virtual BOOL OnMouseMove(int col,long row,POINT *point,UINT flags);
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current);
	virtual void GetBestSize(CDC *dc,CSize *size,CUGCell *cell);
};

#endif //#ifndef _UGCTSpin_H_