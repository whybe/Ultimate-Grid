#include "stdafx.h"


#define DBINITCONSTANTS
#define INITGUID

#include "oledb.h"
#include "oledberr.h"

#include "ugoledb.h"

#include "MSDASQL.H"

#include "ugstrop.h"

//#include "msdaguid.h"

CLSID CLSID_OLEDB_ENUMERATOR = {0xc8b522d0L,0x5cf3,0x11ce,{0xad,0xe5,0x00,0xaa,0x00,0x44,0x77,0x3d}};




//#define COLUMN_ALIGNVAL 8
//#define ROUND_UP( Size, Amount ) (((DWORD)(Size) +  ((Amount) - 1)) & ~((Amount) - 1))

#define MAXBUFLEN 1024
#define NUMELEM(p1) (sizeof(p1) / sizeof(p1[0]))
//#define MAX_NUM_PROVIDERS 20

CUG_OLEDB_DataSource::CUG_OLEDB_DataSource()
{
	m_pIRowset=NULL;
	m_cBind=0;
	m_cMaxRowSize=0;
	m_MaxRow=0;
	m_endSeen=FALSE;
	m_currRow=-NUM_FETCH;
	m_obtRows=NUM_FETCH;
	m_hAccessor=NULL;
	m_Provider="MSDASQL";
	m_pSession=NULL;
	m_pTransaction=NULL;
	m_CurrentCellRow=-1;
	m_CurrentCellCol=-1;
	m_ctrl=NULL;
	CoInitialize(NULL);
}

CUG_OLEDB_DataSource::~CUG_OLEDB_DataSource()
{
	Close();
	// Uninitialize OLE
	CoUninitialize();
}



