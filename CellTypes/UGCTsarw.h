/*************************************************************************
				Class Declaration : CUGSortArrowType
**************************************************************************
	Source file : UGCTsarw.cpp
	Header file : UGCTsarw.h
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.


	Purpose
		This cell type is generally used to indicate the column that
		the grid is sorted by. 
	Details
		The sort arrow is drawn on the right hand side of the cell with
		text on the left. The up or down direction is determined with
		the extended cell type property:
			UGCT_SORTARROWUP or UGCT_SORTARROWDOWN (default)
*************************************************************************/


#ifndef _UGCTsarw_H_
#define _UGCTsarw_H_

//celltype notifications
#define UGCT_SORTARROWUP	16
#define UGCT_SORTARROWDOWN	32

//CUGSortArrowType declaration
class UG_CLASS_DECL CUGSortArrowType: public CUGCellType
{
	int m_ArrowWidth;

public:

	CUGSortArrowType();
	~CUGSortArrowType();

	//overloaded CUGCellType functions
	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current);
	virtual void GetBestSize(CDC *dc,CSize *size,CUGCell *cell);
};

#endif //#ifndef _UGCTsarw_H_
