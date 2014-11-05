/***********************************************
	Ultimate Grid version 7.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Class 
		CUG_HTML_DataSource
	Purpose
		This is a derived grid datasource, that 
		allows HTML tables to be loaded into the 
		standard grid memory manager.  

		While this data source only handles 
		importing simple HTML tables , it will 
		skip over embedded tables to completely
		import the table.  You can decided which
		of the outer most tables to import by 
		passing a table number to the Open 
		function.
	Details
		-This class derives from CUGMem which is 
	     the standard memory manager.
		-The Load method has been implemented.
		-Standard return values for functions are: 
			UG_SUCCESS	- success (0)
			UG_NA		- not available (-1)
			1 and up	- error codes

************************************************/

#include "stdafx.h"
#include "UGCtrl.h"
#include "UGHTML.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***************************************************
Constructor
	Init all data here
****************************************************/
CUG_HTML_DataSource::CUG_HTML_DataSource()
{
		m_rows=0;
		m_cols=0;
		m_ctrl=NULL;
}
/***************************************************
Destructor
	Perform clean up here
****************************************************/
CUG_HTML_DataSource::~CUG_HTML_DataSource()
{
	Close();
}

/***************************************************
********** opening and closing *********************
****************************************************/


// name = name or URL of HTML file
// option = tablenumber (as a string)
/***************************************************
****************************************************/
int CUG_HTML_DataSource::Open(LPCTSTR name,LPCTSTR option)
{

	// close the current table
	Close();
	CWaitCursor wait;
	char* buff=NULL;
	long length=0;
	int number=1;


	// retrieve the table number
	if(option!=NULL)
		number = _ttoi(option);

	// if this is an URL it *must* have http:// in front of it.
	if(_tcsstr(name,_T("http://"))==NULL)
	{
		// open the file and read it into memory 
		try 
		{
			CFile file(name, CFile::modeRead);
			length = file.GetLength();
			buff = new char[length+1];
			file.Read(buff, length);
		}
		catch(CFileException* e)
		{
			e->ReportError();
			e->Delete();
		}
	}
	else
	{	
		// try to open the given URL and read it into memory
		CInternetSession session;
		CHttpConnection* pServer=NULL;
		CHttpFile* pHttpFile=NULL;
		try
		{
			// check to see if this is a reasonable URL
			CString strServerName;
			CString strObject;
			INTERNET_PORT nPort;
			DWORD dwServiceType;

			if (!AfxParseURL(name, dwServiceType, strServerName, strObject, nPort) ||
				dwServiceType != INTERNET_SERVICE_HTTP)
			{
				AfxMessageBox(_T("Error: can only use URLs beginning with http://\n"));
				TRACE ( _T("Error: can only use URLs beginning with http://\n"));
				return UG_ERROR;
			}
			// open the connection and request
			pServer = session.GetHttpConnection(strServerName, nPort);
			ASSERT(pServer);
			pHttpFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET,
				strObject, NULL, 1, NULL, NULL);
			ASSERT (pHttpFile);

			// get the http stream
			pHttpFile->SendRequest();
			DWORD dwRet;
			pHttpFile->QueryInfoStatusCode(dwRet);
			if(dwRet>=200 && dwRet <300)
			{
				length = pHttpFile->GetLength();
				buff = new char[length+1];
				pHttpFile->SetReadBufferSize(length+1);
				pHttpFile->Read(buff, length);
			}
//#ifdef _DEBUG
			else {
				AfxMessageBox(_T("HTTP Query Failed"));
				TRACE (_T("HTTP Query Failed\n"));
			}
//#endif
		}
		catch(CException* e)
		{
			e->ReportError();
			e->Delete();
		}

		// do some clean up
		if(pHttpFile)
		{
			pHttpFile->Close();
			delete pHttpFile;
		}
		if(pServer)
		{
			pServer->Close();
			delete pServer;
		}

	}

	// buff should hold the "file" information
	if(buff)
	{
		int res = LoadTable(buff,buff+length,number);
		TRACE(_T("Result of LoadTable == %d\n"), res);
		if(res == 0)
			AfxMessageBox(_T("No tables found in file!"));
		// update control info
		if(m_ctrl!=NULL)
		{
			m_ctrl->SetNumberRows(m_rows);
			m_ctrl->SetNumberCols(m_cols);
			m_ctrl->RedrawAll();
		}
	}
	else
		return UG_ERROR;


	// delete the temporary mem buffer
	if(buff)
		delete [] buff;

	
	return UG_SUCCESS;
}
/***************************************************
****************************************************/
int CUG_HTML_DataSource::Close()
{
	m_cols=0;
	m_rows=0;
	Empty();
	return UG_NA;
}


