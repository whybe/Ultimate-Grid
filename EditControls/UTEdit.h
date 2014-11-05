// ==========================================================================
//								Class Implementation : 
//				      CUTEdit & CUTNumericEdit & CUTCurrencyEdit
// ==========================================================================

// Header file : UTEdit.h

//// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

/*

DESCRIPTION


CUTEdit

CUTEdit is CEdit derived class that extends the functionality of standard 
edit control.

CUTEdit allows you to easily set/change the following control's features:

	1)	text color
	2)	background color 
	3)	tooltip text
	4)	mask that defines literals (uneditable symbols)


It's really easy to use CUTEdit class. You just work with it as with 
standard CEdit class plus you can call the following functions in order
to exploit new features:


	void SetTextColor(COLORREF clrText, BOOL bRedraw=TRUE)
	COLORREF GetTextColor() const

	void SetBkColor(COLORREF clrBack, BOOL bRedraw=TRUE)
	COLORREF GetBkColor() const

	BOOL SetToolTipText(LPCTSTR sText)
	CString GetToolTipText() const

	BOOL SetMask(LPCTSTR lpszMask)
	CString GetMask() const


Refer to the class function reference for details on all public functions.

The most interesting new feature is the ability to set mask of literals 
to the control. Mask should be specified as "LeftLiterals#RightLiterals"
where '#' stands for editable contents (input data) and 'LeftLiterals'
defines the uneditable text that will be displayed to the left from editable 
text and 'RightLiterals' defines the text that will be displayed to the right 
from editable text.
E.g. you can define mask as "Phone: #".

NOTE.	If you have to use '#' symbol as literal then you have to use '##' instead.

In order to retrieve only the data that was typed in you can use the 
following function:

	GetInputData()


Also CUTEdit control internally provide support for two different edit modes:
insert (the default) and overtype ones. When user presses 'Ins' key the editing 
modes are switched. Programmatically you can change edit mode using 
SetInsertMode() function. in order to retrieve the flag that specifies current 
edit mode you can use GetInsertMode() function.


------------------------------------------------------------------------


CUTNumericEdit

CUTNumericEdit is CUTEdit derived class that was designed specifically to 
support editing of numeric data. While all CUTEdit features are available in
CUTNumericEdit class there are a lot of additional features introduced
in this class that primarily have to do with the numeric data editing and 
displaying rules.

The following features are available:

	1)	max number of decimal digits that might be typed in
		(indefinite number is one of the options)
	2)	symbol that represent decimal separator
	3)	number of fractional digits displayed (value of zero
		means there is no fractional part)
	4)	number of decimal digits divided in groups
	5)	symbol that represent group separator 
	6)	flag that specifies if leading zero must be displayed or not
	7)	text color for negative value
	8)	format of numeric data for positive value
	9)	format of numeric data for negative value


Initially CUTNumericEdit control retrieves default locale settings 
for above described settings, but all of them can be changed at run-time 
using public functions defined in CUTNumericEdit class (refer to class
function reference for details).

We would like to mention that format for positive and negative values 
must be defined as "Literals1.1Literals", where "1.1" stands for numeric 
value and "Literals" could consist of any symbol(s). E.g. if format 
"(1.1)" had been specified for positive value then value -5.26 would 
have been displayed as "(5.26)"



------------------------------------------------------------------------


CUTCurrencyEdit

CUTCurrencyEdit is CUTNumericEdit derived class that was designed specifically to 
support editing of currency data. Currency is numeric data but it is also 
required to display currency name in the control. So CUTCurrencyEdit class
merely add following two functions in which you can set or retrieve currency name 

	SetCurrencyName()
	GetCurrencyName()

By default we use default locale to get currency name.

We have to notr that format for positive and negative values for CUTCurrencyEdit 
must include the placeholder for currency name as one of literals. 
We use '$' symbol as universal currency placeholder.
E.g. if format "1.1$-" had been specified for negative value then value -5.26 
would have been displayed as "5.26$-"



------------------------------------------------------------------------




Refer to ExtendedEditControls sample that can be found in 
.\Samples\gui\ExtendedEditControls subdirectory of your Ultimate Toolbox 
directory for demo that shows the features of above described classes.

Dependencies:

	#include "UGEdit.h"


Source code files:

	"UGEdit.cpp"



*/
                         