HRESULT CUG_OLEDB_DataSource::OpenSession()
{
	HRESULT				hr;
	ISourcesRowset*		pISrcRowset;
	DBPROPSET			rgPropertySet[1];			// Array of property sets
	DBPROP				rgProperties[3];			// Array of property values
	ULONG				chEaten;
	m_pSession=NULL;

	if(m_Provider=="")
		return FALSE;
	if(m_DBName=="")
		return FALSE;
	
	// Initialize the OLE DB Enumerator
	if( FAILED(hr = CoCreateInstance(CLSID_OLEDB_ENUMERATOR, NULL, 
		CLSCTX_INPROC_SERVER, IID_ISourcesRowset, (LPVOID*)&pISrcRowset)))
		// could not create the enumerator!
		return FALSE;

	IParseDisplayName*	pIParse;
	if(SUCCEEDED(hr = pISrcRowset->QueryInterface(IID_IParseDisplayName, (LPVOID*)&pIParse))) 
	{
		WCHAR szProvName[MAXBUFLEN];
		IMoniker* pIMoniker;
#ifndef _UNICODE
		MultiByteToWideChar(CP_ACP, 0, m_Provider, -1, szProvName, MAXBUFLEN+1);
#else
		UGStr::tcscpy(szProvName, 1024, m_Provider);
#endif
		//Determine the ParseDisplayName
		if(SUCCEEDED(hr = pIParse->ParseDisplayName(NULL, szProvName, &chEaten, &pIMoniker)))
		{
			IDBInitialize*	pIDBInit;
			if(SUCCEEDED(hr = BindMoniker(pIMoniker, 0, IID_IDBInitialize, (LPVOID*)&pIDBInit)) )
			{
				ULONG iProp = 0;
				// Initialize Property Buffers
				for(iProp=0; iProp<NUMELEM(rgProperties); iProp++)
					VariantInit(&(rgProperties[iProp].vValue));
				iProp = 0;
				// If DataSource name specified, then create property node
				if( m_DBName != "" )
				{
					// Fill in Data Source
					rgProperties[iProp].dwPropertyID		=	DBPROP_INIT_DATASOURCE;
					rgProperties[iProp].dwOptions			=	DBPROPOPTIONS_REQUIRED;
					rgProperties[iProp].colid				=	DB_NULLID;
					V_VT(&(rgProperties[iProp].vValue))		=	VT_BSTR;
					V_BSTR(&(rgProperties[iProp].vValue))	=	m_DBName.AllocSysString();
					iProp++;
				}

				// If User Name specified, then create property node
				if( m_UserName != "" )
				{
					rgProperties[iProp].dwPropertyID		=	DBPROP_AUTH_USERID;
					rgProperties[iProp].dwOptions			=	DBPROPOPTIONS_REQUIRED;
					rgProperties[iProp].colid				=	DB_NULLID;
					V_VT(&(rgProperties[iProp].vValue))		=	VT_BSTR;
					V_BSTR(&(rgProperties[iProp].vValue))	=	m_UserName.AllocSysString();;
					iProp++;
				}

				// If Password specified, then create property node
				if( m_Password != "" )
				{
					rgProperties[iProp].dwPropertyID		=	DBPROP_AUTH_PASSWORD;
					rgProperties[iProp].dwOptions			=	DBPROPOPTIONS_REQUIRED;
					rgProperties[iProp].colid				=	DB_NULLID;
					V_VT(&(rgProperties[iProp].vValue))		=	VT_BSTR;
					V_BSTR(&(rgProperties[iProp].vValue))	=	m_Password.AllocSysString();
					iProp++;
				}

				if(iProp)
				{
					IDBProperties* pIDBProperties=NULL;
					// Identify Property Set
					rgPropertySet[0].rgProperties		=	rgProperties;
					rgPropertySet[0].cProperties		=	iProp;
					rgPropertySet[0].guidPropertySet	=	DBPROPSET_DBINIT;
					// from the DataSource Object get the Session Object
					hr = pIDBInit->QueryInterface(IID_IDBProperties, (void**)&pIDBProperties);
					if (SUCCEEDED(hr))
					{
						// Set Connection Properties
						hr = pIDBProperties->SetProperties(1, rgPropertySet);
						pIDBProperties->Release();
					}
				}
				
				// clear Property Buffers
				for(iProp=0; iProp<NUMELEM(rgProperties); iProp++)
					VariantClear(&(rgProperties[iProp].vValue));

 				// Initialize the PROVIDER
				hr = pIDBInit->Initialize();
				if (SUCCEEDED(hr))
				{
					IDBCreateSession*	pIDBCreateSession;
					// from the DataSource Object get the Session Object
					hr = pIDBInit->QueryInterface(IID_IDBCreateSession, (void**)&pIDBCreateSession);
					if (SUCCEEDED(hr))
					{
						// from the Session object, attempt to get an IUnknown
						hr = pIDBCreateSession->CreateSession(NULL, IID_IUnknown, (IUnknown**)&m_pSession);
						pIDBCreateSession->Release();
					}
				}
				pIDBInit->Release();
			}
			pIMoniker->Release();
		}
		pIParse->Release();

	}
	return hr;
} 


void CUG_OLEDB_DataSource::CloseSession()
{
	if(m_pSession!=NULL)
		m_pSession->Release();
	m_pSession=NULL;
}

void CUG_OLEDB_DataSource::CloseRowset()
{
	// cleanup and close the rowset
	if(m_pTransaction)
		CancelTransaction();
	if(m_hAccessor!=NULL)
	{
		IAccessor* pIAccessor=NULL;
		m_pIRowset->QueryInterface(IID_IAccessor, (void**)&pIAccessor);
		pIAccessor->ReleaseAccessor( m_hAccessor, NULL );
		pIAccessor->Release();
	}
	m_hAccessor=NULL;

	if(m_pIRowset!=NULL)
		m_pIRowset->Release();
	m_pIRowset=NULL;

	m_MaxRow=0;
	m_endSeen=FALSE;
	m_currRow=-NUM_FETCH;
	m_cBind=0;
	m_cMaxRowSize=0;
}