long CUG_HTML_DataSource::GetNumRows()
{
	return m_rows;
}
/***************************************************
****************************************************/
int CUG_HTML_DataSource::GetNumCols()
{
	return m_cols;
}


// find the start of a table detail
char* CUG_HTML_DataSource::FindDetailStart(char* buff)
{
	
	char* ret=strstr(buff,"<td");
	if(ret==NULL)
		ret=strstr(buff,"<TD");
	return ret;
}

// find the end of the detail section
// it is possible to skip the </td>
// tag and default to a new table detail
// with the start of a new table detail
// or table row, or the end of the table
char* CUG_HTML_DataSource::FindDetailEnd(char* buff)
{
	char* end;
	end=strstr(buff,"</td>");
	if(end==NULL)
		end=strstr(buff,"</TD>");
	if(end==NULL)
	{
		char* ds=FindDetailStart(buff);
		char* rs=FindRowStart(buff);
		char* te=FindTableEnd(buff);
		end=min(ds,min(rs,te));
	}
	return end;
}

// find the row start position
char* CUG_HTML_DataSource::FindRowStart(char* buff)
{
	char* ret=strstr(buff, "<tr");
	if(ret==NULL)
		ret=strstr(buff, "<TR");
	return ret;
}

// find the end row tag
// it is possible to skip the </tr> tag
// and only use <tr> or </table> to
// denote the end of the row
char* CUG_HTML_DataSource::FindRowEnd(char* buff)
{
	char* end = strstr(buff, "</tr>");
	if(end==NULL)
		end=strstr(buff, "</TR>");
	if(end==NULL)
	{
		char* rs=FindRowStart(buff);
		char* te=FindTableEnd(buff);
		end=min(rs,te);
	}
	return end;
}

// find the beginning of the table
char* CUG_HTML_DataSource::FindTableStart(char* buff)
{
	char* ret=strstr(buff, "<table");
	if(ret==NULL)
		ret=strstr(buff, "<TABLE");
	return ret;
}

// find the end of the table
char* CUG_HTML_DataSource::FindTableEnd(char* buff)
{
	char* ret=strstr(buff, "</table>");
	if(ret==NULL)
		ret=strstr(buff, "</TABLE>");
	return ret;
}

// load the columns of this row into the memory manager
long CUG_HTML_DataSource::LoadColumns(char* buff, char* buffEnd)
{
	int col =0;
	CUGCell cell;
	char* begin = FindDetailStart(buff);
	char* next;
	char* end;
	char* tbegin;
	tbegin = FindTableStart(buff);
	if(tbegin > buffEnd)
		tbegin=NULL;


	// iterate until there are no more table
	// details of we are past the row end
	while(begin && begin<buffEnd) 
	{

		// skip the rest of the tabe begin tag
		begin = strstr(begin, ">");
		ASSERT(begin);
		begin++;
		// find the end of the detail
		end=FindDetailEnd(begin);
		// is there an embedded table?
		if(tbegin && begin <= tbegin && tbegin < end)
		{
			// find the end of the embedded table
			int level=0;
			end=FindTableEnd(begin);
			next=tbegin+1;
			while((next=FindTableStart(next))!=NULL && next<end)
			{
				next++;
				level++;
			}
			while(level-->0)
			{
				end++;
				end=FindTableEnd(end);
			}
			ASSERT(end);
			if(OnEmbeddedTableFound(col, m_rows, begin, end)==UG_NA)
			{
				cell.SetText(_T("Embedded Table"));
				SetCell(col, m_rows, &cell);
			}
		}
		else
		{
			// set the current cell.
			CString details(begin, end-begin);
			InterpretTags(details,&cell);
			SetCell(col, m_rows, &cell);
		}
		// goto the next detail section
		begin = FindDetailStart(end);
		col++;
	}
	m_cols=max(col,m_cols);
	return end-buff;		
}

