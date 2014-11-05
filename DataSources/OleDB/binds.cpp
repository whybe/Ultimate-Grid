#include "stdafx.h"

#include "oledb.h"
#include "oledberr.h"

#include "ugoledb.h"
#include "binds.h"

#include "ugstrop.h"

// suppress conversion warnings
#pragma warning (push)
#pragma warning (disable : 4244)
//////////////////////////////////////////////////////////
//  Column class


Column::Column()
{
	m_buffer=NULL;
	m_Status=S_OK;
	m_Length=0;
	m_Dirty=FALSE;
}


Column::~Column()
{
	delete m_buffer;
}

// limit to field length
// currently 10k
#define MAXLENGTH 10240 

BOOL Column::SetBinding(DBCOLUMNINFO* pColInfo)
{
	m_iOrdinal=pColInfo->iOrdinal;
	m_MaxLength=pColInfo->ulColumnSize;
	m_Type=pColInfo->wType;
	m_Precision=pColInfo->bPrecision;
	m_Scale=pColInfo->bScale;
	m_colName=pColInfo->pwszName;

	if(m_Type==DBTYPE_BYTES || m_MaxLength>MAXLENGTH) // no support for binary
		return FALSE;

	if(m_Type==DBTYPE_STR)
		m_MaxLength++;
	if(m_Type==DBTYPE_WSTR)
		m_MaxLength+=2;

	
	try
	{
		m_buffer=new BYTE[m_MaxLength];
	}
	catch(CMemoryException* e)
	{
		e->Delete();
		return FALSE;
	}


	return TRUE;
}


BOOL Column::GetBinding(DBBINDING* pDBBind, long baseAddress)
{
	pDBBind->dwPart	= DBPART_VALUE | DBPART_LENGTH | DBPART_STATUS;
	pDBBind->eParamIO  = DBPARAMIO_NOTPARAM;
	pDBBind->iOrdinal	= m_iOrdinal;
	pDBBind->wType     = m_Type;
	pDBBind->pTypeInfo = NULL;
	pDBBind->obValue   = (long)m_buffer - baseAddress;
	pDBBind->obLength  = (long)&m_Length - baseAddress;
	pDBBind->obStatus  = (long)&m_Status - baseAddress;
	pDBBind->cbMaxLen  = m_MaxLength;
	pDBBind->pObject	= NULL;
	pDBBind->pBindExt	= NULL;
	pDBBind->dwFlags	= 0;
	pDBBind->dwMemOwner = DBMEMOWNER_CLIENTOWNED;
	pDBBind->bPrecision = m_Precision;
	pDBBind->bScale	= m_Scale;
	return TRUE;
}

CString Column::ToString() const
{
	CString temp;
	switch(m_Type)
	{
//		DBTYPE_EMPTY = 0,
//		DBTYPE_NULL,
//		DBTYPE_IDISPATCH,
//		DBTYPE_ERROR,
//		DBTYPE_IUNKNOWN,
//		DBTYPE_ARRAY = 0x2000,
//		DBTYPE_BYREF = 0x4000,
//		DBTYPE_GUID = 72,
//		DBTYPE_VECTOR = 0x1000,
//		DBTYPE_RESERVED = 0x8000,
//		DBTYPE_UDT,
//		DBTYPE_BSTR:
//		DBTYPE_VARIANT:

	case DBTYPE_UI1:
		temp.Format(_T("%d"), *(BYTE*)(m_buffer));
		break;
	case DBTYPE_I1:
		temp.Format(_T("%c"), *(signed char*)(m_buffer));
		break;
	case DBTYPE_I2:
		temp.Format(_T("%d"), *(int*)(m_buffer));
		break;
	case DBTYPE_UI2:
		temp.Format(_T("%u"), *(unsigned int*)(m_buffer));
		break;
	case DBTYPE_I4:
		temp.Format(_T("%d"), *(long*)m_buffer);
		break;
	case DBTYPE_UI4:
		temp.Format(_T("%u"), *(unsigned long*)m_buffer);
		break;
	case DBTYPE_R4:
		temp.Format(_T("%f"), *(float*)m_buffer);
		break;
	case DBTYPE_R8:
		temp.Format(_T("%f"), *(double*)m_buffer);
		break;
	case DBTYPE_CY:
		{
		COleCurrency cy(*(CY*)m_buffer);
		temp=cy.Format();
		}
		break;
	case DBTYPE_BOOL:
		if((*(VARIANT_BOOL*)m_buffer)==VARIANT_TRUE)
			temp="True";
		else
			temp="False";
		break;
	case DBTYPE_STR:
		temp =((LPCSTR)m_buffer);
		break;
	case DBTYPE_WSTR:
		temp =((LPCWSTR)m_buffer);
		break;
	case DBTYPE_DATE:
		{
		COleDateTime date(*(DATE*)m_buffer);
		temp=date.Format();
		}
		break;
	case DBTYPE_DBDATE:
		{
		DBDATE* d= (DBDATE*) m_buffer;
		COleDateTime date(d->year, d->month, d->day,0,0,0);
		temp=date.Format(_T("%x"));
		}
		break;
	case DBTYPE_DBTIME:
		{
		DBTIME* time= (DBTIME*) m_buffer;
		COleDateTime date(0,0,0,time->hour, time->minute, time->second);
		temp=date.Format(_T("%T"));
		}
		break;
	case DBTYPE_DBTIMESTAMP:
		{
		DBTIMESTAMP* ts= (DBTIMESTAMP*) m_buffer;
		COleDateTime date(ts->year, ts->month, ts->day,ts->hour, ts->minute, ts->second);
		temp=date.Format(_T("%c"));
		}
		break;
	case DBTYPE_I8:
// ?
//		temp.Format("%d", *(LARGE_INTEGER*)m_buffer);
//		break;
	case DBTYPE_UI8:
// ?
//		temp.Format("%d", *(ULARGE_INTEGER*)m_buffer);
//		break;
	case DBTYPE_NUMERIC:
	case DBTYPE_DECIMAL:
	case DBTYPE_BYTES:
	default:
		temp=_T("#TYPE#");
		ASSERT(FALSE);
	}
	return temp;
}

