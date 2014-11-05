/*************************************************************************
				Class Declaration : CUGExpandType
**************************************************************************
	Source file : UGCTExpand.cpp
	Header file : UGCTExpand.h
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Purpose
		Expanding/collapsing cell type.  This cell type displays a button which, 
		when pressed, will expand or collapse a group of rows under it, up until the next cell of the same type
		Radio button cell type. This cell type displays a group of radio 
	Details


*************************************************************************/

#ifndef _UGCTExpand_H_
#define _UGCTExpand_H_

#include <map>

// v7.2 - update 03 - added message decl for OnCellTypeNotify call
#define UGCT_EXPANDCONTRACT	16

//CUGExpandType declaration
class UG_CLASS_DECL CUGExpandType: public CUGCellType
{
	// v7.2 - update 01 - derived classes will need access to the CellData
	// structure - access specifier changed from private to protected. Submitted 
	// by mhorowit.
//private:
protected:
	struct CellData
	{
		int numberOfRows;
		bool isOpen;
		bool isSelected;
		bool wasSelected;
	};

	CellData * GetCellData(int col, int row);

	// This container holds the sizes of all the cells we contract, so they can be expanded to the same size again
	std::map<int, int>  m_mapColumnHeights;
	CBitmap m_buttonBack;
	CFont m_font;

	void ExpandOrContract(int col, int row);

	// This method creates the m_buttonBack bitmap, which is then reused in painting the cell type.
	void MakeBitmap(CDC * source, RECT rc);
public:

	CUGExpandType();
	~CUGExpandType();

	void ExpandAll(int col);
	void CollapseAll(int col);
	void SetNumberOfRows(int col, int row, int rows);

#ifdef UGEXPANDUSEMAIL
	void MarkAllRead(int col, int row);
	void MarkAllUnread(int col, int row);
#endif
	void ShowGroups(bool show);

	void ResetCache();

	//overloaded CUGCellType functions
	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();
	virtual BOOL OnLClicked(int col,long row,int updn,RECT *rect,POINT *point);
	virtual BOOL OnRClicked(int col,long row,int updn,RECT *rect,POINT *point);
	virtual BOOL OnKeyDown(int col,long row,UINT *vcKey);
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current);
	virtual void GetBestSize(CDC *dc,CSize *size,CUGCell *cell);
};

#endif //#ifndef _UGCTButn_H_
