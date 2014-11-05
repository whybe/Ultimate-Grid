/*************************************************************************
				Class Implementation : CUGCTDateTimePicker
**************************************************************************
	Source file : UGCTdtp.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"

#if _MFC_VER>0x0421

#include <winuser.h>
#include "UGCtrl.h"
#include "UGCTdtp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define ID_MAXMONTHCOUNT		12
#define ID_MCHORZGAP			6

/***************************************************
****************************************************/
CUGCTDateTimePicker::CUGCTDateTimePicker()
{
	// init common controls
	INITCOMMONCONTROLSEX initDTCtrl;
	initDTCtrl.dwICC = ICC_DATE_CLASSES;
	initDTCtrl.dwSize = sizeof(initDTCtrl);
	InitCommonControlsEx(&initDTCtrl);

	//set up the variables
	m_pen.CreatePen(PS_SOLID,1,GetSysColor(COLOR_BTNFACE));
	m_brush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
	m_btnWidth = GetSystemMetrics(SM_CXVSCROLL);

	m_btnDown = FALSE;

	m_btnCol = -1;
	m_btnRow = -1;

	m_bActiveMonthCal=FALSE;

	m_canOverLap = FALSE;

	m_Lightpen.CreatePen(PS_SOLID,1,RGB(225,225,225));
	m_Darkpen.CreatePen(PS_SOLID,1,GetSysColor(COLOR_BTNSHADOW));
	m_Facepen.CreatePen(PS_SOLID,1,GetSysColor(COLOR_BTNFACE));
}

/***************************************************
****************************************************/
CUGCTDateTimePicker::~CUGCTDateTimePicker(){
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
LPCTSTR CUGCTDateTimePicker::GetName()
{
	return _T("Date-Time Picker");
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
LPCUGID CUGCTDateTimePicker::GetUGID()
{
	static const UGID ugid = { 0x1667a6a0, 0xf746, 
							0x11d0, 0x9c, 0x7f, 
							0x0, 0x80, 0xc8, 0x3f, 
							0x71, 0x2f };

	return &ugid;
}

/***************************************************
GetEditArea - overloaded CUGCellType::GetEditArea

    **See CUGCellType::OnDraw for more details
	about this function
****************************************************/
int CUGCTDateTimePicker::GetEditArea(RECT *rect)
{
	rect->right -=(m_btnWidth+1);

	return TRUE;
}
/***************************************************
OnDClicked - overloaded CUGCellType::OnDClicked

    **See CUGCellType::OnDClicked for more details
	about this function
****************************************************/
BOOL CUGCTDateTimePicker::OnDClicked(int col,long row,RECT *rect,POINT *point){

	return OnLClicked(col,row,1,rect,point);
}
/***************************************************
OnLClicked - overloaded CUGCellType::OnLClicked

    **See CUGCellType::OnLClicked for more details
	about this function
****************************************************/
BOOL CUGCTDateTimePicker::OnLClicked(int col,long row,int updn,
									 RECT *rect,POINT *point)
{
	// v7.2 - update 01 - make sure that the read only cells do not
	// show calendar - submitted by mhorowit
	CUGCell cell;
	m_ctrl->GetCellIndirect(col,row,&cell);

	if ( cell.GetReadOnly() == TRUE )
		return UG_SUCCESS;

	if(updn)
	{
		if(point->x > (rect->right - m_btnWidth))
		{			
			//copy the droplist button co-ords
			CopyRect(&m_btnRect,rect);
			m_btnRect.left = rect->right - m_btnWidth;
		
			//redraw the button
			m_btnDown = TRUE;
			m_btnCol = col;
			m_btnRow = row;
			m_ctrl->RedrawCell(m_btnCol,m_btnRow);

			//start the drop list
			DisplayMonthCalendar();
			return FALSE;
		}
		else if(m_btnCol ==-2)
		{
			m_btnCol = -1;
			m_btnRow = -1;			
			return FALSE;
		}
	}
	else if(m_btnDown)
	{		
		m_btnDown = FALSE;
		m_ctrl->RedrawCell(col,row);
		return TRUE;
	}

	return FALSE;
}
/***************************************************
OnMouseMove - overloaded CUGCellType::OnMouseMove

    **See CUGCellType::OnMouseMove for more details
	about this function
****************************************************/
BOOL CUGCTDateTimePicker::OnMouseMove(int col,long row,POINT *point,UINT flags){

	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);

	if((flags&MK_LBUTTON) == FALSE)
		return TRUE;

	if(m_bActiveMonthCal)
		return TRUE;

	if(point->x >= m_btnRect.left && point->x <= m_btnRect.right){
		if(point->y >= m_btnRect.top && point->y <= m_btnRect.bottom){
			if(!m_btnDown){
				m_btnDown = TRUE;
				m_ctrl->RedrawCell(m_btnCol,m_btnRow);
			}
		}
		else if(m_btnDown){
			m_btnDown = FALSE;
			m_ctrl->RedrawCell(m_btnCol,m_btnRow);
		}
	}
	else if(m_btnDown){
		m_btnDown = FALSE;
		m_ctrl->RedrawCell(m_btnCol,m_btnRow);
	}

	return FALSE;
}
/***************************************************
OnKillFocus - overloaded CUGCellType::OnKillFocus

    **See CUGCellType::OnKillFocus for more details
	about this function
****************************************************/
void CUGCTDateTimePicker::OnKillFocus(int col,long row,CUGCell *cell){

	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(cell);

	m_btnCol = -1;
	m_btnRow = -1;			
}
/***************************************************
OnKeyDown - overloaded CUGCellType::OnKeyDown

    **See CUGCellType::OnKeyDown for more details
	about this function
****************************************************/
BOOL CUGCTDateTimePicker::OnKeyDown(int col,long row,UINT *vcKey){

	// v7.2 - update 01 - make sure that the read only cells do not
	// show calendar - submitted by mhorowit
	CUGCell cell;
	m_ctrl->GetCellIndirect(col,row,&cell);

	if ( cell.GetReadOnly() == TRUE )
		return UG_SUCCESS;

	if(*vcKey==VK_RETURN)
	{
		DisplayMonthCalendar();
		*vcKey =0;
		return TRUE;
	}
	if(*vcKey==VK_DOWN)
	{
		if(GetKeyState(VK_CONTROL) <0)
		{
			DisplayMonthCalendar();
			*vcKey =0;
			return TRUE;
		}
	}
	return FALSE;
}
/***************************************************
OnCharDown - overloaded CUGCellType::OnCharDown

    **See CUGCellType::OnCharDown for more details
	about this function
****************************************************/
BOOL CUGCTDateTimePicker::OnCharDown(int col,long row,UINT *vcKey){

	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);

	if(*vcKey==VK_RETURN)
		return TRUE;
	if(*vcKey==VK_DOWN)
		return TRUE;

	return FALSE;
}


