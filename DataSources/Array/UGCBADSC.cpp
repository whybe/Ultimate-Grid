// ===================================================================
//     Class: CUGCBArrayDataSource
//      File: UGCBADSC.cpp
//   Created: September 19, 1998
//   Revised: 
//   Purpose: Example of simple CByteArray dump datasource
// ===================================================================
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// ===================================================================

#include "stdafx.h"
#include "ugctrl.h"

#include "UGCBADSC.h"


CUGCBArrayDataSource::CUGCBArrayDataSource(){
	
	// init
	m_byteArray = NULL;
	m_strTemp.Empty();
	m_extra = 0;

	// lets set some defaults
	m_radix = UGCBA_RADIX_HEX;
	m_cNonPrintable = '.';
	m_nBlockSize = 20;



}

CUGCBArrayDataSource::~CUGCBArrayDataSource(){
}

CUGCBArrayDataSource::CUGCBArrayDataSource(const CUGCBArrayDataSource& object) {
	// TODO: Insert code to initialize members 
}

CUGCBArrayDataSource CUGCBArrayDataSource::operator=(const CUGCBArrayDataSource& object){
	// TODO: Insert code to copy members 
	return *this;
}

bool operator==(const CUGCBArrayDataSource& object1, const CUGCBArrayDataSource& object2) {
	// TODO: Insert code to perform comparison
	return true;
}

bool operator!=(const CUGCBArrayDataSource& object1, const CUGCBArrayDataSource& object2) {
	if(object1 == object2)
		return false;
	else
		return true;
}

/////////////////////////////////////////////////////////////////////
// CUGDataSource overrides - this is a read-only datasource, so only
// a few basics needed...

int CUGCBArrayDataSource::GetNumCols() {
	// Important: called by CUGCtrl::SetGridUsingDatasrc();
	// But not essential - you could set the grids rows and 
	// columns yourself...

	if (NULL != m_byteArray)
		return 2;
	else 
		return 0;
}

long CUGCBArrayDataSource::GetNumRows() {
	// Important: This called by CUGCtrl::SetGridUsingDatasrc();
	// But not essential - you could set the grids rows and 
	// columns yourself...

	ASSERT(m_nBlockSize != 0);

	long rows;

	if(NULL == m_byteArray){
		return 0;
	}
	else {				// ok - how many rows do we have...and
						// will they fit into m_nBlockSize chunks
		int temp = m_byteArray->GetSize()-1;
	   
		if((m_extra = temp%m_nBlockSize) != 0)
			rows = (temp/m_nBlockSize + 1);
		else
			rows = (temp/m_nBlockSize);

	    if(rows == 0 ) {			// might be less than m_nBlockSize bytes
	        if(temp != 0 ) {
			    rows = 1;
			}
		}
	}
	m_lastRow = rows -1;
	return rows;
}

/***********************************************************************
	GetCell()
	// this is the heart of any datasource.  Given a col and row, fill
	// the cell with data for display...
 ***********************************************************************/
int	CUGCBArrayDataSource::GetCell(int col,long row,CUGCell *cell){

	ASSERT(2 > col);

	if(NULL == m_byteArray)
		return UG_NA;

	if(row > m_lastRow)
		return UG_NA;

	// lets not mess with rows or cols less than -1
	if(-1 > col || -1 > row)
		return UG_NA;

	// don't do corner button
	if(-1 == col && -1 == row)
		return UG_NA;
	
	// if side heading, return byte offset
	if(-1 == col)	{		
		m_strTemp.Format(_T(" %d"), row * m_nBlockSize);
		cell->SetText(m_strTemp);
		cell->SetAlignment(UG_ALIGNRIGHT);
		return UG_SUCCESS;
	}

	// top heading, return 'counter' string
	if (-1 == row) {
		cell->SetAlignment(UG_ALIGNLEFT);
		if(0 == col) {
			switch (m_radix) {
			case UGCBA_RADIX_HEX:
				cell->SetText(_T(" 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20"));
				return UG_SUCCESS;
			case UGCBA_RADIX_DECIMAL:
				cell->SetText(_T("  01  02  03  04  05  06  07  08  09  10  11  12  13  14  15  16  17  18  19  20"));
				return UG_SUCCESS;
			default:
				return UG_ERROR;		// shouldn't happen
			}
		}
		else {
			// assume col = 1 - ascii display
			cell->SetText(_T(" 12345678901234567890 "));
			return UG_SUCCESS;
		}
	}

	// ok - now for the real data
	if( 1 == col) {
		FormatAsciiString(row);
		cell->SetText(m_strTemp);
		return UG_SUCCESS;
	}

	if( 0 == col ) {
		switch (m_radix) {
		case UGCBA_RADIX_HEX:
			FormatHexString(row);
			cell->SetText(m_strTemp);
			return UG_SUCCESS;
		case UGCBA_RADIX_DECIMAL:
			FormatDecimalString(row);
			cell->SetText(m_strTemp);
			return UG_SUCCESS;
		default:
			return UG_ERROR;
		}
	}

	return UG_ERROR;
}

/***********************************************************************
	FindNext()
	// this is a very generic FindNext routine that almost any 
	// datasource can use - the idea is to start from the 
	// current row and return the location of a match in the col & row
	// along with UG_SUCCESS if found.

	// this implementation does not 'wrap' - reporting 'not found' when
	// top or bottom of ds is reached.  The implementation in CUGMem
	// (the memory based default ds for UG) will continue to the top
	// or bottom)

	// When you call FindDialog in your derived grid class,
	// CUGCtrl::ProcessFindDialog() will call FindNext in the active
	// datasource...
 ***********************************************************************/
