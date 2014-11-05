/*************************************************************************
				Class Declaration : CADOImpDatasource
**************************************************************************
	Source file : ADOImpDatasource.cpp
	Header file : ADOImpDatasource.h
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Purpose
		The CADOImpDatasource datasource provides ability to bind Ultimate Grid
		to a database using ADO.  The way ADO is implemented in this datasource
		requires for the application to use #import statement to import ADO DLL.
		Following statement demonstrates what should be added, usually to the
		stdafx.h:

		#import <C:\Program Files\Common Files\System\ado\msado15.dll> no_namespace rename ("EOF", "adoEOF")

		The above statement will work provided that operating system is installed
		on C drive.

		This datasource provides Ghost Row functionality, which adds an empty
		row at the bottom of the grid when end of data was reached.  This row
		is by default enabled, but will not showup is recordset in use cannot
		be updated.

	Details
		Datasource Styles
			UG_ADO_DS_SET_EDITMODE	- turns on or off editing ability, eventhough
									  editing is enabled the datasource will still
									  check if the recordset allows updates.
									  This flag is enabled by default.
			UG_ADO_DS_USE_GHOSTROW	- turns on or off ghost row functionality, ghost
									  row is an empty row that is shown at the end
									  of the dataset.  In order for the ghost row
									  to appear the editing has to be enabled and
									  confirmed that the recordset allows updates.
			UG_ADO_DS_SET_FETCHSIZE	- allows to set new minimum number of rows to
									  fetch, by default set to 50.  When ADO 
									  datasource fetched new batch of records it 
									  calculates number of rows to fetch based on
									  how many rows (of default height) will fit
									  in the current size of the grid window times 3.
									  This flag is used to prevent small number of
									  rows to be fetched at any time, limiting number
									  of times we have to talk to the database.
			UG_ADO_DS_SET_ROWIDCHAR - option allows to change the row identifying
									  character.
			UG_ADO_DS_USE_SIMPLENEW - options allows users to choose between the
									  advanced append style, where new row will be
									  added to the bottom of the recordset, and the
									  Ultimate Grid standard append row.
							*Note:	  This feature is turned on by default and it
									  could be time consuming on large recordsets
									  or where DB connection is slow.  In these
									  cases this option should be disabled.

		Notifictions
			UG_ADO_DS_OPEN_CONN		- is sent just after the connection is opened,
									  param parameter passed in represents pointer
									  to the opened connection object.
			UG_ADO_DS_OPEN_RS		- is sent just after the recordset is opened,
									  param parameter passed in represents pointer
									  to the opened recordset object.
			UG_ADO_DS_SORTBY		- message is called by the SortBy method after
									  the sort string has been created.  It provides
									  ability for the developer to modify the SORT BY
									  portion of the SQL query that will be executed.
			UG_ADO_DS_UPDATE_RECORD	- is sent when the user moves off a record that
									  was edited and requires updating.  The param
									  parameter sent along represents the row number
									  of the updated record and it can be used to 
									  force update cancelation, just set this parameter
									  to -1.
			UG_ADO_DS_UPDATE_ERROR	- is sent when the update function failed.
									  The param parameter passed along contains
									  information on a pointer to a CString object
									  that represents the message that will be displayed
									  to the user.  Setting this string to "" (empty)
									  will prevent the dialog from showing and the user
									  will be forced to stay in the current row.
*************************************************************************/
#ifndef _ADOImpDatasource_H_
#define _ADOImpDatasource_H_

#include "UpdatedRow.h"

// prevent fetching small number (2 or 3) of rows, limiting number of calls
// to the database and at the same time improving performance.
#define MIN_FETCH_ROWS			50
// Define notifications datasource sends to the CUGCtrl::OnDataSourceNotify
#define UG_ADO_DS_OPEN_RS		100
#define UG_ADO_DS_OPEN_CONN		101
#define UG_ADO_DS_SORTBY		102
#define UG_ADO_DS_UPDATE_RECORD	103
#define UG_ADO_DS_UPDATE_ERROR	104
// Define datasource options that can be set with use of the SetOption function
#define UG_ADO_DS_SET_EDITMODE	110
#define UG_ADO_DS_USE_GHOSTROW	111
#define UG_ADO_DS_SET_FETCHSIZE	112
#define UG_ADO_DS_SET_ROWIDCHAR	113
#define UG_ADO_DS_USE_SIMPLENEW	114

class CADOImpDatasource :public CUGDataSource
{
public:
	CADOImpDatasource();
	virtual ~CADOImpDatasource();

	// Functions used to build up the SQL statement in separate pieces
	// when these functions are used, than Open can be called directly
	// instead of OpenSQL.
	virtual int SetCommand( CString command );
	virtual int SetFilter( CString filter );
	virtual int SetSort( CString sort );
	// Function used to retrieve the SQL query currently in use
	CString GetSQL();
	// Function used to set additional login information, if it is
	// not provided through the connection string.
	virtual int SetPassword( LPCTSTR user, LPCTSTR pass );

