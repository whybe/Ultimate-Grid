/***************************************************
Ultimate Grid 97 for MFC

  Copyright © The Ultimate Toolbox 2007, All Rights Reserved

  ODBC Data Source Class

  Standard Return Values: UG_SUCCESS - success (0)
						  UG_NA		 - not available (-1)
						  1 and up   - error codes
****************************************************/


#include "stdafx.h"
#include "UGCtrl.h"
#include "UGODBC.h"
#include "UGStrOp.h"

#include "sqltypes.h"
#include "sqlucode.h"

/***************************************************
****************************************************/
CUGODBCDatasource::CUGODBCDatasource():	m_Db(NULL), 
										m_Record(NULL),
										m_Fields(NULL),
										m_RecordSetAttached(FALSE),
										m_nCurrentRow(0),
										m_totalRows(0),
										m_tableCount(0),
										m_nRecOptions(0)
	{
		m_strSQL.		Empty();
		m_connectString.Empty();
		m_buf.			Empty();
	}
/***************************************************
****************************************************/
CUGODBCDatasource::~CUGODBCDatasource(){
	Close();
}

/***************************************************
CUGODBCDatasource::Browse : call this function to invoke the
ODBC driver to prompt for connection params.

    This function gathers information about all of the  
    tables in the datasource selected, storing the information
    in the array m_dsInfoArray for later retrieval.  

    This function also saves the resulting connect string for
    later use.  

****************************************************/
int CUGODBCDatasource::Browse(HWND hwnd){


	HENV henv;
	HDBC hdbc;
	HSTMT hstmt;
	RETCODE retcode;
	SQLTCHAR  buf[255];

	SQLTCHAR  sqlerror[255];
	SQLTCHAR  sqlstate[255];
	SDWORD nerr, cbVal;
	SWORD num;

	// for table info....
	SQLTCHAR	szTableQualifier[128];
	SQLTCHAR	szTableOwner[128];
	SQLTCHAR	szTableName[128];
	SQLTCHAR	szTableType[128];
	SQLTCHAR	szRemarks[255];

	// close open db
	Close();
	
	// clean up previous data
	m_connectString = "";

	m_tableCount = 0;


	
	retcode = SQLAllocEnv(&henv);              // Environment handle 

	if (retcode == SQL_ERROR) {
		AfxMessageBox(_T("Probable memory allocation error in SQLAllocEnv"));
		return (int) retcode;
	}


	retcode = SQLAllocConnect(henv,&hdbc);

	if (retcode == SQL_ERROR) {
		ReportSQLError(henv, SQL_NULL_HDBC, SQL_NULL_HSTMT, retcode, _T("SQLAllocConnect"));
		SQLFreeEnv(henv);
		return (int) retcode;
	}		

	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {

		// Set login timeout to 5 seconds. 
		 SQLSetConnectOption(hdbc, SQL_LOGIN_TIMEOUT, 5);
		// Connect to data source 
        // this should cause the ODBC Driver to come up with the
		// necessary prompts to form a connect string...
		retcode = SQLDriverConnect(hdbc,hwnd,(SQLTCHAR*)_T(""),
							0,buf,254,&num,SQL_DRIVER_PROMPT);

							
		if (retcode != SQL_SUCCESS) {
			#ifdef UG_REPORT_ERROR
				ReportSQLError(henv, hdbc, SQL_NULL_HSTMT, retcode, _T("SQLDriverConnect"));
			#endif
			// user probably cancelled connection...
                if (retcode != SQL_SUCCESS_WITH_INFO) {
    			SQLFreeConnect(hdbc);
    			SQLFreeEnv(henv);
				return retcode;
                }
		}

			

		if(retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO){
			// retcode from SQLDriverConnect...
			// should be cool to try to open a recordset with the info 
			// we have here in buf...
			CDatabase db;
			TCHAR buf2[255];
			UGStr::stprintf(buf2,255,_T("ODBC;%s"),buf);

            // now we have the connect string in buf2 - but wait to
            // see if we can actually open the db before storing 
            // it in m_connectString...

			try {
				retcode = db.Open(NULL,FALSE,FALSE,buf2);
			}		
			catch(CMemoryException* e){
				#ifdef UG_ODBC_REPORTERROR
					e->ReportError();
				#endif
				e->Delete();
				AfxAbort();
			}
			catch(CDBException* e){
				// standard procedure for ODBC - save the 
				// RETCODE code for the return value - 
				// Report on the error - optional -
				// use Delete to delete the exception object
				RETCODE er = e->m_nRetCode;
				#ifdef UG_ODBC_REPORTERROR
					e->ReportError();
				#endif
				e->Delete();
    			SQLFreeConnect(hdbc);
    			SQLFreeEnv(henv);
				return (int)er;
			}

			// now, given an open connection, we should
			// be able to set up a statement handle..
			retcode = SQLAllocStmt(hdbc, &hstmt);

			
			switch (retcode) {
				case SQL_SUCCESS: {
				//	AfxMessageBox("SQLAllocStmt returned success ");
				//	AfxMessageBox((LPCSTR)buf);
					break;
				}
				case SQL_SUCCESS_WITH_INFO:{
					AfxMessageBox(_T("SQLAllocStmt returned success with info"));
					// this indicates that there is a driver specific warning
					// to be investigated...
					SQLError(SQL_NULL_HENV,hdbc,SQL_NULL_HSTMT,sqlstate,
											&nerr,sqlerror,254,&num);
					AfxMessageBox((LPCTSTR)sqlstate);
					AfxMessageBox((LPCTSTR)sqlerror);
					break;
				}
				case SQL_NO_DATA_FOUND:{
					AfxMessageBox(_T("SQLAllocStmt returned no data found"));
					break;
				}
				case SQL_ERROR:{
					AfxMessageBox(_T("SQLAllocStmt returned sql error"));
					SQLError(SQL_NULL_HENV,hdbc,SQL_NULL_HSTMT,sqlstate,&nerr,sqlerror,254,&num);
					AfxMessageBox((LPCTSTR)sqlstate);
					AfxMessageBox((LPCTSTR)sqlerror);
					break;
				}
				case SQL_INVALID_HANDLE:{
					AfxMessageBox(_T("SQLDriverConnect returned invalid handle"));
					break;
				}
				default:
					break;
				}

				// ok - now lets see if we can enumerate the tables
				// contained in the database...

				retcode = SQLTables(hstmt,	// statement handle for
												// retrieved results
						  NULL,					// szTableQualifier
						  SQL_NTS,				// cbTableQualifier
						  NULL,					// szTableOwner
						  SQL_NTS,				// cbTableOwner
						  NULL,					// szTableName
						  SQL_NTS,				// cbTableName
						  (SQLTCHAR*)_T("'TABLE','VIEW',\
						  'SYSTEM TABLE','GLOBAL TEMPORARY','LOCAL TEMPORARY',\
						  'ALIAS','SYNONYM'"),			// szTableType (list of
												// table types to match)
						  SQL_NTS);					// cbTableTypes
				
                if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO) {
					ReportSQLError(henv, hdbc, hstmt, retcode, _T("SQLTables"));
        			SQLFreeStmt(hstmt, SQL_DROP);
		        	SQLDisconnect(hdbc);
        			SQLFreeConnect(hdbc);
			        SQLFreeEnv(henv);
                    return retcode;         // unable to query tables 
                                            // User should see message box
                }


                // now - can we iterate through the tables found?
#ifndef _UNICODE
				SQLBindCol(hstmt, 1, SQL_C_CHAR, szTableQualifier, 128, &cbVal);
				SQLBindCol(hstmt, 2, SQL_C_CHAR, szTableOwner, 128, &cbVal);
				SQLBindCol(hstmt, 3, SQL_C_CHAR, szTableName, 128, &cbVal);
				SQLBindCol(hstmt, 4, SQL_C_CHAR, szTableType, 128, &cbVal);
				SQLBindCol(hstmt, 5, SQL_C_CHAR, szRemarks, 255, &cbVal);
#else
				SQLBindCol(hstmt, 1, SQL_UNICODE_CHAR, szTableQualifier, 128, &cbVal);
				SQLBindCol(hstmt, 2, SQL_UNICODE_CHAR, szTableOwner, 128, &cbVal);
				SQLBindCol(hstmt, 3, SQL_UNICODE_CHAR, szTableName, 128, &cbVal);
				SQLBindCol(hstmt, 4, SQL_UNICODE_CHAR, szTableType, 128, &cbVal);
				SQLBindCol(hstmt, 5, SQL_UNICODE_CHAR, szRemarks, 255, &cbVal);
#endif
				retcode = SQLFetch(hstmt);

				if (retcode == SQL_ERROR || retcode == SQL_SUCCESS_WITH_INFO)
					ReportSQLError(henv, hdbc, hstmt, retcode, _T("SQLFetch"));

				if (retcode != SQL_NO_DATA_FOUND)
					m_connectString = (LPTSTR)buf2;	// save connection string!


                // Subsequent calls to GetTableInfo will be able to 
                // retrieve this information...
				while (retcode != SQL_NO_DATA_FOUND) {
					UGStr::tcscpy((LPTSTR)m_dsInfoArray[m_tableCount].tableQualifier,128,(LPTSTR)szTableQualifier);
					UGStr::tcscpy((LPTSTR)m_dsInfoArray[m_tableCount].tableOwner,128, (LPTSTR)szTableOwner);
					UGStr::tcscpy((LPTSTR)m_dsInfoArray[m_tableCount].tableName,128,(LPTSTR)szTableName);
					UGStr::tcscpy((LPTSTR)m_dsInfoArray[m_tableCount].tableType,128,(LPTSTR)szTableType);
					UGStr::tcscpy((LPTSTR)m_dsInfoArray[m_tableCount].remarks,255,(LPTSTR)szRemarks);
					
					m_tableCount++;
					if (m_tableCount >= MAX_TABLES)
						break;
					retcode = SQLFetch(hstmt);

				}
			}
			//free these...
			SQLFreeStmt(hstmt, SQL_DROP);
			SQLDisconnect(hdbc);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
		 }
	

	return UG_SUCCESS;

}

