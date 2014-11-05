/*************************************************************************
				Class Implementation : CUGNoteTypeEWnd
**************************************************************************
	Source file : UGCTNoteWnd.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "ugctrl.h"
#include "UGCTNoteWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***************************************************
CUGNoteTypeEWnd - Constructor
*****************************************************/
CUGNoteTypeEWnd::CUGNoteTypeEWnd()
{
}

/***************************************************
~CUGNoteTypeEWnd - Destructor
*****************************************************/
CUGNoteTypeEWnd::~CUGNoteTypeEWnd()
{
}


/***************************************************
MessageMap
*****************************************************/
BEGIN_MESSAGE_MAP(CUGNoteTypeEWnd, CEdit)
	//{{AFX_MSG_MAP(CUGNoteTypeEWnd)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()	
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
	ON_WM_SHOWWINDOW()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/***************************************************
OnEraseBkgnd
*****************************************************/
BOOL CUGNoteTypeEWnd::OnEraseBkgnd(CDC* pDC) 
{
	CRect rect;
	GetClientRect(&rect);
	pDC->FillRect(&rect,&m_bkGndBrush);
	
	return 1;
}

/***************************************************
CtlColor
*****************************************************/
HBRUSH CUGNoteTypeEWnd::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	UNREFERENCED_PARAMETER(nCtlColor);

	pDC->SetBkColor(RGB(250,255,220));

	return m_bkGndBrush;
}

/***************************************************
OnUpdate
Params:
	<none>
Returns:
	<none>
*****************************************************/
void CUGNoteTypeEWnd::OnUpdate() 
{
	CalcEditRect();
}

/***************************************************
OnCreate
*****************************************************/
int CUGNoteTypeEWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_bkGndBrush.CreateSolidBrush(RGB(250,255,220));
	m_font.CreateFont(14,0,0,0,400,0,0,0,0,0,0,0,0,_T("Arial"));

	SetFont(&m_font);
	
	return 0;
}

/***************************************************
CalcEditRect
	function is used to re-calculate the area covered by the edit control, it
	is important piece of an auto expanding edit control.
Params:
	<none>
Returns:
	<none>
*****************************************************/
void CUGNoteTypeEWnd::CalcEditRect()
{
	
	CString string;
	RECT	fmtRect;
	CDC*	dc;
	CFont*	oldFont = NULL;

	GetWindowText(string);
	string += _T(" ");

	GetClientRect(&fmtRect);
	ClientToScreen(&fmtRect);
	GetParent()->ScreenToClient(&fmtRect);

	dc = GetDC();
	if(GetFont() != NULL)
		oldFont = (CFont *)dc->SelectObject(GetFont());

	dc->DrawText(string,&fmtRect,DT_CALCRECT|DT_WORDBREAK);
 	
	if(GetFont() != NULL && oldFont != NULL )
		dc->SelectObject(oldFont);
	ReleaseDC(dc);

	fmtRect.right += 12;
	fmtRect.bottom += 12;

	MoveWindow(&fmtRect,TRUE);
	GetParent()->ValidateRect(&fmtRect);
}

void CUGNoteTypeEWnd::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CEdit::OnShowWindow(bShow, nStatus);
	
	CalcEditRect();
}

void CUGNoteTypeEWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CString string;
	CFont *oldFont;
	CRect rect;

	GetClientRect( rect );
	GetWindowText(string);

	// include margins for the text
	rect.top += 6;
	rect.left += 4;

	if(GetFont() != NULL)
		oldFont = (CFont *)dc.SelectObject(GetFont());

	dc.SetBkMode( TRANSPARENT );
	dc.DrawText(string,&rect,DT_WORDBREAK);
 	
	if(GetFont() != NULL && oldFont != NULL )
		dc.SelectObject(oldFont);
}