BOOL Column::FromString(const CString& str)
{
	switch(m_Type)
	{
//		DBTYPE_EMPTY,
//		DBTYPE_NULL,
//		DBTYPE_IDISPATCH,
//		DBTYPE_ERROR,
//		DBTYPE_IUNKNOWN,
//		DBTYPE_ARRAY,
//		DBTYPE_BYREF,
//		DBTYPE_GUID,
//		DBTYPE_VECTOR,
//		DBTYPE_RESERVED,
//		DBTYPE_UDT,
//		DBTYPE_BSTR,
//		DBTYPE_VARIANT,

	case DBTYPE_UI1:
		{
		BYTE b = _ttoi(str);
		*(BYTE*)(m_buffer) = b;
		}
		break;
	case DBTYPE_I1:
//		temp.Format("%c", *(signed char*)(m_buffer));
		break;
	case DBTYPE_I2:
		{
		int t = _ttoi(str);
		*(int*)(m_buffer) = t;
		}
		break;
	case DBTYPE_UI2:
///		temp.Format("%u", *(unsigned int*)(m_buffer));
		break;
	case DBTYPE_I4:
		{
		long t = _ttol(str);
		*(long*)(m_buffer) = t;
		}
		break;
	case DBTYPE_UI4:
//		temp.Format("%u", *(unsigned long*)m_buffer);
		break;
	case DBTYPE_R4:
	case DBTYPE_R8:
		{
		double t = _tcstod(str,NULL);
		*(double*)(m_buffer) = t;
		}
		break;
	case DBTYPE_CY:
		{
		COleCurrency cy;
		cy.ParseCurrency(str);
		*(CY*)m_buffer = cy;
		}
		break;
	case DBTYPE_BOOL:
		if(str[0] == 'T' || str[0] == 't')
			*(VARIANT_BOOL*)m_buffer=VARIANT_TRUE;
		else
			*(VARIANT_BOOL*)m_buffer=VARIANT_FALSE;
		break;
	case DBTYPE_STR:
#ifndef _UNICODE
		if(str.GetLength()<m_MaxLength)
		{
			UGStr::tcscpy ((LPSTR)m_buffer, m_MaxLength-1, str);
			m_Length=str.GetLength();
		}
		else
		{
			TRACE (_T("Error: string is too long"));
			return FALSE;
		}
#else
		if(str.GetLength()*2<m_MaxLength)
		{
			size_t c;
			UGStr::wcstombs (&c, (LPSTR)m_buffer, m_MaxLength/2, str, str.GetLength());
			m_Length=str.GetLength();
		}
		else
		{
			TRACE (_T("Error: string is too long"));
			return FALSE;
		}
#endif
		break;
	case DBTYPE_WSTR:
#ifndef _UNICODE
		if(str.GetLength()*2<m_MaxLength)
		{
			UGStr::mbstowcs((LPWSTR)m_buffer, m_MaxLength/2, str, str.GetLength());
			m_Length=str.GetLength() * 2;
		}
		else
		{
			TRACE (_T("Error: string is too long"));
			return FALSE;
		}
#else
		if(str.GetLength()*2<m_MaxLength)
		{
			UGStr::tcscpy((LPWSTR)m_buffer, m_MaxLength/2, str);
			m_Length=str.GetLength() * 2;
		}
		else
		{
			TRACE (_T("Error: string is too long"));
			return FALSE;
		}

#endif
		break;
	case DBTYPE_DATE:
		{
		COleDateTime date;
		date.ParseDateTime(str);
		if(date.GetStatus()!=COleDateTime::valid)
			return FALSE;
		*(DATE*)m_buffer = date;
		}
		break;
	case DBTYPE_DBDATE:
		{
		DBDATE* d= (DBDATE*) m_buffer;
		COleDateTime date;
		date.ParseDateTime(str);
		if(date.GetStatus()!=COleDateTime::valid)
			return FALSE;
		d->year=date.GetYear();
		d->month=date.GetMonth();
		d->day=date.GetDay();
		}
		break;
	case DBTYPE_DBTIME:
		{
		DBTIME* t= (DBTIME*) m_buffer;
		COleDateTime date;
		date.ParseDateTime(str);
		if(date.GetStatus()!=COleDateTime::valid)
			return FALSE;
		t->hour = date.GetHour();
		t->minute = date.GetMinute();
		t->second = date.GetSecond();
		}
		break;
	case DBTYPE_DBTIMESTAMP:
		{
		DBTIMESTAMP* ts= (DBTIMESTAMP*) m_buffer;
		COleDateTime date;
		date.ParseDateTime(str);
		if(date.GetStatus()!=COleDateTime::valid)
			return FALSE;
		ts->year=date.GetYear();
		ts->month=date.GetMonth();
		ts->day=date.GetDay();
		ts->hour = date.GetHour();
		ts->minute = date.GetMinute();
		ts->second = date.GetSecond();
		}
		break;
	case DBTYPE_I8:
		{
		__int64 t = _ttoi64(str);
		*(__int64*)m_buffer = t;
		}
		break;
	case DBTYPE_UI8:
// ?
//		temp.Format("%d", *(ULARGE_INTEGER*)m_buffer);
//		break;
	case DBTYPE_NUMERIC:
	case DBTYPE_DECIMAL:
	case DBTYPE_BYTES:
	default:
		ASSERT(FALSE);
		return FALSE;
	}
	m_Dirty=TRUE;
	return TRUE;
}