HRESULT CUG_OLEDB_DataSource::OpenRowset()
{
	WCHAR				wszCommand[MAXBUFLEN+1];
	DBID				TableID;
	HRESULT				hr = S_OK;
	IDBCreateCommand*	pIDBCreateCommand;


	if(m_pSession==NULL && FAILED(OpenSession()))
		return E_FAIL;

	if(m_pIRowset!=NULL)
		CloseRowset();

	CString command=m_Command;

	if(m_Filter!= _T(""))
		command += _T(" WHERE ") + m_Filter;
	if(m_SortOrder!="")
		command += _T(" ORDER BY ") + m_SortOrder;

	// Convert ANSI String to WCHAR	String
#ifndef _UNICODE
	MultiByteToWideChar(CP_ACP, 0, command, -1, wszCommand, MAXBUFLEN+1);
#else
	UGStr::tcscpy(wszCommand, 1025, command);
#endif
	memset(&TableID, 0, sizeof(DBID));

	// from the Session object, attempt to get the IDBCreateCommand interface
	hr = m_pSession->QueryInterface(IID_IDBCreateCommand, (void**)&pIDBCreateCommand);
	if (SUCCEEDED(hr))
	{
		ICommand* pICommand;
		hr = pIDBCreateCommand->CreateCommand(NULL, IID_ICommand, (IUnknown**)&pICommand);
		// done with pIDBCreateCommand
		pIDBCreateCommand->Release();

		ICommandProperties* pICommandProperties;
		hr = pICommand->QueryInterface(IID_ICommandProperties,(LPVOID*)&pICommandProperties);
		if(SUCCEEDED(hr))
		{
			// set some properties of the command object
			DBPROPSET propset[1];
			DBPROP props[5];

			props[0].dwPropertyID = DBPROP_UPDATABILITY;
			props[0].dwOptions = DBPROPOPTIONS_REQUIRED;
			props[0].dwStatus = DBPROPSTATUS_OK;
			props[0].colid = DB_NULLID;
			props[0].vValue.vt = VT_I4;
			props[0].vValue.lVal = DBPROPVAL_UP_CHANGE|DBPROPVAL_UP_INSERT|DBPROPVAL_UP_DELETE;

			props[1].dwPropertyID = DBPROP_IRowsetChange;
			props[1].dwOptions = DBPROPOPTIONS_REQUIRED;
			props[1].dwStatus = DBPROPSTATUS_OK;
			props[1].colid = DB_NULLID;
			props[1].vValue.vt = VT_BOOL;
			props[1].vValue.boolVal = VARIANT_TRUE;

			props[2].dwPropertyID = DBPROP_CANFETCHBACKWARDS;
			props[2].dwOptions = DBPROPOPTIONS_REQUIRED;
			props[2].dwStatus = DBPROPSTATUS_OK;
			props[2].colid = DB_NULLID;
			props[2].vValue.vt = VT_BOOL;
			props[2].vValue.boolVal = VARIANT_TRUE;

			props[3].dwPropertyID = DBPROP_OWNUPDATEDELETE;
			props[3].dwOptions = DBPROPOPTIONS_REQUIRED;
			props[3].dwStatus = DBPROPSTATUS_OK;
			props[3].colid = DB_NULLID;
			props[3].vValue.vt = VT_BOOL;
			props[3].vValue.boolVal = VARIANT_TRUE;

/*			props[4].dwPropertyID = DBPROP_QUICKRESTART;
			props[4].dwOptions = 0;
			props[4].dwStatus = DBPROPSTATUS_OK;
			props[4].colid = DB_NULLID;
			props[4].vValue.vt = VT_BOOL;
			props[4].vValue.boolVal = VARIANT_TRUE;
*/
			propset[0].rgProperties = props;
			propset[0].cProperties = 4;
			propset[0].guidPropertySet=DBPROPSET_ROWSET;

			hr=pICommandProperties->SetProperties(1,propset);
			pICommandProperties->Release();
		}
		ICommandText*		pICommandText;	
		// QueryInterface for ICommandText::SetCommandText
		hr = pICommand->QueryInterface(IID_ICommandText,(LPVOID*)&pICommandText);
		if(SUCCEEDED(hr))
		{
			// Tell the command object to copy this command text
			// The command object will then use this query when we call ICommand::Execute
			hr = pICommandText->SetCommandText(DBGUID_DBSQL, wszCommand);
			pICommandText->Release();
			long cols;
			// From the command object, get a rowset object by executing command
			hr = pICommand->Execute(NULL,IID_IRowset,NULL,&cols,(IUnknown**)&m_pIRowset);
		}
		else
			return hr;
		pICommand->Release();
	}
	else
	{
		IOpenRowset* pIOpenRowset;
		// if no Command object support, attempt to get the IOpenRowset interface
		hr = m_pSession->QueryInterface(IID_IOpenRowset, (void**)&pIOpenRowset);
		if (FAILED(hr))
			return hr;
		// Pass in table/file name
		TableID.eKind = DBKIND_NAME;
		TableID.uName.pwszName = wszCommand;
		// From IOpenRowset, get a rowset object
		hr = pIOpenRowset->OpenRowset(NULL,&TableID,NULL,IID_IRowset,0,
								NULL,(IUnknown**)&m_pIRowset);
		pIOpenRowset->Release();
	}
	if(FAILED(hr))
		return hr;

	// SetUp Bindings
	hr = SetupBindings();

	return hr;
}

