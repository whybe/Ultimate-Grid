/*************************************************************************
				Class Declaration : CUGSliderType
**************************************************************************
	Source file : UGCTsldr.cpp
	Header file : UGCTsldr.h
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Purpose
		An interactive slider control
	Details
		The interactive slider control displays a slider wher the slide
		position is drawn according to the cell's text/value field.
		The value must be a number from 0 to 100.
		The mouse can be used to update the sliders value, by holding down
		the left mouse button and moving the mouse along the slider.
		As the slider moves a cell type event is fired: UGCT_SLIDER_MOVED
		Notifictions
			UGCT_SLIDER_MOVED - fired when the slider is moved interactively
				the param value contains the sliders new value (0-100)
*************************************************************************/

#ifndef _UGCTsldr_H_
#define _UGCTsldr_H_

#define UGCT_SLIDER_MOVED 100

//CUGSliderType declaration
class UG_CLASS_DECL CUGSliderType: public CUGCellType
{
	CPen	m_blackPen;
	CPen	m_grayPen;
	CPen	m_darkGrayPen;
	CPen	m_whitePen;

	BOOL	m_updateSlider;

public:

	CUGSliderType();
	~CUGSliderType();

	//overloaded CUGCellType functions
	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();
	virtual BOOL OnLClicked(int col,long row,int updn,RECT *rect,POINT *point);
	virtual BOOL OnMouseMove(int col,long row,POINT *point,UINT flags);
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,
		CUGCell *cell,int selected,int current);
};

#endif //#ifndef _UGCTsldr_H_