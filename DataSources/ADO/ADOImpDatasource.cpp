/*************************************************************************
				Class Implementation : CADOImpDatasource
**************************************************************************
	Source file : ADOImpDatasource.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/
#include "stdafx.h"
#include "UGCtrl.h"
#include "ADOImpDatasource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/***************************************************
	Standard construction/desrtuction
***************************************************/
CADOImpDatasource::CADOImpDatasource()
{
	m_pConnection = NULL;	// the connection
	m_pRecordSet = NULL;	// the recordset

	m_dbConnection = _T("");// source string for the connection
	m_User = _T("");		// user login name
	m_Password = _T("");	// user login password
	m_Command = _T("");		// command to execute
	m_Filter = _T("");		// filter to be used
	m_SortOrder = _T("");	// sort order to be used
	m_sCurRowID	= _T("»");

	m_numCols = -1;			// indicate that the number of columns is unknown

	// fetching
	m_nFetchedStarting = 0;
	m_pcRowsObtained = 0;
	m_nMinFetchRows = MIN_FETCH_ROWS;

	// editing
	m_bAllowEdits = TRUE;
	m_bEditingConfirmed = FALSE;

	// flag indicating that we can use GhostRow
	m_bUseGhostRow	= TRUE;
	m_nCurGhostRow	= -1;
	m_nOldGhostRow	= -1;
	
	// AppendRow style
	m_bUseSimpleNew = TRUE;

	// number of rows waiting update
	m_iUpdatesPending = 0;

	// Initialize OLE
	CoInitialize( NULL );
}

CADOImpDatasource::~CADOImpDatasource()
{
	// make sure that all changes are saved before exiting
	if ( UpdatePending( FALSE ) == UG_ERROR )
		// clear our the updated cells list
		m_hUpdatedRow.Empty();

	// close recordset and connection
	Close();

	CoUninitialize();
}

/***************************************************
Open
	The ADO datasource uses this function to open the record set
	using information set by the SetPassword and parameters passed in.
Params:
	name		- represents the connection string
	option		- not used
Return:
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CADOImpDatasource::Open(LPCTSTR name,LPCTSTR option)
{
	UNREFERENCED_PARAMETER(option);

	if( name )
		m_dbConnection = name;

	// make sure that the connection string has been specified
	if ( m_dbConnection == _T(""))
		// there is nothing to open
		return UG_ERROR;

	// make sure that the recordset and connection objects are closed
	Close();

	// open the connection
	if( OpenConnection() == UG_ERROR )
		return UG_ERROR;

	// open the recordset
	return OpenRecordset();
}

/***************************************************
OpenSQL
	function can be used to open a record set by specifying the SQL statement
	to be used.
Params:
	sql			- SQL statement to be used
	conStr		- (optional) connection string, it can also be set with
				  SetCommand function.
Return:
	UG_SUCCESS	success
	UG_ERROR	when sql string passed in is empty
****************************************************/
int CADOImpDatasource::OpenSQL(CString sql, CString conStr)
{
	// Clear information on the last query.
	m_Command = "";
	m_Filter = "";
	m_SortOrder = "";

	// copy connection string and the SQL statement
	if( ParseSQLString( sql ) == UG_ERROR )
		return UG_ERROR;

	return Open( conStr, NULL );
}

/***************************************************
ParseSQLString	- protected
	function is called by the OpenSQL function in order to break up the SQL
	statement passed-in into separate components (command, filter, sort).
Params:
	sql			- SQL string passed into the OpenSQL
Return:
	UG_SUCCESS	success, this function will never fail.
****************************************************/
int CADOImpDatasource::ParseSQLString( CString sql )
{
	if ( sql == "" )
		return UG_ERROR;

	CString tempSql( sql );
	tempSql.TrimRight();
	// convert the string to upper case, to make it easier to search
	tempSql.MakeUpper();
	// remove the ';' character from the end of the SQL statement
	tempSql = tempSql.SpanExcluding( _T(";"));

	// look for the WHERE sub string in the SQL statement
	// the position found indicates end of the selection
	// portion of the SQL statement.
	int filterIndex = tempSql.Find( _T("WHERE"), 0 );
	// check if the sort order has been specified
	int orderIndex = tempSql.Find( _T("ORDER BY"), 0 );

	if( filterIndex >= 0 )
	{
		SetCommand( sql.Left( filterIndex - 1 ));
		sql = sql.Right( sql.GetLength() - ( filterIndex + 6 ));

		if ( orderIndex >= 0 )
		{
			orderIndex -= (filterIndex + 6);
			SetFilter( sql.Left( orderIndex - 1 ));
			sql = sql.Right( sql.GetLength() - ( orderIndex + 9 ));
			SetSort( sql );
		}
		else
			SetFilter( sql );
	}
	else if ( orderIndex >= 0 )
	{
		SetCommand( sql.Left( orderIndex - 1 ));
		sql = sql.Right( sql.GetLength() - ( orderIndex + 9 ));

		SetSort( sql );
	}
	else 
		SetCommand( sql );

	return UG_SUCCESS;
}

/***************************************************
SetCommand
	function is used to set the select portion of the SQL statement
	that will be used to open the recordset.
Params:
	<none>
Return:
	UG_SUCCESS	success, this function will never fail.
****************************************************/
int CADOImpDatasource::SetCommand(CString command)
{
	m_Command = command.SpanExcluding( _T(";"));
	return UG_SUCCESS;
}

/***************************************************
SetFilter
	function is used to set the filter criteria for the recordset
	that is currently opened. WHERE portion of the SQL string,
	but whithout WHERE word.
Params:
	<none>
Return:
	UG_SUCCESS	success, this function will never fail.
****************************************************/
int CADOImpDatasource::SetFilter(CString filter)
{
	m_Filter = filter.SpanExcluding( _T(";"));
	return UG_SUCCESS;
}

/***************************************************
SetSort
	function is used to set the sort criteria for the recordset
	that is currently opened. ORDER BY portion of the SQL string,
	but whithout ORDER BY word.
Params:
	sort		- string representing the sort criteria
Return:
	UG_SUCCESS	success, this function will never fail.
****************************************************/
int CADOImpDatasource::SetSort(CString sort)
{
	m_SortOrder = sort.SpanExcluding( _T(";"));
	return UG_SUCCESS;
}

/***************************************************
OpenConnection	- protected
	function is used to open the connection to the data base as specified
	by connection string (m_dbConnection), User Name (m_User) and Password
	(m_Password).
Params:
	<none>
Return:
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CADOImpDatasource::OpenConnection()
{
	if (m_pConnection == NULL)
	{
		try
		{	// create instance of the Connection object
			m_pConnection.CreateInstance(__uuidof(Connection));

			// open the connection
			m_pConnection->Open((_bstr_t)m_dbConnection,(_bstr_t)m_User,(_bstr_t)m_Password,-1);
		}
		catch(_com_error /*&e*/)
		{
			m_pConnection = NULL; 
			return UG_ERROR;
		}
	}

	// provide the CUGCtrl class with information on the connection that
	// was successfuly created and open, allow user with ability to perform
	// further customization on the recordset.
	if(m_ctrl != NULL)
		m_ctrl->OnDataSourceNotify( GetID(), UG_ADO_DS_OPEN_CONN, (long)m_pConnection );

	return UG_SUCCESS;
}