#ifndef _UTEDIT_H__
#define _UTEDIT_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ugctrl.h"
#include <afxcmn.h>

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#define __AFXTEMPL_H__
#endif


// identificator for tool tip control
#ifndef ID_UTEDIT_TOOLTIP
#define ID_UTEDIT_TOOLTIP		0x00000001
#endif


const TCHAR UTEDITABLETEXT_SYMBOL=_T('#');
const TCHAR UTCURRENCY_SYMBOL=_T('$');
const CString UTNUMERICVALUE_PLACEHOLDER(_T("1.1"));
const int UTNUMERICVALUE_PLACEHOLDER_LENGTH = UTNUMERICVALUE_PLACEHOLDER.GetLength();

/////////////////////////////////////////////////////////////////////////////
// CUTEdit window

class UG_CLASS_DECL CUTEdit : public CUGEditBase
{
	DECLARE_DYNAMIC(CUTEdit)
// Construction
public:



	inline COLORREF GetReadOnlyFontColor()
	{	return m_clrReadOnlyFont;	}

	inline void SetReadOnlyFontColor(COLORREF clrReadOnlyFont)
	{	m_clrReadOnlyFont=clrReadOnlyFont;	}

	inline COLORREF GetReadOnlyBkColor()
		{	return m_clrReadOnlyBack;	}

	inline void SetReadOnlyBkColor(COLORREF clrReadOnlyBk)
		{	m_clrReadOnlyBack=clrReadOnlyBk; }

	// --- In  :
	// --- Out : 
	// --- Returns:
	// --- Effect : Constructs the object
	CUTEdit();


