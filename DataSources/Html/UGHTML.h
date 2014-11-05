/***********************************************
	Ultimate Grid version 7.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Class 
		CUG_HTML_DataSource
	Purpose
		This is a derived grid datasource, that 
		allows HTML tables to be loaded into the 
		standard grid memory manager.  

		While this data source only handles 
		importing simple HTML tables , it will 
		skip over embedded tables to completely
		import the table.  You can decided which
		of the outer most tables to import by 
		passing a table number to the Open 
		function.
	Details
		-This class derives from CUGMem which is 
	     the standard memory manager.
		-The Load method has been implemented.
		-Standard return values for functions are: 
			UG_SUCCESS	- success (0)
			UG_NA		- not available (-1)
			1 and up	- error codes

************************************************/
#ifndef __HTML_DS
#define __HTML_DS

/***********************************************
************************************************/
class CUG_HTML_DataSource : public CUGMem
{
protected:
	int		m_cols;
	long	m_rows;

	char* FindTableStart(char* buff);
	char* FindTableEnd(char* buff);
	char* FindRowStart(char* buff);
	char* FindRowEnd(char* buff);
	char* FindDetailStart(char* buff);
	char* FindDetailEnd(char* buff);
	long LoadColumns(char* buff, char* buffEnd);
	long LoadRows(char* buff, char* buffEnd);
	long LoadTable(char* buff, char* buffEnd, int num);

	// overridables for the data source
	virtual void InterpretTags(CString text,CUGCell* cell);
	virtual int OnEmbeddedTableFound(int col, long row, char* buff, char* buffEnd);

public:
	CUG_HTML_DataSource();
	~CUG_HTML_DataSource();

	//opening and closing
	virtual int Open(LPCTSTR name,LPCTSTR option);
	virtual int Close();

	//row and col info
	virtual long GetNumRows();
	virtual int GetNumCols();
};

#endif