/***************************************************
GetSQL	- public
	The GetSQL function will create a string representing
	currently used SQL statement by combining information
	found in the m_Command, m_Filter, and m_SortOrder
Params:
	<none>
Return:
	string representing currently used SQL statement
****************************************************/
CString CADOImpDatasource::GetSQL()
{
	if ( m_Command == _T(""))
		return _T("");

	// construct the SQL statement to use
	CString sqlString = m_Command;
	if ( m_Filter != _T(""))
		sqlString += _T(" WHERE ") + m_Filter;
	if ( m_SortOrder != _T(""))
		sqlString += _T(" ORDER BY ") + m_SortOrder;

	sqlString += _T(";");

	return sqlString;
}

/***************************************************
OpenRecordset	- protected
	function is used to create and open recordset object that will be
	used to populate the grid with.
Params:
	<none>
Return:
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CADOImpDatasource::OpenRecordset()
{
	CString sqlString = GetSQL();

	try	// open the recordset
	{
		m_pRecordSet.CreateInstance(__uuidof(Recordset));
		m_pRecordSet->Open((_bstr_t)sqlString, _variant_t((IDispatch *)m_pConnection), adOpenKeyset, adLockOptimistic, adCmdUnknown);

		if(m_ctrl!=NULL)
			// provide the CUGCtrl class with information on the recordset that
			// was successfuly created and open, allows user with ability to perform
			// further processing on the recordset.
			m_ctrl->OnDataSourceNotify( GetID(), UG_ADO_DS_OPEN_RS, (long)m_pRecordSet );

		if( m_pRecordSet->GetRecordCount())
			m_pRecordSet->MoveFirst();
	}
	catch(_com_error &e)
	{
		AfxMessageBox( e.Description());
		return UG_ERROR;
	}

	return UG_SUCCESS;
}

/***************************************************
IsOpen
	virtual function is most commonly used by datasources
	that bind to a database or some form of an external data.
	It is used to provide feedback to the developer who requires
	to know if a connection to the database is currently open
	or closed.
Params:
	<none>
Return:
	FALSE if the datasource is closed and TRUE if it is open.
***************************************************/
BOOL CADOImpDatasource::IsOpen()
{
	if( m_pRecordSet )
		if(m_pRecordSet->GetState() == adStateOpen)
			return TRUE;

	return FALSE;
}

/***************************************************
Close
	function is used to properly close instances of the recordset
	and connection objects.
Params:
	<none>
Return:
	UG_SUCCESS on success, this function will never fail.
****************************************************/
int CADOImpDatasource::Close()
{
	// if a recordset is open, then close it and release pointer
	if( m_pRecordSet )
	{
		try
		{
			m_pRecordSet->CancelUpdate();
		}
		catch( ... )
		{
		}

		m_nFetchedStarting = 0;
		m_pcRowsObtained = 0;
		m_hUpdatedRow.Empty();
		m_nCurGhostRow	= -1;
		m_nOldGhostRow	= -1;
		m_curBookmark.Clear();
		// number of rows waiting update
		m_iUpdatesPending = 0;

		if(m_pRecordSet->GetState() == adStateOpen)
			m_pRecordSet->Close();

		m_pRecordSet.Release();
		m_pRecordSet=NULL;
	}

	// if connectoin is established, then disconnect and release pointer
	if( m_pConnection )
	{
		m_pConnection->Close();
		m_pConnection.Release();
		m_pConnection=NULL;
	}

	return UG_SUCCESS;
}

/***************************************************
SetPassword
	A virtual function that provides standard interface
	to set user name and password used to open the data
	source.
Params:
	user	- user name to use
	pass	- password
Return:
	UG_SUCCESS	success, this function will not fail.
****************************************************/
int CADOImpDatasource::SetPassword(LPCTSTR user,LPCTSTR pass)
{
	m_User = user;
	m_Password = pass;

	return UG_SUCCESS;
}

/***************************************************
GetNumRowsComplete
	function completes functionality of GetNumRows, 
	and allows us to determine the total number of
	records in the recordset without consideration
	for howmany rows grid is currently aware of.
Params:
	<none>
Return:
	number of rows found in the recordset, or
	-1 on error.
****************************************************/
long CADOImpDatasource::GetNumRowsComplete()
{
	// make sure the recordset is open
	if ( m_pRecordSet == NULL )
		return -1;

	// The RecordCount ADO property will return exact
	// number of records found in the recordset if recordset
	// Supports (adApproxPosition) or Supports (adBookmark).
	return m_pRecordSet->RecordCount;
}

/***************************************************
GetNumRows
	A virtual function that provides standard interface
	for the grid to find out how many rows are in the
	data source.  If the data source is not able to 
	determine how many rows there are, than it should 
	only return a value greater than zero defining how
	many rows it is aware of.  The grid then will use
	the OnHitBottom notification to check if there are
	additional rows.
Params:
	<none>
Return:
	number of rows found in the recordset, this number might
	not represent all of the rows in the recordset, or
	-1 on error.
****************************************************/
long CADOImpDatasource::GetNumRows()
{
	// make sure the recordset is open
	if ( m_pRecordSet == NULL )
		return -1;

	// fetch the first batch of rows
	FetchNewRows( 0 );

	// when number of fetched rows is zero (empty recordser)
	// and ghost row is enabled than we must properly identify
	// number of rows (1)
	if ( m_pcRowsObtained == 0 && m_bUseGhostRow == TRUE )
	{
		m_pcRowsObtained = 1;
		m_nCurGhostRow = 0;
	}

	// assume virtual loading through OnHitBottom
	return m_pcRowsObtained;
}

/***************************************************
FetchNewRows
	This function is called by the GetCell notification when
	it needs to display rows that are not currently cached

	The next fetch position will always be set to bookmark of the 
	first row in the array of fetched HROWs.
Parameters
	row		The row of interest
Returns
	UG_SUCCESS
	UG_ERROR
****************************************************/
int CADOImpDatasource::FetchNewRows( long row )
{
	// Determine howmany rows are currently visible on the screen, use the window
	// size and default row size as a guide.
	CRect rect;
	m_ctrl->GetWindowRect( rect );
	long nVisibleRows = (rect.bottom - rect.top) / m_ctrl->m_GI->m_defRowHeight;
	// nStartingDelta determines the position change in relation to current DB position
	long nStartingDelta = m_nFetchedStarting;

	// find out how many rows need to be fetched
	m_nMaxFetchRows = nVisibleRows * 3;

	// make sure that enough rows are fetched at one time
	if ( m_nMaxFetchRows < m_nMinFetchRows )
		m_nMaxFetchRows = m_nMinFetchRows;

	// reset starting row for the fetch rows buffer
	m_nFetchedStarting = row - ( m_nMaxFetchRows / 2 );

	try
	{
		if ( m_curBookmark.vt == VT_EMPTY || m_nFetchedStarting <= 0 )
		{	// if the book mark does not exist then adjust
			// the starting position to the beggining of the dataset
			nStartingDelta = 0;
			m_nFetchedStarting = 0;
			m_pRecordSet->MoveFirst();
		}
		else
		{	// adjust starting position in relation to current position
			nStartingDelta = m_nFetchedStarting - nStartingDelta;

			// move current record in the recordset to point to new fetch
			// starting position.
			m_pRecordSet->PutBookmark( m_curBookmark );
			// move current row as calculated
			m_pRecordSet->Move( nStartingDelta );
		}

		// store book mark to first row in the fetch array
		m_curBookmark = m_pRecordSet->GetBookmark();
		// fetch rows
		m_curRecords = m_pRecordSet->GetRows( m_nMaxFetchRows );
		// retrieve information on howmany rows were fetched
		if ( m_curRecords.vt != VT_EMPTY )
			SafeArrayGetUBound( m_curRecords.parray, 2, &m_pcRowsObtained );
		else
			m_pcRowsObtained = 0;
	}
	catch (...)
	{
		m_curBookmark.Clear();
		m_pcRowsObtained = 0;
		return UG_ERROR;
	}

	m_pcRowsObtained += 1;

	return UG_SUCCESS;
}

