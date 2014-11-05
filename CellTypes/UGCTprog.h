/*************************************************************************
				Class Declaration : CUGProgressType
**************************************************************************
	Source file : UGCTprog.cpp
	Header file : UGCTprog.h
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Purpose
		a general use progress bar -draws left to right

	Details
		- This progress bar uses the cells text value as a percentage
		for the progress bar.
		- The label field is used to display a label within the progress 
		bar. If the label field is not used then a percentage value
		is displayed instead.
		- The standard background and text colors are used to represent
		the empty portion within the cell. And the highlight colors are
		used to represent the progress bar itself.

		CellTypeEx:
			UGCT_PROGRESSUSELABEL - displays the cells label text instead
				of a percentage value
*************************************************************************/

#ifndef _UGCTprog_H_
#define _UGCTprog_H_

#define UGCT_PROGRESSUSELABEL BIT1

//CUGProgressType Declaration
class UG_CLASS_DECL CUGProgressType: public CUGCellType
{
public:

	CUGProgressType();
	~CUGProgressType();

	//overloaded CUGCellType functions
	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current);
	virtual void GetBestSize(CDC *dc,CSize *size,CUGCell *cell);
};

#endif //#ifndef _UGCTprog_H_