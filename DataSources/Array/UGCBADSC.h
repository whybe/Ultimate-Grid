// ===================================================================
//     Class: CUGCBArrayDataSource
//      File: UGCBADSC.h
//   Created: September 19, 1998
//   Revised: 
//   Purpose: Example of simple CByteArray dump datasource
//				Shows how a simple datasource can
//				reduce memory overhead by working directly
//				from data in memory
// ===================================================================
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// ===================================================================
#ifndef _UGCBADSC_H_
#define _UGCBADSC_H_

#include "ugctrl.h"

// we can control the number of bytes dumped in a cell
#define UGCBA_OPT_BLOCKSIZE 99
// ... and whether we want decimal or hex or...
#define UGCBA_OPT_RADIX	98		
// ... and what to display for non-printing ascii chars
#define UGCBA_OPT_REPCHAR 97	

// radi supported
#define UGCBA_RADIX_HEX 1
#define UGCBA_RADIX_DECIMAL 2

class CUGCBArrayDataSource : public CUGDataSource {
private:
	// private member declarations


protected:
	// protected member declarations
	int				m_nBlockSize;		// how many bytes to format in a cell
	int				m_extra;			// leftover bytes for last row...
	int				m_radix;			// hex or what...
	CString			m_strTemp;			// for formatting block (cell) data
	char			m_cNonPrintable;	// can change from the traditional '.'
	long			m_lastRow;			// set in GetNumRows;
public:
	// public member declarations
	CByteArray		*m_byteArray;		// array in question - possibly 
										// the result of loading a file 
										// in serialize...

	CUGCBArrayDataSource();

	virtual ~CUGCBArrayDataSource();
	CUGCBArrayDataSource(const CUGCBArrayDataSource& );
	CUGCBArrayDataSource operator=(const CUGCBArrayDataSource&);
	
	/////////////////////////////////////////////////////////////////////
	// CUGDataSource overrides - this is a read-only datasource, so only
	// a few basics needed...
	virtual long GetNumRows();
	virtual int GetNumCols();
	virtual int	GetCell(int col,long row,CUGCell *cell);
	virtual int FindNext(CString *string,int *col,long *row,int flags);
	//options
	virtual int SetOption(int option,long param1,long param2);
	virtual int GetOption(int option,long& param1,long& param2);

	// new for dumper app
	void FormatHexString(long row);
    void FormatDecimalString(long row);
	void FormatAsciiString(long row);


};
	bool operator==(const CUGCBArrayDataSource&, const CUGCBArrayDataSource&);
	bool operator!=(const CUGCBArrayDataSource&, const CUGCBArrayDataSource&);

#endif