#define DEFAULT_CBMAXLENGTH 1024

HRESULT CUG_OLEDB_DataSource::SetupBindings()
{

	HRESULT hr;
	IColumnsInfo* pIColumnsInfo;
	// set the column info up in the columns class
	hr = m_pIRowset->QueryInterface(IID_IColumnsInfo, (void **) &pIColumnsInfo );
	if (FAILED(hr))
		return hr;
	// Get column information from the command object via IColumnsInfo::GetColumnsInfo 
	hr = m_Cols.SetColumnInfo(pIColumnsInfo);	
	// Release the IColumnsInfo Object
	pIColumnsInfo->Release();
	// did not get columns info
	if (FAILED(hr))
		return hr; 

	ULONG iBind;				// Binding Index
	DBBINDING*		rgBind=NULL;		// bindings of data
	m_Cols.SetColumnBindings(&rgBind, &iBind);
	IAccessor* pIAccessor;
	hr = m_pIRowset->QueryInterface(IID_IAccessor, (void**)&pIAccessor );
	ASSERT(SUCCEEDED(hr));
	hr = pIAccessor->CreateAccessor(DBACCESSOR_ROWDATA, iBind, rgBind, 0, &m_hAccessor,NULL);
	if (FAILED(hr))
	{
		ReportError(pIAccessor, IID_IAccessor);
	}
	delete [] rgBind;
	pIAccessor->Release();
	return hr;
}

CString CUG_OLEDB_DataSource::GetCellText(int col, long row)
{
	if(SUCCEEDED(LoadRow(row)))
	{
		Column* pCol=m_Cols[col];
		if(pCol!=NULL)
		{
			return pCol->ToString();
		}
	}
	return "";
}


