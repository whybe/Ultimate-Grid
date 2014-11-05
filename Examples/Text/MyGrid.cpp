// MyGrid.cpp : implementation file
//

#include "stdafx.h"
#include "Text.h"
#include "MyGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CMyGrid

CMyGrid::CMyGrid()
{
}

CMyGrid::~CMyGrid()
{
	m_fontHeading.DeleteObject();
	m_fontGrid.DeleteObject();
	m_fontCool.DeleteObject();
}


BEGIN_MESSAGE_MAP(CMyGrid, CWnd)
	//{{AFX_MSG_MAP(CMyGrid)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyGrid message handlers

void CMyGrid::OnSetup()
{
	//
	// virtual void OnSetup()
	//
	//
	// Override the grid's OnSetup to perform custom initialization
	//
	// Here we create two CFont objects. One will be used for the labels
	// inside the grid while the other will be used as the font for the
	// top heading.  To create tilted text simply customize the CFont object
	// by either using the CreateFont member function or alternatively using
	// a LOGFONT structure then calling CreateFontIndirect

	int x,y;
	int nRows = 5;
	int nCols= 4;
	char buf[50];

	// Only True Type Fonts such as Arial are able to be rotated
	m_fontHeading.CreateFont(16,0,365,450,FW_EXTRABOLD,FALSE,TRUE,0,0,0,0,0,0,"Arial");
	m_fontGrid.CreatePointFont(85, "Tahoma");
	m_fontCool.CreateFont(20,0,250,0,FW_BOLD,TRUE,FALSE,0,0,0,0,0,0,"Arial");
 
	
	SetNumberRows(nRows);
	SetNumberCols(nCols);

	SetTH_Height(60);			// adjust height
	
	for(y = 0;y < nRows;y++){
		for(x = 0; x < nCols; x++){
			wsprintf(buf,"%d",x*y);
			if (x % 2)
				QuickSetFont(x, y, &m_fontGrid);
			else
				QuickSetFont(x, y, &m_fontCool);
			QuickSetText(x,y,buf);
		}
	}

	for(x=0; x<nCols; x++){
		QuickSetFont(x,-1, &m_fontHeading);
		wsprintf(buf,"Col %d",x);
		QuickSetText(x,-1,buf);
		QuickSetAlignment(x,-1,UG_ALIGNBOTTOM);
	}
}
