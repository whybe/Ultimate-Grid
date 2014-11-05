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
#include "stdafx.h"

#include "ugoledb.h"


/***************************************************
Open
	Override this function to provide file loading to
	a data source
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)

name = database name
option = open sql/query

****************************************************/
int CUG_OLEDB_DataSource::Open(LPCTSTR name,LPCTSTR option)
{
	// open our database connection and execute command
	Close();
	if(name)
		m_DBName=name;
	if(option)
		m_Command=option;
	if(ExecuteQuery())
		return UG_SUCCESS;
	return UG_ERROR;
}
/***************************************************
SetPassword
	Override this function if a password is needed 
	for the data source
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUG_OLEDB_DataSource::SetPassword(LPCTSTR user,LPCTSTR pass)
{
	// set the username, password
	m_UserName=user;
	m_Password=pass;
	return UG_SUCCESS;
}
/***************************************************
Close
	Override this function if a close command is needed
	for the data source
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUG_OLEDB_DataSource::Close()
{
	CloseRowset();
	CloseSession();

	// clean up everything
	IErrorInfo* pIErrorInfo;

	// Release any remaining error objects.  This is idempotent.
	// Otherwise the provider might have an outstanding global-object count.
	GetErrorInfo( 0, &pIErrorInfo );
	if (pIErrorInfo!= NULL)
		pIErrorInfo->Release();

	// Free the error queues
	SetErrorInfo(0,NULL);
	return UG_NA;
}

/***************************************************
************ row and col info **********************
****************************************************/

/***************************************************
GetNumRows
	Returns the number of rows of data available
return
	UG_NA		not available
	number of rows
****************************************************/
long CUG_OLEDB_DataSource::GetNumRows()
{
	// return 1 to allow us to find out the number of 
	// rows later 
	return 1;
}

/***************************************************
GetNumCols
	Returns the number of Columns of data avialable
return
	UG_NA		not available
	number of cols
****************************************************/
int CUG_OLEDB_DataSource::GetNumCols()
{
	return m_Cols.GetNumCols();
}
/***************************************************
GetColName
	Returns the name of a column
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUG_OLEDB_DataSource::GetColName(int col,CString * string)
{
	Column* pCol=m_Cols[col];
	if(pCol!=NULL)
	{
		*string=pCol->ColumnName();
		return UG_SUCCESS;
	}
	return UG_ERROR;
}

/***************************************************
GetColFromName
	Returns the column number for a named column
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUG_OLEDB_DataSource::GetColFromName(LPCTSTR name,int *col)
{
	int ub=GetNumCols();
	CString temp;
	for(int i=0; i<ub; i++)
	{
		GetColName(i,&temp);
		if(temp==name)
			return i;
	}
	return -1;
}

/***************************************************
GetColType

	Returns the default data type of a column
	type =	0-string 1-bool 2-short 3-long 4-float 
			5-double 6-currency 7-data 8-time
			8-blob 9-graphic 10-ole

return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUG_OLEDB_DataSource::GetColType(int col,int *type)
{

/*	HRESULT hr;

  
	hr=pField->get_Type(&nType);
	pField->Release();

	switch(nType)
	{
	case adTinyInt:
	case adSmallInt:
	case adInteger:
	case adUnsignedTinyInt:
	case adUnsignedSmallInt:
	case adUnsignedInt:
		*type = 2;
		break;
	case adUnsignedBigInt:
	case adBigInt:
	case adDecimal:
	case adNumeric:
		*type = 3;
		break;
	case adSingle:
		*type = 4;
		break;
	case adDouble:
		*type = 5;
		break;
	case adCurrency:
		*type = 6;
		break;
	case adBoolean:
		*type = 1;
		break;
	case adGUID:
		*type = 10;
		break;
	case adDate:
	case adDBDate:
	case adDBTime:
	case adDBTimeStamp:
		*type = 7;
		break;
	case adBSTR:
	case adChar:
	case adVarChar:
	case adWChar:
	case adVarWChar:
		*type = 0;
		break;
	case adLongVarChar:
	case adLongVarWChar:
		*type = 8;
		break;
	case adBinary:
	case adVarBinary:
	case adLongVarBinary:
		*type = 9;
		break;
	case adError:
	case adEmpty:
	case adUserDefined:
	case adVariant:
	case adIDispatch:
	case adIUnknown:
	default:
		*type = 11;
		break;
	} */
	return UG_SUCCESS;
}


	
/***************************************************
************* add-update-clear *********************
****************************************************/

