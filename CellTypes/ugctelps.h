/*************************************************************************
				Class Declaration : CUGEllipsisType
**************************************************************************
	Source file : UGCTelps.cpp
	Header file : UGCTelps.h
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Purpose
		Draws the cells value as text. Plus adds a ellipsis button on the
		right hand side of the cell. This button when clicked will fire a 
		notifiction (UGCT_ELLIPSISBUTTONCLICK).

	Details
		Cell type extended style
			UGCT_ELLIPSISHIDEBUTTON - when set the ellipsis button will not
				be shown unless the cell has focus

		Notifications (OnCellTypeNotify)
			UGCT_ELLIPSISBUTTONCLICK - sent when the ellipsis button is clicked

*************************************************************************/

#ifndef _UGCTelps_H_
#define _UGCTelps_H_

//celltype notification
#define UGCT_ELLIPSISBUTTONCLICK	100

#define UGCT_ELLIPSISHIDEBUTTON		512

//CUGEllipsisType declaration
class UG_CLASS_DECL CUGEllipsisType: public CUGCellType
{
protected:

	int		m_btnWidth;
	int		m_btnDown;
	long	m_btnRow;
	int		m_btnCol;
	RECT	m_btnRect;

	CPen	m_pen;
	CBrush	m_brush;

public:

	CUGEllipsisType();
	~CUGEllipsisType();
	
	//overloaded CUGCellType functions
	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();
	virtual int GetEditArea(RECT *rect);
	virtual BOOL OnLClicked(int col,long row,int updn,RECT *rect,POINT *point);
	virtual BOOL OnDClicked(int col,long row,RECT *rect,POINT *point);
	virtual BOOL OnMouseMove(int col,long row,POINT *point,UINT flags);
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current);
	virtual void GetBestSize(CDC *dc,CSize *size,CUGCell *cell);
};

#endif //#ifndef _UGCTelps_H_