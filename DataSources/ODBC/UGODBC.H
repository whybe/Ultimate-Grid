//: ugodbc.h	Header for CUGODBCDatasource class.
//
//  Ultimate Grid 97 for MFC
//
//// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

#if !defined(UGODBC)
#define UGODBC

#include "ugctrl.h"
#include "ugrecset.h"		


class CUGODBCDatasource : public CUGDataSource{

protected:
	virtual int GotoRecord(long row);
	long  GetCurPos();
	enum {MAX_TABLES = 100};

	CString			m_buf;
	CString			m_strSQL;

	UINT			m_nRecType;
	DWORD			m_nRecOptions;			
	
	LONG			m_nCurrentRow;	//current row 
	LONG			m_totalRows;
	CDatabase* 		m_Db;
	CUGRecordset*	m_Record;
	CString*		m_Fields;

	SQLDatasourceInfo		m_dsInfoArray[MAX_TABLES];
	WORD				    m_tableCount;
	WORD                    m_RecordSetAttached;

    CString	                m_connectString;


public:

	CUGODBCDatasource();
	~CUGODBCDatasource();


	
	int OpenSQL(LPCTSTR database,LPCTSTR sql);

	int Open(LPCTSTR database,LPCTSTR table,DWORD dbOptions,UINT recType,DWORD recOptions,LPCSTR user,LPCSTR pass);
	int OpenSQL(LPCTSTR database,LPCTSTR sql,DWORD dbOptions,UINT recType,DWORD recOptions,LPCSTR user,LPCSTR pass);

	// CUGDataSource overrides
	int Open(LPCTSTR database,LPCTSTR table);

	virtual int Close();

	virtual int	GetCell(int col,long row,CUGCell *cell);
	virtual int	SetCell(int col,long row,CUGCell *cell);

	virtual int AppendRow();
	virtual int AppendRow(CUGCell **cellList,int numCells);
	virtual int DeleteRow(long row);

	virtual long GetNumRows();
	virtual long GetNumRowsComplete();
	virtual int GetNumCols();
	virtual int GetColName(int col,CString * string);
	virtual int GetColType(int col,int *type);	
	
	virtual int OnHitBottom(long numrows,long rowspast,long *rowsfound);

	virtual int SortBy(int col,int flags);
	virtual int SortBy(int *cols,int num,int flags);

	//transactions
	virtual int StartTransaction();
	virtual int CancelTransaction();
	virtual int FinishTransaction();


	int FindNext(CString *string, int *col, long *row, int flags);

  	//new functions
    void SetConnectString(CString* string);
	int Reset();

	int SetFieldValueFromCell(int col, CUGCell *cell);

	int AttachRecordSet(CUGRecordset* rset);    //TODO:
	void ReportSQLError(HENV henv, HDBC hdbc, HSTMT hstmt, RETCODE retcode, LPCTSTR fn); 
	

    CString * GetConnectString();

	int Browse(HWND hwnd);	
	SQLDatasourceInfo * GetTableInfo(int index);

	CUGRecordset* GetRecordset();	

};

#endif