/***************************************************
These open functions provide for opening the datasource
with different forms of information.  If the m_ConnectString
is not NULL, it will be used to open the database, else the
code will attempt to form a connect string based on the 
parameters passed in.

If the Browse method is called to invoke the ODBC driver
manager to prompmt the user for the datasource params, the 
connect string will be set.  Or, use SetConnectString().

****************************************************/
int CUGODBCDatasource::Open(LPCTSTR database,LPCTSTR table){
	return Open(database,table,0,CRecordset::dynaset,0,NULL,NULL);
}
/***************************************************
****************************************************/
int CUGODBCDatasource::OpenSQL(LPCTSTR database,LPCTSTR sql){
	return OpenSQL(database,sql,0,CRecordset::dynaset,0,NULL,NULL);
}
/***************************************************
****************************************************/
int CUGODBCDatasource::Open(LPCTSTR database,LPCTSTR table,DWORD dbOptions,UINT recType,DWORD recOptions,LPCSTR user,LPCSTR pass){
	return OpenSQL(database,table,dbOptions,recType,recOptions,user,pass);
}
/***************************************************
****************************************************/
int CUGODBCDatasource::OpenSQL(LPCTSTR database,LPCTSTR sql,DWORD dbOptions,UINT recType,DWORD recOptions,LPCSTR user,LPCSTR pass){

	//make sure that there are no open databases
	Close();

	//create and open the database
	TCHAR buf[256];
	m_Db = new CDatabase();

	// if the connectstring was set up using a call to Browse
	// we shouldn't have to build one from the parameters passed in.

	if(!m_connectString.IsEmpty()) {
		UGStr::stprintf(buf,256,_T("%s"),m_connectString);		// from OpenEx()
	} else {

		//create the connect string
		if(user!=NULL && pass!=NULL){
			UGStr::stprintf(buf,256,_T("ODBC;DSN=%s;UID=%s;PWD=%s"),database,user,pass);
		}
		else if(user!=NULL){
			UGStr::stprintf(buf,256,_T("ODBC;DSN=%s;UID=%s"),database,user);
		}
		else if(pass!=NULL){
			UGStr::stprintf(buf,256,_T("ODBC;DSN=%s;PWD=%s"),database,pass);
		}
		else{
			UGStr::stprintf(buf,256,_T("ODBC;DSN=%s"),database);
		}
	}

	//open the database
	int errorRet;
	try{
		// params:
		// 1. lpszDSN		set to NULL - we use the connect string instead
		// 2. bExclusive	not supported - MFC ASSERTS if TRUE
		// 3. bReadOnly		using FALSE - recorset would inherit this
		// 4. lpszConnect	our connect string ("ODBC;DSN=...")
		// 5. bUseCursorLib use with caution - if TRUE, recordset
        //                  will be cached on client, and Dynasets
        //                  may not be supported (e.g. SQL Server)
		errorRet = m_Db->Open(NULL,FALSE,FALSE,buf,FALSE);

	}
	// AfxAbort is the only hope...
		catch(CMemoryException* e){
			#ifdef UG_ODBC_REPORTERROR
				e->ReportError();
			#endif
		e->Delete();
		AfxAbort();
	}
	catch(CDBException* e){
 		TRACE(_T("CDBException %d, caught at line %d in %s:\n'%s'\n"), 
				e->m_nRetCode,__LINE__,_T("ugodbc.cpp"), e->m_strError);
		RETCODE er = e->m_nRetCode;
		#ifdef UG_ODBC_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();

		delete m_Db;
		m_Db = NULL;

		return (int)er;
	}

	if(errorRet == 0){
		delete m_Db;
		m_Db = NULL;
		return 1;
	}

	//create and open the recordset
	m_Record = new CUGRecordset(m_Db);

	if(!m_connectString.IsEmpty())
		m_Record->m_defaultConnect = m_connectString;
 
	TRY{

        errorRet = m_Record->Open(recType,sql,recOptions);
		m_strSQL = sql;
		m_nRecType = recType;
		m_nRecOptions = recOptions;

	}
	CATCH_ALL(e) {
		#ifdef UG_ODBC_REPORTERROR
			e->ReportError();
		#endif

	}
	END_CATCH_ALL

	if(!errorRet) {
		delete m_Record;
		m_Record = NULL;
		return 1;		// failed to open recordset
	}

	try{
		m_Record->MoveFirst();
	}
	catch(CMemoryException* e){
		#ifdef UG_ODBC_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		AfxAbort();
	}
	catch(CDBException* e){
		// standard procedure for ODBC - save the 
		// RETCODE code for the return value - 
		// Report on the error - optional -
		// use Delete to delete the exception object
 		TRACE(_T("CDBException %d, caught at line %d in %s:\n'%s'\n"), 
				e->m_nRetCode,__LINE__,"ugodbc.cpp", e->m_strError);
		RETCODE er = e->m_nRetCode;
		#ifdef UG_ODBC_REPORTERROR
			if(1016 != e->m_nRetCode)
				e->ReportError();
		#endif
			e->Delete();
		
		// probably no records in file
		m_nCurrentRow = -1;

	}
	catch(CFileException* e){
		RETCODE er = e->m_cause;
		#ifdef UG_ODBC_REPORTERROR
				e->ReportError();
		#endif
				e->Delete();
		
		return (int)er;
	}

	
	m_nCurrentRow = 0;

	return UG_SUCCESS;
}

