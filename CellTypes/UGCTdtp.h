/*************************************************************************
				Class Declaration : CUGCTDateTimePicker
**************************************************************************
	Source file : UGCTdtp.cpp
	Header file : UGCTdtp.h
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Purpose
		Displays a button along with a cell that can be used to activate
		a full featured Date-Time picker
	Details
		Extended Styles
			UGCT_DROPLISTHIDEBUTTON - if set the button that activates the
				date-time picker is not shown until the cell has focus
		Notifictions
			UGCT_CONVERTDATE - see below for full details
			UGCT_DISPLAYMONTHCAL - see below for full details
*************************************************************************/

#ifndef _UGCTdtp_H_
#define _UGCTdtp_H_

#if _MFC_VER>0x0421

#include <afxdtctl.h>

// The notification ID that is sent to CUGCtrl in form of OnCellTypeNotify()
// function. By handling this notification you can customize the format for
// converting date to string. Argument param of this function will point 
// to UGCTCONVERTDATE structure. This structure contains COleDateTime object 
// to be converted and CString object to save the converted data
// 
#define UGCT_CONVERTDATE			200


// The notification ID that is sent to CUGCtrl in form of OnCellTypeNotify()
// function. By handling this notification you can customize the appearance
// of the popup calendar control. Argument param of this function will point 
// to UGCTMONTHCALSETTINGS structure. This structure contains information 
// related to the calendar control settings
#define UGCT_DISPLAYMONTHCAL		201



// UGCTCONVERTDATE is designed to allow a programmer to specify the format for
// converting date to string. Pointer to an object of this structure
// is sent as param argument in CUGCtrl::OnCellTypeNotify() function 
// (notification ID is UGCT_CONVERTDATE). Here is the description of all 
// structure members:
//			date	-	COleDateTime object to convert to string
//			string	-	CString object to save the formated date
//
typedef struct UG_CLASS_DECL _tagUGCTCONVERTDATE
{
	COleDateTime date;
	CString string;
} UGCTCONVERTDATE;
//
/////////////////////////////////////////////////////////////////////////////////////


// UGCTMONTHCALSETTINGS is designed to allow a programmer to customize the 
// appearance of the popup calendar control. Pointer to an object of this 
// structure is sent as param argument in OnCellTypeNotify() function 
// (notification ID is UGCT_DISPLAYMONTHCAL). The elements of this structure 
// will be set to default values. You can change any of them. Here is the
// description of all structure members
//			nFlags			-	0 or any combination of the following flags:
//								MCS_WEEKNUMBERS
//								MCS_NOTODAYCIRCLE
//								MCS_NOTODAY
//								Refer to the SDK documentation for details on 
//								these flags
//			nFirstDayOfWeek	-	number of first day of the week as it will be 
//								displayed in the calendar control (0 - Monday,
//								1 - Tuesday, ...)
//			nScrollRate		-	the number of months the control's contents
//								will be scrolled back/ahead when scroll button 
//								is pressed
//			szDimension		-	cx element of this CSize object specifies the 
//								number of months displayed horizontally, 
//								cy element specifies the number of months displayed 
//								horizontally
//			lf				-	LOGFONT structure that defines the font that will 
//								be used to display the calendar contents
//			clrBk			-	the background color displayed between months
//			clrText			-	the color used to display text within a month
//			clrMonthBk		-	the background color displayed within the month
//			clrTitleText	-	he color used to display text within the calendar's 
//								title
//			clrTitleBk		-	the background color displayed in the calendar's 
//								title
//			clrTrailingText	-	the color used to display header and trailing-day 
//								text. Header and trailing days are the days from the 
//								previous and following months that appear on the 
//								current calendar
//			dateCur			-	date to be selected as current one
//
typedef struct UG_CLASS_DECL _tagUGCTMONTHCALSETTINGS
{
	int nFlags;
	int nFirstDayOfWeek;
	int nScrollRate;
	CSize szDimension;
	LOGFONT lf;
	COLORREF clrBk;
	COLORREF clrText;
	COLORREF clrMonthBk;
	COLORREF clrTitleText;
	COLORREF clrTitleBk;
	COLORREF clrTrailingText;
	COleDateTime dateCur;
} UGCTMONTHCALSETTINGS;
//
/////////////////////////////////////////////////////////////////////////////////////