/***************************************************
GetNumCols
	A virtual function that provides standard interface
	for the grid to find out how many columns are in the
	data source.
Params:
	<none>
Return:
	number of columns in the datasource, or
	-1 encountered error
****************************************************/
int CADOImpDatasource::GetNumCols()
{
	if( m_pRecordSet )
	{
		try
		{
			m_numCols = (int)m_pRecordSet->GetFields()->GetCount();
		}
		catch(_com_error /*&e*/)
		{	// although the GetCount function returns -1 on error, we
			// set m_numCols = -1 just to make sure.
			m_numCols = -1;
		}
	}
	else
		m_numCols = -1;

	return m_numCols;
}

/***************************************************
GetColName
	A virtual function that provides standard interface
	to provide the grid with the name of a column.
Params:
	col		- column number for which to return name
	string	- pointer to a string which should be populated
			  with the column name.
Return:
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CADOImpDatasource::GetColName( int col, CString* string )
{
	if( m_pRecordSet == NULL || col < 0 || col > m_numCols )
		return UG_ERROR;

	try
	{
		*string = VarToString(m_pRecordSet->GetFields()->GetItem((COleVariant)(long)col)->GetName());
	}
	catch(_com_error /*&e*/)
	{
		return UG_ERROR;
	}

	return UG_SUCCESS;
}

/***************************************************
VarToString	- protected
	function is a helper function that is used to convert strings
	storred in a _variant_tobject to CString.
Params:
	theVariant	- _variant_t object from which extract string.
Return:
	string		- contained string
****************************************************/
CString CADOImpDatasource::VarToString(_variant_t theVariant)
{
	CString tempStr;

	if( theVariant.vt != VT_NULL )
	{
		tempStr = (const char*)_bstr_t(theVariant);
		tempStr.TrimLeft();
		tempStr.TrimRight();
		return tempStr;
	}
	return _T("");
}

/***************************************************
GetCell
	A virtual function that provides standard way
	for the grid to populate a cell object.  This
	function is called as a result of the 
	CUGCtrl::GetCell being called.
Params:
	col, row	- coordinates of the cell to retrieve
				  information on.
	cell		- pointer to CUGCell object to populate
				  with the information found.
Return:
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CADOImpDatasource::GetCell(int col,long row,CUGCell *cell)
{
	if ( m_pRecordSet == NULL )
		return UG_ERROR;

	if ( col >= m_ctrl->GetNumberCols() || row >= m_ctrl->GetNumberRows())
		return UG_ERROR;

	if ( col >= 0 && row == -1 )
	{	// display column headings
		CString tempStr;
		GetColName( col, &tempStr );
		cell->SetText( tempStr );
		return UG_SUCCESS;
	}
	else if ( col == -1 && row == m_ctrl->GetCurrentRow())
	{	// display current row indicator
		cell->SetText( m_sCurRowID );
	}
	else if ( col >= 0 && row >= 0 )
	{	
		if ( row == m_ctrl->GetCurrentRow() && col == m_ctrl->GetCurrentCol() && 
		   (!( row >= m_nFetchedStarting && row <= m_nFetchedStarting + m_pcRowsObtained )))
		{
			return UG_SUCCESS;
		}

		// populate cell with data from data source
		_variant_t var = GetDBCellData( col, row );

		if( var.vt == VT_ERROR )
		{	// the retrieving of cell's data failed
			return UG_ERROR;
		}

		// set the value to the grid.
		PopulateCellFromDB( cell, var );
	}

	return UG_SUCCESS;
}

/***************************************************
GetDBCellData
	function looks for data for a given cell.  The data can be retrieved
	from the database (fetched buffer), database's defaults (in case of
	the ghost row) or list of made updates.
Params:
	col, row
Returns:
	_variant_t object representing cell's data
*****************************************************/
_variant_t CADOImpDatasource::GetDBCellData( int col, long row )
{
	_variant_t result;

	if ( m_hUpdatedRow.GetUpdateRowNumber() == row )
	{
		if ( m_hUpdatedRow.IsUpdated( col ))
		{	// the row in question is not in the fetched rows array,
			// check the new rows list for possible values
			// pSafeRowArray = m_hUpdatedRow.GetRowSArray( row );
			result = m_hUpdatedRow.GetUpdatedVal( col );
		}
	}
	
	if ( row != m_nCurGhostRow && result.vt == VT_EMPTY )
	{
		if (( row - m_nFetchedStarting ) < 0 ||
			 ( row - m_nFetchedStarting ) >= (long)m_pcRowsObtained )
		{	// the row that the grid needs is not in the fetched buffer.
			int fetchRow = row;
			// If the requested row is visible than fetch rows based on
			// the top row
			if ( row >= m_ctrl->GetTopRow() && row <= m_ctrl->GetBottomRow())
				fetchRow = m_ctrl->GetTopRow();
			// Fetch new rows from the data source.
			FetchNewRows( fetchRow );
		}

		if ( row >= m_nFetchedStarting &&
		     row < m_nFetchedStarting + ((long)m_pcRowsObtained ))
		{
			long rgIndices[2];
			rgIndices[0] = col; 
			rgIndices[1] = row - m_nFetchedStarting; 

			try
			{
				if ( m_curRecords.vt != VT_EMPTY )
					SafeArrayGetElement( m_curRecords.parray, rgIndices, &result );
			}
			catch( ... )
			{
			}
		}
		else
		{
			long rowsFound = 0;
			OnHitBottom( row, 0, &rowsFound );
		}
	}

	if (( row == m_nCurGhostRow || row == m_nOldGhostRow ) && result.vt == VT_EMPTY )
	{
		// retrieve column's data type
		DataTypeEnum type;
		m_pRecordSet->GetFields()->GetItem((COleVariant)(long)col)->get_Type( &type );
		if (!( m_pRecordSet->GetFields()->GetItem((COleVariant)(long)col)->GetAttributes()&adFldUpdatable ))
		{
			result.vt = VT_NULL;
			return result;
		}

		switch( type )
		{
		case adTinyInt: // DBTYPE_I1:
			result.cVal = (char)0;
			result.vt = VT_I1;
			break;
		case adUnsignedTinyInt: // DBTYPE_UI1:
			result.bVal = (BYTE)0;
			result.vt = VT_UI1;
			break;
		case adSmallInt: // DBTYPE_I2:
			result.iVal = (short)0;
			result.vt = VT_I2;
			break;
		case adUnsignedSmallInt: // DBTYPE_UI2:
			result.uiVal = (unsigned short)0;
			result.vt = VT_UI2;
			break;
		case adInteger: // DBTYPE_I4:
			result.lVal = (long)0;
			result.vt = VT_I4;
			break;
		case adUnsignedInt: // DBTYPE_UI4:
			result.ulVal = (unsigned long)0;
			result.vt = VT_UI4;
			break;
		case adBigInt: // DBTYPE_I8:
			result.intVal = (LONG)0;
			result.vt = VT_I8;
			break;
		case adUnsignedBigInt: // DBTYPE_UI8:
			result.uintVal = (ULONG)0;
			result.vt = VT_UI8;
			break;
		case adSingle: // DBTYPE_R4:
			result.fltVal = (float)0;
			result.vt = VT_R4;
			break;
		case adDouble: // DBTYPE_R8:
			result.dblVal = (double)0;
			result.vt = VT_R8;
			break;
		case adBoolean: // DBTYPE_BOOL:
			result.boolVal = FALSE;
			result.vt = VT_BOOL;
			break;
		default:
			result.vt = VT_NULL;
			break;
		}
	}

	return result;
}