/***************************************************
****************************************************/
void CUGODBCDatasource::SetConnectString(CString * string) {
      m_connectString = *string;
}
/***************************************************
****************************************************/
CString * CUGODBCDatasource::GetConnectString() {
	return &m_connectString;
}

/***************************************************
****************************************************/
int CUGODBCDatasource::Close(){

	if(m_Fields != NULL){
		delete[] m_Fields;
		m_Fields = NULL;
	}
	if(m_Record != NULL){
		if(m_RecordSetAttached == FALSE){
			if(m_Record->IsOpen())	// could happen - not likely... 
				m_Record->Close();
			delete m_Record;
			m_Record = NULL;
		}
		m_RecordSetAttached = FALSE;
	}

	if(m_Db != NULL){
		if(m_Db->IsOpen())
			m_Db->Close();
		delete m_Db;
		m_Db = NULL;
	}
	
	m_nCurrentRow = 0;
 	
	return UG_SUCCESS;
}

/***************************************************
****************************************************/
int CUGODBCDatasource::DeleteRow(long row){

	int er = 0;

	if(m_Record == NULL)
		return UG_ERROR;

	if(m_Record->CanUpdate() == FALSE)
		return UG_ERROR;

	if(row < 0)
		return UG_ERROR;

	if(m_Record->IsEOF() && m_Record->IsBOF())
		return UG_ERROR;

    // Position recordset
    er = GotoRecord(row);
    if(UG_SUCCESS != er)
        return er;
	
	try{
		m_Record->Delete();
	}
	catch(CDBException* e){
 		TRACE(_T("CDBException %d, caught at line %d in %s:\n'%s'\n"), 
				e->m_nRetCode,__LINE__,_T("ugodbc.cpp"), e->m_strError);
		er = e->m_nRetCode;
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
	}


	// sync m_nCurrent with CRecordset
    Reset();

	return UG_SUCCESS;
}

