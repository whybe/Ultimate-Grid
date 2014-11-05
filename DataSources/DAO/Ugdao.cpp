/***************************************************
Ultimate Grid version 7.2
Copyright © The Ultimate Toolbox 2007, All Rights Reserved

  DAO Data Source Class

  Standard Return Values: UG_SUCCESS - success (0)
						  UG_NA		 - not available (-1)
						  1 and up   - error codes
						  3000 and up - DAO error codes - see DBDAOERR.H
****************************************************/

#include "stdafx.h"
#include "WINNLS.H"
#include "UGCtrl.h"
#include "UGStrOp.h"

#pragma warning (push)
#pragma warning (disable : 4995)
#include "UGDAO.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***************************************************
****************************************************/
CUGDAODataSource::CUGDAODataSource(){
	m_Db				= NULL; 
	m_Record			= NULL;
	m_TableDef			= NULL;
	m_QueryDef			= NULL;
	m_FieldInfo			= NULL;
	m_pPassword			= NULL;
	m_bRecordSetAttached = FALSE;
	m_nCurrentRow		= 0;
	m_GhostRow			= NULL;
	m_nGhostRow			= -1;
	m_bGhostRowMode		= FALSE;
	m_bEditAllowed		= FALSE;
	m_EditRow			= NULL;
	m_nEditRow			= -1;
	m_bEditRowUpdatePending	= FALSE;		
	m_bEditOnGhostRow	= FALSE;
	m_nFailedField		= -1;
	m_bNumberSideHdg	= FALSE;
	m_nSH_NumBase		= 0;
	m_strSQL.Empty();
	m_strDB.Empty();
}
/***************************************************
****************************************************/
CUGDAODataSource::~CUGDAODataSource(){
	// could ask user to commit or abort trans here?
	Close();
}
/***************************************************
****************************************************/
BOOL CUGDAODataSource::IsOpen() {
	if(m_Record != NULL)
		return m_Record->IsOpen();
	return FALSE;
}
/***************************************************
****************************************************/
int CUGDAODataSource::Open(LPCTSTR database,LPCTSTR table){
	return Open(database,table,dbOpenDynaset,NULL,0);
}
/***************************************************
****************************************************/
int CUGDAODataSource::OpenSQL(LPCTSTR database,LPCTSTR sql){
	return Open(database,NULL,dbOpenDynaset,sql,0);
}
/***************************************************
****************************************************/
int CUGDAODataSource::Open(LPCTSTR database,LPCTSTR table,int openType,LPCTSTR sql,int options){

	Close();

	if(m_pPassword != NULL)
		wsprintf(m_buf,_T("PWD=%s"),m_pPassword);
	else
		m_buf[0] = 0;

	m_Db = new CDaoDatabase(NULL);

	try{
		m_Db->Open(database,FALSE,FALSE,m_buf);
	}
	// note that the Dao object member functions
	// can throw CMemoryType exceptions - I guess
	// AfxAbort is the only hope...
		catch(CMemoryException* e){
			#ifdef UG_DAO_REPORTERROR
				e->ReportError();
			#endif
		e->Delete();
		AfxAbort();
	}
	catch(CDaoException* e){
		// standard procedure for DAO - save the 
		// DBDAOERR code for the return value - 
		// Report on the error - optional -
		// use Delete to delete the exception object
		int er = e->m_pErrorInfo->m_lErrorCode;
		TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		return er;
	}

	if(table == NULL && sql == NULL)
		return UG_ERROR;

	if(sql == NULL){

		m_TableDef = new CDaoTableDef(m_Db);

		try{
			m_TableDef->Open(table);
		}
		catch(CMemoryException* e){
			#ifdef UG_DAO_REPORTERROR
				e->ReportError();
			#endif
			e->Delete();
			AfxAbort();
		}
		catch(CDaoException* e){
			int er = e->m_pErrorInfo->m_lErrorCode;
			#ifdef UG_DAO_REPORTERROR
				e->ReportError();
			#endif
			e->Delete();
			return er;
		}
		

		m_Record = new CDaoRecordset(m_Db);

		try{
			m_Record->Open(m_TableDef,openType,options);
		}
		catch(CMemoryException* e){
			#ifdef UG_DAO_REPORTERROR
				e->ReportError();
			#endif
			e->Delete();
			AfxAbort();
		}
		catch(CDaoException* e){
			int er = e->m_pErrorInfo->m_lErrorCode;
			TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
			#ifdef UG_DAO_REPORTERROR
				e->ReportError();
			#endif
			e->Delete();
			return er;
		}

	}
	else{

		m_QueryDef = new CDaoQueryDef(m_Db);

		try{
			m_QueryDef->Create(NULL,sql);
		}
		catch(CMemoryException* e){
			#ifdef UG_DAO_REPORTERROR
				e->ReportError();
			#endif
			e->Delete();
			AfxAbort();
		}
		catch(CDaoException* e){
			int er = e->m_pErrorInfo->m_lErrorCode;
			TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
			#ifdef UG_DAO_REPORTERROR
				e->ReportError();
			#endif
			e->Delete();
			return er;
		}

		m_Record = new CDaoRecordset(m_Db);
		
		

		try{
			m_Record->Open(m_QueryDef,openType,options);
		}

		catch(CMemoryException* e){
			#ifdef UG_DAO_REPORTERROR
				e->ReportError();
			#endif
			e->Delete();
			AfxAbort();
		}
		catch(CDaoException* e){
			int er = e->m_pErrorInfo->m_lErrorCode;
			TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
			#ifdef UG_DAO_REPORTERROR
				e->ReportError();
			#endif
			e->Delete();
			return er;
		}

	}
	//get the field information
	GatherFieldInfo();
 	
	// if we're using the ghost row for interactive appends,
	// we can set it up here...
	if(m_bGhostRowMode) {
		AllocateGhostRow();		// create new cells
		PopulateGhostRow();		// get defaults from table etc.
	}

	// ok - now we can allocate the edit row...
	// Note to self: do this on requery as well...
	AllocateEditRow();


	try{
		m_Record->MoveFirst();
	}
	catch(CMemoryException* e){
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		AfxAbort();
	}
	catch(CDaoException* e){
		int er = e->m_pErrorInfo->m_lErrorCode;
		TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
		e->Delete();
	}					// (no records)...

	// success - save SQL and DB
	m_strDB  = database;
	m_strSQL = sql;

	m_nCurrentRow = 0;

	// grab the fields and make sure that they are set up to
	// perform validation when SetFieldValue called... 
	COleVariant covNumber((long)0);
	short bVal = 1;
	
	DAOFields	*pFields = NULL;
	DAOField	*pField  = NULL;

	// get the fields collection
	DAO_CHECK(m_Record->m_pDAORecordset->get_Fields((DAOFields**)&pFields));


	// loop through fields setting validate on set
	int cols = GetNumCols();
	for (int i = 0; i < cols; i++) {
		covNumber = (long) i;
		DAO_CHECK(pFields->get_Item(covNumber, (DAOField**)&pField));

		DAO_CHECK(pField->put_ValidateOnSet(bVal));
        DAO_CHECK(pField->Release());

	}
    DAO_CHECK(pFields->Release());

	return UG_SUCCESS;
}
/***************************************************
****************************************************/
void CUGDAODataSource::GatherFieldInfo(){

	if(m_Record == NULL)
		return;

	int loop;
	int cols = m_Record->GetFieldCount();

	if(m_FieldInfo != NULL)
		delete[] m_FieldInfo;
	
	m_FieldInfo = new CDaoFieldInfo[cols];
	CDaoFieldInfo di;

	for(loop=0;loop<cols;loop++)
    {
        try {
            if(m_QueryDef != NULL)
		        m_QueryDef->GetFieldInfo(loop,m_FieldInfo[loop],AFX_DAO_ALL_INFO );
            //di = m_FieldInfo[loop];
            else
		        m_TableDef->GetFieldInfo(loop,m_FieldInfo[loop],AFX_DAO_ALL_INFO );

        }
	    catch(CMemoryException* e){
		    #ifdef UG_DAO_REPORTERROR
			    e->ReportError();
		    #endif
		    e->Delete();
		    AfxAbort();
	    }
	    catch(CDaoException* e){
		    int er = e->m_pErrorInfo->m_lErrorCode;
		    TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				    er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
		    #ifdef UG_DAO_REPORTERROR
			    e->ReportError();
		    #endif
		    e->Delete();
	    }
    
    }

    // Added code to get default value - querydef has none?
	COleVariant covNumber((long)0);
	COleVariant var;
	short bVal = 1;

	DAOFields	*pFields = NULL;
	DAOField	*pField  = NULL;

	// get the fields collection
	DAO_CHECK(m_Record->m_pDAORecordset->get_Fields((DAOFields**)&pFields));


	// loop through fields setting validate on set
	for (int i = 0; i < cols; i++) {
		covNumber = (long) i;
		DAO_CHECK(pFields->get_Item(covNumber, (DAOField**)&pField));

        // default value - version 3.5 and up...
		DAO_CHECK(pField->get_DefaultValue(&var));
		var.vt = VT_BSTR;
		m_FieldInfo[i].m_strDefaultValue = V_BSTRT(&var);
		var.Clear();

        DAO_CHECK(pField->Release());
    }
	
}