/***************************************************
PopulateCellFromDB
	Now that we have the value loaded as variant we can do
	further processing based on the data type and the value loaded.
	This function will make sure that the grid shows data correctly
Params:
	cell
	dbVariant
Returns:
	<none>
*****************************************************/
void CADOImpDatasource::PopulateCellFromDB( CUGCell *cell, _variant_t dbVariant )
{
	COleCurrency currency;
	COleDateTime dateTime;
	CString cellString;

	switch( dbVariant.vt )
	{
	case VT_I1:		// char
		cell->SetNumberDecimals( 0 );
		cell->SetNumber( dbVariant.cVal );
		cell->SetAlignment( UG_ALIGNRIGHT|UG_ALIGNVCENTER );
		break;
	case VT_UI1:	// Byte
		cell->SetNumberDecimals( 0 );
		cell->SetNumber( dbVariant.bVal );
		cell->SetAlignment( UG_ALIGNRIGHT|UG_ALIGNVCENTER );
		break;
	case VT_I2:		// Short
		cell->SetNumberDecimals( 0 );
		cell->SetNumber( dbVariant.iVal );
		cell->SetAlignment( UG_ALIGNRIGHT|UG_ALIGNVCENTER );
		break;
	case VT_UI2:	// unsigned short
		cell->SetNumberDecimals( 0 );
		cell->SetNumber( dbVariant.uiVal );
		cell->SetAlignment( UG_ALIGNRIGHT|UG_ALIGNVCENTER );
		break;
	case VT_I4:		// long
		cell->SetNumberDecimals( 0 );
		cell->SetNumber( dbVariant.lVal );
		cell->SetAlignment( UG_ALIGNRIGHT|UG_ALIGNVCENTER );
		break;
	case VT_UI4:	// unsigned long
		cell->SetNumberDecimals( 0 );
		cell->SetNumber( dbVariant.ulVal );
		cell->SetAlignment( UG_ALIGNRIGHT|UG_ALIGNVCENTER );
		break;
	case VT_INT:	// int
		cell->SetNumberDecimals( 0 );
		cell->SetNumber( dbVariant.intVal );
		cell->SetAlignment( UG_ALIGNRIGHT|UG_ALIGNVCENTER );
		break;
	case VT_UINT:	// unsigned int
		cell->SetNumberDecimals( 0 );
		cell->SetNumber( dbVariant.uintVal );
		cell->SetAlignment( UG_ALIGNRIGHT|UG_ALIGNVCENTER );
		break;
	case VT_R4:		// float
		// When converting from a float data type to a double
		// we multiply the float by 10000 and type cast the result
		// to an integer, the integer is then converted to a double
		// and divided by 10000.  We are required to do this
		// due to a precision loss when converting from float
		// data type to double.  This issue is described in
		// "Why Floating-Point Numbers May Lose Precision"
		// article in MSDN.
		cell->SetNumber(((double)((int)( dbVariant.fltVal * 10000 ))) / 10000 );
		cell->SetAlignment( UG_ALIGNRIGHT|UG_ALIGNVCENTER );
		break;
	case VT_R8:		// double
		cell->SetNumber( dbVariant.dblVal );
		cell->SetAlignment( UG_ALIGNRIGHT|UG_ALIGNVCENTER );
		break;
	case VT_BOOL:	// VARIANT_BOOL
		cell->SetBool( dbVariant.boolVal );
		cell->SetCellType( UGCT_CHECKBOX );
		cell->SetCellTypeEx( UGCT_CHECKBOXUSEALIGN );
		cell->SetAlignment( UG_ALIGNCENTER | UG_ALIGNVCENTER );
		break;
	case VT_CY:		// CY
		cell->SetNumberDecimals( 2 );
		cell->SetNumber( dbVariant.lVal / (double)10000 );
		cell->SetDataType( UGCELLDATA_CURRENCY );
		cell->SetAlignment( UG_ALIGNRIGHT|UG_ALIGNVCENTER );
		break;
	case VT_DATE:	// DATE
		dateTime = dbVariant.date;
		cell->SetText( dateTime.Format(VAR_DATEVALUEONLY));

		cellString.Format(_T("%f"), dbVariant.date );
		cell->SetLabelText( cellString );
		cell->SetDataType( UGCELLDATA_TIME );
		cell->SetAlignment( UG_ALIGNLEFT|UG_ALIGNVCENTER );
		break;
	case VT_BSTR:	// BSTR
		cell->SetText( CString( dbVariant.bstrVal ));
		cell->SetAlignment( UG_ALIGNLEFT|UG_ALIGNVCENTER );
		break;
	default:
		// cell is empty
		cell->SetText( _T(""));
		cell->SetAlignment( UG_ALIGNLEFT|UG_ALIGNVCENTER );
		break;
	}
}