	// Oppening the record set.
	virtual int Open( LPCTSTR name, LPCTSTR option );
	virtual int OpenSQL( CString sql, CString conStr );
	virtual BOOL IsOpen();
	virtual int Close();

	// overriden CUGDatasource virtual functions and notifications
	virtual long GetNumRows();
	virtual int GetNumCols();
	virtual int GetColName(int col,CString * string);

	virtual int	GetCell(int col,long row,CUGCell *cell);
	virtual int	SetCell(int col,long row,CUGCell *cell);

	virtual int OnHitBottom(long numrows,long rowspast,long *rowsfound);
	virtual void OnRowChange(long oldRow,long newRow);
	
	virtual int AppendRow();
	virtual int DeleteRow(long row);

	virtual int OnEditStart(int col, long row,CWnd **edit);
	virtual int OnEditVerify(int col,long row,CWnd *edit,UINT *vcKey);
	virtual int OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag);

	// sorting
	virtual int SortBy(int *cols,int num,int flags);
	//options
	virtual int SetOption(int option,long param1,long param2);
	virtual int GetOption(int option,long& param1,long& param2);
	//transactions
	virtual int StartTransaction();
	virtual int CancelTransaction();
	virtual int FinishTransaction();

	// Additional functions that are specific to the ADO datasource:
	// function used to return 'true' number of rows in the recordset
	long GetNumRowsComplete();
	// Function that forces current changes to be made permanent
	int UpdateNow();
	// Function that cancels (undoes) current changes
	int CancelUpdates();
	// Function to force the datasource to re-fetch current block
	int RefreshData();

protected:
	int OpenConnection();
	int OpenRecordset();
	CString VarToString(_variant_t theVariant);

	// SQL process function
	int ParseSQLString( CString sql );

	int RefreshGrid( void );
	// row fetching
	int FetchNewRows( long row );
	_variant_t GetRowSArray( long row );
	// Get cell's data from rowset
	_variant_t GetDBCellData( int col, long row );
	_variant_t SetDBCellData( int col, CUGCell *pCell );
	// set cell's properties based on information retrieved from DB
	void PopulateCellFromDB( CUGCell *cell, _variant_t dbVariant );
	// save changes
	int UpdatePending( BOOL redraw = TRUE );
	// check if the recordset allows updates
	BOOL IsRecordsetUpdatable();

protected:
	_ConnectionPtr	m_pConnection;	// the connection
	_RecordsetPtr	m_pRecordSet;	// the recordset

	// row fetching
	long		m_nFetchedStarting;	// indicates relation between fetched
									// rows and the grid rows.
	long		m_nMaxFetchRows;	// maximum rows allowed for fetching, calculated value
	long		m_pcRowsObtained;	// number of rows fetched with the last fetch operation
	_variant_t	m_curRecords;		// safe array containing rows fetched from DB
	_variant_t	m_curBookmark;		// long integer representing book mark of the record that
									// was the first record in the last fetch operation.
									// This bookmark is used as point of reference for future
									// row fetch operations.
	long		m_nMinFetchRows;	// Long value used to define minimum number of records to
									// fetch from the database in one fetch operation.
									// This value can be changed with UG_ADO_DS_SET_FETCHSIZE
									// option.

	// editing
	BOOL		m_bAllowEdits;		// Flag indicating if editing is enabled or not;
	BOOL		m_bEditingConfirmed;// Flag used to backup state of the m_bAllowEdits,
									// if m_bAllowEdits is set to TRUE then the datasource
									// also has to make sure that the recordset allows
									// updates.  After the check this flag will be set to TRUE
	// updating rowset
	int			m_iUpdatesPending;	// indicate number of rows to update
	BOOL		m_bUseGhostRow;		// flag indicating if we can use GhostRow
	long		m_nCurGhostRow;		// long identifying current location of the G.R.
	long		m_nOldGhostRow;		// long indentifying previous location of GR (usually -1)
									// except when user is editing the GR.
	// inserting new rows
	CUpdatedRow	m_hUpdatedRow;		// link list to temporary hold the new row info
	BOOL		m_bNewRowAdded;		// this flag is used by the auto-updates to pickup
									// newly added rows.
	BOOL		m_bUseSimpleNew;	// this flag is used by the AppendRow function to determine
									// if user wants to use the standard AppendRow functionality
									// or the advanced behavior where new rows will be added to the
									// bottom of the recordset and will by default have focus.

	CString		m_sCurRowID;		// member variable used to identify current row in a side heading
	CString		m_dbConnection;		// source string for the connection
	CString		m_User;				// user login name
	CString		m_Password;			// user login password
	CString		m_Command;			// command to execute (SQL statement without WHERE and 
									// ORDER BY clauses)
	CString		m_Filter;			// filter to be used (WHERE clause)
	CString		m_SortOrder;		// sort order to be used (ORDER BY clause)
	int			m_numCols;			// number of columns in the recordset
};

#endif // _ADOImpDatasource_H_