/***************************************************
AppendRow
	Appends a new row at the end of the current data
	in the data source
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUG_OLEDB_DataSource::AppendRow()
{
	IRowsetChange* pIRowsetChange=NULL;
	HRESULT hr=m_pIRowset->QueryInterface(IID_IRowsetChange, (void**)&pIRowsetChange);
	if(FAILED(hr))
		// no update ability
		return UG_ERROR;
	hr=pIRowsetChange->InsertRow (0,m_hAccessor,NULL, NULL);
	pIRowsetChange->Release();
	if(FAILED(hr))
		// no update ability
		return UG_ERROR;
	return UG_SUCCESS;
}
/***************************************************
DeleteRow
	Deletes the specified row from the data in the 
	data source
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUG_OLEDB_DataSource::DeleteRow(long row)
{
	IRowsetChange* pIRowsetChange=NULL;
	HRESULT hr=m_pIRowset->QueryInterface(IID_IRowsetChange, (void**)&pIRowsetChange);
	if(FAILED(hr))
		// no update ability
		return UG_ERROR;
		
	// make the row one of the current rowset
	LoadRow(row);
	hr=pIRowsetChange->DeleteRows (0, 1, &m_rghRows[row%NUM_FETCH], NULL);
	if(FAILED(hr))
	{	
		ReportError(pIRowsetChange, IID_IRowsetChange);
		pIRowsetChange->Release();
		return UG_ERROR;
	}
	pIRowsetChange->Release();
	return UG_SUCCESS;

}

/***************************************************
Empty 
	Empties all the data in the data source
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUG_OLEDB_DataSource::Empty()
{
	Close();
	return UG_NA;
}
/***************************************************
****************** cell info ***********************
****************************************************/

/***************************************************
GetCell
	Updates the given cell with 'set' information for
	the specified cell. (only information that is 'set'
	should be updated, since every data property has an
	'unset' state).
return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUG_OLEDB_DataSource::GetCell(int col,long row,CUGCell *cell)
{
//	TRACE("col = %d, row = %ld\n",col,row);
	// column headings
	if(col==-1)  // we can do nothing with row headings or corner
    {
        if ( row >= 0 )
        {
            cell->SetNumberDecimals( 0 );
            cell->SetNumber( row + 1 );
        }
		return UG_NA;
    }
	if(row==-1)
	{  // supply field names for column headings 
		CString str;
		GetColName(col, &str);
		cell->SetText(str);
	}
	else{
		cell->SetText(GetCellText(col,row));
	}
	return UG_SUCCESS;
}

/***************************************************
SetCell
	Sets the cell - including all 'unset' information

return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUG_OLEDB_DataSource::SetCell(int col,long row,CUGCell *cell)
{
	CUGCell orig;
	HRESULT hr;
	GetCell(col,row,&orig);

	// has the text changed? -- all other cell attributes 
	// are not persistent
	CString text(cell->GetText());
	if(text==orig.GetText())
		return UG_SUCCESS;
	
	hr=LoadRow(row);
	if(FAILED(hr))
		// row DNE
		return UG_ERROR;

	IRowsetChange* pIRowsetChange=NULL;
	hr=m_pIRowset->QueryInterface(IID_IRowsetChange, (void**)&pIRowsetChange);
	if(FAILED(hr))
		// no update ability
		return UG_ERROR;

	Column* pCol=m_Cols[col];
	if(pCol!=NULL)
	{
		pCol->FromString(text);
	}

	HACCESSOR hAccessor;

	ULONG iBind;				// Binding Index
	DBBINDING*		rgBind=NULL;		// bindings of data
	m_Cols.SetDirtyColumnBindings(&rgBind, &iBind);
	IAccessor* pIAccessor;
	hr = m_pIRowset->QueryInterface(IID_IAccessor, (void**)&pIAccessor );
	ASSERT(SUCCEEDED(hr));
	hr = pIAccessor->CreateAccessor(DBACCESSOR_ROWDATA, iBind, rgBind, 0, &hAccessor,NULL);
	if (FAILED(hr))
	{
		ReportError(pIAccessor, IID_IAccessor);
	}

	
	hr=pIRowsetChange->SetData(m_rghRows[row%NUM_FETCH],hAccessor, m_Cols.BaseAddress());
	delete [] rgBind;
	pIAccessor->ReleaseAccessor(hAccessor, NULL);
	pIAccessor->Release();
	if(FAILED(hr))
	{	
		ReportError(pIRowsetChange, IID_IRowsetChange);
		pIRowsetChange->Release();
		return UG_ERROR;
	}

	pIRowsetChange->Release();
	return UG_NA;
}

/***************************************************
****************  finding sorting ******************
****************************************************/