/***************************************************
****************************************************/
int	CUGODBCDatasource::GetCell(int col,long row,CUGCell *cell){

	if(m_Record == NULL)
		return 1;
    
    if(row < 0) {
        if(row == -1) {
            CString cs;
            GetColName(col,&cs);
            cell->SetText(cs);
        }

        return UG_SUCCESS;
    }

    // Handle the side heading (assumes only one, 
    // col = -1).  Comments hide two different methods.
	if(col <0){
        // Number the side headings
//        TCHAR buf[20];
//        CUGStr::stprintf(buf,20, _T("%d"),row);
//        cell->SetText(buf);
//        cell->SetAlignment(UG_ALIGNRIGHT);

        // ... or use an 'arrow' to indicate current row
		if(m_ctrl->GetCurrentRow() == row){
			cell->SetCellType(UGCT_ARROW);
		}
	
		return UG_SUCCESS;
	}


    // Position recordset
    if(row != m_nCurrentRow) 
    {
        int er = GotoRecord(row);
        if(UG_SUCCESS != er)
            return er;
    }

	//get the field
	CString string;
	
	// get the field info object from the recordset
	SQLColumnInfo* cfi = m_Record->GetFieldInfo(col);

	// if field is NULL, return " " in string 
	if(m_Record->IsFieldNull(cfi->pValue)) {
		string = "";
	}
	else {
		
		switch(cfi->nSQLType){
			case SQL_BINARY:
			case SQL_VARBINARY:
			case SQL_LONGVARBINARY:{
				//How to  display?  Need to know more about what type of
				//object this represents ... 
				string = _T("*Blob File*");
				break;
			}
			case SQL_TINYINT:{
				string.Format(_T("%d"),*(unsigned  char *) cfi->pValue);
				break;	
			}
			case SQL_TIMESTAMP:{
				COleDateTime	cdt(((TIMESTAMP_STRUCT*)(cfi->pValue))->year,
									((TIMESTAMP_STRUCT*)(cfi->pValue))->month,
									((TIMESTAMP_STRUCT*)(cfi->pValue))->day,
									((TIMESTAMP_STRUCT*)(cfi->pValue))->hour,
									((TIMESTAMP_STRUCT*)(cfi->pValue))->minute,
									((TIMESTAMP_STRUCT*)(cfi->pValue))->second);

				if (cdt.GetStatus() == COleDateTime::valid)
					string = cdt.Format();
				else
					string = _T(" ");
				break;
			}
			case SQL_DATE:{		
				string = ((CTime*)(cfi->pValue))->Format( _T("%d %b %Y") );
				break;
			}
			case SQL_TIME:{
				string = ((CTime*)(cfi->pValue))->Format( _T("%H:%M:%S") );
				break;
			}
			
			case SQL_BIT:{
				// again, season to tase - True, False, 1, 0, etc...
				if (*(BOOL*)cfi->pValue)
					string = _T("Yes");
				else
					string = _T("No");
				break;
			}
			case SQL_CHAR:
			case SQL_VARCHAR:
			case SQL_WCHAR:
			case SQL_WVARCHAR:{
				string = *(CString*)cfi->pValue;
				break;
			}
			case SQL_LONGVARCHAR:
			case SQL_WLONGVARCHAR:{
				string = *(CString*)cfi->pValue;
				break;
			}
		
			case SQL_SMALLINT:{
				string.Format(_T("%d"),*(int *) cfi->pValue);
				break;
			}
			case SQL_INTEGER:{
				string.Format(_T("%ld"),*(long *) cfi->pValue);
				break;
			}
			case SQL_NUMERIC:
			case SQL_DECIMAL:
			case SQL_REAL:
			case SQL_FLOAT:{
				string.Format(_T("%.2f"),*(float *) cfi->pValue);
				break;
			}
			case SQL_DOUBLE:{
				string.Format(_T("%.2f"),*(double *) cfi->pValue);
				break;
			}
			case SQL_BIGINT:
				string.Format(_T("%.0f"),*(double *) cfi->pValue);
				break;
			default: {
				AfxMessageBox(_T("Type not found!"));
					 }
		}
	}	
	
	cell->SetText(string);
	

	return UG_SUCCESS;
}
/***************************************************
****************************************************/
int	CUGODBCDatasource::SetCell(int col,long row,CUGCell *cell){
	
    // Position recordset
    int er = GotoRecord(row);
    if(UG_SUCCESS != er)
        return er;
	

	try {
		m_Record->Edit();
	}
			catch(CMemoryException* e){
		#ifdef UG_ODBC_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		AfxAbort();
	}
	catch(CDBException* e){
 	TRACE(_T("CDBException %d, caught at line %d in %s:\n'%s'\n"), 
			e->m_nRetCode,__LINE__,"ugodbc.cpp", e->m_strError);
		int er = e->m_nRetCode;
		#ifdef UG_ODBC_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		return er;
	}


	// ok - transfer the cell's contents to the proper 
	// field buffer and type...

	TRY {

        SetFieldValueFromCell(col, cell);
		m_Record->Update();

	}
	CATCH_ALL(e) {
	#ifdef UG_ODBC_REPORTERROR
		e->ReportError();
	#endif
	}
	END_CATCH_ALL;

   
	return UG_SUCCESS;
}


