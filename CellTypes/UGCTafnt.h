/*************************************************************************
				Class Declaration : CUGAutoFontType
**************************************************************************
	Source file : UGCTAfnt.cpp
	Header file : UGCTAfnt.h
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

    Purpose
		This class will automatically size the font of any cell using 
		this celltype so that all of the text will be visible.
*************************************************************************/
#ifndef _UGCTAfnt_H_
#define _UGCTAfnt_H_


//CUGAutoFontType class declaration
class UG_CLASS_DECL CUGAutoFontType: public CUGCellType
{
protected:

	HFONT CreateAutoSizeFont(HDC hdc, RECT *rect,LPCTSTR string);

public:

	CUGAutoFontType();
	~CUGAutoFontType();

	//overloaded CUGCellType functions
	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,
		CUGCell *cell,int selected,int current);

};

#endif //#ifndef _UGCTAfnt_H_