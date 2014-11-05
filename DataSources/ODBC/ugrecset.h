// ugrecset.h : header file
//
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

/////////////////////////////////////////////////////////////////////////////
// CUGRecordset recordset


#define UG_ODBC_REPORTERROR
// Comment out this define to eliminate message boxes in the
// ODBC exception handlers - usefull for debugging...

#define UG_ODBC_MAXBINARY 65535
// type SQL_LONGVARBINARY is read into a CByteArray.
// if datasource reports Data Truncated, this value may need to
// be increased...

#define UG_ODBC_MAXTEXT 14000
// Basically truncation value for LONGVARCHAR (ms access memos).
// Also used to set buffer size for string.Format in GetCell
// When adjusting, 255 is a suggested minimum.

// structure to hold information gathered from SQLTables...
typedef struct tagSQLDatasourceInfo {
	SQLTCHAR	tableQualifier[128];
	SQLTCHAR	tableOwner[128];
	SQLTCHAR	tableName[128];
	SQLTCHAR	tableType[128];
	SQLTCHAR	remarks[255];
}SQLDatasourceInfo;


// minimal structure for getting field info...
typedef struct tagSQLColumnInfo {
	CString	strName;			// name of field
	CString strLabel;			// column label
	SWORD	nSQLType;			// SQL_XXX type of field
	UDWORD	nPrecision;			// precision of the data type
	SWORD	nScale;				// scale of the datatype
	SWORD	nNullable;			// does field allow nulls?
	SQLINTEGER	nUpdatable;			// is field updatable?
	SQLINTEGER	nAutoValue;			// is field a counter?
	void*	pValue;				// storage for retieved data
} SQLColumnInfo;




class CUGRecordset : public CRecordset
{

public:

	CString		m_defaultConnect;

	CPtrArray*	m_pSQLColumnInfoList;
		
	CString		m_strNameParam;
	CString		m_strOtherParam;
	CString		m_dataFileName;

	CUGRecordset(CDatabase* data);
	~CUGRecordset();

// added to CUGRecordset
	void CleanUp();
	BOOL BindFields(HSTMT hstmt);
	void ReportSQLError(RETCODE retcode, LPCTSTR func, HSTMT hstmt=SQL_NULL_HSTMT); 
	SQLColumnInfo* GetFieldInfo(int col);

// Overrides
	public:
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	virtual BOOL Open(UINT nOpenType, LPCTSTR lpszSQL, DWORD dwOptions);  // RFX support
	virtual CString GetDefaultConnect();    // Default connection string

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