/***************************************************
****************************************************/
int CUGODBCDatasource::AppendRow(){

	if(m_Record == NULL)
		return 1;
	if(m_Record->CanAppend()==0)
		return 2;

	SQLColumnInfo	*pCI;			// for col attr and pValue
	
	int cols	=   GetNumCols();	// for loop

	try{
		// attempt to add blank record - all nulls...
		m_Record->AddNew();

		// ... so be selective about which fields to update...
		int dirty   =   0;
		for ( int i = 0; i < cols; i++) {
			pCI = m_Record->GetFieldInfo(i);
			if( pCI->nNullable &&		// can be NULL
				pCI->nUpdatable &&		// can be updated
			   !pCI->nAutoValue)		// is NOT autoincrement (redundant - 
										// probably covered by updateble)
			{
					m_Record->SetFieldDirty(pCI->pValue);
					dirty++;
			}
		}

		if(!dirty)
			TRACE(_T("Warning: no dirty fields on update in AppendRow()\n"));

		m_Record->Update();

	}
	catch(CDBException* e){
 		TRACE(_T("CDBException %d, caught at line %d in %s:\n'%s'\n"), 
				e->m_nRetCode,__LINE__,_T("ugodbc.cpp"), e->m_strError);
		int er = e->m_nRetCode;
		e->ReportError();
		e->Delete();
		return er;
	}

	// sync current with CRecordset after successful append!
	m_Record->MoveFirst();
	m_nCurrentRow = 0;

	return UG_SUCCESS;
}

/***************************************************
	AppendRow - this is a CUGDataSource override
	To use, you need to pass in an array of cells:

	// append an array of cells...
	int cols = m_odbc.GetNumCols();

	CUGCell **cellArray;

	// make array of cell pointers
	cellArray = new CUGCell*[cols];
		
	// fill with pointers to new cells
	for (int i = 0; i < cols; i++)		// will throw, but rarely...
		cellArray[i] = new CUGCell;


	// set some text...
	for (i = 0; i < cols; i++) {
		cellArray[i]->SetText("Test");
	}

	// call append row...
	m_odbc.AppendRow(cellArray, cols);


	// delete cells...
	for (i = 0; i < cols; i++) {
		delete cellArray[i];
		cellArray[i] = NULL;
	}

	// delete array of pointers
	delete [] cellArray;
   	cellArray = NULL;

****************************************************/
int CUGODBCDatasource::AppendRow(CUGCell **cellList,int numCells){

	int er = UG_SUCCESS;

	if(m_Record == NULL)
		return UG_ERROR;
	if(m_Record->CanAppend()==0)
		return UG_NA;

	try{
		m_Record->AddNew();		
	}
	catch(CDBException *e){
		int er = e->m_nRetCode;
 		TRACE(_T("CDBException %d, caught at line %d in %s:\n'%s'\n"), 
				e->m_nRetCode,__LINE__,_T("ugodbc.cpp"), e->m_strError);
		#ifdef UG_ODBC_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		return er;
	}
	
	for(int loop = 0;loop <numCells;loop++){
		er = SetFieldValueFromCell(loop, cellList[loop]);
		if(er != UG_SUCCESS)
			return er;
	}

	
	try{
		m_Record->Update();		
	}
	catch(CDBException *e){
 		TRACE(_T("CDBException %d, caught at line %d in %s:\n'%s'\n"), 
				e->m_nRetCode,__LINE__,_T("ugodbc.cpp"), e->m_strError);
		int er = e->m_nRetCode;
		#ifdef UG_ODBC_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		return er;
	}

	
	// sync current with CRecordset after successful append!
	m_Record->MoveFirst();
	m_nCurrentRow = 0;

	return UG_SUCCESS;
}

/***************************************************
****************************************************/
long CUGODBCDatasource::GetNumRows(){
	if(m_Record == NULL)
		return UG_NA;

	TRY{
		m_Record->MoveFirst();
	}
	CATCH_ALL(e){
		// shouldn't whine if no rows returned
		// so don't call report error..

		return (m_totalRows = 0);
	}
	END_CATCH_ALL

	return (m_totalRows = 1);

}
/***************************************************
****************************************************/
long CUGODBCDatasource::GetNumRowsComplete(){
	if(m_Record == NULL)
		return UG_NA;
	TRY{
		while(1)
			m_Record->MoveNext();
			//  this is the logical, though expensive
			//  way to get the record count.  MoveLast
			//  doesn't update the record count for
			//  performance reasons...
	}
	CATCH_ALL(e){
		#ifdef UG_ODBC_REPORTERROR
	//		e->ReportError();
		#endif
		return m_Record->GetRecordCount();
	}
	END_CATCH_ALL

// *NOTE* Use this function with caution!
// This took 2 minutes 40 seconds to read through 
// 129550 records of a db (dynaset) on a local drive.
	
}
/***************************************************
****************************************************/
int CUGODBCDatasource::GetNumCols(){
	
	if(m_Record == NULL)
		return UG_NA;
	return m_Record->m_nFields;
}
/***************************************************
****************************************************/
int CUGODBCDatasource::GetColName(int col,CString * string){
	if(m_Record == NULL)
		return UG_NA;
	
	if((UINT)col < 0 || (UINT)col >= m_Record->m_nFields)
		return 1;

	SQLColumnInfo * cfi = m_Record->GetFieldInfo(col);

	if (cfi == NULL)
		return UG_NA;
	else {
		*string = cfi->strName;
		// if name empty, try label...(see CUGRecordset::BindFields)
		if(string->IsEmpty())
			*string = cfi->strLabel;
		return UG_SUCCESS;
	}
}
/***************************************************

	0-string 1-bool 2-short 3-long 4-float 
	5-double 6-currency 7-date 8-time
	8-memo 9- blob 10-ole  11-other
****************************************************/
int CUGODBCDatasource::GetColType(int col,int *type){
	if(m_Record == NULL)
		return UG_NA;
	
	if((UINT)col < 0 || (UINT)col >= m_Record->m_nFields)
		return 1;

	SQLColumnInfo*	cfi = m_Record->GetFieldInfo(col);

	if (cfi == NULL)
		return UG_NA;
	else {
		*type = cfi->nSQLType;
		return UG_SUCCESS;
	}
}		
													