	// --- In  :	dwStyle		-	Specifies the edit control's style. Apply any 
	//								combination of edit control styles to the control. 
	//								See the CEdit:Create function for details.
	//				rect		-	Specifies the edit control's size and position. 
	//								It can be either a CRect object or a RECT structure.
	//				pParentWnd	-	Specifies the edit control's parent window, 
	//								usually a CDialog. It must not be NULL.
	//				nID			-	Specifies the edit control's ID.
	// --- Out : 
	// --- Returns: TRUE if successful or FALSE otherwise
	// --- Effect : Create the control
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);


	// --- In  :	clrText	-	color of text
	//				bRedraw -	if TRUE then control will be redrawn 
	// --- Out : 
	// --- Returns:
	// --- Effect : sets the color that CUTEdit object uses to draw text
	void SetTextColor(COLORREF clrText, BOOL bRedraw=TRUE);

	// --- In  :
	// --- Out : 
	// --- Returns: text color
	// --- Effect :	gets the color that CUTEdit object uses to draw text
	inline COLORREF GetTextColor() const { return m_clrText; }


	// --- In  :	clrBack	-	background color
	//				bRedraw -	if TRUE then control will be redrawn 
	// --- Out : 
	// --- Returns:
	// --- Effect : sets the color that CUTEdit object uses to draw its background
	void SetBkColor(COLORREF clrBack, BOOL bRedraw=TRUE);

	// --- In  :
	// --- Out : 
	// --- Returns: background color
	// --- Effect :	gets the color that CUTEdit object uses to draw text
	inline COLORREF GetBkColor() const { return m_clrBack; }


	// Tooltips
	// 

	// --- In  :	sText	-	text to be shown in the tooltip window
	// --- Out : 
	// --- Returns: TRUE if tooltip text was successfully set
	// --- Effect :	Sets the tooltip text.
	BOOL SetToolTipText(LPCTSTR sText);

	// --- In  :	
	// --- Out : 
	// --- Returns:	tooltip text
	// --- Effect :	retrieves tooltip text
	inline CString GetToolTipText() const { return m_sToolTipText; }

	// --- In  :	
	// --- Out : 
	// --- Returns:	pointer to the internal tooltip control
	// --- Effect :	retrieves pointer to the internal tooltip control
	inline CToolTipCtrl* GetToolTip() { return &m_ttc; }


	// Mask
	//

	// --- In  :	lpszMask-	mask to be used while displaying control contents.
	//							Mask should be specified as "LeftLiterals#RightLiterals"
	//							where # stands for editable contents and LeftLiterals
	//							defines the text that will be displayed from the left 
	//							side of editable text and RightLiterals
	//							defines the text that will be displayed from the right 
	//							side of editable text, e.g. "Phone: #".
	//							if you have to use '#' symbol as literal then you 
	//							have to use '##' instead.
	// --- Out : 
	// --- Returns: TRUE if mask was successfully set
	// --- Effect :	Sets the control's mask. By default we use "#" mask.
	BOOL SetMask(LPCTSTR lpszMask);

	// --- In  :	
	// --- Out : 
	// --- Returns: mask string
	// --- Effect :	Retrieves the control's mask.
	inline CString GetMask() const { return m_sMask; }


	// --- In     :
	// --- Out    :
	// --- Returns: The fully formatted mask with all input data. 
	// --- Effect : Retrieves the text that will be displayed (combination of 
	//				mask and input data)
	CString GetFormattedText() const ;


	// --- In     :
	// --- Out    :
	// --- Returns: text without mask
	// --- Effect : retrieves text without mask
	virtual CString GetInputData() const;
	
	// --- In     : pszInputData -	Each character is entered into the control as 
	//								if the user typed it in. 
	//            : nBeginPos    -	Begin position for inserting or overwriting the 
	//								input data depending on current state of 
	//								insert mode. 
	// --- Out    :
	// --- Returns: TRUE if some data was inserted. 
	// --- Effect : Use to programmatically insert pszInputData into the edit control. 
	//            : The mask is applied to the input data. 
	virtual BOOL SetInputData(LPCTSTR pszInputData, int nBeginPos=0);


	// --- In     : bOnlyInput - set to TRUE to clear just the input data. 
	// --- Out    :
	// --- Returns:
	// --- Effect : Clears the contents of the edit. Depending on the 
	//				bOnlyInput clears all data (mask + input) or only input data
	virtual void EmptyData(BOOL bOnlyInput=FALSE);


	// --- In     :	bInsertMode	-	if TRUE then typing mode is insert mode 
	//								(the default one), otherwise overwriting mode
	// --- Out    :
	// --- Returns:
	// --- Effect : Changes the typing mode. 
	void SetInsertMode(BOOL bInsertMode);

	// --- In     :
	// --- Out    :
	// --- Returns: The insert mode. If TRUE then edit is in insert mode
	//				(the default one), if FALSE then edit is in overwriting mode
	// --- Effect : Retrieves typing mode
	BOOL GetInsertMode() const;
	

	// --- In     :	nRealPos	-	real position in edit control (taking into account 
	//								all symbols including literals)
	// --- Out    :
	// --- Returns: corresponding logical position (taking into account only 
	//				non-literals)
	// --- Effect : converts real position within masked edit control to corresponding
	//				logical one
	int RPtoLP(int nRealPos) const;
	
	// --- In     :	nLogicalPos	-	logical position in edit control (taking into 
	//								account only non-literals)
	// --- Out    :
	// --- Returns: corresponding real position (taking into account all symbols 
	//				including literals)
	// --- Effect : convert logical position within masked edit control to 
	//				corresponding real one
	int LPtoRP(int nLogicalPos) const;


	// --- In     :
	// --- Out    :
	// --- Returns:
	// --- Effect : This function gets called when a user error occurs. 
	virtual void ValidationError();

	
	// --- In     :	bHighlightOnSetFocus	-	flag that specifies the behaviour 
	//											of the control when focus is being 
	//											set to it
	// --- Out    :
	// --- Returns: 
	// --- Effect : sets the flag that specifies the behaviour of the 
	//				control when focus is being set to it. Refer to the 
	//				GetHighlightOnSetFocus() function description for details 
	//				on this flag
	inline void SetHighlightOnSetFocus(BOOL bHighlightOnSetFocus) 
	{ 
		m_bHighlightOnSetFocus=bHighlightOnSetFocus; 
	}

	// --- In     :
	// --- Out    :
	// --- Returns: flag that specifies the behaviour of the control when 
	//				focus is being set to it
	// --- Effect : retrieves the flag that specifies the behaviour of the 
	//				control when focus is being set to it. The default 
	//				behaviour of the standard edit control is to select all 
	//				text and cursor is being set at the end of the text. 
	//				CUTEdit handles this event in the following way: it sets 
	//				cursor at the first symbol that can be modified without 
	//				selecting any text. Turning this flag on and off you can 
	//				specify whether you would like to use the standard 
	//				functionality or new one (by default we use the new 
	//				functionality is when the text is not selected, i.e. the flag 
	//				is set to FALSE)
	inline BOOL GetHighlightOnSetFocus() const { return m_bHighlightOnSetFocus; }


