/*************************************************************************
				Class Declaration : CUGCTAutoSize
**************************************************************************
	Source file : UGCTAutoSize.cpp
	Header file : UGCTAutoSize.h
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Purpose:
		The CUGCTAutoSize celltype extends the standard celltype providing
		funcitonality to size its cell to make sure that cell's data is
		visible in full.  It will not make columns or rows smaller,
		but it will enlarge them whenever needed.
	
	Details:
		This celltype does not send any notifications to the CUGCtrl derived
		classes.
*************************************************************************/
#ifndef _UGCTOutlookHeader_H_
#define _UGCTOutlookHeader_H_

class UG_CLASS_DECL CUGCTOutlookHeader: public CUGCellType
{
protected:

public:
	CUGCTOutlookHeader();
	~CUGCTOutlookHeader();

protected:
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current);

private:
	CFont m_font;

};

#endif // _UGCTAutoSize_H_