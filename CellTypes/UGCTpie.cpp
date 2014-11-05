/*************************************************************************
				Class Implementation : CUGPieChartType
**************************************************************************
	Source file : UGCTpie.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTpie.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/***************************************************
CUGPieChartType - Constructor
	Initialize member variables
****************************************************/
CUGPieChartType::CUGPieChartType(){
	m_Separation = 0;
	m_AspectRatio = TRUE;
	m_btnWidth = GetSystemMetrics(SM_CXVSCROLL);

}

/***************************************************
~CUGPieChartType - Destructor
	Cleanup all allocated resources
****************************************************/
CUGPieChartType::~CUGPieChartType(){

}

/***************************************************
GetName  - overloaded CUGCellType::GetName
	Returns a readable name for the cell type.
	Returned value is used to help end-users
	to see what cell type are available.

    **See CUGCellType::GetName for more details
	about this function

Params:
	<none>
Return:
	cell type name
****************************************************/
LPCTSTR CUGPieChartType::GetName()
{
	return _T("Pie Chart");
}

/***************************************************
GetUGID  - overloaded CUGCellType::GetUGID
	Returns a GUID for the cell type, this number
	is unique for each cell type and never changes.
	This number can be used to find the cell types
	added to this instance of the Ultimate Grid.

    **See CUGCellType::GetUGID for more details
	about this function

Params:
	<none>
Returns:
	UGID (which is actually a GUID)
****************************************************/
LPCUGID CUGPieChartType::GetUGID()
{
	static const UGID ugid = 
	{ 0x4585888b, 0xd9eb, 0x11d5, { 0x9b, 0x37, 0x0, 0x50, 0xba, 0xd4, 0x4b, 0xcd } };

	return &ugid;
}
/***************************************************
SetSeparation
	Sets the number of pixels of space around each
	slice in the pie. The default value is 0.
Params
	separation - number of pixels of separation
Return
	UG_SUCCESS - success
	UG_ERROR - erorr
****************************************************/
int CUGPieChartType::SetSeparation(int separation){
	if(separation <0 || separation > 64)
		return UG_ERROR;
	m_Separation = separation;
	return UG_SUCCESS;
}
/***************************************************
OnDraw - overloaded CUGCellType::OnDraw

    **See CUGCellType::GetEditArea for more details
	about this function
****************************************************/
int CUGPieChartType::GetEditArea(RECT *rect){

	
	CUGCell cell;	
	m_ctrl->GetCell(m_ctrl->GetCurrentCol(),m_ctrl->GetCurrentRow(),&cell);

	int alignment = UG_ALIGNLEFT;
	if( cell.IsPropertySet( UGCELL_CELLTYPEEX_SET ) == TRUE )
		if(cell.GetCellTypeEx() & UGCT_PIECHARTDATARIGHT)
			alignment = UGCT_PIECHARTDATARIGHT;

	if(alignment == UG_ALIGNLEFT)
		rect->right -= m_btnWidth;
	else
		rect->left += m_btnWidth;

	if(m_ctrl->m_editInProgress)
		m_ctrl->RedrawCell(m_ctrl->m_editCol,m_ctrl->m_editRow);

	return TRUE;
}