/***************************************************
GetDefaultValue
	This function is used to make sure that the variant
	contains proper value only used for new rows.
Params:
	cell
	dbVariant
Returns:
	<none>
*****************************************************/
_variant_t CADOImpDatasource::SetDBCellData( int col, CUGCell *pCell )
{
	DataTypeEnum type;
	_variant_t dbVariant;
	COleCurrency currency;
	COleDateTime dateTime;
	CString cellString;

	// retrieve column's data type
	m_pRecordSet->GetFields()->GetItem((COleVariant)(long)col)->get_Type( &type );

	switch( type )
	{
	case adTinyInt: // DBTYPE_I1:
		if ( pCell->GetPropertyFlags()&UGCELL_STRING_SET )
		{
			dbVariant.cVal = (char)pCell->GetNumber();
			dbVariant.vt = VT_I1;
		}
		else
			dbVariant.vt = VT_NULL;
		break;
	case adUnsignedTinyInt: // DBTYPE_UI1:
		if ( pCell->GetPropertyFlags()&UGCELL_STRING_SET )
		{
			dbVariant.bVal = (BYTE)pCell->GetNumber();
			dbVariant.vt = VT_UI1;
		}
		else
			dbVariant.vt = VT_NULL;
		break;
	case adSmallInt: // DBTYPE_I2:
		if ( pCell->GetPropertyFlags()&UGCELL_STRING_SET )
		{
			dbVariant.iVal = (short)pCell->GetNumber();
			dbVariant.vt = VT_I2;
		}
		else
			dbVariant.vt = VT_NULL;
		break;
	case adUnsignedSmallInt: // DBTYPE_UI2:
		if ( pCell->GetPropertyFlags()&UGCELL_STRING_SET )
		{
			dbVariant.uiVal = (unsigned short)pCell->GetNumber();
			dbVariant.vt = VT_UI2;
		}
		else
			dbVariant.vt = VT_NULL;
		break;
	case adInteger: // DBTYPE_I4:
		if ( pCell->GetPropertyFlags()&UGCELL_STRING_SET )
		{
			dbVariant.lVal = (long)pCell->GetNumber();
			dbVariant.vt = VT_I4;
		}
		else
			dbVariant.vt = VT_NULL;
		break;
	case adUnsignedInt: // DBTYPE_UI4:
		if ( pCell->GetPropertyFlags()&UGCELL_STRING_SET )
		{
			dbVariant.ulVal = (unsigned long)pCell->GetNumber();
			dbVariant.vt = VT_UI4;
		}
		else
			dbVariant.vt = VT_NULL;
		break;
	case adBigInt: // DBTYPE_I8:
		if ( pCell->GetPropertyFlags()&UGCELL_STRING_SET )
		{
			dbVariant.intVal = (LONG)pCell->GetNumber();
			dbVariant.vt = VT_I8;
		}
		else
			dbVariant.vt = VT_NULL;
		break;
	case adUnsignedBigInt: // DBTYPE_UI8:
		if ( pCell->GetPropertyFlags()&UGCELL_STRING_SET )
		{
			dbVariant.uintVal = (ULONG)pCell->GetNumber();
			dbVariant.vt = VT_UI8;
		}
		else
			dbVariant.vt = VT_NULL;
		break;
	case adSingle: // DBTYPE_R4:
		if ( pCell->GetPropertyFlags()&UGCELL_STRING_SET )
		{
			dbVariant.fltVal = (float)pCell->GetNumber();
			dbVariant.vt = VT_R4;
		}
		else
			dbVariant.vt = VT_NULL;
		break;
	case adDouble: // DBTYPE_R8:
		if ( pCell->GetPropertyFlags()&UGCELL_STRING_SET )
		{
			dbVariant.dblVal = (double)pCell->GetNumber();
			dbVariant.vt = VT_R8;
		}
		else
			dbVariant.vt = VT_NULL;
		break;
	case adDecimal:
		//dbVariant.decVal = 0;
		//dbVariant.vt = VT_DECIMAL;
		break;
	case adNumeric:
		break;
	case adBoolean: // DBTYPE_BOOL:
		if ( pCell->GetPropertyFlags()&UGCELL_STRING_SET )
		{
			if((BOOL)pCell->GetNumber() == FALSE)
				dbVariant.boolVal = 0;
			else
				dbVariant.boolVal = -1;
			dbVariant.vt = VT_BOOL;
		}
		else
			dbVariant.vt = VT_NULL;
		break;
	case adCurrency: // DBTYPE_CY:
		currency.ParseCurrency( pCell->GetText());
		if ( currency.GetStatus() == 0 )
		{
			dbVariant.cyVal = currency;
			dbVariant.vt = VT_CY;
		}
		else
			dbVariant.vt = VT_NULL;
		break;
	case adChar:
	case adVarChar:
	case adLongVarChar:
	case adWChar:
	case adVarWChar:
	case adLongVarWChar:
	//case DBTYPE_STR:
	//case DBTYPE_WSTR:
	case adBSTR: // DBTYPE_BSTR:
		cellString = pCell->GetText();
		if ( cellString.GetLength() > 0 )
		{
			dbVariant.bstrVal = cellString.AllocSysString();
			dbVariant.vt = VT_BSTR;
		}
		else
			dbVariant.vt = VT_NULL;
		break;
	case adDate:	// DBTYPE_DATE:
	case adDBDate:	// DBTYPE_DBDATE:
	case adDBTime:	// DBTYPE_DBTIME:
	case adDBTimeStamp: // DBTYPE_DBTIMESTAMP:
		dateTime.ParseDateTime( pCell->GetText());
		if ( dateTime.GetStatus() == 0 )
		{
			dbVariant.date = dateTime;
			dbVariant.vt = VT_DATE;
		}
		else
			dbVariant.vt = VT_NULL;
		break;
	case adEmpty: // DBTYPE_EMPTY:
	//case DBTYPE_NULL:
		dbVariant.vt = VT_NULL;
		break;
	case adUserDefined:
	case adVariant:
	case adIDispatch:
	case adIUnknown:
	case adBinary:
	case adVarBinary:
	case adLongVarBinary:
	case adError: //DBTYPE_ERROR:
	default:
		dbVariant.vt = VT_ERROR;
		break;
	}

	return dbVariant;
}

/***************************************************
SetCell
	This function is called everytime user made changes to the
	data.  It is used to make changed permanent.
Params:
	col, row
	cell
Returns:
	<none>
*****************************************************/
int CADOImpDatasource::SetCell(int col,long row,CUGCell *cell)
{
	// variant that will hold new data
	_variant_t variantVal;
	_variant_t saRow;

	if ( m_bUseGhostRow == TRUE && row == m_nCurGhostRow )
	{	// if needed show new Ghost row
		m_nOldGhostRow = m_nCurGhostRow;
		m_ctrl->SetNumberRows( m_ctrl->GetNumberRows() + 1, FALSE );
		m_nCurGhostRow = m_ctrl->GetNumberRows() - 1;
		// update grid's view
		CRect rect;
		m_ctrl->GetRangeRect( m_ctrl->GetLeftCol(),
							  m_ctrl->GetTopRow(),
							  m_ctrl->GetRightCol(),
							  m_ctrl->GetBottomRow(),
							  rect );
		m_ctrl->m_CUGGrid->m_drawHint.ClearHints();
		m_ctrl->m_CUGGrid->m_drawHint.AddHint( m_ctrl->GetLeftCol(),
							  m_ctrl->GetTopRow(),
							  m_ctrl->GetRightCol(),
							  m_ctrl->GetBottomRow());

		// The PaintDrawHintsNow call causes the text to be lost, so we grab a copy of the cell first
		// ( as I presume other data is also lost )
		CUGCell c;
		cell->CopyCellInfo(cell, &c);

		m_ctrl->m_CUGGrid->PaintDrawHintsNow( rect );

		// And copy it back.
		cell->CopyCellInfo(&c, cell);

		m_ctrl->m_CUGGrid->m_drawHint.ClearHints();
		m_ctrl->m_CUGSideHdg->Update();
	}

	variantVal = SetDBCellData( col, cell );

	if ( variantVal.vt == VT_ERROR )
	{	// an error occured while converting data
		return UG_ERROR;
	}

	m_hUpdatedRow.SetUpdateRowNumber( row );
	m_hUpdatedRow.UpdateCell( col, variantVal );
	// increase number of pending updates
	m_iUpdatesPending ++;

	return UG_SUCCESS;
}

/***************************************************
RefreshGrid
	Purpose of this function is to make sure that the grid
	gets fresh data from the database.

	This is simply done by calling FetchNewRows function looking
	for current top row.  Also I determine here if rows were
	added or deleted, so the grid will show all fetchd rows.
Params:
	<none>
Returns:
	UG_SUCCESS on success, this function will never fail.
***************************************************/
int CADOImpDatasource::RefreshGrid( void )
{
	// fetch new rows
	if ( FetchNewRows( m_ctrl->GetTopRow()) == UG_ERROR )
	{
		return UG_ERROR;
	}

	// update grid's view
	CRect rect;
	m_ctrl->GetRangeRect( m_ctrl->GetLeftCol(),
						  m_ctrl->GetTopRow(),
						  m_ctrl->GetRightCol(),
						  m_ctrl->GetBottomRow(),
						  rect );
	m_ctrl->m_CUGGrid->m_drawHint.ClearHints();
	m_ctrl->m_CUGGrid->m_drawHint.AddHint( m_ctrl->GetLeftCol(),
						  m_ctrl->GetTopRow(),
						  m_ctrl->GetRightCol(),
						  m_ctrl->GetBottomRow());
	m_ctrl->m_CUGGrid->PaintDrawHintsNow( rect );
	m_ctrl->m_CUGGrid->m_drawHint.ClearHints();
	m_ctrl->m_CUGSideHdg->Update();

	return UG_SUCCESS;
}

