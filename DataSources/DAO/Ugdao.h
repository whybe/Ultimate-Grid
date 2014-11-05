//  ugdao.h		The Ultimate Grid DAO datasource

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

#pragma once
// define the ID for the Dao datasource
#define	UGDS_ID_DAO		1000

// define the options that can be acted upon in SetOption and
// GetOption
#define UGDAO_OPT_GHOSTROWMODE  99
#define UGDAO_OPT_ALLOWEDITS	100
#define UGDAO_OPT_NUMBERSIDEHDG	101

// define messages for OnDataSourceNotify calls
// end of file...
#define UGDSM_DAO_EOF	26
#define UGDSM_DAO_UPDATEFAILED 13
#define UGDSM_DAO_KILLEXTRAROW 14
#define UGDSM_DAO_ADJUSTROWS 15

// Comment out this define to eliminate message boxes in the
// DAO exception handlers - usefull for debugging...
#define UG_DAO_REPORTERROR

class CUGDAODataSource: public CUGDataSource{

protected:
	
	
	CString			m_strSQL;		// were not overriding a 
									// recordset here, so may need this

	CString			m_strDB;		// database...

	TCHAR			m_buf[100];
	LPSTR			m_pPassword;

	long			m_nCurrentRow;	//current row

	CUGCell**		m_EditRow;	// array of cells for record based editing...
	long			m_nEditRow;		// number of edit row - should be -1 if
									// we're not editing...

	BOOL			m_bEditOnGhostRow;	// sometimes we need to adjust if we're
										// cancelling an edit on a new row...

	CUGCell			**m_GhostRow;	// array of *cells for the extra blank row...
	long			m_nGhostRow;	// number of row displayed with ghost 

	BOOL			m_bGhostRowMode;// See SetOption

	BOOL			m_bEditAllowed;	// See SetOption

	BOOL			m_bEditRowUpdatePending;	

	int				m_nFailedField;	// if a row update fails, this is set 
									// to the value of the position of
									// the errant field so that editing can 
									// resume on that field 

	BOOL			m_bNumberSideHdg;	// See SetOption
	int				m_nSH_NumBase;		// usually 0 or 1 for sidehdg numbers
										// see SetOption
	
	CDaoDatabase* 	m_Db;
	CDaoTableDef*	m_TableDef;
	CDaoQueryDef*	m_QueryDef;
	CDaoRecordset*	m_Record;
	CDaoFieldInfo*  m_FieldInfo;

    COleVariant     m_coVariant;        // for field retrieval...
    COleCurrency    m_coCurrency;
    COleDateTime    m_coDateTime;

	int m_bRecordSetAttached;

	void GatherFieldInfo();

public:
	CUGDAODataSource();
	~CUGDAODataSource();

	virtual int Open(LPCTSTR database,LPCTSTR table);
	virtual int OpenSQL(LPCTSTR database,LPCTSTR sql);
	int Open(LPCTSTR database,LPCTSTR table,int openType,LPCTSTR sql,int options);
	virtual int Close();

	//cell info
	virtual int	GetCell(int col,long row,CUGCell *cell);
	virtual int	SetCell(int col,long row,CUGCell *cell);

	//options
	virtual int SetOption(int option,long param1,long param2);
	virtual int GetOption(int option,long param1,long param2);

	virtual long GetNumRows();
	virtual int GetNumCols();
	virtual int GetColName(int col,CString * string);
	virtual int GetColType(int col,int *type);	//0-string 1-bool 2-short 3-long 4-float 
													//5-double 6-currency 7-data 8-time
													//8-blob 9-graphic 10-ole
	virtual int OnHitBottom(long numrows,long rowspast,long *rowsfound);

	virtual int FindFirst(CString *string,int *col,long *row,long flags);
	virtual int FindNext(CString *string,int *col,long *row,int flags);

	virtual int SortBy(int col,int flags = UG_SORT_ASCENDING);
	virtual int SortBy(int *cols,int num,int flags);

	virtual int AppendRow();
	virtual int DeleteRow(long row);

	int AppendRow(CUGCell *cellList,int numCells);

	int StartTransaction();
	int CancelTransaction();
	int FinishTransaction();

	// editing notifications...
	virtual int OnEditStart(int col, long row,CWnd **edit);
	virtual int OnEditVerify(int col,long row,CWnd *edit,UINT *vcKey);
	virtual int OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag);
	virtual int OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow);

	// grid movement...
	virtual int OnCanMove(int oldcol,long oldrow,int newcol,long newrow);
	

	//new functions - not derived from the base class (CUGDatasource)
	long GetNumRowsComplete();
	BOOL IsOpen();
	BOOL CanEditCell(int col, long row);

	int GotoRecord(long row);
	int SetFieldValueFromCell(int col, CUGCell *cell);
	int UpdateCurrentRecord();


	void AllocateGhostRow();
	int  PopulateGhostRow();
	void ClearGhostRow();

	void AllocateEditRow();
	void ReadEditRow(long row);
	void ClearEditRow();
	int	 UpdateFromEditRow();

	// temporary - override this to supply default vals when
	// using GhostRowMode
	virtual int AddDefaultRow();

	void CancelEdit();

	int Reset();
	int AttachRecordSet(CDaoRecordset* rset);
	int SetPassword(LPSTR password);
	CDaoRecordset* GetRecordSet();
	CDaoDatabase*  GetDatabase();

	// debug ...
	int CheckPosition();
	void VerifyPosition();

};