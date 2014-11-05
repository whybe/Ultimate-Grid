/***********************************************
    Ultimate Grid version 7.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Class 
		CUG_Delimitted
	Purpose
		This is a derived grid datasource, that 
		allows information to be loaded and saved 
		from a delimitted file.  
	Details
		-This class derives from CUGMem which is 
	     the standard memory manager.
		-The Load, Save and SaveAs datasource 
		 methods have been implemented.
		-The delimitter and quote characters can
		 be specified -- by default this 
		 datasource is comma delimitted.
		-Characters that need to be quoted can be
		 specified.
		-Standard return values for functions are: 
			UG_SUCCESS	- success (0)
			UG_NA		- not available (-1)
			1 and up	- error codes
	Notifications
		-Notifications sent by the data source 
		 through OnDataSourceNotify include
			UG_DELIM_DS_CLOSEDIRTY  - closing a
						when file may need to be
						saved.

************************************************/

#ifndef __DELIMITTED_DS
#define __DELIMITTED_DS


#define UG_DELIM_DS_CLOSEDIRTY 1
/***********************************************
************************************************/
class CUG_Delimitted : public CUGMem{

protected:
	int		m_cols;
	long	m_rows;


	TCHAR	m_delim;    // the delimiter (default ,)
	TCHAR   m_quote;    // the quoting character (default ")
	CString m_quoted;   // chars that need to be quoted (default ,")
	CString m_fileName; // filename passed to open -- Stored for save
	BOOL	m_dirty;	// dirty flag

public:
	CUG_Delimitted(TCHAR delim= _T(','), TCHAR quote= _T('"'), LPCTSTR quoted= _T(",\""));
	~CUG_Delimitted();

	BOOL GetDirty()	{
		return m_dirty; }
	void SetDirty(BOOL dirty=TRUE) {
		m_dirty=dirty; }
	TCHAR GetDelimiter(){
		return m_delim; }
	void SetDelimiter(TCHAR delim){
		m_delim = delim; }

	const TCHAR GetQuote(){
		return m_quote; }
	void SetQuote(TCHAR quote){
		m_quote = quote; }


	//opening and closing
	virtual int Open(LPCTSTR name,LPCTSTR option);
	virtual int Close();
	virtual int Save();
	virtual int SaveAs(LPCTSTR name,LPCTSTR option);

	//row and col info
	virtual long GetNumRows();
	virtual int GetNumCols();

	virtual int	SetCell(int col,long row,CUGCell *cell);
};

#endif
