/*************************************************************************
				Class Declaration : CUGRadioType
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
		Radio button cell type. This cell type displays a group of radio 
		buttons	along with an associated label (if set).
	Details
		To add a radio button to the cell the cell's label property must
		be set to hold a list of the items, separated by line feed.

		"Apple\nOrange\nBanna\n"

		The cell's text/value field will contain the number of the selected
		radio button item (zero based index).

		A radio button can be select with a left mouse click, or by the
		spacebar (if the cell has focus). Each tap of the space bar will 
		move the current selection to the next item.


		Notifications
			UGCT_RADIOBUTTON_SELECTED - this cell type notification is
			fired when the state of the radio button is changed
*************************************************************************/

#ifndef _UGCTButn_H_
#define _UGCTButn_H_

#define UGCT_RADIOBUTTON_SELECTED 100

//CUGRadioType declaration
class UG_CLASS_DECL CUGRadioType: public CUGCellType
{
private:

	CUGCell m_cell;
	CPen m_darkPen;
	CPen m_lightPen;

public:

	CUGRadioType();
	~CUGRadioType();

	//overloaded CUGCellType functions
	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();
	virtual BOOL OnLClicked(int col,long row,int updn,RECT *rect,POINT *point);
	virtual BOOL OnKeyDown(int col,long row,UINT *vcKey);
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current);
	virtual void GetBestSize(CDC *dc,CSize *size,CUGCell *cell);
};

#endif //#ifndef _UGCTButn_H_