/***************************************************
SortBy
	Sorts (or indexes) the data by the specified column

return
	UG_NA		not available
	UG_SUCCESS	success
	1...		error codes (data source dependant)
****************************************************/
int CUG_OLEDB_DataSource::SortBy(int col,int flags)
{

	CString str;
	GetColName(col,&str);
	m_SortOrder = str;
	OpenRowset();
	return UG_NA;
}

/****************************************************
****************************************************/
int CUG_OLEDB_DataSource::StartTransaction()
{
	// we are allowing only one transaction per datasource 
	if(m_pTransaction!=NULL)
		return UG_ERROR;

	m_pSession->QueryInterface(IID_ITransaction, (void**) &m_pTransaction);
	return UG_SUCCESS;
}
/****************************************************
****************************************************/
int CUG_OLEDB_DataSource::CancelTransaction()
{
	if(m_pTransaction==NULL)
		return UG_ERROR;
	m_pTransaction->Abort(NULL, FALSE,FALSE);
	m_pTransaction->Release();
	m_pTransaction=NULL;
	return UG_NA;
}
/****************************************************
****************************************************/
int CUG_OLEDB_DataSource::FinishTransaction()
{
	if(m_pTransaction==NULL)
		return UG_ERROR;
	m_pTransaction->Commit(FALSE,XACTTC_SYNC,0);
	m_pTransaction->Release();
	m_pTransaction=NULL;
	return UG_NA;
}


/***************************************************
****************************************************/
int CUG_OLEDB_DataSource::OnCellChange(long col,long row)
{

	// cache the current cell's text
	if(row!=m_CurrentCellRow || col!=m_CurrentCellCol)
	{
		m_CurrentCellText=GetCellText(col,row);
		m_CurrentCellRow=row;
		m_CurrentCellCol=col;
	}
	return UG_NA;
}



BOOL CUG_OLEDB_DataSource::IsFunctionSupported(long type)
{
		// return true for alll functions that we do support.
	if((type&UGDS_SUPPORT_DELETEROW)==UGDS_SUPPORT_DELETEROW)
		return TRUE;
	if((type&UGDS_SUPPORT_APPENDROW)==UGDS_SUPPORT_APPENDROW)
		return TRUE;
	if((type&UGDS_SUPPORT_EMPTY)==UGDS_SUPPORT_EMPTY)
		return TRUE;
	if((type&UGDS_SUPPORT_CLOSE)==UGDS_SUPPORT_CLOSE)
		return TRUE;
	if((type&UGDS_SUPPORT_CLOSE)==UGDS_SUPPORT_CLOSE)
		return TRUE;
	if((type&UGDS_SUPPORT_SORT)==UGDS_SUPPORT_SORT)
		return TRUE;
	if((type&UGDS_SUPPORT_GETNUMCOLS)==UGDS_SUPPORT_GETNUMCOLS)
		return TRUE;
	if((type&UGDS_SUPPORT_GETCOLTYPE)==UGDS_SUPPORT_GETCOLTYPE)
		return TRUE;
	if((type&UGDS_SUPPORT_GETNUMCOLS)==UGDS_SUPPORT_GETNUMCOLS)
		return TRUE;
	if((type&UGDS_SUPPORT_SETCELL)==UGDS_SUPPORT_SETCELL)
		return TRUE;
	if((type&UGDS_SUPPORT_GETCELL)==UGDS_SUPPORT_GETCELL)
		return TRUE;
	if((type&UGDS_SUPPORT_TRANSACTIONS)==UGDS_SUPPORT_TRANSACTIONS)
		return TRUE;
	if((type&UGDS_SUPPORT_HITBOTTON)==UGDS_SUPPORT_HITBOTTON)
		return TRUE;
	return FALSE;

}



/***************************************************
****************************************************/
int CUG_OLEDB_DataSource::OnHitBottom(long numrows,long rowspast,long *rowsfound)
{
	if(m_endSeen)
	{
		/*if(numrows!=m_MaxRow)
			*rowsfound=m_MaxRow-numrows;
		else*/
			*rowsfound=0;
	}
	else if(m_MaxRow>numrows)
		*rowsfound=m_MaxRow-numrows;
	else
	{
		LoadRow(numrows);
		*rowsfound=m_MaxRow-numrows;
	}
	return UG_SUCCESS;
}