/***************************************************
****************************************************/
int CUGDAODataSource::Close(){

	ClearGhostRow();	
	ClearEditRow();		 

	if(m_FieldInfo != NULL){
		delete[] m_FieldInfo;
		m_FieldInfo = NULL;
	}
	if(m_Record != NULL){
		if(m_bRecordSetAttached == FALSE){
			m_Record->Close();
			delete m_Record;
			m_Record = NULL;
		}
		m_bRecordSetAttached = FALSE;
	}
	if(m_TableDef != NULL){
		m_TableDef->Close();
		delete m_TableDef;
		m_TableDef = NULL;
	}
	if(m_QueryDef != NULL){
		m_QueryDef->Close();
		delete m_QueryDef;
		m_QueryDef = NULL;
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
	SetOption

    Options:
		UGDAO_OPT_ALLOWEDITS	param1 BOOL
		UGDAO_OPT_GHOSTROWMODE, param1 BOOL
		UGDAO_OPT_NUMBERSIDEHDG param1 BOOL
								param2 base (start from 0 or 1)
		(note that ghostrow makes no sense if
		 editing disabled)
****************************************************/
int CUGDAODataSource::SetOption(int option,long param1,long param2){
	switch (option) {
	case UGDAO_OPT_GHOSTROWMODE: //  TRUE or FALSE
		if (param1)		
			m_bGhostRowMode = TRUE;
		else
			m_bGhostRowMode = FALSE;
		break;

	case UGDAO_OPT_ALLOWEDITS:
		if (param1)		
			m_bEditAllowed = TRUE;
		else
			m_bEditAllowed = FALSE;
		break;

	case UGDAO_OPT_NUMBERSIDEHDG:
		if (param1)	{	
			m_bNumberSideHdg = TRUE;
			m_nSH_NumBase = param2;
		}
		else
			m_bNumberSideHdg = FALSE;
		break;

	default:
		break;
	}
 	return UG_SUCCESS;
}
/***************************************************
****************************************************/
int CUGDAODataSource::GetOption(int option,long param1,long param2){
	switch (option) {
	case UGDAO_OPT_GHOSTROWMODE:
		return (int) m_bGhostRowMode;
		break;
	case UGDAO_OPT_ALLOWEDITS:
		return (int) m_bEditAllowed;
		break;
	case UGDAO_OPT_NUMBERSIDEHDG:
		return (int) m_bNumberSideHdg;
		break;
	default:
		break;
	}
	return UG_SUCCESS;
}

/***************************************************
  This is the point at which we update the buffered edit...
****************************************************/
int CUGDAODataSource::OnCanMove(int oldcol,long oldrow,int newcol,long newrow){

	if(m_bEditRowUpdatePending) {	// we're editing...
		if(oldrow != newrow) {		// and the user wants to  move off the row...
			if(UpdateFromEditRow()==UG_SUCCESS) {
				m_nEditRow = -1;		// good update - 
				m_ctrl->RedrawAll();
			}
			else {						// bad update...
				// since we do field level checking in OnEditFinish,
				// this code is unlikely to execute...
				m_ctrl->m_CUGGrid->SetFocus();
				m_ctrl->GotoCell(m_nFailedField,oldrow);
				m_ctrl->RedrawRow(oldrow);
				m_ctrl->StartEdit();
				return FALSE;
			}
		}
	}
	return TRUE;
}

/***************************************************
****************************************************/
BOOL CUGDAODataSource::CanEditCell(int col, long row){

	if(m_Record == NULL)
		return FALSE;

	// 1st, is the record updateable...
	if(!m_Record->CanUpdate()){
		#ifdef UG_DAO_REPORTERROR
	//	AfxMessageBox(_T("You cannot edit this cell - the recordset is not updatable."));
	//	m_ctrl->m_CUGGrid->SetFocus();
		#endif
		return FALSE;
	}

	// now - is it an updatable field...
	if((m_FieldInfo[col].m_lAttributes & dbUpdatableField) ==0) {
		#ifdef UG_DAO_REPORTERROR
	//	AfxMessageBox(_T("You cannot edit this cell - the field is not updatable."));
	//	m_ctrl->m_CUGGrid->SetFocus();
		#endif
		return FALSE;
	}

	// finally, it might be an autonumber (counter)
    if((m_FieldInfo[col].m_lAttributes&dbAutoIncrField) !=0) {
		#ifdef UG_DAO_REPORTERROR
	//	AfxMessageBox(_T("You cannot edit this cell - the field is autonumber."));
	//	m_ctrl->m_CUGGrid->SetFocus();
		#endif
		return FALSE;
	}

	// also, could be deleted by another user...
	CUGCell cell;
	int err = GetCell(col,row,&cell);
	if (err != UG_SUCCESS) {
		if (err == 3167){
			#ifdef UG_DAO_REPORTERROR
	//		AfxMessageBox(_T("You cannot edit this record - it has been deleted."));
	//		m_ctrl->m_CUGGrid->SetFocus();
			#endif
		}
	return FALSE;
	}

	// and check that we can actually do a meaningful edit...
	int type = m_FieldInfo[col].m_nType;
	if (type == dbGUID || type == dbLongBinary) {
		#ifdef UG_DAO_REPORTERROR
	//	AfxMessageBox(_T("You cannot edit this cell - the field is an OLE type."));
	//	m_ctrl->m_CUGGrid->SetFocus();
		#endif
		return FALSE;
	}



	return TRUE;
}

/****************************************************
****************************************************/
int CUGDAODataSource::StartTransaction(){
	
	if(m_Record == NULL)
		return UG_NA;

	try {
		// does  recordset support transactions?
		if (!m_Record->CanTransact()) {
			AfxMessageBox(_T("Transactions not supported on this recordset"));
			return UG_NA;
		}
		m_Db->m_pWorkspace->BeginTrans();
	}

	catch(CMemoryException* e){
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		AfxAbort();
	}
	catch(CDaoException* e){
		int er = e->m_pErrorInfo->m_lErrorCode;
		TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		return er;
	}

	
	return UG_SUCCESS;
}
/****************************************************
****************************************************/
int CUGDAODataSource::CancelTransaction(){

	if(m_Record == NULL)
		return UG_NA;

	if(m_bEditRowUpdatePending)
		CancelEdit();

	try {
		// does  recordset support transactions?
		if (!m_Record->CanTransact())
			return UG_NA;

		m_Db->m_pWorkspace->Rollback();
	}

	catch(CMemoryException* e){
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		AfxAbort();
	}
	catch(CDaoException* e){
		int er = e->m_pErrorInfo->m_lErrorCode;
		TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		return er;
	}

	// ok - all bets are off for the ghostrow etc if deleted
	// or added rows were rolled back...
	m_nGhostRow = -1;
	m_ctrl->OnDataSourceNotify(UGDS_ID_DAO,UGDSM_DAO_ADJUSTROWS,GetNumRows());

	return UG_SUCCESS;
}
/****************************************************
****************************************************/
int CUGDAODataSource::FinishTransaction(){

	
	if(m_Record == NULL)
		return UG_NA;

	if(m_bEditRowUpdatePending)
		if(UpdateFromEditRow() != UG_SUCCESS)
			return UG_ERROR;
	
	try {
		// does  recordset support transactions?
		if (!m_Record->CanTransact())
			return UG_NA;

		m_Db->m_pWorkspace->CommitTrans();
	}

	catch(CMemoryException* e){
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		AfxAbort();
	}
	catch(CDaoException* e){
		int er = e->m_pErrorInfo->m_lErrorCode;
		TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		return er;
	}

	return UG_SUCCESS;
}


/***************************************************
****************************************************/
int	CUGDAODataSource::GetCell(int col,long row,CUGCell *cell){


	int er = 0;

	if(m_Record == NULL)
		return UG_NA;

	if(col <0){
		if(row < 0)
			return UG_SUCCESS;  // disregard corner button

		if(m_ctrl->GetCurrentRow() == row){
			if (m_nEditRow != -1)
				cell->SetText(_T(" ! "));
			else
				cell->SetCellType(UGCT_ARROW);
		}
		else {
			if(row == m_nGhostRow) {
				cell->SetText(_T(" * "));
			}
			else{
				if(m_bNumberSideHdg) {
					UGStr::stprintf(m_buf, sizeof(m_buf),_T("%ld"), row+m_nSH_NumBase);
					cell->SetAlignment(UG_ALIGNRIGHT);
					cell->SetText(m_buf);
				}
			}			
		}
		
		return UG_SUCCESS;
	}
	if(row < 0){
		CString string;
		GetColName(col,&string);
		cell->SetText(string);
		return UG_SUCCESS;
	}

	// if this is the edit row, get info from edit row cells
	if(row == m_nEditRow){
		return cell->CopyInfoFrom(m_EditRow[col]);
	}

	// if this is the ghost row, get info from ghost row cells
	if(row == m_nGhostRow){
		return cell->CopyInfoFrom(m_GhostRow[col]);
	}

	// goto the right record...
	er = GotoRecord(row);
	if (er!=UG_SUCCESS)
		return er;

    
   
    //get the field
	try{
		m_coVariant = m_Record->GetFieldValue(col);
	}
	catch(CMemoryException* e){
	#ifdef UG_DAO_REPORTERROR
		e->ReportError();
	#endif
		e->Delete();
		AfxAbort();
	}
	catch(CDaoException* e){
		int er = e->m_pErrorInfo->m_lErrorCode;
		TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
		if (er == 3167)	{	// record deleted by another app...
			cell->SetText(_T("#Deleted"));
			e->Delete();
			return er;
		}
		if (er == 3021) {	// probably past end of file - don't report
			e->Delete();
			return er;
		}
		#ifdef UG_DAO_REPORTERROR
			TCHAR buf[20];
			wsprintf(buf,_T("Error %d"),er);
			AfxMessageBox(buf);
			e->ReportError();
		#endif
		e->Delete();
		return er;
	}


	//retrieve the data from the variant
	switch(m_coVariant.vt){		
        case VT_BYREF|VT_UI1:
			cell->SetText(_T(""));
            break;
        case VT_ARRAY|VT_UI1:
            cell->SetText(_T("LongBinary"));
            break;
        case VT_DISPATCH:
			cell->SetText(_T(""));
            break;
        case VT_UNKNOWN:
			cell->SetText(_T(""));
            break;
        case VT_VARIANT:
			cell->SetText(_T(""));
            break;
		case VT_EMPTY:
			cell->SetText(_T(""));
            break;
		case VT_BSTR:			
			cell->SetText((TCHAR *)m_coVariant.bstrVal);
            break;
		case VT_UI1:
			cell->SetBool( m_coVariant.bVal );
            break;
		case VT_I2:
			cell->SetNumber( m_coVariant.iVal );
            break;
		case VT_I4:
			cell->SetNumber( m_coVariant.lVal);
            break;
		case VT_R4:
			cell->SetNumber( m_coVariant.fltVal);
            break;
		case VT_R8:
			cell->SetNumber( m_coVariant.dblVal);
            break;
		case VT_BOOL:
			if(m_coVariant.iVal)
				cell->SetBool(TRUE);
			else
				cell->SetBool(FALSE);
            break;
		case VT_CY:{
            m_coCurrency = m_coVariant;
			cell->SetText(m_coCurrency.Format(LOCALE_NOUSEROVERRIDE,LANG_USER_DEFAULT));
			cell->SetDataType( UGCELLDATA_CURRENCY );
            break;
				   }
		case VT_DATE:{
            m_coDateTime = m_coVariant;
    		cell->SetText(m_coDateTime.Format());
			cell->SetDataType( UGCELLDATA_TIME );
            break;
					 }
 		case VT_NULL:
			cell->SetText(_T(""));
            break;
        case VT_ERROR:
            cell->SetText(_T(""));
            break;
		default:
			cell->SetText(_T("*unknown*"));
	}

//        SAFEARRAY           FAR* parray;    // VT_ARRAY|*.
//        unsigned char       FAR* pbVal;     // VT_BYREF|VT_UI1.
//        short               FAR* piVal;     // VT_BYREF|VT_I2.
//        long                FAR* plVal;     // VT_BYREF|VT_I4.
//        float               FAR* pfltVal;   // VT_BYREF|VT_R4.
//        double              FAR* pdblVal;   // VT_BYREF|VT_R8.
//        VARIANT_BOOL        FAR* pboolVal;  // VT_BYREF|VT_BOOL.
//        SCODE               FAR* pscode;    // VT_BYREF|VT_ERROR.
//        CY                  FAR* pcyVal;    // VT_BYREF|VT_CY.
//        DATE                FAR* pdate;     // VT_BYREF|VT_DATE.
//        BSTR                FAR* pbstrVal;  // VT_BYREF|VT_BSTR.
//        IUnknown FAR*       FAR* ppunkVal;  // VT_BYREF|VT_UNKNOWN.
//        IDispatch FAR*      FAR* ppdispVal; // VT_BYREF|VT_DISPATCH.
//        SAFEARRAY FAR*      FAR* pparray;   // VT_ARRAY|*.
//        VARIANT             FAR* pvarVal;   // VT_BYREF|VT_VARIANT.

	return UG_SUCCESS;
}
/***************************************************
****************************************************/
int	CUGDAODataSource::SetCell(int col,long row,CUGCell *cell){

	int append = FALSE;
	int er;
	
	if(m_Record == NULL)
		return UG_NA;
	
	if(col < 0 || row < 0)
		return UG_ERROR;

	if(CanEditCell(col,row)==0)
		return UG_ERROR;

	// if this is the edit row, just transfer - OnRowChange will do
	// the update...
	if (row == m_nEditRow) {
		CString cs;			// don't want to copy all info...
		cell->GetText(&cs);
		m_EditRow[col]->SetText((LPCTSTR)cs);
		return UG_SUCCESS;
	}

	// at this point, we're in the data directly - only buffering
	// user edits...

	//goto the correct row
	GotoRecord(row);

	if(m_Record->IsEOF())
		append = TRUE;


	try{
	  	if(append == FALSE)
			m_Record->Edit();
		else {
			m_Record->AddNew();	
		}

	}
	catch(CMemoryException* e){
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		AfxAbort();
	}
	catch(CDaoException* e){
		er = e->m_pErrorInfo->m_lErrorCode;
		TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		return er;
	}

	// do the translations etc.
	er = SetFieldValueFromCell(col,cell);
	if (er != UG_SUCCESS)
		return er;
	
	return UpdateCurrentRecord();	
}
/***************************************************
CUGDAODataSource::GetNumRows
// The code below implements GetNumRows for use with SetGridUsingDatasource()
// of CUGCtrl. It returns either 0 or 1 and relies on the OnHitBottom mechanism
// to tell the grid there are more records to be had.  Use of this
// method assumes the following code in the OnHitBottom method of your 
// CUGCtrl derived class:
//	
//	if(rowsfound >0){
//		SetNumberRows(numrows+rowsfound,FALSE);
//	
// DO NOT rely on this method to tell you the complete
// count of records.  Use GetNumRowsComplete (which can
// be slow).  
****************************************************/
long CUGDAODataSource::GetNumRows(){
	

	if(m_Record == NULL)
		return UG_NA;

	TRY{
		m_Record->MoveFirst();
	}
	CATCH_ALL(e){
		int er;
		if(e->IsKindOf(RUNTIME_CLASS(CDaoException))) {
			er = ((CDaoException*)e)->m_pErrorInfo->m_lErrorCode;
			TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"),((CDaoException*) e)->m_pErrorInfo->m_strDescription);
		}

		#ifdef UG_DAO_REPORTERROR
			if(3021 != er)		// lets not bother the user with this - empty file
				e->ReportError();
		#endif
			// we're assuming there are no records in the file...
			if(m_bGhostRowMode){
				m_nGhostRow = 0;
				return 1;
			}
			return 0;
	}
	END_CATCH_ALL



	return 1;		// assume virtual loading through the OnHitBottom
					// mechanism 

	
}
/***************************************************
	GetNumRowsComplete() 

    This is not in the base class.  Use this if
	you must know the record count - it may be
	slow in certain situations.  Internally, only the 
	FindNext() method uses GetNumRowsComplete().
	
    Returns count of records or -1 (UG_NA) if an error 
	occurred... candidate for a GetLastError type call...
****************************************************/
long CUGDAODataSource::GetNumRowsComplete() {

	long nRecs;
    if(TRUE == m_bGhostRowMode)
        nRecs = 1;
    else
        nRecs = 0;

	int  er = 0;

	if(NULL == m_Record)
		return UG_NA;
	
	// don't do this if edit buffer active...
	if(m_bEditRowUpdatePending)
		return UG_NA;

	// is this a table?
	if(m_TableDef) {
		try {
			nRecs = m_Record->GetRecordCount();
		}
		catch(CMemoryException* e){
			#ifdef UG_DAO_REPORTERROR
				e->ReportError();
			#endif
			e->Delete();
			AfxAbort();
		}
		catch(CDaoException* e){
			int er = e->m_pErrorInfo->m_lErrorCode;
			TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
			#ifdef UG_DAO_REPORTERROR
				e->ReportError();
			#endif
			e->Delete();
		}
	}
	else {
		try {
			m_Record->MoveLast();
			// loc is 0 based
			nRecs = m_Record->GetAbsolutePosition()+1;

			// current row reset...
			if(0 != nRecs) {
				m_Record->MoveFirst();
				m_Record->Move(m_nCurrentRow);
			}
		}
		catch(CMemoryException* e){
			#ifdef UG_DAO_REPORTERROR
				e->ReportError();
			#endif
			e->Delete();
			AfxAbort();
		}
		catch(CDaoException* e){
			int er = e->m_pErrorInfo->m_lErrorCode;
			TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
//			#ifdef UG_DAO_REPORTERROR
//				e->ReportError();
//			#endif
			e->Delete();
		}
	}

	if(0 == er)
		return nRecs;
	else 
		return UG_NA;
}

/***************************************************
****************************************************/
int CUGDAODataSource::GetNumCols(){
	
	if(m_Record == NULL)
		return UG_NA;
	
	return m_Record->GetFieldCount();
}
/***************************************************
****************************************************/
int CUGDAODataSource::GetColName(int col,CString * string){
	if(m_Record == NULL)
		return UG_NA;
	
	if(col < 0 || col >= m_Record->GetFieldCount())
		return 1;

	*string = m_FieldInfo[col].m_strName;

	return UG_SUCCESS;
}
/***************************************************

	0-string 1-bool 2-short 3-long 4-float 
	5-double 6-currency 7-date 8-time
	8-memo 9- blob 10-ole  11-other
****************************************************/
int CUGDAODataSource::GetColType(int col,int *type){
	if(m_Record == NULL)
		return UG_NA;
	
	if(col < 0 || col >= m_Record->GetFieldCount())
		return 1;

	switch(m_FieldInfo[col].m_nType){
		case dbText:
			*type = 0;
			break;
		case dbBoolean:
			*type = 1;
			break;
		case dbInteger:
			*type = 2;
			break;
		case dbLong:
			*type = 3;
			break;
		case dbSingle:
			*type = 4;
			break;
		case dbDouble:
			*type = 5;
			break;
		case dbCurrency:
			*type = 6;
			break;
		case dbDate:
			*type = 7;
			break;
		case dbMemo:
			*type = 8;
			break;
		case dbLongBinary:
			*type = 9;
			break;
		case dbGUID:
			*type = 10;
			break;
		default:
			*type = 11;
			break;
	}		
	return UG_SUCCESS;
}
													
/***************************************************
****************************************************/
int CUGDAODataSource::OnHitBottom(long numrows,long rowspast,long *rowsfound){

	numrows --;

	long newrow = numrows +rowspast;

	*rowsfound = 0;

	// special action for ghostrow mode
	if (m_nGhostRow == 0) 
		return 1;

	if (m_nEditRow == 0)
		return 1; 

	if(m_bGhostRowMode){
		if (m_nGhostRow != -1) {
			if (newrow <= m_nGhostRow) {
				*rowsfound = rowspast;
				return UG_SUCCESS;
			}
		}
	}


	if( newrow == m_nCurrentRow){
		if(m_Record->IsEOF( ))
			return 1;
		*rowsfound = rowspast;
		return UG_SUCCESS;
	}


	while(m_nCurrentRow < newrow){
		if(m_Record->IsEOF( ))
			return 1;
		try{
			m_Record->MoveNext();
		}
		catch(CMemoryException* e){
			#ifdef UG_DAO_REPORTERROR
				e->ReportError();
			#endif
			e->Delete();
			AfxAbort();
		}
		catch(CDaoException* e){
			int er = e->m_pErrorInfo->m_lErrorCode;
			TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
			#ifdef UG_DAO_REPORTERROR
				e->ReportError();
			#endif
			e->Delete();
			return er;
		}
		
		m_nCurrentRow++;
	}

	if(m_Record->IsEOF( )) 
		if (m_bGhostRowMode) {
			if (m_nGhostRow == -1)
				m_nGhostRow = numrows+1;
		} else {
			numrows++;		// original code...
		}

	*rowsfound = m_nCurrentRow - numrows;
	if(*rowsfound <0)
		*rowsfound =0;

	return UG_SUCCESS;
}

/***************************************************
****************************************************/
int CUGDAODataSource::FindFirst(CString *string, int *col,long *row, long flags){

	// don't do this if edit buffer active...
	if(m_bEditRowUpdatePending)
		return UG_ERROR;

	// TODO: position grid and record at first cell
	// or first cell in column if flags & UG_FIND_ALLCOLUMNS
	// User best to GotoRow(0) then make this call.
	return FindNext(string, col, row, flags);

}

/***************************************************
****************************************************/
int CUGDAODataSource::FindNext(CString *string, int *col, long *row, int flags){

	if(NULL == m_Record)
		return UG_NA;
	
	// don't do this if edit buffer active...
	if(m_bEditRowUpdatePending)
		return 1;

	int type = m_FieldInfo[*col].m_nType;

	int  retval = UG_SUCCESS;


	long nStartRow = m_ctrl->GetCurrentRow();
	long nSearchRow = nStartRow;

	int  nMaxCol = GetNumCols()-1;

	int  nStartColumn = *col;	
	int  nSearchColumn = *col;		
	CUGCell cell;
	CString strCell;

	BOOL bCheckForWrap = FALSE;		// as soon as we're past the raw start +2 we 
									// can start checking for wrap.  This would 
									// be easier with a counter (X recs processed)
									// checked against a record count.
	
	long nSearchCount = 0;			// Help! I've wrapped and I can't find the text!
									// Must be > 1 to enter wrap detection code

	long nRecs = GetNumRowsComplete();
	
	if(-1 == nRecs)		// error getting number of records
		return UG_NA;

	CWaitCursor	cw;					// a nice touch...


	while(1) {


		// positioning... a bit complex, but all in one place.
		if(UG_FIND_ALLCOLUMNS&flags) {
			if(UG_FIND_UP&flags) {
				nSearchColumn--;
				if(nSearchColumn < 0) {
					nSearchColumn = nMaxCol;
					nSearchRow--;
					if(nSearchRow < 0) {
						nSearchRow = nRecs-1;
					}
					// wrap code - have we looped longer than nRecs?
					if(nSearchCount > nRecs+1) {
						retval = UG_NA;
						break;
					}
					else {
						nSearchCount++;
					}
				}
			}
			else {  // finding downward...
				nSearchColumn++;
				if(nSearchColumn > nMaxCol) {
					nSearchColumn = 0;
					nSearchRow++;
					if(nSearchRow > nRecs-1) {
						nSearchRow = 0;
					}
					// wrap code - have we looped longer than nRecs?
					if(nSearchCount > nRecs+1) {
						retval = UG_NA;
						break;
					}
					else {
						nSearchCount++;
					}
				}
			}
		}
		else {
		
			if(UG_FIND_UP&flags) {
				nSearchRow--;
				if(nSearchRow < 0) {
					nSearchRow = nRecs-1;
				}

				// wrap code - have we looped longer than nRecs?
				if(nSearchCount > nRecs+1) {
					retval = UG_NA;
					break;
				}
				else {
					nSearchCount++;
				}
			}
			else {
				nSearchRow++;
				if(nSearchRow > nRecs-1) {
					nSearchRow = 0;
				}

				// wrap code - have we looped longer than nRecs?
				if(nSearchCount > nRecs+1) {
					retval = UG_NA;
					break;
				}
				else {
					nSearchCount++;
				}
			}

		}

		

		
		if(GetCell(nSearchColumn, nSearchRow, &cell) != UG_SUCCESS) { 
			TRACE(_T("Unexpected return code from GetCell in FindNext"));
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
flags - UG_SORT_ASSENDING or UG_SORT_DESCENDING
****************************************************/
int CUGDAODataSource::SortBy(int col,int flags){
	return SortBy(&col,1,flags);
}

/***************************************************
****************************************************/
int CUGDAODataSource::SortBy(int *cols,int num,int flags)
{
	if(m_bEditRowUpdatePending) {
		return UG_ERROR;	// don't sort if edit in progress...
	}

	int loop;

	// can't use dates, blobs, memos in ORDER BY...
	for (loop = 0; loop < num; loop++) {
		int type = m_FieldInfo[cols[loop]].m_nType;
		switch (type) {
		case dbMemo:
		#ifdef UG_DAO_REPORTERROR
			AfxMessageBox(_T("Sort not supported for memo type."));
		#endif
			return 3117;
			break;
		case dbLongBinary:
		case dbGUID:
		#ifdef UG_DAO_REPORTERROR
			AfxMessageBox(_T("Sort not supported for OLE objects."));
		#endif
			return 3117;
			break;
		default:
			break;
		}
	} 

	short	nSetType;
    CString strOrderBy = " ORDER BY ";
    CString strColName;
	CString	strSQL;
    
    try
    {
        nSetType = m_Record->GetType();
    
		for(loop = 0;loop < num;loop++) {

			GetColName(cols[loop],&strColName);
			strOrderBy += "[" + strColName + "]";
			if (flags == UG_SORT_DESCENDING)
			{
				if (num-1 != loop)
					strOrderBy += " DESC, ";
				else strOrderBy += " DESC";
			}
			else if (num-1 != loop) strOrderBy += " , ";
		}
    
		if(m_bRecordSetAttached) {
			m_Record->m_strSort = strOrderBy;												
			m_Record->Requery();

		}
		else {
			strSQL = m_strSQL;

			// remove previous ORDER BY...
			CString strTemp = strSQL;
			strTemp.MakeUpper();
			int loc = strTemp.Find(_T(" ORDER BY "));
			if (-1 != loc) {
				strSQL = strSQL.Left(loc);
			}

			strSQL += strOrderBy;

			
	
			int res = Open(m_strDB,NULL,nSetType,strSQL,0);

			m_ctrl->OnDataSourceNotify(UGDS_ID_DAO,UGDSM_DAO_ADJUSTROWS,GetNumRows());

		}

	
	}
    catch(CMemoryException* e){
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
        e->Delete();
        AfxAbort();
    }
    catch(CDaoException* e){
        int er = e->m_pErrorInfo->m_lErrorCode;
		TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__,"ugdao.cpp", e->m_pErrorInfo->m_strDescription);
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
        e->Delete();
        return er;
    }

	return UG_SUCCESS;
}
 

/***************************************************
****************************************************/
int CUGDAODataSource::Reset(){

	m_nCurrentRow = 0;

	if(m_Record != NULL){
		if(m_Record->IsEOF() && m_Record->IsBOF()){
			return UG_ERROR;
		}
		else{
			try{
				m_Record->MoveFirst();
                m_nCurrentRow = 0;
			}
			catch(CMemoryException* e){
				#ifdef UG_DAO_REPORTERROR
					e->ReportError();
				#endif
				e->Delete();
				AfxAbort();
			}
			catch(CDaoException* e){
				int er = e->m_pErrorInfo->m_lErrorCode;
				TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
					er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
				#ifdef UG_DAO_REPORTERROR
					e->ReportError();
				#endif
				e->Delete();
				return er;
			}
		}
	}

	return UG_SUCCESS;
}
/***************************************************
****************************************************/
int CUGDAODataSource::AttachRecordSet(CDaoRecordset* rset){

	Close();
	
	m_Record = rset;

	m_bRecordSetAttached = TRUE;

	GatherFieldInfo();

	Reset();

	return UG_SUCCESS;
}
/***************************************************
****************************************************/
CDaoRecordset* CUGDAODataSource::GetRecordSet(){
	return m_Record;
}
/***************************************************
****************************************************/
CDaoDatabase* CUGDAODataSource::GetDatabase(){
	return m_Db;
}
/***************************************************
****************************************************/
int CUGDAODataSource::AppendRow(){

	// don't append rows if edit buffer active...
	if(m_bEditRowUpdatePending)
		return 1;

	if(m_Record == NULL)
		return UG_NA;
	if(m_Record->CanAppend()==0)
		return UG_ERROR;
	try{
		m_Record->AddNew();
		m_Record->Update();
		m_Record->MoveFirst();
		m_Record->Move(m_nCurrentRow);

	}
	catch(CMemoryException* e){
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		AfxAbort();
	}
	catch(CDaoException* e){
		int er = e->m_pErrorInfo->m_lErrorCode;
		TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		return er;
	}
	if(m_bGhostRowMode)
		if(m_nGhostRow != -1)
			m_nGhostRow++;

	return UG_SUCCESS;
}
/***************************************************
****************************************************/
int CUGDAODataSource::AppendRow(CUGCell *cellList,int numCells){

	int er = UG_SUCCESS;

	// don't append rows if edit buffer active...
	// if(m_bEditRowUpdatePending)
	//	return 1;

	if(m_Record == NULL)
		return UG_NA;

	if(m_Record->CanAppend()==0)
		return UG_ERROR;
	try{
		m_Record->AddNew();
	}
	catch(CMemoryException* e){
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		AfxAbort();
	}
	catch(CDaoException* e){
		er = e->m_pErrorInfo->m_lErrorCode;
		TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		return er;
	}

	for(int loop = 0;loop <numCells;loop++){
		er = SetFieldValueFromCell(loop, &cellList[loop]);
		if(er != UG_SUCCESS)
			return er;
	}

	er = UpdateCurrentRecord();
	if (er != UG_SUCCESS)
		return er;
	
	if(m_bGhostRowMode)
		if(m_nGhostRow != -1)
			m_nGhostRow++;
	
	return UG_SUCCESS;
}
/***************************************************
****************************************************/
int CUGDAODataSource::DeleteRow(long row){

    if(m_bEditRowUpdatePending) 
    {
        if(m_bEditOnGhostRow) {
            // if were on the ghost, there's nothing to delete
            // - call CancelEdit to 'delete' the row...
            CancelEdit();
            return UG_NA;
        }
        // other wise
        CancelEdit();
    }
    else if(row == m_nGhostRow) {
        // nothing to do
        return UG_NA;
    }

	int er = 0;
    long oldPos = m_nCurrentRow;
///////
	if(m_Record == NULL)
		return UG_NA;

	if(m_Record->CanUpdate() == FALSE)
		return UG_ERROR;

	if(row < 0)
		return UG_ERROR;

	if(m_Record->IsEOF() && m_Record->IsBOF())
		return UG_ERROR;

	// ok - now, lets try to move to the correct row...
	// if m_nCurrentRow = m_nGhostRow we may have probs...
	if(m_nCurrentRow == m_nGhostRow){
		if (m_Record->IsEOF()) {
			m_Record->MovePrev();
		}
		m_nCurrentRow = m_Record->GetAbsolutePosition();
		m_ctrl->GotoRow(m_nCurrentRow);

	}
	// move to the row...
	er = GotoRecord(row);

	// OK -	if er, we couldn't move to the row...
	// lets assume m_nCurrent can stay where it is...
	if(er != UG_SUCCESS){
		m_nCurrentRow = oldPos;
		return er;			// EXIT point
	}

	try{
		m_Record->Delete();
	}
	catch(CMemoryException* e){
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		AfxAbort();
	}
	catch(CDaoException* e){
		er = e->m_pErrorInfo->m_lErrorCode;
		TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
//		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
//		#endif
		e->Delete();
	}


	if(er == UG_SUCCESS){		
		if (row > 0)
			m_Record->MovePrev();
		else
			m_Record->MoveNext();

		m_nCurrentRow = m_Record->GetAbsolutePosition();
		m_ctrl->GotoRow(m_nCurrentRow);

        if(m_bGhostRowMode)
			if(m_nGhostRow != -1)
				m_nGhostRow--;
	}
	CheckPosition();
	VerifyPosition();
	return er;
}
/***************************************************
	*Obsolete
****************************************************/
int CUGDAODataSource::SetPassword(LPSTR pass){
	
	m_pPassword = pass;
	return UG_SUCCESS;
}


/***************************************************
****************************************************/

void CUGDAODataSource::ClearGhostRow() {

	if(NULL == m_Record)
		return;

	if (!m_Record->IsOpen())
		return;

	int cols = GetNumCols();

	if(m_GhostRow != NULL) {
		for (int i = 0; i < cols; i++) {
			delete m_GhostRow[i];
			m_GhostRow[i] = NULL;
		}

		delete [] m_GhostRow;
	   	m_GhostRow = NULL;

	}
	m_nGhostRow = -1;	

	// we don't buffer writes to the heading cells, so -1
	// a safe bet..
	
}

/***************************************************
****************************************************/

void CUGDAODataSource::AllocateGhostRow() {

	// this is used for the access style extra row 

	int i;

	ClearGhostRow();

	// allocate cell for each column...
	int cols = GetNumCols();

	// make array of cell pointers
	m_GhostRow = new CUGCell*[cols];
	
	// fill with pointers to new cells
	for (i = 0; i < cols; i++) {
		m_GhostRow[i] = new CUGCell;
		if (m_GhostRow[i] == NULL)
			TRACE(_T("Allocation failed for col = i\n"));
	}
}

/***************************************************
****************************************************/
int CUGDAODataSource::PopulateGhostRow() {

	if(m_Record == NULL)
		return UG_NA;

	if(!m_Record->CanUpdate())
		return UG_ERROR;

	// store data in cells...
	int cols = GetNumCols();

	// what we need to do here is set up the fields with 
	// defaults 
	for (int col = 0; col < cols; col++){
		if(m_FieldInfo[col].m_lAttributes&dbAutoIncrField) {
			m_GhostRow[col]->SetText(_T("(AutoNumber)"));
		}else{
            //TRACE(" %s\n", m_FieldInfo[col].m_strDefaultValue);
			if(m_FieldInfo[col].m_strDefaultValue!="") {
				CString cs = m_FieldInfo[col].m_strDefaultValue;
				int len = _tcslen(m_FieldInfo[col].m_strDefaultValue);
				TCHAR * buf = cs.GetBuffer(1);
				*(buf+(_tcslen(buf)-1)) = '\0';	// eliminate quote
				m_GhostRow[col]->SetText((buf+1));
			}else{
			//	if((m_FieldInfo[col].m_bRequired) || (!m_FieldInfo[col].m_bAllowZeroLength)){
			//		m_GhostRow[col]->SetText(_T(" "));
			//	}
			}
		}
	}


	return UG_SUCCESS;

}

// Edit notifications...
/***************************************************
****************************************************/
int CUGDAODataSource::OnEditStart(int col, long row,CWnd **edit){

	if(!m_bEditAllowed)
		return FALSE;

	// check if the record/field can be updated/edited...
	if(CanEditCell(m_ctrl->GetColTranslation(col),row)==FALSE)
		return FALSE;			// this should stop the edit process...

	// m_bEditUpdatePending is crucial to the proper behavior of the 
	// grid - don't allow row insertions or deletions while 
	// an edit row is active.
	m_bEditRowUpdatePending = TRUE;

	if(m_nEditRow == -1) {		// we haven't set it up...
		if (m_nGhostRow == row) {	// we just replaced the ghost row..
			m_bEditOnGhostRow = TRUE;		// need to know this when we end...

			m_nCurrentRow = row;
		    ReadEditRow(row);
			m_nGhostRow++;
			m_ctrl->OnDataSourceNotify(UGDS_ID_DAO,UGDSM_DAO_ADJUSTROWS,m_nGhostRow+1);
			m_ctrl->RedrawRow(row);
			m_ctrl->RedrawRow(m_nGhostRow);
		//	if(UG_SUCCESS == AddDefaultRow()) {
		//		m_Record->MoveLast();
		//		m_nCurrentRow = row;
		//		m_nGhostRow++;
		//		ReadEditRow(row);
		//		m_ctrl->OnDataSourceNotify(UGDS_ID_DAO,UGDSM_DAO_ADJUSTROWS,m_nGhostRow+1);
		//		m_ctrl->RedrawRow(row);
		//		m_ctrl->RedrawRow(m_nGhostRow);
		//	}
        //    else {
        //        _asm int 3;
        //    }
            
		}
		else {
			ReadEditRow(row);
		}
	}


	return TRUE;
}

/***************************************************
  A temporary fix - try to add a row that will get 
  past non-zero length and required fields so that 
  we can supply the user with a complete row to 
  edit.
****************************************************/
int CUGDAODataSource::AddDefaultRow() {

	if(m_Record == NULL)
		return UG_NA;

	int retval;

	// make array of cell pointers
	int cols = GetNumCols();

	CUGCell cell; 

	
	m_Record->AddNew();
	
	for(int i = 0; i < cols; i++) {
		// ok folks, here's where we do our best to 
		// allow a blank row to be appended to the recordset.

		// 1. if it's autonumber, leave it alone.
		if((m_FieldInfo[i].m_lAttributes&dbAutoIncrField) != 0)
			continue;

		if((m_FieldInfo[i].m_lAttributes&dbUpdatableField) == 0)
			continue;

		// if it has a default value lets assume its a good one...
        if(!(m_FieldInfo[i].m_strDefaultValue.IsEmpty()) ) {
			continue;	
        }
        
        // now comes the hard part - if it is a required field
		// or can't be zero length...
		if((m_FieldInfo[i].m_bRequired) || (!m_FieldInfo[i].m_bAllowZeroLength)){
								
			COleVariant* cov;

			switch(m_FieldInfo[i].m_nType){
				case dbBoolean:
					cov = new COleVariant((BYTE)0);
					break;
				case dbByte:
					cov = new COleVariant((BYTE)0);
					break;
				case dbInteger:
					cov = new COleVariant((short)0);
					break;
				case dbLong:
					cov = new COleVariant((long)0);
					break;
				case dbCurrency:
					cov = new COleVariant((long)0);
					try{
						cov->ChangeType(VT_CY,NULL);
					}
					catch(CException *e){
						TCHAR buf[255];
						TCHAR buf2[80];
						CString cs;
						GetColName(i,&cs);
						UGStr::tcscpy(buf,255,_T("The field '"));
						UGStr::tcscat(buf,255,(LPCTSTR) cs);
						UGStr::tcscat(buf,255, _T("' failed conversion - "));
						e->GetErrorMessage((LPTSTR)buf2,80);
						UGStr::tcscat(buf, 255, buf2);
						AfxMessageBox(buf);

						e->Delete();
						retval =  UG_ERROR;
					}
					break;
				case dbSingle:
					cov = new COleVariant((float)0);
					break;
				case dbDouble:
					cov = new COleVariant((double)0);
					break;
				case dbDate:
					cov = new COleVariant(_T("1-1-1"));
					try{
						cov->ChangeType(VT_DATE,NULL);
					}
					catch(CException *e){
						TCHAR buf[255];
						TCHAR buf2[80];
						CString cs;
						GetColName(i,&cs);
						UGStr::tcscpy(buf,255,_T("The field '"));
						UGStr::tcscat(buf,255,(LPCTSTR) cs);
						UGStr::tcscat(buf,255,_T("' failed conversion - "));
						e->GetErrorMessage((LPTSTR)buf2,80);
						UGStr::tcscat(buf,255, buf2);
						AfxMessageBox(buf);
						e->Delete();
						retval =  UG_ERROR;
					}
					break;
				case dbText:
					cov = new COleVariant(_T("."),VT_BSTRT);
					break;
				case dbMemo:
					cov = new COleVariant(_T(" "),VT_BSTRT);
					break;
				case dbGUID:
					retval = UG_NA; // com ID
					break;
				case dbLongBinary:	// OLE Object
					retval = UG_NA;
					break;
			}		

			try{
				m_Record->SetFieldValue(i,cov);
			}
			catch(CMemoryException* e){
				#ifdef UG_DAO_REPORTERROR
					e->ReportError();
				#endif
				e->Delete();
				AfxAbort();
			}
			catch(CDaoException* e){
				// field failed validation...
				int er = e->m_pErrorInfo->m_lErrorCode;
				TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
					er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
				TCHAR buf[255];
				CString cs;
				GetColName(i,&cs);
				UGStr::tcscpy(buf,255,_T("The field '"));
				UGStr::tcscat(buf,255,(LPCTSTR) cs);
				UGStr::tcscat(buf,255, _T("' failed validation - "));
				UGStr::tcscat(buf,255, e->m_pErrorInfo->m_strDescription);
				AfxMessageBox(buf);
				//e->ReportError();
				e->Delete();
                Reset();
				delete cov;			// don't forget this...
				return er;			// no need to continue...
			}
			delete cov;		
		}
	}
		

	retval = UpdateCurrentRecord();

    if(UG_SUCCESS != retval )
        return retval;

	m_nCurrentRow = m_Record->GetAbsolutePosition();

	return UG_SUCCESS;
}

/***************************************************
****************************************************/
int CUGDAODataSource::OnEditVerify(int col,long row,CWnd *edit,UINT *vcKey){


	return TRUE;
}
/***************************************************
****************************************************/
int CUGDAODataSource::OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag){

	if(cancelFlag) {
		CUGEdit *ed = (CUGEdit*)edit;
		UINT lastKey = ed->GetLastKey();
//		if(lastKey == VK_ESCAPE)
//			;
		CancelEdit();
		return TRUE;
	}

	if(m_bEditOnGhostRow)
		return TRUE;		// as yet no cell by cell validation
							// on ghost row...
	
	// ok - lets do some field level validation if the text has changed...
	CUGCell cell;
	GetCell(col,row, &cell);
	CString str;
	cell.GetLabelText(&str);
	if( str == string )			// don't bother if unchanged...
		return TRUE;			// this is how access works...

	str = string;

	// goto the row...
    GotoRecord(m_nEditRow);

	try{
		  m_Record->Edit();
	}
	catch(CMemoryException* e){
		#ifdef UG_DAO_REPORTERROR
		e->ReportError();
		#endif

		e->Delete();
		AfxAbort();
	}
	catch(CDaoException* e){
		int er = e->m_pErrorInfo->m_lErrorCode;
		TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"),
			er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
			e->Delete();
		return FALSE;
	}

	int retval;
	cell.SetText(string);
    int coltrans = m_ctrl->GetColTranslation(col);
	if(UG_SUCCESS != SetFieldValueFromCell(coltrans,&cell)) {
		retval = FALSE;
	}
	else {
		retval = TRUE;
	}

	if(m_Record->GetEditMode() != dbEditNone)
		m_Record->CancelUpdate();

	return retval;

}
/***************************************************
****************************************************/
int CUGDAODataSource::OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow){

	if(oldrow != *newrow) {		// and the user wants to  move off the row...
		if(UpdateFromEditRow()==UG_SUCCESS) {
			m_nEditRow = -1;		// good update - 
			m_ctrl->RedrawAll();
		}
		else {						// bad update...
			// 
			m_ctrl->m_CUGGrid->SetFocus();
			*newcol = m_nFailedField;
			*newrow = oldrow;
			return TRUE;
		}
	}

	// if the col remains the same, assume editing ok.
	int temp = *newcol;  // work with temp

	// which direction are we going in?
	int dir = 0;

	if (oldcol == GetNumCols()-1 && *newcol == 0)
		dir = +1;
	else if (oldcol < *newcol) 
		dir = +1;
	else
		dir = -1;

	while(temp != oldcol && !CanEditCell(temp, *newrow) ) {
		temp += dir;
		if (temp > GetNumCols()-1)
			temp = 0;
		else if(temp < 0)
			temp = GetNumCols()-1;
	}

	*newcol = temp;

	return TRUE;
}

// functions related to the edit row...


/***************************************************
****************************************************/
void CUGDAODataSource::ClearEditRow() {

	if(NULL == m_Record)
		return;

	if (!m_Record->IsOpen())
		return;

	int cols = GetNumCols();

	if(m_EditRow != NULL) {
		for (int i = 0; i < cols; i++) {
			delete m_EditRow[i];
			m_EditRow[i] = NULL;
		}

		delete [] m_EditRow;
	   	m_EditRow = NULL;

	}
	m_nEditRow = -1;

	// we don't buffer writes to the heading cells, so -1
	// a safe bet..
	
}

/***************************************************
****************************************************/
void CUGDAODataSource::AllocateEditRow() {

	// ok - if you had a buffer you didn't write,
	// you lose it here...

	int i;

	ClearEditRow();

	// allocate and populate
	int cols = GetNumCols();

	// make array of cell pointers
	m_EditRow = new CUGCell*[cols];
	
	// fill with pointers to new cells
	for (i = 0; i < cols; i++) {
		m_EditRow[i] = new CUGCell;
		if (m_EditRow[i] == NULL)	// ze auld fasioned way...
			TRACE(_T("Allocation failed for col = i\n"));
	}
}


/***************************************************
****************************************************/
void CUGDAODataSource::ReadEditRow(long row) {
	// store data in cells
	int cols = GetNumCols();


	// this code grabs text from GetCell and then 
	// copies the text into the LabelText - this 
	// gives us the capability of having a 'double
	// buffer' for writes - if the two fields are 
	// equal, there's no need to set field value value
	// for edits.  Shouldn't do this for AddNew tho...
	for (int col = 0; col < cols; col++){
//		GetCell(m_ctrl->GetColTranslation(col),row,m_EditRow[col]);
	    GetCell(col,row,m_EditRow[col]);
		m_EditRow[col]->SetLabelText(m_EditRow[col]->GetText());
	}

	// now we can set the value for m_nEditRow
	m_nEditRow = row;

	m_ctrl->RedrawRow(row);
}

/***************************************************
****************************************************/
int	CUGDAODataSource::UpdateFromEditRow(){
    // we can assume that this is being called following 
    // some trigger, probably OnCanMove, that has checked
    // that there is a valid edit buffer, but just to be
    // finicky...
    ASSERT(m_EditRow);

	int er = UG_SUCCESS;
	int append = FALSE;
	
	if(m_Record == NULL)
		return UG_NA;

	if(m_Record->CanUpdate()==0)
		return UG_ERROR;

	// goto the row...
    if(m_bEditOnGhostRow == TRUE) 
    {
        append = TRUE;
    }
    else {
    	GotoRecord(m_nEditRow);
    	if(m_Record->IsEOF())
	    	append = TRUE;
    }

	try{
	  	if(append == FALSE)
			m_Record->Edit();
		else
			m_Record->AddNew();
	}
	catch(CMemoryException* e){
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif

		e->Delete();
		AfxAbort();
	}
	catch(CDaoException* e){
		int er = e->m_pErrorInfo->m_lErrorCode;
		TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		return er;
	}


    // loop though the cells in the buffer
    int cols = GetNumCols();
	
    for (int col = 0; col < cols; col++) {

		// this added for release builds - may be temporary fix... trying to avoid
		// writing a NULL to a newly created date field... (conversion will fail).
		if(NULL == m_EditRow[col]->GetText() && _T("") == m_EditRow[col]->GetLabelText())
			continue;

		// fails for newly added rows... make sure not NULLs
        if(m_EditRow[col]->GetText() != NULL) {
			if(_tcscmp(m_EditRow[col]->GetText(), m_EditRow[col]->GetLabelText())==0){
//				TRACE("Field %d skipped...", col);
				continue;	// no need to setfield value - we're not 'dirty'
			}
	
            int coltrans = m_ctrl->GetColTranslation(col);
            TRACE(_T("*** col = %d, coltrans = %d\n"), col, coltrans);
            er = SetFieldValueFromCell(col,m_EditRow[col]);
		    if (er != UG_SUCCESS) {
			    m_nFailedField = col;
			    return er;
		    }
        }
	}

//	TRACE("\n");
    // end for loop - record should now be set for the update...

	er = UpdateCurrentRecord();
	if (er != UG_SUCCESS)
		return er;

	// ok - a successful update.  Now, if this was an append, make the 
	// m_nCurrentRow this one... *** this is important ****
	if (append) {
		m_Record->MoveLast();
		m_nCurrentRow = m_nEditRow;
		m_ctrl->GotoRow(m_nEditRow);
	}

	long row = m_nEditRow;
	m_nEditRow = -1;
	m_bEditOnGhostRow = FALSE;

	m_ctrl->RedrawRow(row);
	
	// release the obligation - see also CancelEdit()
	m_bEditRowUpdatePending = FALSE;
	

	return UG_SUCCESS;
}

/***************************************************
****************************************************/
void CUGDAODataSource::CancelEdit() {
	long row = m_nEditRow;
	// if this was the ghost row when we started editing...
	if(m_bEditOnGhostRow) {
		// release the obligation...see also UpdateFromRowBuffer()
		m_bEditRowUpdatePending = FALSE;
		m_bEditOnGhostRow = FALSE;
		// DeleteRow will adjust ghostrow
//		DeleteRow(m_nEditRow);
		// reset m_nEditRow
		m_nEditRow = -1;
        m_nGhostRow--;
		// and tell the control that the number of rows has been adjusted...
		m_ctrl->OnDataSourceNotify(UGDS_ID_DAO,UGDSM_DAO_ADJUSTROWS,m_nGhostRow+1);
		m_ctrl->GotoRow(m_nGhostRow);
	}
	else {
		// simply reset the edit row number....
		row = m_nEditRow;
		m_nEditRow = -1;
		// ...and redraw the row to get what it was before we started.
		m_ctrl->RedrawRow(row);
		// and release the obligation...see also UpdateFromRowBuffer()
		m_bEditRowUpdatePending = FALSE;
	}
	m_ctrl->RedrawRow(row);		// necessary???
}

/***************************************************
****************************************************/
int CUGDAODataSource::GotoRecord(long row) {
	//goto the correct row
	try {
		if(row == 0){
			m_Record->MoveFirst();
			m_nCurrentRow = 0;
		}
		else if( row != m_nCurrentRow){
			m_Record->Move(row - m_nCurrentRow );
			m_nCurrentRow = row;
		}
	}
	catch(CMemoryException* e){
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		AfxAbort();
	}
	catch(CDaoException* e){
		int er = e->m_pErrorInfo->m_lErrorCode;
		TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
		#ifdef UG_DAO_REPORTERROR
			TCHAR buf[20];
			wsprintf(buf,_T("Error %d"),er);
   		    AfxMessageBox(buf);
		    e->ReportError();
		#endif
		e->Delete();
		return er;
	}

	return UG_SUCCESS;

}

/***************************************************
****************************************************/
int CUGDAODataSource::SetFieldValueFromCell(int col, CUGCell *cell){
	// given a cell: determine the type, get the value into an
	// ole variant, and set the field value.  Assume we are 
	// positioned on the correct record...
	int retval = UG_SUCCESS;

	COleVariant* cov;

	switch(m_FieldInfo[col].m_nType){
		case dbBoolean:
			cov = new COleVariant((BYTE)cell->GetBool());
			break;
		case dbByte:
			cov = new COleVariant((BYTE)cell->GetNumber());
			break;
		case dbInteger:
			cov = new COleVariant((short)cell->GetNumber());
			break;
		case dbLong:
			cov = new COleVariant((long)cell->GetNumber());
			break;
		case dbCurrency:
			cov = new COleVariant(cell->GetText());
			try{
				cov->ChangeType(VT_CY,NULL);
			}
			catch(CException *e){
				TCHAR buf[255];
				TCHAR buf2[80];
				CString cs;
				GetColName(col,&cs);
				UGStr::tcscpy(buf,255,_T("The field '"));
				UGStr::tcscat(buf,255,(LPCTSTR) cs);
				UGStr::tcscat(buf,255, _T("' failed conversion - "));
				e->GetErrorMessage((LPTSTR)buf2,80);
				UGStr::tcscat(buf,255, buf2);
				AfxMessageBox(buf);


				e->Delete();
				retval = UG_ERROR;
			}
			break;
		case dbSingle:
			cov = new COleVariant((float)cell->GetNumber());
			break;
		case dbDouble:
			cov = new COleVariant((double)cell->GetNumber());
			break;
		case dbDate:
			cov = new COleVariant(cell->GetText());
			try{
				cov->ChangeType(VT_DATE,NULL);
			}
			catch(CException *e){
				TCHAR buf[255];
				TCHAR buf2[80];
				CString cs;
				GetColName(col,&cs);
				UGStr::tcscpy(buf,255,_T("The field '"));
				UGStr::tcscat(buf,255,(LPCTSTR) cs);
				UGStr::tcscat(buf,255,_T("' failed conversion - "));
				e->GetErrorMessage((LPTSTR)buf2,80);
				UGStr::tcscat(buf,255, buf2);
				AfxMessageBox(buf);

       		TRACE(_T("CException caught at line %d in %s\n"), 
				__LINE__, _T("CUGDAODataSource"));

				e->Delete();
				retval = UG_ERROR;
			}
			break;
		case dbText:
			cov = new COleVariant(cell->GetText(),VT_BSTRT);
			break;
		case dbMemo:
			cov = new COleVariant(cell->GetText(),VT_BSTRT);
			break;
		case dbGUID:
			retval = UG_NA; // com ID
			break;
		case dbLongBinary:	// OLE Object
			retval = UG_NA;
			break;
	}

	if(retval != UG_SUCCESS) {
		if(UG_NA != retval)
			delete cov;
		return retval;			// if we didn't get this far...
	}

	// check that field is updatable and *not* an auto (counter)
    if(m_FieldInfo[col].m_lAttributes&dbUpdatableField  &&
		!((m_FieldInfo[col].m_lAttributes&dbAutoIncrField) !=0)) {

		try{
			m_Record->SetFieldValue(col,cov);
		}
		catch(CMemoryException* e){
		    #ifdef UG_DAO_REPORTERROR
				e->ReportError();
			#endif
			e->Delete();
			AfxAbort();
		}
		catch(CDaoException* e){
			// field failed validation...
			int er = e->m_pErrorInfo->m_lErrorCode;
			TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
			TCHAR buf[255];
			CString cs;
			GetColName(col,&cs);
			UGStr::tcscpy(buf,255,_T("The field '"));
			UGStr::tcscat(buf,255,(LPCTSTR) cs);
			UGStr::tcscat(buf,255, _T("' failed validation - "));
			UGStr::tcscat(buf,255, e->m_pErrorInfo->m_strDescription);
			AfxMessageBox(buf);
			//e->ReportError();
			e->Delete();
			delete cov;			// don't forget this...
			// set the value of m_nFailedField so that we
			// can resume the editing on that field...
			m_nFailedField = col;
		    return er;			// no need to continue...
			}
	}
	
	delete cov;
	return UG_SUCCESS;
}


/***************************************************
****************************************************/
int CUGDAODataSource::UpdateCurrentRecord() {
	// assume setfieldvalue called....
	try {
		m_Record->Update();
	}
	catch(CMemoryException* e){
		#ifdef UG_DAO_REPORTERROR
			e->ReportError();
		#endif
		e->Delete();
		AfxAbort();
	}
	catch(CDaoException* e){
		int er = e->m_pErrorInfo->m_lErrorCode;
		TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
	//	#ifdef UG_DAO_REPORTERROR
			e->ReportError();
	//	#endif
		e->Delete();
        Reset();
		return er;
	}

	return UG_SUCCESS;
}

int CUGDAODataSource::CheckPosition() {
	// a silly function - this will change or be obsolete...
	if (m_Record->GetAbsolutePosition()==-1 ) {
		// reset...
		try {
			m_Record->MoveFirst();
			m_nCurrentRow = 0;
		}
		catch(CMemoryException* e){
			#ifdef UG_DAO_REPORTERROR
				e->ReportError();
			#endif
			e->Delete();
			AfxAbort();
		}
		catch(CDaoException* e){
			int er = e->m_pErrorInfo->m_lErrorCode;
			TRACE(_T("CDaoException %d, caught at line %d in %s:\n'%s'\n"), 
				er,__LINE__, _T("CUGDAODataSource"), e->m_pErrorInfo->m_strDescription);
//			#ifdef UG_DAO_REPORTERROR
//				TCHAR buf[20];
//				wsprintf(buf,_T("Error %d"),er);
//				AfxMessageBox(buf);
//				e->ReportError();
//			#endif
			e->Delete();
			return er;		// this is rediculous...
		}
	}		
	
	return UG_SUCCESS;
}

void CUGDAODataSource::VerifyPosition(){
	long row = m_Record->GetAbsolutePosition();
	if (m_bGhostRowMode && m_nGhostRow != 0)
		ASSERT(m_nCurrentRow == row);
}
#pragma warning (pop)