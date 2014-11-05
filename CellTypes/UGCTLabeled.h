/*************************************************************************
				Class Declaration : CUGLabeledType
**************************************************************************
	Source file : UGCTLabeled.cpp
	Header file : UGCTLabeled.h
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
#ifndef _UGCTLabeled_H_
#define _UGCTLabeled_H_


//CUGLabeledType class declaration
class UG_CLASS_DECL CUGLabeledType: public CUGCellType
{
protected:

	int	  m_fontHeight;
	CFont m_labelFont;
	COLORREF m_labelColor;

public:

	CUGLabeledType();
	~CUGLabeledType();

	//overloaded CUGCellType functions
	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();
	virtual int GetEditArea(RECT *rect);
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current);
	virtual void GetBestSize(CDC *dc,CSize *size,CUGCell *cell);

	int SetLabelFont(int height,int weight,LPCTSTR name,COLORREF color);
};

#endif //#ifndef _UGCTLabeled_H_