//////////////////////////////////////////////////////////
//  Columns class


Columns::~Columns()
{
	delete [] m_cols;
}

HRESULT Columns::SetColumnInfo(IColumnsInfo* pIColumnsInfo)
{
	DBCOLUMNINFO* pColumnInfo;
	HRESULT		hr;
    OLECHAR*		pStringsBuffer;
	ULONG		numBound=0;
	// Get column information from the command object via IColumnsInfo::GetColumnsInfo 
	hr = pIColumnsInfo->GetColumnInfo(&m_NumCols, &pColumnInfo, &pStringsBuffer );
	// did not get columns info
	if (FAILED(hr))
		return hr; 

	// store the columns 
	delete [] m_cols;
	m_cols=new Column[m_NumCols];

	for(ULONG i=0; i<m_NumCols; i++)
	{
		if(m_cols[numBound].SetBinding(&pColumnInfo[i]))
			numBound++;
	}
	m_NumCols=numBound;

	// cleanup our buffers
	if(pStringsBuffer || pColumnInfo)
	{
		IMalloc* pIMalloc=NULL;
	    hr = CoGetMalloc(MEMCTX_TASK, &pIMalloc);
		if(SUCCEEDED(hr))
		{
			pIMalloc->Free(pStringsBuffer);	    	
			pIMalloc->Free(pColumnInfo);
			pIMalloc->Release();
		}

	}
	return hr;
}



Column* Columns::operator[](int nIndex)
{
	if( nIndex>=0 && nIndex < (LONG)m_NumCols )
		return &m_cols[nIndex];
	return NULL;
}


HRESULT Columns::SetDirtyColumnBindings(DBBINDING** ppBinds, ULONG* cBound)
{
	delete [] *ppBinds;
	*cBound=0;
	ULONG numBound=0;

	DBBINDING* pBinds = new DBBINDING[m_NumCols];
	long baseAdd = (long)BaseAddress();
	for(ULONG i=0; i<m_NumCols; i++)
	{
		if(m_cols[i].GetDirty())
		{
			m_cols[i].GetBinding(&pBinds[numBound], baseAdd);
			numBound++;
			m_cols[i].SetDirty(FALSE);
		}
	}

	*cBound=numBound;
	*ppBinds=pBinds;
	return S_OK;
}

HRESULT Columns::SetColumnBindings(DBBINDING** ppBinds, ULONG* cBound)
{
	delete [] *ppBinds;

	DBBINDING* pBinds = new DBBINDING[m_NumCols];
	long baseAdd = (long)BaseAddress();
	for(ULONG i=0; i<m_NumCols; i++)
		m_cols[i].GetBinding(&pBinds[i], baseAdd);

	*ppBinds=pBinds;
	*cBound = m_NumCols;
	return S_OK;
}
#pragma warning ( pop )