/***************************************************
OnDraw - overloaded CUGCellType::OnDraw

    **See CUGCellType::OnDraw for more details
	about this function
****************************************************/
void CUGCTDateTimePicker::OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,
								 int selected,int current)
{
	if (!m_drawThemesSet)
		m_useThemes = cell->UseThemes();

	int left = rect->left;
	RECT rectout;
	CPen * oldpen;

	int style = 0;
	if(cell->IsPropertySet(UGCELL_CELLTYPEEX_SET))
		style = cell->GetCellTypeEx();

	//if the cell is not current and hide button is on
	//then dont draw the button
	if(style&UGCT_DROPLISTHIDEBUTTON && !current)
	{
		int nOldTextColor=cell->GetTextColor();
		if(cell->GetParam())
			cell->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));

		CUGCellType::OnDraw(dc,rect,col,row,cell,selected,current);
	
		if(cell->GetParam())
			cell->SetTextColor(nOldTextColor);

		return;
	}

	DrawBorder(dc,rect,rect,cell);

	//draw the button side of the the cell
	rect->left = rect->right - m_btnWidth;
	
	//draw the 3D border
	if(m_btnDown && current){
		cell->SetBorder(UG_BDR_RECESSED);
		DrawBorder(dc,rect,&rectout,cell);
	}
	else{
		cell->SetBorder(UG_BDR_RAISED);
		DrawBorder(dc,rect,&rectout,cell);
	}

	if (!m_useThemes || !UGXPThemes::DrawBackground(NULL, *dc, XPCellTypeData, UGXPThemes::GetState(selected > 0, current > 0), rect, NULL) ||
		!UGXPThemes::DrawBackground(NULL, *dc, XPCellTypeCombo, UGXPThemes::GetState(selected > 0, current > 0), rect, NULL))
	{
		//fill the border in
		dc->FillRect(&rectout,&m_brush);

		//make a line to separate the border from the rest ofthe cell
		oldpen = (CPen *)dc->SelectObject((CPen *)&m_pen);
		dc->MoveTo(rect->left-1,rect->top);
		dc->LineTo(rect->left-1,rect->bottom);

		//draw the down arrow
		int x= ((m_btnWidth-5)/2) + rect->left;
		int y = ((rect->bottom - rect->top -3)/2) + rect->top;
		dc->SelectObject((CPen*)CPen::FromHandle((HPEN)GetStockObject(BLACK_PEN)));
		dc->MoveTo(x,y);
		dc->LineTo(x+5,y);
		dc->MoveTo(x+1,y+1);
		dc->LineTo(x+4,y+1);
		dc->MoveTo(x+2,y+2);
		dc->LineTo(x+2,y+1);


		dc->SelectObject(oldpen);
	}
	//draw the check box
	rect->left = left;
	rect->right -=(m_btnWidth+1);

	int nOldTextColor=cell->GetTextColor();
	if(cell->GetParam() && cell->GetReadOnly())
		cell->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));

	CUGCellType::DrawText(dc,rect,0,col,row,cell,selected,current);
	
	if(cell->GetParam())
		cell->SetTextColor(nOldTextColor);
}

