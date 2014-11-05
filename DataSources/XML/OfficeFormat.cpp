/***********************************************
	Ultimate Grid

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.


	class CUGFormat
************************************************/

#include "stdafx.h"
#include "OfficeFormat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
/////////////////////////////////////////////////////////////////////////////
COfficeFormat::COfficeFormat()
{
}

COfficeFormat::~COfficeFormat()
{
}

/////////////////////////////////////////////////////////////////////////////
//	ApplyDisplayFormat
void COfficeFormat::ApplyDisplayFormat( CUGCell *pCell )
{
	CString formatStr = pCell->GetLabelText();
	if ( formatStr == _T(""))
		// Return if the format string was not specified
		return;

	switch( pCell->GetDataType())
	{
	case UGCELLDATA_NUMBER:
		if ( formatStr == _T("Fixed"))
		{
			pCell->SetNumberDecimals( 2 );
		}
		else if ( formatStr.GetLength() > 1 )
		{
			int strPos = formatStr.Find(_T('.')) + 1;
			pCell->SetNumberDecimals( formatStr.GetLength() - strPos );
		}
		else
		{
			pCell->SetNumberDecimals( 0 );
		}
		break;
	case UGCELLDATA_TIME:
		break;
	}
}
