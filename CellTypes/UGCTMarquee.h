/*************************************************************************
				Class Declaration : CUGMarqueeType
**************************************************************************
	Source file : UGCTMarquee.cpp
	Header file : UGCTMarquee.h
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
#ifndef _UGCTMarquee_H_
#define _UGCTMarquee_H_


//CUGMarqueeType class declaration
class UG_CLASS_DECL CUGMarqueeType: public CUGCellType
{
protected:
	
	INT_PTR m_timerID;
	long m_interval;

	void StartUp();

// v7.2 - update 02 - 64-bit - TimerProc is declared with UINT_PTR as param 3
#if defined(_WIN64)
	static VOID CALLBACK EXPORT TimerProc(
			HWND hwnd,         // handle to window
			UINT uMsg,         // WM_TIMER message
			UINT_PTR idEvent,  // timer identifier
			DWORD dwTime       // current system time
			);
#else
	static VOID CALLBACK EXPORT TimerProc(
			HWND hwnd,         // handle to window
			UINT uMsg,         // WM_TIMER message
			unsigned int idEvent,  // timer identifier
			DWORD dwTime       // current system time
			);
#endif
public:

	CUGMarqueeType();
	~CUGMarqueeType();

	int SetScrollInterval(long nMilliSec);

	//overloaded CUGCellType functions
	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,
		CUGCell *cell,int selected,int current);

};

#endif //#ifndef _UGCTMarquee_H_