/////////////////////////////////////////////////////////////////
//	OnHitBottom
//		This notification is calle when the last row in the gird is 
//		visible in the view, use this notification to:
//		- check the data base if there are more rows ready for viewing
//		- if necessarry fetch new range of rows.
int CADOImpDatasource::OnHitBottom(long numrows,long rowspast,long *rowsfound)
{
	UNREFERENCED_PARAMETER(rowspast);

	if ( m_pcRowsObtained < m_nMaxFetchRows )
	{	// the recordset alredy reached the bottom, there is no need to try
		// to fetch additional (new) rows.  They will always be the same
		*rowsfound = 0;

		if ( !m_bEditingConfirmed )
			IsRecordsetUpdatable();

		// if the Ghost Row is enabled, but not shown yet ...
		if ( m_nCurGhostRow < 0 && m_bUseGhostRow == TRUE )
		{
			m_nCurGhostRow = numrows;
			*rowsfound = 1;
		}
	}
	else if ( FetchNewRows( numrows ) == UG_SUCCESS )
	{	// calculate the actual number of rows found
		*rowsfound = ( m_nFetchedStarting + m_pcRowsObtained ) - m_ctrl->GetNumberRows();

		if ( !m_bEditingConfirmed )
			IsRecordsetUpdatable();

		// if we have reached the bottom of the rowset, add ghost row
		if ( m_bUseGhostRow == TRUE && m_pcRowsObtained < m_nMaxFetchRows )
			*rowsfound = *rowsfound + 1;
	}
	else
	{	// fetching operation failed
		*rowsfound = 0;
	}

	return UG_SUCCESS;
}

/***************************************************
OnRowChange
	Sent whenever the current row changes
Params:
	oldrow		- row that is losing the focus
	newrow		- row that user moved into
Return:
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
void CADOImpDatasource::OnRowChange(long oldRow,long newRow)
{
	UNREFERENCED_PARAMETER(newRow);

	// make changes permanent
	if ( m_iUpdatesPending > 0 )
	{
		long nUpdateRow = oldRow;
		m_ctrl->OnDataSourceNotify( GetID(), UG_ADO_DS_UPDATE_RECORD, (long)&nUpdateRow );

		if ( nUpdateRow < 0 )
		{
			CancelUpdates();
			// Adjust the current row and edit information
			m_ctrl->m_GI->m_currentRow = oldRow;
			m_ctrl->m_editInProgress = FALSE;
		}
		// set pending updates
		else if ( UpdatePending( FALSE ) == UG_ERROR )
		{
			// Prompt the user that the data cannot be saved
			// and allow them to continue editing current row or
			// to loose the changes
			CString szErrMessage = _T("An error occured while updating the database.\n");
			szErrMessage += _T("Do you want to lose changes and continue to another record?");
			// Allow for the error string to be modified before
			// the message box is displayed.
			m_ctrl->OnDataSourceNotify( GetID(), UG_ADO_DS_UPDATE_ERROR, (long)&szErrMessage );
			// if the error message is empty then assume that the
			// developer does not want to show the message box.
			if ( szErrMessage.GetLength() > 0 )
			{
				if ( m_ctrl->MessageBox( szErrMessage, _T("Error while updating."), MB_YESNO ) == IDYES )
				{
					// clear our the updates list
					CancelUpdates();
					// make sure the editing is canceled
					m_ctrl->m_editInProgress = FALSE;
					return;
				}
			}

			// reset user's position to the last cell
			m_ctrl->m_GI->m_dragRow = oldRow;
			m_ctrl->m_GI->m_currentRow = oldRow;
			m_ctrl->m_editRow = oldRow;
			m_ctrl->m_GI->m_multiSelect->ClearAll();

			if ( m_ctrl->m_editInProgress == FALSE )
				m_ctrl->RedrawRow( newRow );
		}
		else
		{	// indicate that all cells were updated
			m_nOldGhostRow = -1;
			// and fully redraw the updated row
			m_ctrl->RedrawRow( nUpdateRow );
		}
	}
	else if ( m_bUseGhostRow != TRUE )
	{
		// clear the ghost row information
		m_nOldGhostRow = -1;
		m_nCurGhostRow = - 1;
		// remove the additional row
		if ( m_hUpdatedRow.GetUpdateRowNumber() >= 0 )
		{
			m_hUpdatedRow.SetUpdateRowNumber( -1 );
			m_ctrl->SetNumberRows( m_ctrl->GetNumberRows() - 1 );
		}
	}
}

/***************************************************
UpdatePending
	function is used to make permanent all of the changes that the
	user has made.
Params:
	<none>
Return:
	UG_SUCCESS	success
	UG_ERROR	if no updates are pending
****************************************************/
int CADOImpDatasource::UpdatePending( BOOL redraw /*= TRUE*/ )
{
	if ( m_hUpdatedRow.Count() == 0 )
		return UG_ERROR;

	_variant_t tempVar;
	int numCols = GetNumCols();

	try
	{
		if ( m_hUpdatedRow.GetUpdateRowNumber() == m_nOldGhostRow && m_nOldGhostRow >= 0 )
		{	// insert new record into the database
			m_pRecordSet->AddNew();
		}
		else
		{
			int nStartingDelta = m_hUpdatedRow.GetUpdateRowNumber() - m_nFetchedStarting;
			// move to proper record in the database
			m_pRecordSet->PutBookmark( m_curBookmark );
			// move current row as calculated
			m_pRecordSet->Move( nStartingDelta );
		}

		tempVar.vt = VT_I4;

		for ( int nIndex = 0; nIndex < numCols; nIndex ++ )
		{
			if ( m_hUpdatedRow.IsUpdated( nIndex ) &&
				 m_pRecordSet->GetFields()->GetItem((COleVariant)(long)nIndex)->GetAttributes()&adFldUpdatable )
			{
				tempVar.lVal = nIndex;
				m_pRecordSet->PutCollect( tempVar, m_hUpdatedRow.GetUpdatedVal( nIndex ));
			}
		}

		// update the record
		m_pRecordSet->Update();
		// clear our the updated cols list
		m_hUpdatedRow.Empty();
		m_iUpdatesPending = 0;
		// current ghost row does not contain any data
		// at this point so there is not need to store
		// the last ghost row position.
		m_nOldGhostRow = -1;
		if ( m_bUseGhostRow != TRUE )
			// clear the ghost row number when not used
			m_nCurGhostRow = - 1;

		// reload the memory buffer
		if ( m_ctrl->GetSafeHwnd() != NULL )
		{
			FetchNewRows( m_ctrl->GetTopRow());

			if ( redraw )
				RefreshGrid();
		}
	}
	catch(...)
	{
		m_pRecordSet->CancelUpdate();

		return UG_ERROR;
	}

	return UG_SUCCESS;
}

