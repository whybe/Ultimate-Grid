/***********************************************
	Ultimate Grid

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Class 
		CUG_OLEDB_DataSource -- An OLE DB DataSource 
		for	Ultimate Grid.

	Purpose:
		- this datasource can be used to connect to 
		data providers through the OLE DB interfaces.
	Details:
		-return values from a datasource are
			UG_SUCCESS	- success (0)
			UG_NA		- not available (-1)
			1 and up	- error codes

************************************************/
#include "ugctrl.h"
#include "oledb.h"
#include "binds.h"


#define NUM_FETCH 10		// affects opening speed!  
							// but scroll bar stable!

class CUG_OLEDB_DataSource : public CUGDataSource 
{
protected:
	Columns			m_Cols;


	HROW 	m_rghRows[NUM_FETCH];				// Row Handles
	long m_MaxRow;					// highest row seen to date
	BOOL m_endSeen;					// seen the end of rowset
	long m_currRow;					// the current Row
	long m_obtRows;					// number of rows retrieved in the last LoadRow operation

	IUnknown*		m_pSession;		// the current session	
	IRowset*		m_pIRowset;		// the rowset
	HACCESSOR		m_hAccessor;	// accessor to data

	ITransaction*   m_pTransaction; 

	ULONG			m_cBind;
	ULONG			m_cMaxRowSize;
	CString			m_Provider;
	CString			m_DBName;
	CString			m_UserName;
	CString			m_Password;
	CString			m_Command;
	CString			m_Filter;		// filter to be used ie a WHERE clause
	CString			m_SortOrder;	// sort order to be used ie an ORDER BY clause


	CString			m_CurrentCellText; // cached current text
	long			m_CurrentCellRow;
	long			m_CurrentCellCol;


	HRESULT OpenSession();
	void CloseSession();
	HRESULT OpenRowset();
	void CloseRowset();

	BOOL ExecuteQuery();
	HRESULT SetupBindings();
	HRESULT LoadRow(long row);


	CString GetCellText(int col, long row);
	HRESULT ReportError(IUnknown* pBadObject, GUID IID_BadIntereface);





public:
	CString GetProvider() const
		{ return m_Provider; }
	void	SetProvider(const CString& prov)
		{ m_Provider = prov; }


	CString GetDBName() const
		{ return m_DBName; }
	void	SetDBName(const CString& DB)
		{ m_DBName = DB; }
	CString GetUser() const
		{ return m_UserName; }
	void	SetUser(const CString& user)
		{ m_UserName = user; }
	CString GetPassword() const
		{ return m_Password; }
	void	SetPassword(const CString& password)
		{ m_Password = password; }
	CString GetCommand() const
		{ return m_Command; }
	void	SetCommand(const CString& command)
		{ m_Command = command; }
	CString GetFilter() const
		{ return m_Filter; }
	void	SetFilter(const CString& filter)
		{ m_Filter = filter; }
	CString GetSortOrder() const
		{ return m_SortOrder; }
	void	SetSortOrder(const CString& order)
		{ m_SortOrder = order; }



	CUG_OLEDB_DataSource(); 
	~CUG_OLEDB_DataSource();


	//opening and closing
	virtual int Open(LPCTSTR name,LPCTSTR option);
	virtual int SetPassword(LPCTSTR user,LPCTSTR pass);
	virtual int Close();
	virtual long GetNumRows();
	virtual int GetNumCols();
	virtual int GetColName(int col,CString * string);
	virtual int GetColType(int col,int *type);	//0-string 1-bool 2-short 3-long 4-float 
													//5-double 6-currency 7-data 8-time
													//8-memo 9-blob 10-ole
	virtual int GetColFromName(LPCTSTR name,int *col);
	//add-update-clear
	virtual int AppendRow();
	virtual int DeleteRow(long row);
	virtual int Empty();
	//cell info
	virtual int	GetCell(int col,long row,CUGCell *cell);
	virtual int	SetCell(int col,long row,CUGCell *cell);
	//finding sorting
	virtual int SortBy(int col,int flags);
	//movement 
	virtual int OnHitBottom(long numrows,long rowspast,long *rowsfound);
	//grid movement
	virtual int OnCellChange(long col,long row);
	//used to check to see if the data source supports a standard function
	BOOL IsFunctionSupported(long type);
	//transactions
	virtual int StartTransaction();
	virtual int CancelTransaction();
	virtual int FinishTransaction();

};