int CUGCBArrayDataSource::FindNext(CString *string,int *col,long *row,int flags) {
	
//	TRACE("Col: %d, Row %d 
	int  retval = UG_SUCCESS;

	long nStartRow = m_ctrl->GetCurrentRow();
	long nSearchRow = nStartRow;

	int  nMaxCol = GetNumCols()-1;

	int  nStartColumn = *col;
	int  nSearchColumn = *col;
	CUGCell cell;
	CString strCell;


	while(1) {

		// positioning...
		if(UG_FIND_ALLCOLUMNS&flags) {
			if(UG_FIND_UP&flags) {
				nSearchColumn--;
				if(nSearchColumn < 0) {
					nSearchColumn = nMaxCol;
					nSearchRow--;
				}
			}
			else {
				nSearchColumn++;
				if(nSearchColumn > nMaxCol) {
					nSearchColumn = 0;
					nSearchRow++;
				}
			}
		}
		else {
		
			if(UG_FIND_UP&flags)
				nSearchRow--;
			else
				nSearchRow++;

		}

		if(nSearchRow < 0) {		// don't search headings...
			// reset to last position
			
			retval = UG_NA;
			break;
		}
		
		if(GetCell(nSearchColumn, nSearchRow, &cell) != UG_SUCCESS) { 
			retval = UG_NA;			// no more data.
			break;
		}

		cell.GetText(&strCell);		// get the text.

		if(UG_FIND_CASEINSENSITIVE&flags) {
			// make both upper case
			string->MakeUpper();
			strCell.MakeUpper();
		}

		if(UG_FIND_PARTIAL&flags) {
			if(strCell.Find(*string) != -1) {		// compare partial
				*col = nSearchColumn;
				*row = nSearchRow;
				retval = UG_SUCCESS;
				break;
			}
		}
		else {
			if(strCell == *string) {					// match whole cell
				*col = nSearchColumn;
				*row = nSearchRow;
				retval = UG_SUCCESS;
				break;
			}
		}
	}		
	
	return retval;

}
//options
int CUGCBArrayDataSource::SetOption(int option,long param1,long param2){

	int retval = UG_SUCCESS;

	switch (option) {
	case UGCBA_OPT_BLOCKSIZE:			// how many bytes to display
		m_nBlockSize = (int) param1;
		break;
	case UGCBA_OPT_RADIX:				// hex, dec, etc
		m_radix     = (int) param1;
		break;
	case UGCBA_OPT_REPCHAR: 
		m_cNonPrintable = (char) param1;
		break;
	default:
		retval = UG_NA;
	}
	return retval;
}

int CUGCBArrayDataSource::GetOption(int option,long& param1,long& param2){

	int retval = UG_SUCCESS;

	switch (option) {
	case UGCBA_OPT_BLOCKSIZE:			// how many bytes to display
		param1 = (long)m_nBlockSize;
		break;
	case UGCBA_OPT_RADIX:				// hex, dec, etc
		param1 = (long)m_radix;
		break;
	case UGCBA_OPT_REPCHAR: 
		param1 = (long) m_cNonPrintable;
		break;
	default:
		retval = UG_NA;
	}
	return retval;
}

// ////////////////////////////////////////////////
// fns specific to this datasource

/***************************************************
	FormatHexString
****************************************************/
void CUGCBArrayDataSource::FormatHexString(long row){

	ASSERT(m_byteArray);

	CString str;
	m_strTemp= " ";

	long loc = row * m_nBlockSize;	// offset into byte array

    // calculate leftovers - GetAt will assert if
    // we go to far - may not have m_nBlockSize bytes left...
    int max;
	if(row == m_lastRow && m_extra%m_nBlockSize != 0) 
        max = m_extra%m_nBlockSize;
    else
        max = m_nBlockSize;

    for(int i = 0; i < max; i++) {
		
		str.Format(_T("%2.2x"), (BYTE)m_byteArray->GetAt(loc + i));
		m_strTemp += str + " ";
	}
}

/***************************************************
	FormatAsciiString
****************************************************/
void CUGCBArrayDataSource::FormatAsciiString(long row){

	ASSERT(m_byteArray);

	CString str;
	m_strTemp = " ";

	long loc = row * m_nBlockSize;	// offset into byte array
	char c;

    // calculate leftovers - GetAt will assert if
    // we go to far - may not have m_nBlockSize bytes left...
    int max;
	if(row == m_lastRow && m_extra%m_nBlockSize != 0) 
        max = m_extra%m_nBlockSize;
    else
        max = m_nBlockSize;

	for(int i = 0; i < max; i++) {
		c = (BYTE)m_byteArray->GetAt(loc + i);
		if(!isprint(c))
			c = '.';
		
		m_strTemp += c;
	}
	m_strTemp += " ";		// balance width for bestfit...
}


/***************************************************
	FormatHexString
****************************************************/
void CUGCBArrayDataSource::FormatDecimalString(long row){

	ASSERT(m_byteArray);

	CString str;
	m_strTemp = " ";

	long loc = row * m_nBlockSize;	// offset into byte array

    // calculate leftovers - GetAt will assert if
    // we go to far - may not have m_nBlockSize bytes left...
    int max;
	if(row == m_lastRow  && m_extra%m_nBlockSize != 0)  
        max = m_extra%m_nBlockSize;
    else
        max = m_nBlockSize;

	for(int i = 0; i < max; i++) {
		
		str.Format(_T("%3.3d"), (BYTE)m_byteArray->GetAt(loc + i));
		m_strTemp += str + _T(" ");
	}
}