/***************************************************
AppendRow
	just let the grid go ahad and create new row, the data source
	will handle the user's imput when necessary.
Params:
	<none>
Return:
	UG_SUCCESS	success
****************************************************/
int CADOImpDatasource::AppendRow()
{
	// check if the recordset supports updates
	if ( !m_bEditingConfirmed )
		IsRecordsetUpdatable();

	if ( !m_bAllowEdits )
		// make sure that new records are not added
		// when edits are not allowed
		return UG_ERROR;

	// Once it it confirmed that the recordset is updatable
	// than we can check if the recordset allows appends
	try
	{
		_variant_t bSupports = m_pRecordSet->Supports( adAddNew );
		
		if ( bSupports.boolVal == FALSE )
			return UG_ERROR;
	}
	catch(...)
	{
		return UG_ERROR;
	}

	// return success if user decided to use standard way of appending rows
	if ( m_bUseSimpleNew == FALSE )
		return UG_SUCCESS;

	// if GhostRow is enabled than make sure that all records are loaded
	// and move the focus rectangle to the first column in the ghost row
	if ( m_bUseGhostRow == TRUE )
	{
		if ( m_nCurGhostRow < 0 )
		{
			m_ctrl->SetNumberRows( GetNumRowsComplete());
			m_ctrl->GotoCell( 0, m_ctrl->GetNumberRows() - 1 );
		}

		m_ctrl->GotoCell( 0, m_nCurGhostRow );

		return UG_NA;
	}

	// In non-ghost row mode, make sure that the grid reflects the full
	// row number in the recordset.
	m_ctrl->SetNumberRows( GetNumRowsComplete() + 1 );
	m_ctrl->GotoCell( 0, m_ctrl->GetNumberRows() - 1 );
	m_hUpdatedRow.SetUpdateRowNumber( m_ctrl->GetNumberRows() - 1 );
	m_nCurGhostRow = m_ctrl->GetNumberRows() - 1;
	m_nOldGhostRow = m_ctrl->GetNumberRows() - 1;
	m_ctrl->RedrawRow( m_ctrl->GetNumberRows() - 1 );

	return UG_NA;
}

/***************************************************
DeleteRow
	A virtual function that provides standard interface
	to delete specified row from the data source.
Params:
	row			- indicates the row number to delete
Return:
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CADOImpDatasource::DeleteRow(long row)
{
	if ( !m_bEditingConfirmed )
		IsRecordsetUpdatable();

	// make sure that rows cannot be deleted when edits are not allowed
	if ( !m_bAllowEdits )
		return UG_ERROR;

	_variant_t tempVar;

	try
	{
		long nRowUpdated = m_hUpdatedRow.GetUpdateRowNumber();

		if ( nRowUpdated == row && nRowUpdated >= 0 )
		{
			m_hUpdatedRow.Empty();
			m_iUpdatesPending = 0;
		}

		if ( nRowUpdated == m_nOldGhostRow && nRowUpdated >= 0 )
		{	// delete half populated ghost row, not saved yet
			m_nCurGhostRow = m_ctrl->GetNumberRows() - 1;
			m_nOldGhostRow = -1;
		}
		else
		{
			int nStartingDelta = row - m_nFetchedStarting;
			// move to proper record in the database
			m_pRecordSet->PutBookmark( m_curBookmark );
			// move current row as calculated
			m_pRecordSet->Move( nStartingDelta );
			// delete record from database
			m_pRecordSet->Delete( adAffectCurrent );

			// update position of the ghost row
			if ( m_nCurGhostRow == m_ctrl->GetNumberRows() - 1 )
			{
				m_nCurGhostRow -= 1;
			}
		}
		// the SAFEARRAY of fetched rows needs to be updated
		// after the record is deleted from the databse.
		// And the grid's view needs to be updated.
		RefreshGrid();
	}
	catch(...)
	{
		if ( m_pRecordSet->GetEditMode() == adEditDelete )
			m_pRecordSet->CancelUpdate();

		return UG_ERROR;
	}

	return UG_SUCCESS;
}

/***************************************************
OnEditStart
	This message is sent whenever the grid is ready to
	start editing a cell
Params:
	col, row - location of the cell that edit was requested over
	edit -	pointer to a pointer to the edit control,
			allows for swap of edit control if edit 
			control is swapped permanently (for the
			whole grid) is it better to use 'SetNewEditClass'
			function.
Return:
	TRUE - to allow the edit to start
	FALSE - to prevent the edit from starting
****************************************************/
int CADOImpDatasource::OnEditStart(int col, long row,CWnd **edit)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(row);
	UNREFERENCED_PARAMETER(edit);

	if ( m_pRecordSet->GetFields()->GetItem((COleVariant)(long)col)->GetAttributes()&adFldUpdatable )
	{
		if ( !m_bEditingConfirmed )
			IsRecordsetUpdatable();

		return m_bAllowEdits;
	}

	return FALSE;
}

/***************************************************
IsRecordsetUpdatable
	function is used to double check if the recordset allows
	editing.
Params:
	<none>
Return:
	TRUE - to allow the edit to start
	FALSE - to prevent the edit from starting
****************************************************/
int CADOImpDatasource::IsRecordsetUpdatable()
{
	if ( m_bAllowEdits == TRUE )
	{
		try
		{
			_variant_t bSupports = m_pRecordSet->Supports( adUpdate );
			
			if ( bSupports.boolVal == FALSE )
				m_bAllowEdits = FALSE;
		}
		catch(...)
		{
			m_bAllowEdits = FALSE;
		}
	}

	// if editing is not allowed, than make sure that
	// the ghost row is also disabled.
	if ( m_bAllowEdits == FALSE )
		m_bUseGhostRow = FALSE;

	m_bEditingConfirmed = TRUE;

	return m_bAllowEdits;
}

/***************************************************
OnEditVerify
	This notification is sent every time the user hits
	a key while in edit mode.  It is mostly used to create
	custom behavior of the edit contol, because it is
	so eazy to allow or disallow keys hit.
Params:
	col, row	- location of the edit cell
	edit		-	pointer to the edit control
	vcKey		- virtual key code of the pressed key
Return:
	TRUE - to accept pressed key
	FALSE - to do not accept the key
****************************************************/
int CADOImpDatasource::OnEditVerify(int col,long row,CWnd *edit,UINT *vcKey)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(edit);
	UNREFERENCED_PARAMETER(vcKey);

	if ( m_bUseGhostRow == TRUE && row == m_nCurGhostRow )
	{	// if needed show new Ghost row
		m_nOldGhostRow = m_nCurGhostRow;
		m_ctrl->SetNumberRows( m_ctrl->GetNumberRows() + 1, FALSE );
		m_nCurGhostRow = m_ctrl->GetNumberRows() - 1;
		m_hUpdatedRow.SetUpdateRowNumber( row );

		// update the grid's view
		CRect rect;
		m_ctrl->GetRangeRect( m_ctrl->GetLeftCol(),
							  m_ctrl->GetTopRow(),
							  m_ctrl->GetRightCol(),
							  m_ctrl->GetBottomRow(),
							  rect );
		m_ctrl->m_CUGGrid->m_drawHint.ClearHints();
		m_ctrl->m_CUGGrid->m_drawHint.AddHint( m_ctrl->GetLeftCol(),
							  m_ctrl->GetTopRow(),
							  m_ctrl->GetRightCol(),
							  m_ctrl->GetBottomRow());
		m_ctrl->m_CUGGrid->PaintDrawHintsNow( rect );
		m_ctrl->m_CUGGrid->m_drawHint.ClearHints();
		m_ctrl->m_CUGSideHdg->Update();
	}

	return TRUE;
}

/***************************************************
OnEditFinish
	This notification is sent when the edit is being finised
Params:
	col, row	- coordinates of the edit cell
	edit		- pointer to the edit control
	string		- actual string that user typed in
	cancelFlag	- indicates if the edit is being cancelled
Return:
	TRUE - to allow the edit it proceede
	FALSE - to force the user back to editing of that same cell
****************************************************/
int CADOImpDatasource::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag)
{
	UNREFERENCED_PARAMETER(col);
	UNREFERENCED_PARAMETER(edit);
	UNREFERENCED_PARAMETER(string);
	// if we are editing the last row and the user canceled the edit and this was
	// the only value in the new row, than we should delete the new row.
	
	if ( cancelFlag == TRUE && row == m_nOldGhostRow && m_hUpdatedRow.Count() == 0 )
	{
		m_ctrl->SetNumberRows( m_ctrl->GetNumberRows() - 1, FALSE );
		m_nCurGhostRow = m_ctrl->GetNumberRows() - 1;
		m_nOldGhostRow = -1;

		RefreshGrid();
	}

	return TRUE;
}