// load the rows from a table into the memory manager
long CUG_HTML_DataSource::LoadRows(char* buff, char* buffEnd)
{
	char* begin=FindRowStart(buff);
	char* next;
	char* end=buff;
	char* tbgein= FindTableStart(buff);
	if(tbgein >= buffEnd)
		tbgein=NULL;
 
	// iterate through all rows
	while(begin && begin<buffEnd) 
	{
		// skip the rest of the row start tag
		begin = strstr(begin, ">");
		ASSERT(begin);
		begin++;
		end = FindRowEnd(begin);
		if(tbgein && begin<tbgein && tbgein<end)
		{   // there is a table in this row
			int level=0;
			end=FindTableEnd(begin);
			next=tbgein+1;
			while((next=FindTableStart(next))!=NULL && next<end)
			{
				next++;
				level++;
			}
			while(level-->0)
			{
				end++;
				end=FindTableEnd(end);
			}
			end=FindRowEnd(end);
			tbgein= FindTableStart(end);
			if(tbgein >= buffEnd)
				tbgein=NULL;
		}
 		ASSERT(end);
		// load the details for the current row
		LoadColumns(begin,end);
		begin=FindRowStart(end);
		m_rows++;
	}
	return end-buff;		
}

// load a table into the memory manager
long CUG_HTML_DataSource::LoadTable(char* buff, char* buffEnd, int num)
{
	// find table def
	char* begin=FindTableStart(buff);
	// if begin == "" no table found...
	if(!begin)
		return 0;

	char* next;
	char* end;
	int level=0;
	// keep going until we find the correct table
	while(begin && num--) 
	{
		level=0;
		// skip over the rest of tag
		begin = strstr(begin, ">");
		ASSERT(begin);
		begin++;
		next=begin;
		end=FindTableEnd(begin);
		while((next=FindTableStart(next))!=NULL && next<end)
		{
			next++;
			level++;
		}
		while(level-->0)
		{
			end++;
			end=FindTableEnd(end);
		}
//		ASSERT(end);
		if(num==0)
			LoadRows(begin, end);
		begin=begin=FindTableStart(begin);
	}
	return end-buff;
}


// strip out all the extra tags, white space, etc
// can be overridden in a subclass, for fancier processing of
// the tags
void CUG_HTML_DataSource::InterpretTags(CString text,CUGCell* cell)
{
	int i;
	// take out extra tags
	while ((i=text.Find(_T("<"))) !=-1)
		text = text.Left(i) + text.Mid(text.Find(_T(">"))+1);
	// take out extra line feed, carriage returns, tabs etc.
	while ((i=text.FindOneOf(_T("\f\r\n\t"))) !=-1)
		text = text.Left(i) + text.Mid(i+1);
	// take out extra spaces
	while ((i=text.Find(_T("  "))) !=-1)
		text = text.Left(i) + text.Mid(i+1);
	// take out the MS space 
	while ((i=text.Find(_T("&nbsp;"))) !=-1)
		text = text.Left(i) + text.Mid(i+6);
	cell->SetText(text);
}


// can be overridden in a subclass for special processing of embedded table
// return UG_NA for default action
//		  UG_SUCCESS if handled
int CUG_HTML_DataSource::OnEmbeddedTableFound(int col, long row, char* buff, char* buffEnd)
{
	return UG_NA;
}