/***************************************************
****************************************************/
int CUGODBCDatasource::OnHitBottom(long numrows,long rowspast,long *rowsfound){

	numrows --;

	long newrow = numrows +rowspast;

	if( newrow == m_nCurrentRow){
		if(m_Record->IsEOF( ))
			return 1;
		*rowsfound = rowspast;
		return UG_SUCCESS;
	}

	while(m_nCurrentRow < newrow){
		if(m_Record->IsEOF( ))
			return 1;
		
		TRY {
			m_Record->MoveNext();
		}
		CATCH_ALL(e) {
			#ifdef UG_ODBC_REPORTERROR
				e->ReportError();
			#endif
			return 1;
		}
		END_CATCH_ALL
	
		m_nCurrentRow++;
		m_totalRows++;
	}
	if(m_Record->IsEOF( ))
		numrows ++;

	*rowsfound = m_nCurrentRow - numrows;
	if(*rowsfound <0)
		*rowsfound =0;

	return UG_SUCCESS;
}

/***************************************************
****************************************************/
int CUGODBCDatasource::Reset(){

	m_nCurrentRow = 0;

	if(m_Record != NULL){
		if(m_Record->IsEOF() && m_Record->IsBOF()){
			return 1;
		}
		else{
			
			TRY {
				m_Record->MoveFirst();
			}
			CATCH_ALL(e) {
				#ifdef UG_ODBC_REPORTERROR
					e->ReportError();
				#endif
				return -1;
			}
			END_CATCH_ALL
		}
	}

	return UG_SUCCESS;
}
/***************************************************
****************************************************/
int CUGODBCDatasource::AttachRecordSet(CUGRecordset* rset){

	return UG_NA;

	// Aug 97
	// TODO: Insert code that will effectively 'clone' a 
	// recordset by:
	//
	// getting the defaultconnect string
	// getting the default SQL
	// closing and calling open on m_Record
	//
	// the goal here is to provide a grid view of an existing
	// recordset in the host application.


}

