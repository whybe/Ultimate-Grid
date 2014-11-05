/*************************************************************************
				Class Declaration : CUGPieChartType
**************************************************************************
	Source file : UGCTpie.cpp
	Header file : UGCTpie.h
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Purpose
		Pie Chart Cell Type Add-on
	  
	Details:
		- Add the UGCT_PIECHART cell type to the grid
		- Create one to n cells using the pie chart cell type along with
		  the UGCT_PIECHARTDATA cell type extended style, and load numbers 
		  into these cells. These cells are also used as the legend for
		  the pie chart
		- Add the following text to another celll using the pie chart cell type
		  "startcol\nstartrow\nendcol\nendrow\n"
		  where startcol,startrow start of the block of UGCT_PIECHARTDATA cells
		  and endrow,endcol end of the block of UGCT_PIECHARTDATA cells
		 
		- the highlight back color of the UGCT_PIECHARTDATA cells is used as the
		  pie slice color, plus it is used to draw the color rect on the right 
		  side of the data
		- use the UGCT_PIECHARTSEPARATE extended style to give the cell a 
		  default pie slice separation of 2 pixels
		- use the UGCT_PIECHARTDATALEFT to display pie chart data cells with
		  the data on the left and the legend color block on the right
		  use the UGCT_PIECHARTDATARIGHT to swith the positions.
*************************************************************************/

#ifndef _UGCTpie_H_
#define _UGCTpie_H_

//extended types
#define UGCT_PIECHARTSEPARATE	16
#define UGCT_PIECHARTPERCENT	32
#define UGCT_PIECHARTDATA		64
#define UGCT_PIECHARTDATALEFT	0
#define UGCT_PIECHARTDATARIGHT	128

//CUGPieChartType declaration
class UG_CLASS_DECL CUGPieChartType: public CUGCellType
{
	int m_btnWidth;
	int m_Separation;
	BOOL m_AspectRatio;

public:
	CUGPieChartType();
	~CUGPieChartType();

	//overloaded CUGCellType functions
	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current);
	virtual int GetEditArea(RECT *rect);
	virtual void GetBestSize(CDC *dc,CSize *size,CUGCell *cell);

	int DrawPieSlice(CDC *pDC,RECT *rect,int startAngle,int endAngle,int separation,COLORREF color);
	int SetSeparation(int separation);	
	void OnDrawChartData(CDC *dc,RECT *rect,CUGCell *cell,int selected,int current);
};

#endif //#ifndef _UGCTpie_H_