// Internal Member functions ------------------------------------------------
protected:
	// virtual function that is called when control is initialized
	// and every time system settings has been changed
	virtual BOOL GetLocaleSettings() { return TRUE; }

	// initialize edit control (create tooltip control. etc.). Override this function
	// in order to initialize any data in your derived class
	virtual BOOL InitControl();

	// function is called every time the contents of the control has been changed.
	// In derived class this function can be overridden in order to retrieve
	virtual int ValidateInput() { return 0; }

	// function is called every time mask info for edit control has to be cleaned up
	virtual void DeleteContents();
	
	// checks specified real position as position at which valid input data is located
	virtual BOOL IsInputData(int nPosition) const;
	// checks specified real position as position at which valid input data can be typed
	virtual BOOL IsInputPosition(int nPosition) const;

	// retrieves string that represents left literals
	CString GetLeftLiterals() const;
	// retrieves string that represents right literals
	CString GetRightLiterals() const;

	// called every time when user is deleting symbol or range of symbols
	virtual int DeleteRange(int& nSelectionStart, int& nSelectionEnd, BOOL bInsert = FALSE);
	// called every time user typed new symbol (insert mode is on)
	virtual int InsertAt(int nSelectionStart, TCHAR chNewChar);
	// called every time user typed new symbol (overwrite mode is on)
	virtual int SetAt(int nSelectionStart, TCHAR chNewChar);
	// retrieves next location starting from the specified one (and including it)
	// at which new symbol can be typed in
	virtual int GetNextInputLocation(int nSelectionStart);
	// retrieves previous location starting from the specified one (and including it)
	// at which new symbol can be typed in
	virtual int GetPreviousInputLocation(int nSelectionStart);

	virtual void UpdateMask() {};

	// redraw control's contents and move caret to the specified position
	void Update(int nSelectionStart=0);  // UpdateInsertionPoint is automatic. 
	// move caret to the specified position. Location will be adjust to right 
	// to guarantee to be valid input position
	void UpdateInsertionPointForward (int nSelectionStart);
	// move caret to the specified position. Location will be adjust to left 
	// to guarantee to be valid input position
	void UpdateInsertionPointBackward(int nSelectionStart);

	BOOL NotifyParent(UINT nNotificationID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUTEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

protected:
	// color of text
	COLORREF m_clrText;	
	// background color
	COLORREF m_clrBack;	

	// control's font
	CFont m_font;

	// mask for control, by default use "#"
	CString m_sMask;
	// array of symbols that represents left literals
	CArray<TCHAR,TCHAR> m_arrLeftLiterals;
	// array of symbols that represents right literals
	CArray<TCHAR,TCHAR> m_arrRightLiterals;
	// array of symbols that represents input data
	CArray<TCHAR,TCHAR> m_arrInputData;

	// flag that specifies if control is insert or overwrite edit mode
	BOOL m_bInsertMode;

	// text of the tooltip
	CString m_sToolTipText;
	// tooltip control
	CToolTipCtrl m_ttc;

	// internal variables for handling WM_SETTEXT message
	int m_nSetTextSemaphor;
	int m_bNotifyParent;
	////////////////////////////////////

	// flag that specifies the behaviour of the control when 
	// focus is being set to it. The default behaviour of the 
	// standard edit control is to select all text and cursor 
	// is being set at the end of the text. CUTEdit handles this 
	// event in the following way: it sets cursor at the first 
	// symbol that can be modified without selecting any text.
	// Turning this flag on and off you can specify whether you 
	// would like to use the standard functionality or new one
	// (by default we use the new functionality when the text is 
	// not selected, i.e. the flag is set to FALSE)
	BOOL m_bHighlightOnSetFocus;

	// internal flag that stipulates that the class calls SetFocus function 
	// itself for internal purposes
	BOOL m_bNoSaveFont;

private:
	// flag that specifies that edit control was completely initialized
	BOOL m_bInitialized;


protected:
	int Validate();
	COLORREF m_clrReadOnlyBack;
	COLORREF m_clrReadOnlyFont;
	// helper function, saves info about control's font 
	BOOL SaveFont();

	inline BOOL IsInitialized() const { return m_bInitialized; }

	// Generated message map functions
	//{{AFX_MSG(CUTEdit)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	// v7.2 - update 02 - 64-bit - changed these from LONG, UINT, LONG to LRESULT, WPARAM, LPARAM
	afx_msg LRESULT OnCut(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCopy(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPaste(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClear(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam) ;
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CUTNumericEdit window

class UG_CLASS_DECL CUTNumericEdit : public CUTEdit
{
// Construction
public:
	// --- In  :
	// --- Out : 
	// --- Returns:
	// --- Effect : Constructs the object
	CUTNumericEdit();


	// --- In     :
	// --- Out    :
	// --- Returns: text without mask
	// --- Effect : retrieves text without mask
	virtual CString GetInputData() const;
	
	
	// --- In  :	chGroupSeparator	-	symbol used as group separator 
	//										(number can be divided in group e.g.
	//										of three numbers in order to ease
	//										the process of reading them)
	// --- Out : 
	// --- Returns:
	// --- Effect : sets the group separator
	BOOL SetGroupSeparator(TCHAR chGroupSeparator);

	// --- In  :
	// --- Out : 
	// --- Returns: symbol that is used as group separator
	// --- Effect :	retrieves the symbol that is used as group separator
	inline TCHAR GetGroupSeparator() const { return m_chGroupSeparator; }


	// --- In  :	nGroupLength	-	number of digits in group (by default we 
	//									organize numbers by 3 in group). If zero
	//									is specified then digits won't be organized
	//									in groups.
	// --- Out : 
	// --- Returns:
	// --- Effect : sets the number of decimal digits in group. If you don't 
	//				want to organize your decimal digits in groups then specify
	//				zero as function argument.
	BOOL SetGroupLength(int nGroupLength);

	// --- In  :
	// --- Out : 
	// --- Returns: number of figures in group
	// --- Effect :	retrieves the number of decimal digits in group. Zero value means
	//				decimal digits won't be organized in groups.
	inline int GetGroupLength() const { return m_nGroupLength; }


	// --- In  :	chDecimalSeparator	-	symbol used as decimal separator 
	// --- Out : 
	// --- Returns:
	// --- Effect : sets the decimal separator
	BOOL SetDecimalSeparator(TCHAR chDecimalSeparator);

	// --- In  :
	// --- Out : 
	// --- Returns: symbol that is used as decimal separator
	// --- Effect :	retrieves the symbol that is used as decimal separator
	inline TCHAR GetDecimalSeparator() const { return m_chDecimalSeparator; }


	// --- In  :	bShowLeadingZero		-	flag that specifies if we have to show
	//											leading zero or not
	// --- Out : 
	// --- Returns:
	// --- Effect : sets the flag that specifies if we have to show 
	//				leading zero or not
	void SetShowLeadingZero(BOOL bShowLeadingZero);

	// --- In  :
	// --- Out : 
	// --- Returns: flag that specifies if we have to show leading zero or not
	// --- Effect :	retrieves the flag that specifies if we have to show 
	//				leading zero or not
	inline BOOL GetShowLeadingZero() const { return m_bShowLeadingZero; }


	// --- In  :	nFractionalDigitCount	-	number of fractional digits displayed.
	//											Can be any value >=0
	// --- Out : 
	// --- Returns:
	// --- Effect : sets the number of fractional digits displayed
	BOOL SetFractionalDigitCount(int nFractionalDigitCount);

	// --- In  :
	// --- Out : 
	// --- Returns: number of fractional digits displayed.
	// --- Effect :	retrieves the number of fractional digits displayed
	inline int GetFractionalDigitCount() const { return m_nFractionalDigitCount; }


	// --- In  :	nDecimalDigitCount	-	max number of decimal digits displayed.
	//										Can be any value >=-1. Value -1 means
	//										that indefinite number of decimal 
	//										digits can be displayed
	// --- Out : 
	// --- Returns:
	// --- Effect : sets the max number of decimal digits that can be displayed
	BOOL SetDecimalDigitCount(int nDecimalDigitCount);

	// --- In  :
	// --- Out : 
	// --- Returns: max number of decimal digits displayed.
	// --- Effect :	retrieves the max number of decimal digits displayed. 
	//				Value of -1 means that indefinite number of decimal digits
	//				can be displayed
	inline int GetDecimalDigitCount() const { return m_nDecimalDigitCount; }


	// Number format
	//

	// --- In  :	lpszFormatPositive	-	mask to be used while displaying 
	//										control's positive value. 
	//										Mask should be specified as 
	//										"Literals1.1Literals", where "1.1" 
	//										stands for value and "Literals" 
	//										could consists of any symbol(s).
	//										E.g. if format "<1.1>" had been
	//										specified then value 5.26 would have 
	//										been displayed as "<5.26>"
	// --- Out : 
	// --- Returns: TRUE if display format was successfully set
	// --- Effect :	Sets the control's display format for positive values. 
	virtual BOOL SetPositiveFormat(LPCTSTR lpszFormatPositive);

	// --- In  :	
	// --- Out : 
	// --- Returns: display format string for negative value
	// --- Effect :	Retrieves the control's display format string for negative value.
	inline CString GetPositiveFormat() const { return m_sFormatPositive; }


	// --- In  :	lpszFormatNegative	-	mask to be used while displaying 
	//										control's negative value. 
	//										Mask should be specified as 
	//										"Literals1.1Literals", where "1.1" 
	//										stands for value and "Literals" 
	//										could consists of any symbol(s).
	//										E.g. if format "(1.1)" had been
	//										specified then value -5.26 would have 
	//										been displayed as "(5.26)"
	// --- Out : 
	// --- Returns: TRUE if display format was successfully set
	// --- Effect :	Sets the control's display format for negative values. 
	virtual BOOL SetNegativeFormat(LPCTSTR lpszFormatNegative);

	// --- In  :	
	// --- Out : 
	// --- Returns: display format string for negative value
	// --- Effect :	Retrieves the control's display format string for negative value.
	inline CString GetNegativeFormat() const { return m_sFormatNegative; }


	// --- In  :	clrTextNegative	-	color of text for negative value
	//				bRedraw			-	if TRUE then control will be redrawn 
	// --- Out : 
	// --- Returns:
	// --- Effect : sets the color that CUTNumericEdit object uses to draw text
	//				when its value is negative. By default we use the same color
	//				for positive and negative value. In order to set text color 
	//				for positive value call CUTEdit::SetTextColor() function
	void SetNegativeTextColor(COLORREF clrTextNegative, BOOL bRedraw=TRUE);

	// --- In  :
	// --- Out : 
	// --- Returns: text color when value is negative
	// --- Effect :	gets the color that CUTNumericEdit object uses to draw text
	//				when its value is negative. In order to retrieve text color 
	//				for positive value call CUTEdit::GetTextColor() function
	inline COLORREF GetNegativeTextColor() const { return m_clrTextNegative; }


	// --- In     :
	// --- Out    :
	// --- Returns: numeric value associated with the control
	// --- Effect : retrieves numeric value associated with the control
	double GetValue() const { return m_dValue; }
	
	// --- In     : dValue -	double value to be associated with the control
	// --- Out    :
	// --- Returns: TRUE if value was successfully set or FALSE otherwise. 
	// --- Effect : Use to programmatically set numeric value into the edit control. 
	BOOL SetValue(double dValue);


	// --- In     : 
	// --- Out    :
	// --- Returns: TRUE if numeric value is negative or FALSE otherwise. 
	// --- Effect : Retrieves flag that specifies whether numeric value associated
	//				with the control is negative or positive
	inline BOOL IsNegativeValue() const { return m_bNegativeValue; }


	// --- In  :	bForceToUsePeriod	-	if TRUE then whenever period character
	//										is typed in it will be intepreted as
	//										decimal point
	// --- Out : 
	// --- Returns:
	// --- Effect : Sets the flag that specifies whether the event of typing in
	//				of period character will be interpreted as decimal point 
	//				all the time or not
	void SetForceToUsePeriod(BOOL bForceToUsePeriod);

	// --- In  :
	// --- Out : 
	// --- Returns: flag that specifies whether the event of typing in
	//				of period character will be interpreted as decimal point 
	//				all the time or not
	// --- Effect :	gets the flag that specifies whether the event of typing in
	//				of period character will be interpreted as decimal point 
	//				all the time or not
	inline BOOL GetForceToUsePeriod() const { return m_bForceToUsePeriod; }


// Internal Member functions ------------------------------------------------
protected:
	// virtual function that is called when control is initialized
	// and every time system settings has been changed. Retrieves
	// default settings for displaying numeric values based on 
	// default locale
	virtual BOOL GetLocaleSettings();

	// initializes control
	virtual BOOL InitControl();

	// checks control's contents and updates it in order to conform 
	// with rules defining the appearance of numeric data 
	virtual int ValidateInput();

	// resets associated numeric value
	virtual void DeleteContents();
	
	// checks specified real position as position at which valid input data is located
	virtual BOOL IsInputData(int nPosition) const;

	// function is called whenever the sigh of value must be changed
	virtual int ChangeSign(BOOL bNegative);

	// called every time when user is deleting symbol or range of symbols
	virtual int DeleteRange(int& nSelectionStart, int& nSelectionEnd, BOOL bInsert = FALSE);
	// called every time user typed new symbol (insert mode is on)
	virtual int InsertAt(int nSelectionStart, TCHAR chNewChar);
	// called every time user typed new symbol (overwrite mode is on)
	virtual int SetAt(int nSelectionStart, TCHAR chNewChar);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUTNumericEdit)
	//}}AFX_VIRTUAL

protected:
	DECLARE_DYNAMIC(CUTNumericEdit)

	// group separator
	TCHAR m_chGroupSeparator;	
	// group length
	int m_nGroupLength;	

	// decimal separator
	TCHAR m_chDecimalSeparator;	

	// show leading zero
	BOOL m_bShowLeadingZero;

	// number of fractional digits (>=0)
	int m_nFractionalDigitCount;

	// number of decimal digits (>=-1)
	int m_nDecimalDigitCount;

	// display format for negative value
	CString m_sFormatNegative;
	// display format for positve value
	CString m_sFormatPositive;

	// text color for negative value
	COLORREF m_clrTextNegative;

	// numeric value associated with the control
	double m_dValue;

	// flag that specifies if value is negative or positive
	BOOL m_bNegativeValue;

	// flag that specifies whether the period character must be always 
	// intepreted as decimal separator when it pressed
	BOOL m_bForceToUsePeriod;

	// set of values retrived from the recent locale
	// 
	TCHAR m_chGroupSeparatorDefault;	
	// group length
	int m_nGroupLengthDefault;	
	// decimal separator
	TCHAR m_chDecimalSeparatorDefault;	
	// show leading zero
	BOOL m_bShowLeadingZeroDefault;
	// number of fractional digits (>=0)
	int m_nFractionalDigitCountDefault;
	// number of decimal digits (>=-1)
	int m_nDecimalDigitCountDefault;
	// display format for negative value
	CString m_sFormatNegativeDefault;
	// display format for positve value
	CString m_sFormatPositiveDefault;
	//
	////////////////////////////////////////////////////

protected:
	// retrieves number of decimal digits inserted in the control
	int GetDecimalDigitsInserted() const;
	// retrieves number of fractional digits inserted in the control
	int GetFractionalDigitsInserted() const;

	// retrieves real position of specified symbol. Search only within input data
	// symbols. If specified symbol hasn't been found, returns -1
	int FindSymbol(TCHAR chSymbol) const;

	// processes new symbol that is about to be added to control's contents
	// at specified position. The third argument specifies whether symbol at 
	// nSelectionStart position must be inserted or replaced.
	virtual int TranslateSymbol(int nSelectionStart, TCHAR chNewChar, 
		BOOL bReplaceExisting);

	// Generated message map functions
	//{{AFX_MSG(CUTNumericEdit)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifdef _BUILD_UG_INTO_EXTDLL
	#ifndef OX_API_DECL
		#define OX_API_DECL			AFX_API_EXPORT
	#endif
#elif defined _LINK_TO_UG_IN_EXTDLL
	#ifndef OX_API_DECL
		#define OX_API_DECL			AFX_API_IMPORT
	#endif
#else
	#ifndef OX_API_DECL
		#define OX_API_DECL
	#endif
#endif

/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
// CUTCurrencyEdit window

class UG_CLASS_DECL CUTCurrencyEdit : public CUTNumericEdit
{
// Construction
public:
	// --- In  :
	// --- Out : 
	// --- Returns:
	// --- Effect : Constructs the object
	CUTCurrencyEdit();


	// --- In  :	lpszCurrency	-	string of text (at least one 
	//									symbol long) used as currency name 
	// --- Out : 
	// --- Returns:
	// --- Effect : sets the string that represents currency name
	BOOL SetCurrencyName(LPCTSTR lpszCurrency);

	// --- In  :
	// --- Out : 
	// --- Returns: string that is used as currency name
	// --- Effect :	retrieves the symbol that is used as group separator
	inline CString GetCurrencyName() const { return m_sCurrency; }


	// Currency format
	//

	// --- In  :	lpszFormatPositive	-	mask to be used while displaying 
	//										control's positive value. 
	//										Mask should be specified as 
	//										"Literals1.1Literals", where "1.1" 
	//										stands for value and "Literals" 
	//										could consist of any symbol(s). One of
	//										the Literals string must have the 
	//										symbol that represents placeholder
	//										for currency name using universal 
	//										currency symbol - "$".
	//										E.g. if format "$1.1" had been
	//										specified then value 5.26 would have 
	//										been displayed as "$5.26"
	// --- Out : 
	// --- Returns: TRUE if display format was successfully set
	// --- Effect :	Sets the control's display format for positive values. 
	virtual BOOL SetPositiveFormat(LPCTSTR lpszFormatPositive);

	// --- In  :	lpszFormatNegative	-	mask to be used while displaying 
	//										control's negative value. 
	//										Mask should be specified as 
	//										"Literals1.1Literals", where "1.1" 
	//										stands for value and "Literals" 
	//										could consist of any symbol(s). One of
	//										the Literals string must have the 
	//										symbol that represents placeholder
	//										for currency name using universal 
	//										currency symbol - "$".
	//										E.g. if format "($1.1)" had been
	//										specified then value -5.26 would have 
	//										been displayed as "($5.26)"
	// --- Out : 
	// --- Returns: TRUE if display format was successfully set
	// --- Effect :	Sets the control's display format for negative values. 
	virtual BOOL SetNegativeFormat(LPCTSTR lpszFormatNegative);


// Internal Member functions ------------------------------------------------
protected:
	// virtual function that is called when control is initialized
	// and every time system settings has been changed. Retrieves
	// default settings for displaying numeric values based on 
	// default locale
	virtual BOOL GetLocaleSettings();

	virtual void UpdateMask();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUTCurrencyEdit)
	//}}AFX_VIRTUAL

protected:
	DECLARE_DYNAMIC(CUTCurrencyEdit)

	// currency name
	CString m_sCurrency;

	// default currency name
	CString m_sCurrencyDefault;

protected:
	// Generated message map functions
	//{{AFX_MSG(CUTCurrencyEdit)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // _UTEDIT_H__