class UG_CLASS_DECL CUGCTDateTimePicker: public CUGCellType
{
	// width of the dropdown button
	int		m_btnWidth;
	// internal flag. Set to TRUE if dropdown button is currently pressed
	int		m_btnDown;
	// current rectangle for the dropdown button
	RECT	m_btnRect;
	// coordinates of the currently displayed cell
	int		m_btnCol;
	long	m_btnRow;

	// pens used to draw the cell contents
	CPen	m_Darkpen;
	CPen	m_Lightpen;
	CPen	m_Facepen;
	CPen	m_pen;
	CBrush	m_brush;

protected:

	// internal flag. Set to TRUE if popup calendar is currently displayed
	BOOL	m_bActiveMonthCal;


protected:
	// displays month calendar for current cell
	int DisplayMonthCalendar();

	// --- In  :	date	-	COleDateTime object that represents the date 
	//							to be formated into the string
	// --- Out :	string	-	the result of the conversion of the specified
	//							COleDateTime object in the string
	// --- Returns:
	// --- Effect : Converts COleDateTime object into a string. Advanced 
	//				overridable, use your own implementation in order to save
	//				the date that was chosen by a user into the cell
	//				(cell saves data internally as a string)
	virtual void ConvertDateToString(COleDateTime& date, CString& string);

	// --- In  :	string	-	CString object that represents the string 
	//							to be parsed into the COleDateTime object
	// --- Out :	date	-	the result of the conversion of the specified
	//							CString object in the COleDateTime object
	// --- Returns:
	// --- Effect : Converts CString object into a COleDateTime object. Advanced 
	//				overridable, use your own implementation in order to convert
	//				the cell string data into a date (cell saves data internally 
	//				as a string)
	virtual BOOL ConvertStringToDate(CString& string, COleDateTime& date);


	// --- In  :	pRect	-	points to the rectangle that defines the position
	//							of the calendar control in screen coordinates
	// --- Out :	
	// --- Returns:
	// --- Effect : Adjusts the position of the calendar control window before 
	//				displaying it. Advanced overridable, use your own implementation 
	//				in order to position the calendar control window in a specific way
	virtual void AdjustMonthCalPosition(RECT* pRect);
	
public:

	// --- In  :
	// --- Out : 
	// --- Returns:
	// --- Effect : Constructs the object
	CUGCTDateTimePicker();

	// --- In  :
	// --- Out : 
	// --- Returns:
	// --- Effect : Destructs the object
	~CUGCTDateTimePicker();


	//overloaded CUGCellType functions
	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();
	virtual int GetEditArea(RECT *rect);
	virtual BOOL OnLClicked(int col,long row,int updn,RECT *rect,POINT *point);
	virtual BOOL OnDClicked(int col,long row,RECT *rect,POINT *point);
	virtual BOOL OnKeyDown(int col,long row,UINT *vcKey);
	virtual BOOL OnCharDown(int col,long row,UINT *vcKey);
	virtual BOOL OnMouseMove(int col,long row,POINT *point,UINT flags);
	virtual void OnKillFocus(int col,long row,CUGCell *cell);	
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current);
	virtual void GetBestSize(CDC *dc,CSize *size,CUGCell *cell);

	static BOOL SetMonthCalDimension(CMonthCalCtrl* pMonthCal, CSize szDimension,
		CSize szMargins=CSize(0,0));
	static BOOL GetMonthCalReqRect(CMonthCalCtrl* pMonthCal, RECT* pRect, 
		CSize szDimension);
};
#endif	//_MFC_VER>0x0421
#endif  //#ifndef _UGCTdtp_H_