/***************************************************
SortBy
	A virtual function that provides standard interface
	to sort data in the data source.  This function is
	called when user calls CUGCtrl::SortBy
Params:
	cols		- array of columns to be sorted, in the
				  sort order.
	num			- number of elements in the array
	flags		- sort flag identifying the sort direction
					UG_SORT_ASCENDING
					UG_SORT_DESCENDING
Return:
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CADOImpDatasource::SortBy(int *cols,int num,int flags)
{
	// clear previous sort criteria
	m_SortOrder = "";

	CString tempColName;
	// crate new sort (ORDER BY) string
	for ( int nIndex = 0; nIndex < num; nIndex ++ )
	{
		if ( m_SortOrder != "" )
			m_SortOrder += ", ";

		GetColName( cols[nIndex], &tempColName );
		m_SortOrder += "[";
		m_SortOrder += tempColName;
		m_SortOrder += "]";

		if ( flags == UG_SORT_DESCENDING )
			m_SortOrder += " DESC";
	}

	// provide the developer with a chance to perform final adjustments
	// to the ORDER BY string created.
	if(m_ctrl != NULL)
		m_ctrl->OnDataSourceNotify( GetID(), UG_ADO_DS_SORTBY, (long)&m_SortOrder );

	// re-open the recordset using the new sort criteria
	if ( Open( NULL, NULL ) != UG_ERROR )
	{
		return FetchNewRows( m_ctrl->GetTopRow());
	}
	return UG_ERROR;
}

/***************************************************
SetOption
	Datasource dependant function. Used to set data source
	specific information and modes of operation
Params:
	option		- integer identifying the option to set
	param1		- option depanded parameter
	param2		- option depanded parameter
Return:
	UG_SUCCESS	success
****************************************************/
int CADOImpDatasource::SetOption(int option,long param1,long param2)
{
	UNREFERENCED_PARAMETER(param2);

	switch( option )
	{
	case UG_ADO_DS_SET_EDITMODE:
		if ( param1 != FALSE )
			param1 = TRUE;

		m_bAllowEdits = param1;
		m_bEditingConfirmed = FALSE;
		break;
	case UG_ADO_DS_USE_GHOSTROW:
		if ( param1 != FALSE )
			param1 = TRUE;

		m_bUseGhostRow = param1;
		break;
	case UG_ADO_DS_SET_FETCHSIZE:
		m_nMinFetchRows = param1;
		break;
	case UG_ADO_DS_SET_ROWIDCHAR:
		m_sCurRowID = CString((char)param1);
		break;
	case UG_ADO_DS_USE_SIMPLENEW:
		if ( param1 != FALSE )
			param1 = TRUE;

		m_bUseSimpleNew = param1;
		break;
	}
	return UG_SUCCESS;
}

/***************************************************
GetOption
	Datasource dependant function. Used to get data source
	specific information and modes of operation
Params:
	option		- integer identifying the option to set
	param1		- option depanded parameter
	param2		- not used
Return:
	UG_SUCCESS	success
****************************************************/
int CADOImpDatasource::GetOption(int option,long& param1,long& param2)
{
	UNREFERENCED_PARAMETER(param2);

	switch( option )
	{
	case UG_ADO_DS_SET_EDITMODE:
		m_bAllowEdits = (BOOL)param1;
		m_bEditingConfirmed = FALSE;
		break;
	case UG_ADO_DS_USE_GHOSTROW:
		m_bUseGhostRow = (BOOL)param1;
		m_bEditingConfirmed = FALSE;
		break;
	case UG_ADO_DS_SET_FETCHSIZE:
		m_nMinFetchRows = param1;
		break;
	case UG_ADO_DS_SET_ROWIDCHAR:
		param1 = (long)m_sCurRowID.GetAt(0);
		break;
	}
	return UG_SUCCESS;
}

/****************************************************
StartTransaction
	A virtual function that provides standard method
	to start a transaction.  Very important when
	working with databases.
Params:
	<none>
Return:
	UG_SUCCESS	success
	UG_ERROR	error codes (data source dependant)
****************************************************/
int CADOImpDatasource::StartTransaction()
{
	try
	{
		m_pConnection->BeginTrans();
	}
	catch(...)
	{
		return UG_ERROR;
	}

	return UG_SUCCESS;
}

/****************************************************
CancelTransaction
	A virtual function that provides standard method
	to cancel (undo) changes that were made after
	last call to the StartTransaction.
Params:
	<none>
Return:
	UG_SUCCESS	success
	UG_ERROR	error codes (data source dependant)
****************************************************/
int CADOImpDatasource::CancelTransaction()
{
	try
	{
		m_pConnection->RollbackTrans();
	}
	catch(...)
	{
		return UG_ERROR;
	}

	return UG_SUCCESS;
}

/****************************************************
FinishTransaction
	A virtual function that provides standard method
	to make permanent the changes that were made
	after the last call to the StartTransaction.
Params:
	<none>
Return:
	UG_SUCCESS	success
	UG_ERROR	error codes (data source dependant)
****************************************************/
int CADOImpDatasource::FinishTransaction()
{
	try
	{
		m_pConnection->CommitTrans();
	}
	catch(...)
	{
		return UG_ERROR;
	}

	return UG_SUCCESS;
}


/****************************************************
UpdateNow
	function forces current changes to be made permanent
	without waiting for user's action (ie change row).
Params:
	<none>
Return:
	UG_SUCCESS	success
	UG_NA		the updaate command is not necessary,
				there is nothing to update.
	UG_ERROR	error, the update operation failed.
****************************************************/
int CADOImpDatasource::UpdateNow()
{
	if ( m_iUpdatesPending <= 0 )
		return UG_NA;

	return UpdatePending( FALSE );
}

/****************************************************
CancelUpdates
	function cancels (or un-does) current changes.
	It will delete all entries from the m_hUpdatedRow
	object and it will reset the ghostrow position.
Params:
	<none>
Return:
	UG_SUCCESS	success
	UG_ERROR	error, this function will never fail.
****************************************************/
int CADOImpDatasource::CancelUpdates()
{
	// clear our the updated cols list
	m_hUpdatedRow.Empty();
	m_iUpdatesPending = 0;

	if ( m_nOldGhostRow > 0 )
	{
		// adjust number of rows in the grid
		m_ctrl->SetNumberRows( m_ctrl->GetNumberRows() - 1, FALSE );
		m_ctrl->m_CUGSideHdg->Update();
		m_nCurGhostRow = m_ctrl->GetNumberRows() - 1;
		m_nOldGhostRow = -1;
	}

	return UG_SUCCESS;
}

/****************************************************
RefreshView
	function forces the datasource to refresh current block
	of rows by reallocating the memory buffer.
Params:
	<none>
Return:
	UG_SUCCESS	success
	UG_ERROR	error, the fetch operation failed
				or the recordset is not open at the moment.
****************************************************/
int CADOImpDatasource::RefreshData()
{
	// make sure the recordset is open
	if ( m_pRecordSet == NULL )
		return UG_ERROR;

	m_nCurGhostRow = -1;
	m_nOldGhostRow = -1;

	return FetchNewRows( m_ctrl->GetTopRow());
}