/***************************************************
DisplayMonthCalendar
	Displays the pop-up date-time calendar next to
	the current cell.
	If a date is selected a cell type notification
	is sent (UGCT_CONVERTDATE) then the date is updated
Params
	none
Return
	UG_SUCCESS - success
	UG_ERROR - error
****************************************************/
int CUGCTDateTimePicker::DisplayMonthCalendar()
{
	CUGCell cell;
	m_ctrl->GetCellIndirect(m_ctrl->GetCurrentCol(),m_ctrl->GetCurrentRow(),&cell);

	CString sText=cell.GetText();
	COleDateTime date;
	ConvertStringToDate(sText,date);

	if(cell.GetParam())
	{
		cell.SetParam(FALSE);
		m_ctrl->SetCell(m_ctrl->GetCurrentCol(),m_ctrl->GetCurrentRow(),&cell);
		m_ctrl->RedrawCell(m_ctrl->GetCurrentCol(),m_ctrl->GetCurrentRow());
	}

	CRect rectCell;
	m_ctrl->GetCellRect(m_ctrl->GetCurrentCol(),m_ctrl->GetCurrentRow(),&rectCell);
	m_ctrl->m_CUGGrid->ClientToScreen(rectCell);
	
	CMonthCalCtrl wndMonthCal;
	if(!wndMonthCal.CreateEx(WS_EX_DLGMODALFRAME,MONTHCAL_CLASS,_T(""),WS_POPUP,
		CRect(rectCell.left,rectCell.bottom+1,rectCell.left,rectCell.bottom+1),
		m_ctrl,0,NULL))
	{
		return UG_ERROR;
	}

	// populate structure with default values
	UGCTMONTHCALSETTINGS mcs;
	mcs.clrBk=wndMonthCal.GetColor(MCSC_BACKGROUND);
	mcs.clrText=wndMonthCal.GetColor(MCSC_TEXT);
	mcs.clrMonthBk=wndMonthCal.GetColor(MCSC_MONTHBK);
	mcs.clrTitleText=wndMonthCal.GetColor(MCSC_TITLETEXT);
	mcs.clrTitleBk=wndMonthCal.GetColor(MCSC_TITLEBK);
	mcs.clrTrailingText=wndMonthCal.GetColor(MCSC_TRAILINGTEXT);
	mcs.nFirstDayOfWeek=wndMonthCal.GetFirstDayOfWeek();
	mcs.nFlags=wndMonthCal.GetStyle()&(MCS_WEEKNUMBERS|MCS_NOTODAYCIRCLE|MCS_NOTODAY);
	mcs.nScrollRate=wndMonthCal.GetMonthDelta();
	mcs.szDimension=CSize(1,1);
	mcs.dateCur=date;
	CFont* pFont=wndMonthCal.GetFont();
	ASSERT(pFont!=NULL);
	VERIFY(pFont->GetLogFont(&mcs.lf));

	// check if this data is wanted to be customized
	OnCellTypeNotify(m_ID,m_ctrl->GetCurrentCol(),
		m_ctrl->GetCurrentRow(),UGCT_DISPLAYMONTHCAL,(LPARAM)&mcs);
	wndMonthCal.SetColor(MCSC_BACKGROUND,mcs.clrBk);
	wndMonthCal.SetColor(MCSC_TEXT,mcs.clrText);
	wndMonthCal.SetColor(MCSC_MONTHBK,mcs.clrMonthBk);
	wndMonthCal.SetColor(MCSC_TITLETEXT,mcs.clrTitleText);
	wndMonthCal.SetColor(MCSC_TITLEBK,mcs.clrTitleBk);
	wndMonthCal.SetColor(MCSC_TRAILINGTEXT,mcs.clrTrailingText);
	wndMonthCal.SetFirstDayOfWeek(mcs.nFirstDayOfWeek);
	wndMonthCal.
		ModifyStyle((MCS_WEEKNUMBERS|MCS_NOTODAYCIRCLE|MCS_NOTODAY),mcs.nFlags);
	wndMonthCal.SetMonthDelta(mcs.nScrollRate);
	CFont font;
	VERIFY(font.CreateFontIndirect(&mcs.lf));
	wndMonthCal.SetFont(&font);

	SetMonthCalDimension(&wndMonthCal,mcs.szDimension);
	CRect rect;
	wndMonthCal.GetWindowRect(rect);
	AdjustMonthCalPosition(rect);
	wndMonthCal.SetWindowPos(NULL,rect.left,rect.top,rect.Width(),rect.Height(),
		SWP_NOZORDER);

	wndMonthCal.SetCurSel(mcs.dateCur);

	ReleaseCapture();
	wndMonthCal.ShowWindow(SW_SHOWNA);
	wndMonthCal.SetFocus();

	m_bActiveMonthCal=TRUE;

	MSG lastMsg;
	BOOL bRouteLastMessage=FALSE;
	// init message loop
	// nState = 0 - control is active
	// nState = 1 - user selected some date
	// nState = 2 - user left control without selecting any date
	int nState=0;
	while(nState==0)
	{
		MSG msg;
		VERIFY(::GetMessage(&msg, NULL, 0, 0));

		if(msg.message==WM_LBUTTONDOWN || msg.message==WM_RBUTTONDOWN ||
			msg.message==WM_MBUTTONDOWN || msg.message==WM_NCLBUTTONDOWN ||
			msg.message==WM_NCRBUTTONDOWN || msg.message==WM_NCMBUTTONDOWN)
		{
			if(msg.hwnd!=wndMonthCal.GetSafeHwnd())
			{
				nState=2;
				lastMsg=msg;
				bRouteLastMessage=TRUE;
				break;
			}
		}

		if(msg.message==WM_KEYDOWN && msg.hwnd==wndMonthCal.GetSafeHwnd() &&
			(int)msg.wParam==VK_ESCAPE)
		{
			nState=2;
		}

		if(msg.message==WM_LBUTTONUP && msg.hwnd==wndMonthCal.GetSafeHwnd())
		{
			POINTS points=MAKEPOINTS(msg.lParam);	
			CPoint pt(points.x,points.y);
			MCHITTESTINFO mcHitTestInfo={ sizeof(MCHITTESTINFO) };
			mcHitTestInfo.pt=pt;
			wndMonthCal.HitTest(&mcHitTestInfo);
			if(mcHitTestInfo.uHit==MCHT_CALENDARDATE || 
				mcHitTestInfo.uHit==MCHT_CALENDARDATENEXT || 
				mcHitTestInfo.uHit==MCHT_CALENDARDATEPREV ||
				mcHitTestInfo.uHit==MCHT_TODAYLINK)
			{
				nState=1;
				if(mcHitTestInfo.uHit!=MCHT_TODAYLINK)
				{
					date.SetDateTime(mcHitTestInfo.st.wYear,mcHitTestInfo.st.wMonth,
						mcHitTestInfo.st.wDay,mcHitTestInfo.st.wHour,
						mcHitTestInfo.st.wMinute,mcHitTestInfo.st.wSecond);
				}
				else
				{
					wndMonthCal.GetToday(date);
				}
			}
		}

		if(msg.message==WM_KEYDOWN && msg.hwnd==wndMonthCal.GetSafeHwnd() &&
			(int)msg.wParam==VK_RETURN)
		{
			nState=1;
		}

		::DispatchMessage(&msg);
	}

	ASSERT(nState==1 || nState==2);

	m_bActiveMonthCal=FALSE;
	m_btnDown = FALSE;

	if( nState==1 && cell.GetReadOnly() != TRUE )
	{
		UGCTCONVERTDATE cd;
		cd.date=date;
		ConvertDateToString(date,cd.string);
		OnCellTypeNotify(m_ID,m_ctrl->GetCurrentCol(),
			m_ctrl->GetCurrentRow(),UGCT_CONVERTDATE,(LPARAM)&cd);
		cell.SetText(cd.string);
		m_ctrl->SetCell(m_ctrl->GetCurrentCol(),m_ctrl->GetCurrentRow(),&cell);
		m_ctrl->RedrawCell(m_ctrl->GetCurrentCol(),m_ctrl->GetCurrentRow());
	}

	VERIFY(wndMonthCal.DestroyWindow());
	m_ctrl->m_CUGGrid->SetFocus();
	m_ctrl->RedrawAll();

	if(bRouteLastMessage)
		::DispatchMessage(&lastMsg);

	return UG_SUCCESS;
}

