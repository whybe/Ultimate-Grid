/*************************************************************************
				Class Declaration : COfficeFormat
**************************************************************************
	Source file : OfficeFormat.cpp
	Header file : OfficeFormat.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Purpose
	
	Numeric
		"User-Defined Numeric Formats (Format Function)"
		FormatNumber
		FormatCurrency
		FormatPercent

	Date format is defined in the (VB reference)
		"User-Defined Date/Time Formats (Format Function)"
*************************************************************************/
#ifndef _OfficeFormat_H_
#define _OfficeFormat_H_

#include "UGCtrl.h"

class COfficeFormat: public CUGCellFormat
{
public:
	COfficeFormat();
	virtual ~COfficeFormat();

	virtual void ApplyDisplayFormat(CUGCell *pCell);
};

#endif	// _OfficeFormat_H_