HRESULT CUG_OLEDB_DataSource::LoadRow(long row)
{
	HRESULT 	hr;

	// Asserts
	ASSERT(m_pIRowset != NULL);
	ASSERT(m_hAccessor!=NULL);

    if(row>=m_currRow && row<m_currRow+NUM_FETCH)  // in current range of hrows
	{
		hr = m_pIRowset->GetData(m_rghRows[row%NUM_FETCH],m_hAccessor, m_Cols.BaseAddress());
		return S_OK;
	}

	// Release row handles
	hr = m_pIRowset->ReleaseRows(NUM_FETCH, m_rghRows, NULL, NULL, NULL);

	ULONG 	cRowsObtained;			// Number of rows obtained
	HROW*   pRow=&m_rghRows[0];

	long modRow = row/NUM_FETCH*NUM_FETCH;
	long startRow = modRow-(m_currRow+m_obtRows);    

	hr = m_pIRowset->GetNextRows(0,startRow,NUM_FETCH,&cRowsObtained,&pRow);
	TRACE( _T("LoadRow - %d, %d, %d, %d\n"), row, modRow, startRow, m_currRow );

	if (SUCCEEDED(hr))
	{
		hr = m_pIRowset->GetData(m_rghRows[row%NUM_FETCH],m_hAccessor,m_Cols.BaseAddress());
		m_MaxRow=max(((long)cRowsObtained)+row, m_MaxRow);
		if(cRowsObtained>NUM_FETCH)
			m_endSeen=TRUE;
		m_currRow = modRow;
		m_obtRows = cRowsObtained;
	}
	else if (hr==DB_E_BADSTARTPOSITION)
		m_endSeen=TRUE;

	return hr;
}

BOOL CUG_OLEDB_DataSource::ExecuteQuery()
{
	HRESULT	hr;
	// Execute the Command Object
	hr = OpenRowset();
	if (FAILED(hr))
		return FALSE;
	// Empty IRowset
	if(hr == S_FALSE)
		return FALSE;
	// Get first row
	hr = LoadRow(0);
	if (FAILED(hr))
		return FALSE;
	return TRUE;
}



HRESULT CUG_OLEDB_DataSource::ReportError(IUnknown * pBadObject, GUID IID_BadIntereface)
{
	ISupportErrorInfo* pSupportErrorInfo;
	HRESULT hr;
	DWORD MYLOCALEID=0x0409;       //American English

	hr = pBadObject->QueryInterface (IID_ISupportErrorInfo,
	(LPVOID FAR*)&pSupportErrorInfo);

	if (SUCCEEDED(hr)) 
		{
		hr = pSupportErrorInfo->InterfaceSupportsErrorInfo(IID_BadIntereface);
		if (hr ==S_OK) 
			{
			IErrorInfo* pErrorInfo; 
			//Get Error Object. Return if no object Exists
			hr = GetErrorInfo (0,&pErrorInfo);
			if (SUCCEEDED(hr) && pErrorInfo) 
			{
				ULONG i,ulNumErrorRecs;
				IErrorRecords* pErrorRecords;
				//Get the IErrorRecord interface and get the count of error recs.
				hr = pErrorInfo->QueryInterface(IID_IErrorRecords,(LPVOID FAR*)&pErrorRecords);
				if (SUCCEEDED(hr))
				{
					hr = pErrorRecords->GetRecordCount (&ulNumErrorRecs);
					if (FAILED(hr))
						ulNumErrorRecs=0;


					//Go through and print messages
					for (i=0;i<ulNumErrorRecs;i++) 
					{
						BSTR bstrDescriptionOfError = NULL;
						BSTR bstrSourceOfError = NULL;
						IErrorInfo*	pErrorInfoRec;

						hr = pErrorRecords->GetErrorInfo (i,MYLOCALEID,&pErrorInfoRec);
						if (SUCCEEDED(hr))
						{
							pErrorInfoRec->GetDescription (&bstrDescriptionOfError);
							pErrorInfoRec->GetSource (&bstrSourceOfError);
							if (bstrDescriptionOfError!=NULL )
							{
								TRACE(_T("%ws\n"), bstrDescriptionOfError);
							}
							if (bstrSourceOfError!=NULL )
							{
								TRACE(_T("%ws\n"), bstrSourceOfError);
							}
							SysFreeString (bstrDescriptionOfError);
							SysFreeString (bstrSourceOfError);
							pErrorInfoRec->Release();
						}
					}
		
					pErrorInfo->Release();
					pErrorRecords->Release();
				}
			}
		} 
	pSupportErrorInfo->Release();
	} 
	return hr;
} //PrintErrorInfo