/***************************************************
SetMonthCalDimension
	This function is used internally to set the
	size of the pop-up calendar
****************************************************/
BOOL CUGCTDateTimePicker::SetMonthCalDimension(CMonthCalCtrl* pMonthCal, 
											   CSize szDimension,
											   CSize szMargins/*=CSize(0,0)*/) {
	ASSERT(pMonthCal!=NULL);
	ASSERT(szDimension.cx>0 && szDimension.cy>0);

	if(szDimension.cx*szDimension.cy>ID_MAXMONTHCOUNT)
	{
		TRACE(_T("CUGCTDateTimePicker::SetMonthCalDimension: The maximum total number of displayed months is %d\n"),ID_MAXMONTHCOUNT);
		return FALSE;
	}

	CRect rect;
	pMonthCal->GetWindowRect(rect);
	CPoint ptTopLeft=rect.TopLeft();

	BOOL bResult=FALSE;
	if(GetMonthCalReqRect(pMonthCal,rect,szDimension))
	{
		rect.right+=szMargins.cx*2;
		rect.bottom+=szMargins.cy*2;
		pMonthCal->CalcWindowRect(rect);
		if(pMonthCal->SetWindowPos(&CWnd::wndTop,ptTopLeft.x,ptTopLeft.y,rect.Width(),
			rect.Height(),SWP_NOACTIVATE))
		{
			bResult=TRUE;
		}
	}

	return bResult;
}

