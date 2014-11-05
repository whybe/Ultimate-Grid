/*************************************************************************
				Class Declaration : CUGNoteType
**************************************************************************
	Source file : UGCTNote.cpp
	Header file : UGCTNote.h
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

    Purpose
		
*************************************************************************/
#ifndef _UGCTNote_H_
#define _UGCTNote_H_

#include "UGCTNoteWnd.h"

#define ID_NOTEWND 300
#define OFSET_VERT 15
#define OFSET_HORIZ 5

static CRect m_noteCellRect;

//CUGNoteType class declaration
class UG_CLASS_DECL CUGNoteType: public CUGCellType
{
protected:
	
	INT_PTR m_timerID;

	BOOL m_bInit;
	CUGNoteTypeEWnd m_noteWnd;

	int m_nNoteWidth,m_nNoteHeight;
	
// v7.2 - update 02 - 64-bit - TimerProc is declared with UINT_PTR as param 3
#if defined(_WIN64)
	static VOID EXPORT CALLBACK TimerProc(
			HWND hwnd,         // handle to window
			UINT uMsg,         // WM_TIMER message
			UINT_PTR idEvent,  // timer identifier
			DWORD dwTime       // current system time
			);
#else
	static VOID EXPORT CALLBACK TimerProc(
			HWND hwnd,         // handle to window
			UINT uMsg,         // WM_TIMER message
			unsigned int idEvent,  // timer identifier
			DWORD dwTime       // current system time
			);
#endif
public:

	CUGNoteType();
	~CUGNoteType();

	//overloaded CUGCellType functions
	virtual LPCTSTR GetName();
	virtual LPCUGID GetUGID();
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,
		CUGCell *cell,int selected,int current);
	virtual void OnSetFocus(int col,long row,CUGCell *cell);
	virtual void OnKillFocus(int col,long row,CUGCell *cell);
	virtual BOOL OnLClicked(int col,long row,int updn,RECT *rect,POINT *point);
	virtual BOOL OnMouseMove(int col,long row,POINT *point,UINT nFlags);
	virtual void OnScrolled(int col,long row,CUGCell *cell);

	int SetNoteSize(int width, int height);

};

#endif //#ifndef _UGCTNote_H_