/***************************************************
OnDraw - overloaded CUGCellType::OnDraw

    **See CUGCellType::OnDraw for more details
	about this function
****************************************************/
void CUGPieChartType::OnDraw(CDC *dc,RECT *rect,int col,long row,
							CUGCell *cell,int selected,int current)
{
	if (!m_drawThemesSet)
		m_useThemes = cell->UseThemes();

	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	
	DrawBorder(dc,rect,rect,cell);

	long properties = cell->GetPropertyFlags();
	long cellTypeEx = 0;

	//get the extended style
	if(properties&UGCELL_CELLTYPEEX_SET)
		cellTypeEx = cell->GetCellTypeEx();
	
	if(cellTypeEx&UGCT_PIECHARTDATA){
		OnDrawChartData(dc,rect,cell,selected,current);
		return;
	}
	

	int separation = m_Separation;
	if(cellTypeEx&UGCT_PIECHARTSEPARATE && separation == 0)
		separation = 2;

	if (!m_useThemes || !UGXPThemes::DrawBackground(NULL, *dc, cell->GetXPStyle(), UGXPThemes::GetState(selected > 0, current > 0), rect, NULL))
	{
		//check the selected and current states
		if(selected || (current && m_ctrl->m_GI->m_currentCellMode&2)){
			CBrush brush(cell->GetHBackColor());
			dc->FillRect(rect,&brush);
		}
		else{
			CBrush brush(cell->GetBackColor());
			dc->FillRect(rect,&brush);
		}
	}

	//adjust the rect
	RECT origRect;
	CopyRect(&origRect,rect);
	rect->left +=2+separation;
	rect->top +=2+separation;
	rect->right -=2+separation;
	rect->bottom -=2+separation;

	if(m_AspectRatio == TRUE){
		int width = rect->right - rect->left;
		int height = rect->bottom - rect->top;
		if(width != height){
			if(width >height){
				int dif = (width - height)/2;
				rect->left += dif;
				rect->right -= dif;
			}
			else{
				int dif = (height - width)/2;
				rect->top += dif;
				rect->bottom -= dif;
			}
		}
	}

	//get the pie data range
	long range[4];
	CString pString = cell->GetText();
	int len = pString.GetLength();
	int spos =0;
	int index = 0;

	// This is reused below, which only works in VC6 when it's declared in the loop
	int t=0;

	for(;t<len;t++){
		if(pString.GetAt(t)==_T('\n')){
			range[index] = _ttol(pString.Mid(spos,t-spos));
			index++;
			spos = t+1;
		}
	}
	if(range[0] > range[2])
		return;
	if(range[1] > range[3])
		return;
	
	//get the data values total
	CUGCell		c;	
	double		totalValue =0;
	double		*Values = new double[(range[2]-range[0]+1) * (range[3]-range[1]+1)];
	COLORREF	*Colors = new COLORREF[(range[2]-range[0]+1) * (range[3]-range[1]+1)];
	long		totalSlices =0;
	for(int x= range[0];x<=range[2];x++){
		for(int y= range[1];y<=range[3];y++){
			m_ctrl->GetCellIndirect(x,y,&c);
			Values[totalSlices] = c.GetNumber();
			totalValue +=Values[totalSlices];
			Colors[totalSlices] = c.GetHBackColor();
			totalSlices ++;
		}
	}

	//draw the slices
	double scale = 0;

	if ( totalValue != 0 )
		scale = 360 / totalValue;

	int startAngle = 0;
	int endAngle = 0;

	for(t= 0;t< totalSlices ;t++){
		endAngle = startAngle + (int)(Values[t] *scale); 
		if(endAngle == startAngle)
			continue;
		if(t == totalSlices-1)
			endAngle = 360;
		DrawPieSlice(dc,rect,startAngle,endAngle,separation,Colors[t]);
		startAngle = endAngle;
	}

	//reset the rect
	CopyRect(rect,&origRect);

	delete[] Values;
	delete[] Colors;

}
/***************************************************
DrawPieSlice
	Draws in individual pie slice.
Params
	pDC	- device context to draw the slice on
	rect - rectangle of the pie chart area
	startAngle - start angle of the slice
	endAngle - end angle of the slice
	separation - separation from the center of the pie in pixels
	color - color of the pie slice
Return
	UG_SUCCESS - success
	UG_ERROR - erorr
****************************************************/
int CUGPieChartType::DrawPieSlice(CDC *pDC,RECT *rect,int startAngle,int endAngle,int separation,COLORREF color){
	
	
	POINT start;
	POINT end;
	RECT  tRect;
	CBrush brush(color);
	CBrush * oldbrush = pDC->SelectObject(&brush);
	
	CopyRect(&tRect,rect);
		
	double sa = (6.28318 / 360 ) * (double)startAngle*-1;	//start angle
	double ea = (6.28318 / 360 ) * (double)endAngle*-1;		//end angle
	double ma = (6.28318 / 360 ) * 
		(double)(startAngle+(endAngle-startAngle)/2) *-1;//middle angle

	//separation
	if(separation >0){
		separation +=1;
		POINT sep;
		sep.x = (int)(cos(ma) * (double)separation);
		sep.y = (int)(sin(ma) * (double)separation);
		
		//adjust the rect
		tRect.left +=sep.x;
		tRect.right +=sep.x;
		tRect.top +=sep.y;
		tRect.bottom +=sep.y;
	}

	int width	= tRect.right - tRect.left;
	int height	= tRect.bottom - tRect.top;
	int yCenter = tRect.top + (height/2)  ;
	int xCenter = tRect.left + (width/2) ;

	start.x = (int)(cos(sa) * width) + xCenter;
	start.y = (int)(sin(sa) * height) + yCenter;

	end.x = (int)(cos(ea) * width) + xCenter;
	end.y = (int)(sin(ea) * height) + yCenter;

	pDC->Pie(&tRect,start,end);

	pDC->SelectObject(oldbrush);

	return UG_SUCCESS;
}