/***************************************************
****************************************************/
int CUGODBCDatasource::FindNext(CString *string, int *col, long *row, int flags){
	
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
/***************************************************
ReportErrorSql could be enhanced to take THIS_FILE, __LINE__, etc.
****************************************************/
void CUGODBCDatasource::ReportSQLError(HENV henv,
							  HDBC hdbc,
							  HSTMT hstmt,
							  RETCODE retcode,
							  LPCTSTR func) 
{
	TCHAR 			buf[512];
	SQLTCHAR		szSqlState[255];	
	SQLTCHAR		szErrorMsg[254];	
	SDWORD			pfNativeError;	
	SWORD			cbErrorMsgMax = 254;	
	SWORD		 	pcbErrorMsg;
	WORD			rc;

	rc = SQLError(henv, hdbc, hstmt, szSqlState, &pfNativeError, 
		szErrorMsg, cbErrorMsgMax, &pcbErrorMsg);

	if (rc == SQL_NO_DATA_FOUND || rc == SQL_ERROR)
		UGStr::stprintf(buf,512,_T("An unknown error occurred in %s"), func);
	else 
		UGStr::stprintf(buf,512,_T("SQL_ERROR retcode in function:%s  SqlState: %s\nError: %s"), func, szSqlState, szErrorMsg);

	AfxMessageBox(buf);

	return;
}



/***************************************************
GetTableInfo	call this function after Browse.
				By passing index in a loop, one
				can retrieve information for each
				table in the ODBC datasource.
****************************************************/
SQLDatasourceInfo * CUGODBCDatasource::GetTableInfo(int index) {
	if(m_tableCount == 0 || index >= m_tableCount)
		return NULL;
	return &m_dsInfoArray[index];
}

/***************************************************
	SetFieldValueFromCell()

	Buffers for each column were allocated in 
	BindFields of the CUGRecordset, and pointers
	(pValue) to these buffers stored in the ColumnInfo
	structs.
	
	Assume that Edit or Addnew has been 
	called, and update will be invoked by caller.
****************************************************/
int CUGODBCDatasource::SetFieldValueFromCell(int col, CUGCell *cell) {

	ASSERT_VALID(m_Record);
	if (NULL == m_Record)
		return UG_NA;

	CString text;
	cell->GetText(&text);

	SQLColumnInfo* cfi = m_Record->GetFieldInfo(col);

	// check updatability of field first...
	if(	!cfi->nUpdatable ||		// can't be updated
		cfi->nAutoValue)		// is autoincrement 
			return UG_SUCCESS;

	
	switch(cfi->nSQLType){

		case SQL_DATE: {

			LPCTSTR data = text.operator LPCTSTR ();

			COleVariant  cov(data);
			COleDateTime covdate(cov);

			if(covdate.m_status != 0)	// invalid date
				break;


			((TIMESTAMP_STRUCT*)(cfi->pValue))->year = (SWORD) covdate.GetYear();
			((TIMESTAMP_STRUCT*)(cfi->pValue))->month= (UWORD) covdate.GetMonth();
			((TIMESTAMP_STRUCT*)(cfi->pValue))->day  = (UWORD) covdate.GetDay();
			((TIMESTAMP_STRUCT*)(cfi->pValue))->hour = (UWORD) 0;
			((TIMESTAMP_STRUCT*)(cfi->pValue))->minute=(UWORD) 0;
			((TIMESTAMP_STRUCT*)(cfi->pValue))->second=(UWORD) 0;
				
			break;
		}
		case SQL_TIME: {

			LPCTSTR data = text.operator LPCTSTR ();

			COleVariant  cov(data);
			COleDateTime covdate(cov);

			if(covdate.m_status != 0)	// invalid date
				break;


			((TIMESTAMP_STRUCT*)(cfi->pValue))->year = (SWORD) 0;
			((TIMESTAMP_STRUCT*)(cfi->pValue))->month= (UWORD) 0;
			((TIMESTAMP_STRUCT*)(cfi->pValue))->day  = (UWORD) 0;
			((TIMESTAMP_STRUCT*)(cfi->pValue))->hour = (UWORD) covdate.GetHour();
			((TIMESTAMP_STRUCT*)(cfi->pValue))->minute=(UWORD) covdate.GetMinute();
			((TIMESTAMP_STRUCT*)(cfi->pValue))->second=(UWORD) covdate.GetSecond();
				
			break;
		
		
		}
		case SQL_TIMESTAMP:{
		
			LPCTSTR data = text.operator LPCTSTR ();

			COleVariant  cov(data);
			COleDateTime covdate(cov);

			if(covdate.m_status != 0)	// invalid date
				break;


			((TIMESTAMP_STRUCT*)(cfi->pValue))->year = (SWORD) covdate.GetYear();
			((TIMESTAMP_STRUCT*)(cfi->pValue))->month= (UWORD) covdate.GetMonth();
			((TIMESTAMP_STRUCT*)(cfi->pValue))->day  = (UWORD) covdate.GetDay();
			((TIMESTAMP_STRUCT*)(cfi->pValue))->hour = (UWORD) covdate.GetHour();
			((TIMESTAMP_STRUCT*)(cfi->pValue))->minute=(UWORD) covdate.GetMinute();
			((TIMESTAMP_STRUCT*)(cfi->pValue))->second=(UWORD) covdate.GetSecond();
				
			break;
		}
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_LONGVARCHAR:
		case SQL_WCHAR:
		case SQL_WVARCHAR:
		case SQL_WLONGVARCHAR:{
			*(CString*) cfi->pValue = text;
			break;
		}
		case SQL_BIGINT:
		case SQL_DOUBLE:{
			*(double*) cfi->pValue = _tcstod(text,NULL);
			break;
		}
		case SQL_INTEGER:{
			*(long*) cfi->pValue  = _ttol(text);
			break;
		}
		case SQL_BIT:{
			if(_ttol(text))
				*(BOOL*) cfi->pValue = TRUE;
			else
				*(BOOL*) cfi->pValue = FALSE;
    		break;
		}
		case SQL_NUMERIC:
		case SQL_REAL:
		case SQL_DECIMAL:
		case SQL_FLOAT:{
			*(float*) cfi->pValue = (float)_tcstod(text,NULL);
			break;
		}
		case SQL_SMALLINT:{
			*(int*) cfi->pValue = _ttoi(text);
			break;
		}
		case SQL_TINYINT:{
			*(TCHAR*) cfi->pValue = text[0];
			break;	
		}
		case SQL_BINARY:
		case SQL_VARBINARY:
		case SQL_LONGVARBINARY:{
			return UG_NA;				// unsupported edit...
			break;
		}
		// oops...
		default: {
			ASSERT(0);
		}
	}	
	return UG_SUCCESS;
}



/***************************************************
  GetRecordset returns the CUGRecordset pointer
****************************************************/
CUGRecordset* CUGODBCDatasource::GetRecordset(){
		return m_Record;
}

/***************************************************
flags - UG_SORT_ASSENDING or UG_SORT_DESCENDING
****************************************************/
int CUGODBCDatasource::SortBy(int col,int flags){
	return SortBy(&col,1,flags);
}

/***************************************************
	SortBy()

	This is intended to simplify life by allowing
	the user to use the built in SortBy method of
	CUGCtrl.  There is another strategy that can 
	be used - if the original query had no ORDER BY
	clause, simply set the m_strSort of the recordset
	(GetRecordset()->m_strSort = ...) then call 
	Requery() (on the recordset)

****************************************************/
int CUGODBCDatasource::SortBy(int *cols,int num,int flags)
{
	int loop;
	SQLColumnInfo* cfi;

	// can't use blobs, memos in ORDER BY...
	for (loop = 0; loop < num; loop++) 
	{
		cfi = m_Record->GetFieldInfo(cols[loop]);
	
		switch(cfi->nSQLType)
		{
		case SQL_LONGVARCHAR:
			#ifdef UG_ODBC_REPORTERROR
				AfxMessageBox(_T("Sort not supported for memo type."));
			#endif
			return UG_NA;
			break;
		case SQL_BINARY:
		case SQL_VARBINARY:
		case SQL_LONGVARBINARY:
			#ifdef UG_ODBC_REPORTERROR
				AfxMessageBox(_T("Sort not supported for OLE objects."));
			#endif
			return UG_NA;
			break;
		default:
			break;
		}
	} 

    CString strOrderBy = _T(" ORDER BY ");
    CString strColName;
	CString	strSQL;
    
    try
    {
    	strSQL = m_strSQL;
		// remove any previous terminators
		strSQL.TrimRight();
		strSQL.TrimRight( _T(";") );

		// remove previous ORDER BY...
		CString strTemp = strSQL;
		strTemp.MakeUpper();
		int loc = strTemp.Find(_T("ORDER BY"));		// ok ok will fail if
													// field name is [SORT ORDER BYTE]
		if (-1 != loc) {
			strSQL = strSQL.Left(loc);
		}

		for(loop = 0;loop < num;loop++) 
		{
			if ( loop > 0 )
			{
				strColName.Format( _T(", %d"), cols[loop] + 1 );
			}
			else 
			{
				strColName.Format( _T("%d"), cols[loop] + 1 );
			}
			strOrderBy += strColName;
		}
    
		strSQL.TrimRight();

		if ( flags == UG_SORT_DESCENDING )
		{
			strOrderBy += _T(" DESC");
		}
		strSQL += strOrderBy + _T(";");

		int res = m_Record->Open(m_nRecType,strSQL,m_nRecOptions);
		if(FALSE == res) 
		{
			// oops - that didn't work.  One possible scenario is that we tried to 
			// tack our ORDER BY clause using a calculated field, which gives
			// 'too few parameters' error.

			// So, we'll try to go back to what we had...
			res = m_Record->Open(m_nRecType,m_strSQL,m_nRecOptions);
			if(FALSE == res)
				return UG_ERROR;	// leaving m_strSQL alone
		}
		else 
		{
			m_strSQL = strSQL;
		}
	}
    catch(CMemoryException* e)
	{
		#ifdef UG_ODBC_REPORTERROR
			e->ReportError();
		#endif
        e->Delete();
        AfxAbort();
    }
    catch(CDBException* e)
	{
		int er = e->m_nRetCode;
 		TRACE(_T("CDBException %d, caught at line %d in %s:\n'%s'\n"), 
				e->m_nRetCode,__LINE__,_T("ugodbc.cpp"), e->m_strError);
		#ifdef UG_ODBC_REPORTERROR
			e->ReportError();
		#endif
        e->Delete();
        return er;
    }

	return UG_SUCCESS;
}

/**********************************

  GetCurPos is a debug tool - useful to 
  check if the underlying recordset's 
  current record is available.

  returns -2 if record pointer undefined,
          -1 if record at BOF
          or current record.

  AFX_CURRENT_RECORD_UNDEFINED = -2
  AFX_CURRENT_RECORD_BOF = -1

  *************************************/
long CUGODBCDatasource::GetCurPos()
{
    CRecordsetStatus crs;
    m_Record->GetStatus(crs);
    return crs.m_lCurrentRecord;
}

/****************************************************
****************************************************/
int CUGODBCDatasource::StartTransaction(){
	m_Db->BeginTrans();
    return UG_SUCCESS;
}
/****************************************************
****************************************************/
int CUGODBCDatasource::CancelTransaction(){
	return m_Db->Rollback();
}
/****************************************************
****************************************************/
int CUGODBCDatasource::FinishTransaction(){
	return m_Db->CommitTrans();
}

/****************************************************
    Added 7/99.  Previously, this code was
    duplicated in SetCell, GetCell, and 
    DeleteRow.  
****************************************************/
int CUGODBCDatasource::GotoRecord(long row)
{
	//goto the correct row
    //TRACE("m_nCurrentRow = %ld, row = %ld\n", m_nCurrentRow, row);

	if(row == 0){
		m_nCurrentRow = 0;
		try{
			m_Record->MoveFirst();
		}
		catch(CMemoryException* e){
			#ifdef UG_ODBC_REPORTERROR
				e->ReportError();
			#endif
			e->Delete();
			AfxAbort();
		}
		catch(CDBException* e){
			int er = e->m_nRetCode;
	 		TRACE(_T("CDBException %d, caught at line %d in %s:\n'%s'\n"), 
				e->m_nRetCode,__LINE__,_T("ugodbc.cpp"), e->m_strError);
			#ifdef UG_ODBC_REPORTERROR
			TCHAR buf[255];
				UGStr::stprintf(buf,255,_T("Error %d"),er);
				AfxMessageBox(buf);
				e->ReportError();
			#endif
			e->Delete();
			return er;
			// probably no records in file - error 1016
		}
		catch(CFileException* e) {		
			int er = e->m_cause;
			#ifdef UG_ODBC_REPORTERROR
			TCHAR buf[255];
				UGStr::stprintf(buf,255,_T("Error %d"),er);
				AfxMessageBox(buf);
				e->ReportError();
			#endif
			e->Delete();
			return er;
		}

	}
	else if( row != m_nCurrentRow){
		try{
			

		m_Record->Move(row - m_nCurrentRow);
			m_nCurrentRow = row;
		}
		catch(CMemoryException* e){
			#ifdef UG_ODBC_REPORTERROR
				e->ReportError();
			#endif
			e->Delete();
			AfxAbort();
		}
		catch(CDBException* e){
			int er = e->m_nRetCode;
	 		TRACE(_T("CDBException %d, caught at line %d in %s:\n'%s'\n"), 
				e->m_nRetCode,__LINE__,"ugodbc.cpp", e->m_strError);
		//	char buf[255];
			#ifdef UG_ODBC_REPORTERROR
			/*	CUGStr::stprintf(buf,255,_T("Error %d"),er);
				AfxMessageBox(buf);
				e->ReportError(); */    
			#endif
				e->Delete();
                return er;
		}
		catch(CFileException* e) {
			int er = e->m_cause;
			#ifdef UG_ODBC_REPORTERROR
			TCHAR buf[255];
			UGStr::stprintf(buf,255,_T("Error %d"),er);
				AfxMessageBox(buf);
				e->ReportError();
			#endif

			e->Delete();
			return er;
		}
		
	} 
    return UG_SUCCESS;
}