/***************************************************
GetMonthCalReqRect
	This function is used internally to set the
	size of the pop-up calendar
****************************************************/
BOOL CUGCTDateTimePicker::GetMonthCalReqRect(CMonthCalCtrl* pMonthCal, RECT* pRect, 
											 CSize szDimension)
{
	ASSERT(pMonthCal!=NULL);
	ASSERT(szDimension.cx>0 && szDimension.cy>0);

	CMonthCalCtrl ctlDummy;
	if(ctlDummy.Create((pMonthCal->GetStyle()&~(MCS_NOTODAY|WS_POPUP)),
		CRect(0,0,0,0),pMonthCal,100) && ctlDummy.GetMinReqRect(pRect))
	{
		pRect->right*=szDimension.cx;
		pRect->right+=ID_MCHORZGAP*(szDimension.cx-1);
		pRect->bottom*=szDimension.cy;

		CFont* pFont=pMonthCal->GetFont();
		ASSERT(pFont!=NULL);
		LOGFONT lf;
		VERIFY(pFont->GetLogFont(&lf));
		pRect->bottom-=abs(lf.lfHeight)*(szDimension.cy-1);

		pMonthCal->CalcWindowRect(pRect);
		pRect->right-=pRect->left;
		pRect->bottom-=pRect->top;
		pRect->left=0;
		pRect->top=0;

		return TRUE;
	}
	else
		return FALSE;
}