/***************************************************
OnDrawChartData
	Draws the pic chart cells that have the
	UGCT_PIECHARTDATA extended style.
	The drawing represents a simple legend for the
	pie chart.
Params
	dc - device context
	rect - rectanle of the cell
	cell - the cell to draw
	selected - the cells selected state
	current - the cells focus state
Return
	none
****************************************************/
void CUGPieChartType::OnDrawChartData(CDC *dc,RECT *rect,CUGCell *cell,int selected,int current){
	
	RECT origRect;
	CopyRect(&origRect,rect);

	//get the alignment
	int alignment = UG_ALIGNLEFT;
	if( cell->IsPropertySet( UGCELL_CELLTYPEEX_SET ) == TRUE )
		if(cell->GetCellTypeEx() & UGCT_PIECHARTDATARIGHT)
			alignment = UGCT_PIECHARTDATARIGHT;
		
	float fScale = 1.0;
#ifdef UG_ENABLE_PRINTING
	fScale = m_ctrl->GetUGPrint()->GetPrintVScale(dc);
#endif

	//draw the colored rect
	int bwidth = (int) (fScale * m_btnWidth);
	if( bwidth >= (rect->right - rect->left) )
		bwidth = (rect->right - rect->left);

	if( alignment == UGCT_PIECHARTDATARIGHT)
		rect->right = rect->left + bwidth;
	else
		rect->left = rect->right - bwidth;
	int offset = (rect->bottom - rect->top - bwidth)/2 + (int) fScale;
	if(offset <0)
		offset = 0;

	CBrush brush(cell->GetBackColor());
	dc->FillRect(rect,&brush);

	rect->top += offset;
	rect->bottom -= offset;
	rect->left += (int) (2 * fScale);
	rect->right -= (int) (2 * fScale);
	CBrush brush2(cell->GetHBackColor());
	dc->FillRect(rect,&brush2);

	//draw the text in using the default drawing routine
	CopyRect(rect,&origRect);
	if( alignment == UGCT_PIECHARTDATARIGHT)
		rect->left += bwidth;
	else
		rect->right -= bwidth;
	DrawText(dc,rect,0,0,0,cell,selected,current);
}

/****************************************************
GetBestSize
	Returns the best (nominal) size for a cell using
	this cell type, with the given cell properties.
Params:
	dc		- device context to use to calc the size on	
	size	- return the best size in this param
	cell	- pointer to a cell object to use for the calc.
Return:
	<none>
*****************************************************/
void CUGPieChartType::GetBestSize(CDC *dc,CSize *size,CUGCell *cell)
{
	CUGCellType::GetBestSize( dc, size, cell );

	if( cell->GetCellTypeEx()&UGCT_PIECHARTDATA )
	{
		// add the size of the color button to the size of the text
		size->cx += m_btnWidth;
	}
}