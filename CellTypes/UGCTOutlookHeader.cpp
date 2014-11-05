/*************************************************************************
				Class Implementation : CUGCTAutoSize
**************************************************************************
	Source file : UGCTButn.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGCTOutlookHeader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
	typedef BOOL (__stdcall *GRADIENTFILL)(HDC,PTRIVERTEX,ULONG,PVOID,ULONG,ULONG);

	BOOL GradientFill95(HDC hdc, PTRIVERTEX pVertex, ULONG dwNumVertex, PVOID pMesh, ULONG dwNumMesh, ULONG dwMode)
	{
		BOOL success = FALSE;

		HMODULE hLib = ::LoadLibrary(_T("Msimg32.dll"));

		if (hLib != NULL)
		{
			GRADIENTFILL pGradientFill = (GRADIENTFILL)GetProcAddress(hLib, "GradientFill");

			if (pGradientFill)
			{
				success = (*pGradientFill)(hdc, pVertex, dwNumVertex, pMesh, dwNumMesh, dwMode);
			}
		}

		return success;
	}
}

/***************************************************
CUGCTOutlookHeader - Constructor
	Initialize member variables
****************************************************/
CUGCTOutlookHeader::CUGCTOutlookHeader()
{
	m_font.CreateFont( 20, 0, 0, 0, 600, 0, 0, 0, 0, 0, 0, 0, 0, _T( "Arial" ) );
}

/***************************************************
~CUGCTOutlookHeader - Destructor
	Clean up all allocated resources
****************************************************/
CUGCTOutlookHeader::~CUGCTOutlookHeader()
{
}

/***************************************************
OnDraw
	The Ultimate Grid calls this virtual function
	every time it is drawing a cell.  It is up to
	the individual cell type to properly draw itself.
Params:
	dc		- device context to draw the cell with
	rect	- rectangle to draw the cell in
	col		- column that is being drawn
	row		- row that is being drawn
	cell	- cell that is being drawn
	selected- TRUE if the cell is selected, otherwise FALSE
	current - TRUE if the cell is the current cell, otherwise FALSE
Return
	<none>
****************************************************/
void CUGCTOutlookHeader::OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,int selected,int current)
{
	if (!m_drawThemesSet)
		m_useThemes = cell->UseThemes();

	CUGCellType::OnDraw( dc, rect, col, row, cell, selected, current );

	// before drawing of the cell check if it's content will fully fit
	CSize size( 0, 0 );
	GetBestSize( dc, &size, cell );

	TRIVERTEX      vert[2];
    GRADIENT_RECT  gRect;
    vert[0].x      = rect->left;
    vert[0].y      = rect->top;
    vert[0].Red    = MAKEWORD(0, 89);
    vert[0].Green  = MAKEWORD(0, 135);
    vert[0].Blue   = MAKEWORD(0, 214);
    vert[0].Alpha  = 0x0000;

    vert[1].x      = rect->right;
    vert[1].y      = rect->bottom; 
    vert[1].Red    = MAKEWORD(0, 3);
    vert[1].Green  = MAKEWORD(0, 56);
    vert[1].Blue   = MAKEWORD(0, 147);
    vert[1].Alpha  = 0x0000;

    gRect.UpperLeft  = 0;
    gRect.LowerRight = 1;

    GradientFill95(dc->GetSafeHdc(),vert,2,&gRect,1,GRADIENT_FILL_RECT_V);

	CFont * poldFont = dc->SelectObject(&m_font);
	dc->SetTextColor(RGB(255, 255, 255));
	dc->TextOut(6, 4, cell->GetText());
	dc->SelectObject(poldFont);
}