/***************************************************
ConvertStringToDate
	Converts the given date into a string value
Params
	string - [out] string vlue of the given date
	date - date to convert into a string
return
	none
****************************************************/
void CUGCTDateTimePicker::ConvertDateToString(COleDateTime& date, CString& string)
{
	string=date.Format(VAR_DATEVALUEONLY);
}

/***************************************************
ConvertStringToDate
	Converts the given string into a date
Params
	string - string to convert
	date - [out] converted date
return
	TRUE if successful
	FALSE upon failure
****************************************************/
BOOL CUGCTDateTimePicker::ConvertStringToDate(CString& string, COleDateTime& date)
{
	return date.ParseDateTime(string,VAR_DATEVALUEONLY);
}

/***************************************************
AdjustMonthCalPosition
	This function is used internally to set the
	position of the pop-up calendar
****************************************************/
void CUGCTDateTimePicker::AdjustMonthCalPosition(RECT* pRect)
{
	CRect rectCell;
	m_ctrl->GetCellRect(m_ctrl->GetCurrentCol(),m_ctrl->GetCurrentRow(),rectCell);

	BOOL bTopMostParent=(m_ctrl->GetTopLevelParent()!=NULL &&
		m_ctrl->GetTopLevelParent()->GetExStyle()&WS_EX_TOPMOST);

	CRect rectDisplay;
#if(WINVER >= 0x0500)
	// if we use Win 98/NT5 we have to take into account multiple monitors
	OSVERSIONINFO osvi={ sizeof(OSVERSIONINFO) };
	VERIFY(::GetVersionEx(&osvi)!=0);
	if(osvi.dwMajorVersion>4 || 
		(osvi.dwMajorVersion==4 && osvi.dwMinorVersion>0))
	{
        CPoint pt;
        ::GetCursorPos(&pt);
		HMONITOR hMonitor=::MonitorFromPoint(pt,MONITOR_DEFAULTTONEAREST);
		ASSERT(hMonitor!=NULL);
		MONITORINFO monitorInfo={ sizeof(MONITORINFO) };
		VERIFY(::GetMonitorInfo(hMonitor,&monitorInfo));
		if(bTopMostParent)
			rectDisplay=monitorInfo.rcMonitor;
		else
			rectDisplay=monitorInfo.rcWork;
	}
	else
	{
#endif
		if(bTopMostParent)
			CWnd::GetDesktopWindow()->GetWindowRect(rectDisplay);
		else
			::SystemParametersInfo(SPI_GETWORKAREA,NULL,&rectDisplay,NULL);
#if(WINVER >= 0x0500)
	}
#endif

	CRect rectIntersect;
	if(rectIntersect.IntersectRect(rectDisplay,pRect) && 
		rectIntersect==*pRect)
	{
		return;
	}

	if(pRect->right>rectDisplay.right)
	{
		pRect->left-=pRect->right-rectDisplay.right;
		pRect->right=rectDisplay.right;
	}
	if(pRect->left<rectDisplay.left)
	{
		pRect->right+=rectDisplay.left-pRect->left;
		pRect->left=rectDisplay.left;
	}
	if(pRect->bottom>rectDisplay.bottom)
	{
		pRect->top-=pRect->bottom-rectDisplay.bottom;
		pRect->bottom=rectDisplay.bottom;
	}
	if(pRect->top<rectDisplay.top)
	{
		pRect->bottom+=rectDisplay.top-pRect->top;
		pRect->top=rectDisplay.top;
	}

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
void CUGCTDateTimePicker::GetBestSize(CDC *dc,CSize *size,CUGCell *cell)
{
	CUGCellType::GetBestSize( dc, size, cell );
	// in the case of the drop list celltype we will take the normal
	// width of the text selected, and if the drop button is vible,
	// we will increate the width by the width of the button.
	if (!( cell->GetCellTypeEx()&UGCT_DROPLISTHIDEBUTTON ))
	{
		size->cx += m_btnWidth;
	}
}

#endif	//	_MFC_VER>0x0421
