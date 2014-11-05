// ===================================================================
//     Class: COXParser (including COXParserObject, COXAttribute, COXParserElement and COXToken)
//      File: OXParser.cpp
//   Purpose: Parser for XML like structures

// Product Version: 7.51

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXParser.h"
#include "UGStrOp.h"

#ifndef CSTR_EQUAL
#define CSTR_EQUAL                2           // string 1 equal to string 2
#endif
//////////////////////////////////////////////////////////////////////
// Macros for debugging
//////////////////////////////////////////////////////////////////////

#ifndef TRACE0      // If this isn't defined, a whole bunch of stuff isn't defined
#undef TRACE1
#undef TRACE2
#undef TRACE3
#undef UNUSED_ALWAYS
#undef UNUSED

#define UNUSED_ALWAYS(x) (x);
#ifdef _DEBUG
    #define UNUSED(x)
    #include <crtdbg.h>
	#define TRACE0(text)			        _RPT0(_CRT_WARN, text)
	#define TRACE1(format, a1)		        _RPT1(_CRT_WARN, format, a1)
	#define TRACE2(format, a1, a2)	        _RPT2(_CRT_WARN, format, a1, a2)
	#define TRACE3(format, a1, a2, a3)      _RPT3(_CRT_WARN, format, a1, a2, a3)
#else
    #define UNUSED(x)                        (x);
    #define TRACE0(text)
	#define TRACE1(format, a1)
	#define TRACE2(format, a1, a2)	
	#define TRACE3(format, a1, a2, a3)
#endif

#endif

#ifdef _DEBUG
    #define TRACE4(format, a1, a2, a3, a4 ) _RPT4(_CRT_WARN, format, a1, a2, a3, a4)
#else
	#define TRACE4(format, a1, a2, a3, a4)
#endif

//////////////////////////////////////////////////////////////////////
// Static data
//////////////////////////////////////////////////////////////////////

// This is the list of default entities. Just add entities to this list
// and they will be automatically encoded/decoded during text processing.
// Note that when the parser writes out text, it will only convert from
// text to entity (eg '>' ==> &gt;) when the literal text is a single character
// (so if you add "date == "10 May" and "10 May" appears in text, it won't
// be converted to "&date;")
ParserEntity COXParser::m_Entity[] = 
{
    {TEXT("gt"),   TEXT(">")},
    {TEXT("lt"),   TEXT("<")},
    {TEXT("amp"),  TEXT("&")},
    {TEXT("apos"), TEXT("\'")},
    {TEXT("quot"), TEXT("\"")},

    { NULL, NULL }  // must be last
};

//////////////////////////////////////////////////////////////////////
// COXToken
//////////////////////////////////////////////////////////////////////

COXToken::COXToken()
{
    Clear();
}

COXToken::~COXToken()
{
    Clear();
}

// --- In  : 
// --- Out :
// --- Returns : 
// --- Effect : Resets the token to an empty state
void COXToken::Clear()
{
    m_nType = UNKNOWN;
}

//////////////////////////////////////////////////////////////////////
// COXParserObject
//////////////////////////////////////////////////////////////////////

COXParserObject::COXParserObject()
{
    m_nType   = UNKNOWN;
    m_pParent = NULL;
    m_nFlags  = 0;
}

COXParserObject::COXParserObject(COXParserElement* pParent, int nType, 
								 LPCTSTR szText)
{
    m_pParent = pParent;
    m_nType   = nType;
    m_nFlags  = 0;

    SetText(szText);
}

COXParserObject::~COXParserObject()
{
}

COXParserElement* COXParserObject::GetParent() const                      
{ 
    if (m_pParent && m_pParent->GetType() == ELEMENT)
        return m_pParent;
    else
        return NULL;
}

BOOL COXParserObject::SetText(LPCTSTR szText)
{
    return m_Text.SetString(szText);
}

BOOL COXParserObject::IsText(LPCTSTR szText, 
							 BOOL bCaseSensitive /*=FALSE*/)
{
    return m_Text.Compare(szText, bCaseSensitive);
}

//////////////////////////////////////////////////////////////////////
// COXAttribute
//////////////////////////////////////////////////////////////////////

COXAttribute::COXAttribute()
{
    m_nValue = 0; 
    SetType(ATTRIBUTE);
    SetAttributeType(ATTR_UNKNOWN);
}

COXAttribute::COXAttribute(LPCTSTR szName, LPCTSTR szValue)
{
    m_nValue = 0; 
    SetName(szName);
    SetValue(szValue);
}

COXAttribute::COXAttribute(LPCTSTR szName, int nValue)
{
    SetName(szName);
    SetValue(nValue);
}

COXAttribute::~COXAttribute()
{
    m_szValue.Empty();
}

LPCTSTR COXAttribute::GetStringValue()             
{ 
    static TCHAR strValue[20];

    if (GetAttributeType() == ATTR_INTEGER)
    {
		UGStr::stprintf(strValue, 20, TEXT("%d"), m_nValue);
        return strValue;
    }
    else if (m_szValue.IsEmpty())
    {
        strValue[0] = TEXT('\0');
        return strValue;
    }
    else
        return m_szValue.GetString();
}

int COXAttribute::GetIntValue() const                
{
    if (GetAttributeType() == ATTR_STRING)
        return 0;
    else
        return m_nValue;  
}

void COXAttribute::SetValue(LPCTSTR szValue)   
{
    m_szValue.SetString(szValue);
    SetAttributeType(ATTR_STRING); 
}

void COXAttribute::SetValue(int nValue)   
{ 
    if (GetAttributeType() == ATTR_STRING)
        m_szValue.Empty();

    m_nValue = nValue; 
    SetAttributeType(ATTR_INTEGER); 
}

BOOL COXAttribute::IsValue(LPCTSTR szValue, 
						   BOOL bCaseSensitive /*=FALSE*/)
{
    if (!szValue || GetAttributeType() != ATTR_STRING || !m_szValue)
        return FALSE;

    BOOL bFound = FALSE;
    if (!bCaseSensitive)
        bFound = (_tcsicmp(m_szValue, szValue) == 0);
    else
        bFound = (_tcscmp(m_szValue, szValue) == 0);

    return bFound;
}

void COXAttribute::operator=(COXAttribute& Attr)
{
    SetType(Attr.GetType());
    SetName(Attr.GetName());

    if (Attr.GetAttributeType() == ATTR_STRING)
        SetValue(Attr.GetStringValue());
    else
        SetValue(Attr.GetIntValue());
}


//////////////////////////////////////////////////////////////////////
// COXParserElement
//////////////////////////////////////////////////////////////////////

COXParserElement::COXParserElement()
{
    SetType(ELEMENT);
}

COXParserElement::COXParserElement(COXParserElement* pParent, 
								   LPCTSTR szName)
{
    SetParent(pParent);
    SetType(ELEMENT);
    SetName(szName);
}

COXParserElement::~COXParserElement()
{
    Clear();
}

COXParserObject* COXParserElement::AddObject(COXParserObject* pObject)   
{
    pObject->SetParent(this);
    m_Objects.push_back(pObject);

    return pObject; 
}

COXParserElement* COXParserElement::AddElement(LPCTSTR szName)
{
    COXParserElement *pElement = new COXParserElement(this, szName);
    if (!pElement)
        return NULL;

    return (COXParserElement*) AddObject(pElement);
}

COXParserObject* COXParserElement::InsertObject(int nIndex, 
												COXParserObject* pObject)   
{
    pObject->SetParent(this);
    m_Objects.insert(m_Objects.begin() + nIndex, pObject);

    return pObject; 
}

COXParserObject* COXParserElement::MoveObject(int nIndex, 
											  COXParserObject* pObject)   
{
    if (!pObject)
        return FALSE;

    // Find object and remove it from the list
    for (int i = 0; i < NumObjects(); i++)
    {
        if (Object(i) == pObject)
        {
            m_Objects.erase(m_Objects.begin() + i); 
            break;
        }
    }
    return InsertObject(nIndex, pObject);
}

COXParserElement* COXParserElement::InsertElement(int nIndex, 
												  LPCTSTR szName)
{
    COXParserElement *pElement = new COXParserElement(this, szName);
    if (!pElement)
        return NULL;

    return (COXParserElement*) InsertObject(nIndex, pElement);
}

BOOL COXParserElement::DelObject(int nIndex)
{
    if (nIndex >= NumObjects())
        return FALSE;

    COXParserObject *pObject = Object(nIndex);
    if (pObject)
        delete pObject;

    m_Objects.erase(m_Objects.begin() + nIndex); 

    return TRUE;
}

BOOL COXParserElement::DelObject(COXParserObject* pObject)
{
    if (!pObject)
        return FALSE;

    for (int i = 0; i < NumObjects(); i++)
    {
        if (Object(i) == pObject)
            return DelObject(i);
    }

    return FALSE;
}

void COXParserElement::ClearObjects()
{
    for (int i = 0; i < NumObjects(); i++)
    {
        COXParserObject* pObject = Object(i);
        if (pObject)
            delete pObject;
    }

    m_Objects.clear();
}

#if _MSC_VER >=1200
#pragma warning(push)
#endif
#pragma warning(disable:4239)
COXParserElement* COXParserElement::FindElement(LPCTSTR szName, 
												BOOL bCaseSensitive /*=FALSE*/)
{
    COXQuickString str = szName;
    UINT nLevel = 0;

    COXQuickString strFolderName = str.GetToken(nLevel++, TEXT('\\'));
    if (strFolderName.IsEmpty())
        return NULL;


    COXParserElement* pElement = this;
    COXParserElement* pTargetElement = NULL;

    while (!strFolderName.IsEmpty())
    {
        pTargetElement = NULL;

        for (int i = 0; i < pElement->NumObjects(); i++)
        {
            COXParserElement* pSearchElement = 
				(COXParserElement*) pElement->Object(i);
            if (!pSearchElement || pSearchElement->GetType() != ELEMENT) 
                continue;

            // Found folder
            if (pSearchElement->IsName(strFolderName, bCaseSensitive))
            {
                pTargetElement = pSearchElement;
                pElement = pTargetElement;
                break;
            }
        }
        strFolderName = str.GetToken(nLevel++, TEXT('\\'));
    }

    return pTargetElement;
}
#if _MSC_VER >=1200
#pragma warning(pop)
#else
#pragma warning(default:4239)
#endif
COXAttribute* COXParserElement::AddAttribute(COXAttribute* pAttribute)
{
    pAttribute->SetParent(this);
    m_Attributes.push_back(pAttribute); 

    return pAttribute; 
}

COXAttribute* COXParserElement::AddAttribute(LPCTSTR szName, 
											 LPCTSTR szValue)
{
    COXAttribute *pAttribute = new COXAttribute;
    if (!pAttribute)
        return NULL;

    pAttribute->SetName(szName);
    pAttribute->SetValue(szValue);
    pAttribute->SetParent(this);

    return AddAttribute(pAttribute);
}

COXAttribute* COXParserElement::AddAttribute(LPCTSTR szName, 
											 int nValue)
{
    COXAttribute *pAttribute = new COXAttribute;
    if (!pAttribute)
        return NULL;

    pAttribute->SetName(szName);
    pAttribute->SetValue(nValue);
    pAttribute->SetParent(this);

    return AddAttribute(pAttribute);
}

BOOL COXParserElement::DelAttribute(int nIndex)
{
    if (nIndex >= NumAttributes())
        return FALSE;

    COXAttribute *pAttribute = Attribute(nIndex);
    delete pAttribute;

    m_Attributes.erase(m_Attributes.begin() + nIndex); 

    return TRUE;
}

BOOL COXParserElement::DelAttribute(COXAttribute* pAttribute)
{
    if (!pAttribute)
        return FALSE;

    for (int i = 0; i < NumAttributes(); i++)
    {
        if (Attribute(i) == pAttribute)
            return DelAttribute(i);
    }

    return FALSE;
}

void COXParserElement::ClearAttributes()
{
    for (int i = 0; i < NumAttributes(); i++)
    {
        COXAttribute *pAttribute = Attribute(i);
        delete pAttribute;
    }

    m_Attributes.clear();
}

COXAttribute* COXParserElement::FindAttribute(LPCTSTR szName, 
											  bool bCaseSensitive /*=false*/)
{
    if (!szName)
        return NULL;

    for (int i = 0; i < NumAttributes(); i++)
    {
        COXAttribute *pAttribute = Attribute(i);
        if (pAttribute->IsName(szName, (BOOL) bCaseSensitive))
            return pAttribute;
    }
    return NULL;
}

COXAttribute* COXParserElement::FindAttribute(LPCTSTR szName, 
											  LPCTSTR szValue, 
                                   bool bCaseSensitive /*=false*/)
{
    if (!szName || !szValue)
        return NULL;

    for (int i = 0; i < NumAttributes(); i++)
    {
        COXAttribute* pAttribute = Attribute(i);
        if (!pAttribute || 
			pAttribute->GetAttributeType() != COXAttribute::ATTR_STRING) 
            continue;

        if (pAttribute->IsName(szName, (BOOL) bCaseSensitive) && 
            pAttribute->IsValue(szValue, (BOOL) bCaseSensitive))
            return pAttribute;
    }
    return NULL;
}

COXAttribute* COXParserElement::FindAttribute(LPCTSTR szName, int nValue, 
                                   bool bCaseSensitive /*=false*/)
{
    if (!szName)
        return NULL;

    for (int i = 0; i < NumAttributes(); i++)
    {
        COXAttribute* pAttribute = Attribute(i);
        if (!pAttribute || 
			pAttribute->GetAttributeType() != COXAttribute::ATTR_INTEGER) 
            continue;

        if (pAttribute->IsName(szName, (BOOL) bCaseSensitive) && 
			pAttribute->GetIntValue() == nValue)
            return pAttribute;
    }
    return NULL;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COXParser::COXParser()
{
    m_chStartDelim = TEXT('<');
    m_chEndDelim   = TEXT('>');
    m_chTagEnd     = TEXT('/');
    m_chProcInstr  = TEXT('?');
    m_chMarkup     = TEXT('!');
    m_chDash       = TEXT('-');
    m_chCR         = TEXT('\r');
    m_chLF         = TEXT('\n');
    m_chNULL       = TEXT('\0');
    m_chEsc        = TEXT('&');

    m_szTab        = TEXT("   ");       // indent tab when writing XML files
    m_nLineLength  = 80;                // Max length of a line of text when writing files

    m_bErrorOnMissingTag = TRUE;
    m_bCaseSensitive = TRUE;
    m_nLine = 0;
    m_nColumn = 0;

    m_pfnErrorFn = NULL;
    m_dwErrData  = 0;

    // Fill hash table with special characters
    for (int i = 0; m_Entity[i].szName; i++)
        m_EntityTable.Add(m_Entity[i].szName, 
			(DWORD) m_Entity[i].szLiteral);
}

COXParser::~COXParser()
{
    Clear();
}

//////////////////////////////////////////////////////////////////////
// Parsing routines
//////////////////////////////////////////////////////////////////////

void COXParser::Clear()
{
    m_Token.Clear();
    m_Root.ClearObjects(); 
    m_Root.ClearAttributes(); 
    m_nLine = 0;
    m_nColumn = 0;
    m_pBuf = m_pBufStart = NULL;
}

BOOL COXParser::Initialize()
{
    m_pBuf = m_pBufStart;
    m_nLine = 1;
    m_nColumn = 1;

    m_Root.SetName(TEXT("[Root]"));
    m_Root.SetParent(NULL);

    return TRUE;
}

BOOL COXParser::Cleanup()
{
    return TRUE;
}

BOOL COXParser::IsEmpty() const
{
    return (!m_Root.NumAttributes() && !m_Root.NumObjects());
}

void COXParser::SetErrorRptFunction(ParserErrorFn pFn, DWORD dwData)
{
    m_pfnErrorFn = pFn; 
    m_dwErrData = dwData; 
}

BOOL COXParser::Parse(LPTSTR pBuf)
{
    if (!pBuf)
        return FALSE;

    Clear();

    m_pBufStart = pBuf;

    Initialize();
    BOOL bResult = ParseElement(&m_Root, 0);
    Cleanup();

    return bResult;
}

TCHAR COXParser::GetNextChar(int nSteps /*=1*/, 
							 BOOL bWarnOnError /*=FALSE*/)
{
    ASSERT(m_pBuf);
    if (!m_pBuf)
    {
        if (bWarnOnError)
            ReportError(ERROR_NULL_BUFFER, TEXT("NULL buffer supplied."));
        return m_chNULL;
    }

    TCHAR ch = *m_pBuf;
    for (int i = 0; i < nSteps && ch; i++)
    {
        ch = *m_pBuf;
        if (!ch)
            break;

        m_pBuf++;

        // Convert CRLF's to LF's, and CR's to LF's
        if (ch == m_chCR)
        {
            ch = m_chLF;
            if (*m_pBuf == m_chLF)
                m_pBuf++;
        }

        m_nColumn++;
        if (ch == m_chLF)
        {
            m_nLine++;
            m_nColumn = 0;
        }
    }

    if (ch == m_chNULL)
    {
        if (bWarnOnError)
            ReportError(ERROR_END_OF_BUFFER, 
				TEXT("Unexpected end of buffer."));
        return m_chNULL;
    }

    return ch;
}

void COXParser::UngetChar(int nSteps /*=1*/)
{
    for (int i = 0; i < nSteps; i++)
    {
        if (m_pBuf <= m_pBufStart)
            break;

        m_pBuf--;
        if (*m_pBuf == m_chLF || 
			(*m_pBuf == m_chCR && *(m_pBuf+1) != m_chLF) )
        {
            m_nLine--;
            m_nColumn = 0;
            for (LPTSTR ptr = m_pBuf; 
                 ptr >= m_pBufStart && *ptr != m_chLF && *ptr != m_chCR;
				 ptr--)
                    m_nColumn++;
        }
        else
            m_nColumn--;
    }
}

BOOL COXParser::RemoveWhiteSpace()
{
    TCHAR ch = GetNextChar();
    while (ch && _istspace(ch))
        ch = GetNextChar();

    if (ch)
    {
        UngetChar();
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void COXParser::SaveBufferPos(SAVEPOS& pos)
{
    pos.pBuf  = m_pBuf;
    pos.nLine = m_nLine;
    pos.nCol  = m_nColumn;
}

void COXParser::RestoreBufferPos(SAVEPOS& pos)
{
    m_pBuf    = pos.pBuf;
    m_nLine   = pos.nLine;
    m_nColumn = pos.nCol;
}

BOOL COXParser::GetNameToken(COXQuickString& str)
{
    str.Empty();
    str.SetLength(100);
    
    TCHAR ch = GetNextChar();
    while (ch && !_istspace(ch) &&
            (_istalnum(ch) || ch == TEXT(':') || 
				ch == TEXT('_') || ch == TEXT('-')) )
    {
        str.Append(ch);
        ch = GetNextChar();
    }
    
    BOOL bResult = TRUE;

    if (ch == m_chNULL)
    {
        ReportError(ERROR_END_OF_BUFFER,  
			TEXT("Unexpected end of buffer while name."));
        bResult = FALSE;
    }
    else if (ch != m_chEndDelim && ch != m_chTagEnd && 
				ch != TEXT('=') && !_istspace(ch))
    {
        ReportError(ERROR_ILLEGAL_CHAR,
            TEXT("Illegal character (%c) encountered while parsing name."), ch);
        bResult = FALSE;
    }

    if (bResult)
        UngetChar();
    else
        str.Empty();

    return bResult;
}

BOOL COXParser::GetNumberToken(int& nNumber)
{
    COXQuickString str;
    str.SetLength(20);

    int nMultiplier = 1;

    TCHAR ch = GetNextChar();
    if (ch == TEXT('-'))
    {
        nMultiplier = -1;
        ch = GetNextChar();
    }
    else if (ch == TEXT('+'))
        ch = GetNextChar();

    while (_istdigit(ch))
    {
        str.Append(ch);
        ch = GetNextChar();
    }

    if (ch == m_chNULL)
    {
        ReportError(ERROR_END_OF_BUFFER, 
            TEXT("Unexpected end of buffer while parsing integer."));
        str.Empty();
        return FALSE;
    }
    UngetChar();
            
    nNumber = _ttoi((LPCTSTR) str) * nMultiplier;
    
    return TRUE;
}

BOOL COXParser::GetStringToken(COXQuickString& str, TCHAR chQuoteChar)
{
    str.Empty();
    str.SetLength(100);
    
    TCHAR ch = GetNextChar();
    while (ch && ch != chQuoteChar)
    {

#ifdef OXPARSER_CONVERT_ENTITY
		if (ch!=m_chEsc)
		{
#endif
		str.Append(ch);
        ch = GetNextChar();

#ifdef OXPARSER_CONVERT_ENTITY
		}
		else
		{
			BOOL bContinue=TRUE;
			COXQuickString sEsc;
			do
			{
				ch=GetNextChar();
				if (!ch || ch==chQuoteChar)
					bContinue=FALSE;
				else
					if (ch!=TEXT(';'))
						sEsc.Append(ch);
			}
			while(bContinue && ch!=TEXT(';'));
			if (bContinue)
			{
				LPCTSTR lpSymb=GetLiteralString((LPCTSTR) sEsc);
				if (lpSymb)
				{
					str.Append(*lpSymb);
				}
				else
				{
					str.Append(TEXT('&'));
					str.AddString((LPCTSTR) sEsc);
					str.Append(TEXT(';'));
				}
				ch=GetNextChar();

			}
		}
#endif
    }
    
    if (ch != chQuoteChar)
    {
        ReportError(ERROR_END_OF_BUFFER, 
            TEXT("Unexpected end of buffer while parsing string."));
        str.Empty();
        return FALSE;
    }
    TRACE1("%s\n",(LPCTSTR) str);
    return TRUE;
}

BOOL COXParser::GetToken(COXToken& token, BOOL bWarnOnEOF /*=FALSE*/) 
{
    if (!RemoveWhiteSpace())
        return FALSE;

    token.SetType(COXToken::UNKNOWN);

    TCHAR ch = GetNextChar(1, bWarnOnEOF);
    if (!ch)
        return FALSE;

    // "<"
    if (ch == m_chStartDelim) 
    {
        ch = GetNextChar(1, bWarnOnEOF);
        if (!ch)
            return FALSE;

        // "<?"
        if (ch == m_chProcInstr)
        {
            token.SetType(COXToken::OPEN_PROCINSTR_BRACKET);
        }
        // "</"
        else if (ch == m_chTagEnd)
        {
            token.SetType(COXToken::OPEN_ENDTAG_BRACKET);
        }
        // "<!"
        else if (ch == m_chMarkup)
        {
            token.SetType(COXToken::OPEN_MARKUP_BRACKET);

            ch = GetNextChar(1, bWarnOnEOF);
            if (ch != m_chDash)
                UngetChar();
            else
            {
                ch = GetNextChar(1, bWarnOnEOF);
                if (ch != m_chDash)
                    UngetChar(2);
                else
                    token.SetType(COXToken::OPEN_COMMENT_BRACKET);
            }
        }
        else
        {
            UngetChar();
            token.SetType(COXToken::OPEN_TAG_BRACKET);
        }
    }

    // ">"
    else if (ch == m_chEndDelim)
    {
        token.SetType(COXToken::CLOSE_TAG_BRACKET);
    }

    // "/>"
    else if (ch == m_chTagEnd)
    {
        ch = GetNextChar(1, bWarnOnEOF);
        if (!ch)
            return FALSE;

        if (ch == m_chEndDelim)
            token.SetType(COXToken::CLOSE_EMPTYTAG_BRACKET);
        else
        {
            UngetChar(2);
            token.SetType(COXToken::STRING);
        }
    }

    // "="
    else if (ch == TEXT('='))
    {
        token.SetType(COXToken::EQUAL_SIGN);
    }
 
    // """
    else if (ch == TEXT('"'))
    {
        token.SetType(COXToken::QUOTE);
    }

    // "'"
    else if (ch == TEXT('\''))
    {
        token.SetType(COXToken::APOSTROPHE);
    }

    // "-->"
    else if (ch == m_chDash)
    {
        ch = GetNextChar(1, bWarnOnEOF);
        if (ch != m_chDash)
        {
            UngetChar(2);
            token.SetType(COXToken::STRING);
        }
        else
        {
            ch = GetNextChar(1, bWarnOnEOF);
            if (ch != m_chEndDelim)
            {
                UngetChar(3);
                token.SetType(COXToken::STRING);
            }
            else
                token.SetType(COXToken::CLOSE_COMMENT_BRACKET);
        }
    }

    // Plain ol' text
    else
    {
        UngetChar();
        token.SetType(COXToken::STRING);
    }

#if defined(_DEBUG) && 0
    USES_CONVERSION;
    LPCSTR strToken = NULL;
    switch (token.GetType())
    { 
        case COXToken::OPEN_PROCINSTR_BRACKET: 
			strToken = "OPEN_PROCINSTR_BRACKET";  
			break;
        case COXToken::OPEN_ENDTAG_BRACKET:    
			strToken = "OPEN_ENDTAG_BRACKET";     
			break;
        case COXToken::OPEN_COMMENT_BRACKET:   
			strToken = "OPEN_COMMENT_BRACKET";    
			break;
        case COXToken::OPEN_MARKUP_BRACKET:    
			strToken = "OPEN_MARKUP_BRACKET";     
			break;
        case COXToken::OPEN_TAG_BRACKET:       
			strToken = "OPEN_TAG_BRACKET";        
			break;
        case COXToken::CLOSE_TAG_BRACKET:      
			strToken = "CLOSE_TAG_BRACKET";       
			break;
        case COXToken::CLOSE_EMPTYTAG_BRACKET: 
			strToken = "CLOSE_EMPTYTAG_BRACKET";  
			break;
        case COXToken::EQUAL_SIGN:             
			strToken = "EQUAL_SIGN";              
			break;
        case COXToken::QUOTE:                  
			strToken = "QUOTE";                   
			break;
        case COXToken::APOSTROPHE:             
			strToken = "APOSTROPHE";              
			break;
        case COXToken::CLOSE_COMMENT_BRACKET:  
			strToken = "CLOSE_COMMENT_BRACKET";   
			break;
        case COXToken::STRING:                 
			strToken = "STRING";                  
			break;
        case COXToken::UNKNOWN:                
        default:
            ASSERT(FALSE);
    }
    TRACE3("COXParser: Found %s token at Line %d, Col %d.\n", 
          (LPCSTR) strToken, m_nLine, m_nColumn);
#endif

    return TRUE;
}

void COXParser::AddObjectToElement(COXParserElement* pElement, 
								   COXParserObject* pObject)
{
    if (pObject)           
        pElement->AddObject(pObject);
}

BOOL COXParser::ParseAttributes(COXParserElement* pElement)
{
    BOOL bResult = FALSE;
    COXAttribute* pAttribute = NULL;

    do
    {
        // What is next in line? If it's not a string value, 
		//it's not a name/value pair
        pAttribute = NULL;
        bResult = GetToken(m_Token, TRUE);
        if (!bResult || m_Token.GetType() != COXToken::STRING)
            break;

        // Create a new name Attribute
        pAttribute = new COXAttribute;
        if (!pAttribute)
        {
            ReportError(ERROR_OUT_OF_MEMORY,
                        TEXT("Unable to create new attribute (element %s)"), 
                        pElement->GetName());
            bResult = FALSE;
            break;
        }

        // Get the name of the name/value pair
        COXQuickString str;
        if (!GetNameToken(str))
        {
            bResult = FALSE;
            break;
        }
        pAttribute->SetName(str);

        // Search for a "=" sign next
        if (!GetToken(m_Token))
        {
            ReportError(ERROR_BAD_TOKEN, 
                        TEXT("Error while parsing attribute (element %s, name %s)."),
                        pElement->GetName(), pAttribute->GetName());
            bResult = FALSE;
            break;
        }
        if (m_Token.GetType() != COXToken::EQUAL_SIGN)
        {
            ReportError(ERROR_UNEXPECTED_TOKEN,
                        TEXT("Unexpected token while parsing attribute (element %s, name %s)."),
                        pElement->GetName(), pAttribute->GetName());
            bResult = FALSE;
            break;
        }

        // Should have a number, "string" or 'string' value next.
        if (!GetToken(m_Token))
        {
            ReportError(ERROR_BAD_TOKEN, 
                        TEXT("Error while parsing attribute (element %s, name %s)."),
                        pElement->GetName(), pAttribute->GetName());
            bResult = FALSE;
            break;
        }

        if (m_Token.GetType() == COXToken::STRING)
        {
            int nValue;
            if (!GetNumberToken(nValue))
            {
                bResult = FALSE;
                break;
            }
            pAttribute->SetValue(nValue);
        }
        else if (m_Token.GetType() == COXToken::QUOTE)
        {
            if ( !GetStringToken(str, TEXT('"')) ) 
            {
                bResult = FALSE;
                break;
            }
            pAttribute->SetValue(str);
        }
        else if (m_Token.GetType() == COXToken::APOSTROPHE)
        {
            if ( !GetStringToken(str, TEXT('\'')) ) 
            {
                bResult = FALSE;
                break;
            }
            pAttribute->SetValue(str);
        }
        else
        {
            ReportError(ERROR_UNEXPECTED_TOKEN, 
                        TEXT("Unexpected token while parsing attribute (element %s, name %s)."),
                        pElement->GetName(), pAttribute->GetName());
            bResult = FALSE;
            break;
        }

        if (bResult)
            pElement->AddAttribute(pAttribute);

    } while (bResult);

    if (bResult)
        return TRUE;
    else
    {
        delete pAttribute;
        return FALSE;
    }
}

COXParserElement* COXParser::ParseStartTag(COXParserElement* pParent, 
										   BOOL& bEmptyTag)
{
    // Get tag name
    if (!GetToken(m_Token))
    {
        ReportError(ERROR_END_OF_BUFFER, 
                    TEXT("Unexpected end of buffer while searching for tag name."));
        return NULL;
    }

    if (m_Token.GetType() != COXToken::STRING)
    {
        ReportError(ERROR_UNEXPECTED_TOKEN, 
			TEXT("Expecting tag name - none found."));
        return NULL;
    }

    // Get the name of the name/value pair
    COXQuickString str;
    if (!GetNameToken(str))
        return NULL;

    COXParserElement* pElement = new COXParserElement(pParent, str);
    if (!pElement)
    {
        ReportError(ERROR_OUT_OF_MEMORY, 
			TEXT("Unable to create new parser Element"));
        return NULL;
    }

    // Search through for attributes
    BOOL bResult = ParseAttributes(pElement);

    if (bResult)
    {
        bEmptyTag = FALSE;
        
        if (m_Token.GetType() == COXToken::CLOSE_TAG_BRACKET)
            /* do nothing */;
        else if (m_Token.GetType() == COXToken::CLOSE_EMPTYTAG_BRACKET)
            bEmptyTag = TRUE;
        else
        {
            bResult = FALSE;
            ReportError(ERROR_MISSING_END_BRACKET, 
                        TEXT("Closing bracket for start tag '%s' not found."), 
                        pElement->GetName());
        }
    }

    if (!bResult)
    {
        delete pElement;
        return NULL;
    }
    else
        return pElement;
}

BOOL COXParser::IsEndTagMissing(LPCTSTR szCurrentTag, LPCTSTR szNewTag, 
                              BOOL NewTagIsEndTag)
{
    UNUSED_ALWAYS(szCurrentTag);
    UNUSED_ALWAYS(szNewTag);
    UNUSED_ALWAYS(NewTagIsEndTag);

    return FALSE;
}

BOOL COXParser::IgnoreStartTag(COXParserElement* pElement, 
							   BOOL bEmptyTag)
{
    UNUSED_ALWAYS(pElement);
    UNUSED_ALWAYS(bEmptyTag);

    return FALSE;
}

BOOL COXParser::IgnoreEndTag(LPCTSTR szEndTag)
{
    UNUSED_ALWAYS(szEndTag);

    return FALSE;
}

BOOL COXParser::ParseEndTag(COXParserElement* pElement, 
							COXQuickString& strEndTag)
{
    UNUSED_ALWAYS(pElement);

    if (!GetToken(m_Token, TRUE))
    {
        ReportError(ERROR_BAD_TOKEN, 
                    TEXT("Unexpected end of buffer while parsing endtag."));
        return FALSE;
    }

    if (m_Token.GetType() != COXToken::STRING)
    {
        ReportError(ERROR_UNEXPECTED_TOKEN, TEXT("Missing end tag name."));
        return FALSE;
    }

    // Get the end tag name
    if (!GetNameToken(strEndTag))
        return FALSE;

    // peel off the final ">"
    if (!GetToken(m_Token) || m_Token.GetType() != COXToken::CLOSE_TAG_BRACKET)
    {
        ReportError(ERROR_BAD_TOKEN, 
                    TEXT("Missing end bracket while parsing end tag '%s'."),
                    (LPCTSTR) strEndTag);
        return FALSE;
    }

    return TRUE;
}

COXParserObject* COXParser::ParseProcessingInstruction(
								COXParserElement* pParent)
{
    COXQuickString str;
    str.SetLength(100);

    TCHAR ch = GetNextChar();
    while (ch)
    {
        TCHAR chNextChar = GetNextChar();
        if (!chNextChar)
        {
            ReportError(ERROR_END_OF_BUFFER, 
                       TEXT("Unexpected end of buffer while parsing processing instruction."));
            return NULL;
        }
        if (ch == m_chProcInstr && chNextChar == m_chEndDelim)
            ch = m_chNULL;
        else
        {
            str.Append(ch);
            ch = chNextChar;
        }
    }

    return new COXParserObject(pParent, COXParserObject::PROCINSTR, str);
}

COXParserObject* COXParser::ParseMarkup(COXParserElement* pParent)
{
    int nMarkupType = COXParserObject::MARKUP;

    COXQuickString str;
    str.SetLength(100);

    if (!_tcsncmp(m_pBuf, TEXT("DOCTYPE"), 7))
    {
        TCHAR ch = GetNextChar();
        // Parse initial bit before DTD info
        while (ch && ch != m_chEndDelim && ch != TEXT('['))
        {
            str.Append(ch);
            ch = GetNextChar();
        }
        // Parse DTD info
        if (ch == TEXT('['))
        {
			BOOL bOpened=FALSE;
			CString sEntity;
			LPTSTR pData=m_pBuf;
			TCHAR chSpace=TEXT(' ');
			TCHAR chTab=TEXT('\t');
			while (ch && ch != TEXT(']'))
            {
				if (!bOpened)
				{
					if (ch==TCHAR(0x3c))
					{
						bOpened=TRUE;
						pData=m_pBuf;
					}
				}
				else
				{
					if (ch==TCHAR(0x3e))
					{
						if (sEntity.GetLength()>8)
						{
							int nRet=CompareString(LOCALE_SYSTEM_DEFAULT,
								NORM_IGNORECASE,(LPCTSTR) sEntity,8,
								_T("!ENTITY "),8);
							
							if (CSTR_EQUAL==nRet)
							{
								//found entity
								sEntity=sEntity.Right(sEntity.GetLength()-8);
								CString sLiteral=sEntity;
								int nSpace=sEntity.Find(_T(" "));
								if (nSpace!=-1)
								{
									pData=pData+nSpace+8;
									while (*pData==chSpace || 
										*pData==chTab)
										pData++;
									sEntity=sEntity.Left(nSpace);
									sLiteral=sLiteral.Right(sLiteral.GetLength()-nSpace);
									sLiteral.TrimLeft();
									m_EntityTable.Add((LPCTSTR) sEntity,(DWORD) pData);
								}
							}
						}
						sEntity=_T("");
						bOpened=FALSE;
					}
					else
					{
						sEntity+=ch;
					}
				}
			ch = GetNextChar();
			}
        }
        // Parse any remaining left over stuff
        while (ch && ch != m_chEndDelim)
        {
            str.Append(ch);
            ch = GetNextChar();
        }
        if (!ch)
        {
            ReportError(ERROR_END_OF_BUFFER, 
                TEXT("Unexpected end of buffer while parsing DOCTYPE entry."));
            return NULL;
        }
    }
    else if (!_tcsncmp(m_pBuf, TEXT("[CDATA["), 7))
    {
        TCHAR ch = GetNextChar(7+1);
        while (ch)
        {
            TCHAR chNextChar1 = GetNextChar();
            TCHAR chNextChar2 = GetNextChar();
            
            if (!chNextChar1 || !chNextChar2)
            {
                ReportError(ERROR_END_OF_BUFFER, 
                    TEXT("Unexpected end of buffer while CDATA."));
                return NULL;
            }
            if (ch == TEXT(']') && chNextChar1 == TEXT(']') && chNextChar2 == m_chEndDelim)
                ch = m_chNULL;
            else
            {
                str.Append(ch);
                ch = chNextChar1;
                UngetChar();
            }
        }
        nMarkupType = COXParserObject::CDATA;
    }
    else
    {
        TCHAR ch = GetNextChar();
        while (ch && ch != m_chEndDelim)
        {
            str.Append(ch);
            ch = GetNextChar();
        }
        if (!ch)
        {
            ReportError(ERROR_END_OF_BUFFER, 
                TEXT("Unexpected end of buffer while parsing markup."));
            return NULL;
        }
    }

    return new COXParserObject(pParent, nMarkupType, str);
}

COXParserObject* COXParser::ParseComment(COXParserElement* pParent)
{
    COXQuickString str;
    str.SetLength(100);

    TCHAR ch = GetNextChar();
    while (ch)
    {
        TCHAR chNextChar1 = GetNextChar();
        TCHAR chNextChar2 = GetNextChar();

        if (!chNextChar1 || !chNextChar2)
        {
            ReportError(ERROR_END_OF_BUFFER, 
                       TEXT("Unexpected end of buffer while parsing comment."));
            return NULL;
        }
        if (ch == m_chDash && chNextChar1 == m_chDash && chNextChar2 == m_chEndDelim)
            ch = m_chNULL;
        else
        {
            str.Append(ch);
            ch = chNextChar1;
            UngetChar();
        }
    }

    return new COXParserObject(pParent, COXParserObject::COMMENT, str);
}

LPCTSTR COXParser::GetLiteralString(LPCTSTR szStr)
{
    static TCHAR szLiteral[2] = { 0,0 };
    szLiteral[0] = TCHAR(0);

    // Decode numeric character references
    if (szStr[0] == TEXT('#'))
    {
        BOOL bHexValue = ( szStr[1] == TEXT('x') || szStr[1] == TEXT('X') );
        LPCTSTR szNumber = (bHexValue)? szStr+2 : szStr+1;

        // Check it's valid
        for (LPCTSTR ptr = szNumber; *ptr; ptr++)
        {
            if (! ( (bHexValue)? _istxdigit(*ptr) : _istdigit(*ptr) ) )
                return NULL;
        }

		// TD v 7.2 change here to 4 chars - ref kvt
        TCHAR ch[4];
#if _MSC_VER >= 1400
		if (!_stscanf_s(szNumber, (bHexValue)? TEXT("%x") : TEXT("%d"), &ch, 4))
            return NULL;
#else
		if (!_stscanf(szNumber, (bHexValue)? TEXT("%x") : TEXT("%d"), &ch, 4))
            return NULL;
#endif
        szLiteral[0] = ch[0];

        return szLiteral;
    }

    // Decode character entity references
    DWORD dw;
    if (!m_EntityTable.Lookup(szStr, dw))
        return NULL;

    return (LPCTSTR) dw;
}

LPTSTR COXParser::GetCharEntity(TCHAR ch)
{
    static TCHAR szEntity[256];

    HASH_POS pos = m_EntityTable.GetStartPosition();
    while (pos)
    {
        LPCTSTR szName = NULL;
        DWORD dwData = 0;
        m_EntityTable.GetNextAssoc(pos, szName, dwData);

        LPCTSTR szLiteral = (LPCTSTR) dwData;

        if (ch == szLiteral[0] && szLiteral[1] == m_chNULL)
        {
            UGStr::stprintf(szEntity, 256, TEXT("&%s;"), szName);
            return szEntity;
        }
    }
    
    // unable to find - so just return the character as a string
    szEntity[0] = ch;
    szEntity[1] = TEXT('\0');

    return szEntity;
}

const COXQuickString COXParser::EncodeText(LPCTSTR szStr)
{
    COXQuickString str;

    if (!szStr || !szStr[0])
        return str;

    // An initial guess of the string size
    str.SetLength(_tcslen(szStr)+1);

    while (*szStr)
        str.AddString(GetCharEntity(*szStr++));

    return str;
}

COXParserObject* COXParser::ParseText(COXParserElement* pParent)
{
    COXQuickString str;
    str.SetLength(100);

    TCHAR ch = GetNextChar();
    while (ch && ch != m_chStartDelim)
    {
        // Process any entities found
        if (ch == m_chEsc)
        {
            // Move past the '&'
            ch = GetNextChar();

            COXQuickString strEntity;
            while (ch && ch != m_chStartDelim && ch != TEXT(';') && !_istspace(ch))
            {
                strEntity.Append(ch);
                ch = GetNextChar();
            }

            // Final char should be the ';'
            if (ch != TEXT(';'))
            {
                ReportError(ERROR_BAD_ENTITY, 
                            TEXT("Missing ';' on character entity '&%s'."),
                            (LPCTSTR) strEntity);
                str.Append(TEXT('&'));
                str += strEntity;
            }
            else
            {
                LPCTSTR szEntity = GetLiteralString(strEntity);
                if (szEntity)
                    InsertEntityValue(str,szEntity);
                else
                {
                    ReportError(ERROR_BAD_ENTITY, 
                                TEXT("Bad character entity '&%s;' encountered."),
                                (LPCTSTR) strEntity);
                    str.Append(TEXT('&'));
                    str += strEntity;
                    str.Append(TEXT(';'));
                }
                ch = GetNextChar();
            }

            // finished processing entity - ch will be the char directly
            // after the entity
        }
        else
        {
            str.Append(ch);
            ch = GetNextChar();
        }
    }

    if (!ch)
    {
        //ReportError(ERROR_END_OF_BUFFER, 
        //            TEXT("Unexpected end of buffer while parsing text."));
        //return NULL;
    }
    else
        UngetChar();

    str.Trim();

    return new COXParserObject(pParent, 
		COXParserObject::PLAINTEXT, str.GetString());
}


BOOL COXParser::ParseElement(COXParserElement *pElement, int nLevel)
{
    SAVEPOS pos;
    SaveBufferPos(pos);

    COXParserObject* pObject;
    BOOL bFoundMatchingEndTag;

    BOOL bContinue = TRUE;
    BOOL bResult = FALSE;

    do 
    {
        // The new object that will be added to this element
        pObject = NULL;
        bFoundMatchingEndTag = FALSE;

        // Get the first token of the next object. Only report errors for
        // elements that are at least a level above the root element
        bResult = GetToken(m_Token, FALSE);
        if (!bResult)
        {
            bContinue = FALSE;
            bResult = TRUE;
            break;
        }

        switch (m_Token.GetType())
        {
            case COXToken::OPEN_PROCINSTR_BRACKET:       // Processing instruction
                pObject = ParseProcessingInstruction(pElement);
                bResult = bContinue = (pObject != NULL);
                break;

            case COXToken::OPEN_MARKUP_BRACKET:          // Markup
                pObject = ParseMarkup(pElement);
                bResult = bContinue = (pObject != NULL);
                break;

            case COXToken::OPEN_COMMENT_BRACKET:          // Comment
                pObject = ParseComment(pElement);
                bResult = bContinue = (pObject != NULL);
                break;

            case COXToken::QUOTE:
            case COXToken::APOSTROPHE:
                UngetChar();
                // Fall through
            case COXToken::STRING:                        // Plain ol' text
			case COXToken::EQUAL_SIGN:    
				pObject = ParseText(pElement);
                bResult = bContinue = (pObject != NULL);
                break;

            case COXToken::OPEN_TAG_BRACKET:              // New element
                {
                    BOOL bEmptyTag = FALSE;
                    pObject = ParseStartTag(pElement, bEmptyTag);
                    if (!pObject)
                    {
                        bResult = bContinue = FALSE;
                        break;
                    }

                    // Allow derived classes to simply ignore this element. This is
                    // useful if you wish to treat tags as "toggles" (eg <b> in
                    // HTML), instead of actual XML nodes.
                    if (IgnoreStartTag((COXParserElement*) pObject, 
						bEmptyTag))
                    {
                        delete pObject;
                        pObject = NULL;
                        break;
                    }

                    // Allow derived classes to close off this element and start a 
                    // new one if there is a missing end tag.
                    // If we have a missing end tag, then we end processing of the
                    // current element, restore the buffer to the point just before
                    // this open tag, and return from this function
                    if (nLevel > 0 && 
                        IsEndTagMissing(pElement->GetName(), 
						pObject->GetText(), FALSE))
                    {
                        // Pretend we never saw this tag, and just quit as if
                        // we had reached an end tag
                        RestoreBufferPos(pos);

                        delete pObject;
                        pObject = NULL;

                        bFoundMatchingEndTag = TRUE;
                        bResult = TRUE;
                        bContinue = FALSE;
                        break;
                    }
                    
                    // If not an empty element, then try and parse the element.
                    if ( !bEmptyTag && 
                         !ParseElement((COXParserElement*) pObject, 
							nLevel+1) )
                    {
                        delete pObject;
                        pObject = NULL;

                        bResult = bContinue = FALSE;
                        break;
                    }

                    bResult = TRUE;
                }
                break;

            // An end tag should halt processing - but we allow some leniency here. 
            // We allow derived classes to decide when to cease processing this 
            // element, by either return FALSE in ParseEndTag, or setting 
            // bFoundMatchingEndTag to TRUE (useful for HTML...)
            case COXToken::OPEN_ENDTAG_BRACKET:           // </...
                {
                    // Get the end tag
                    COXQuickString strEndTag;
                    if (!ParseEndTag(pElement, strEndTag))
                    {
                        bResult = bContinue = FALSE;
                        break;
                    }

                    // Allow derived classes to simply ignore this tag. This is
                    // useful if you wish to treat tags as "toggles" (eg </b> in
                    // HTML), instead of actual XML nodes.
                    if (IgnoreEndTag(strEndTag))
                        break;

                    // If we are at top level, then issue a warning but continue
                    if (nLevel == 0)
                    {
                        ReportError(WARNING_UNEXPECTED_END_TAG, 
                                    TEXT("Unexpected end tag '%s'."), (LPCTSTR) strEndTag);
                        break;
                    }
                    
                    // If it matches the current element, then we finish processing here
                    if (strEndTag.Compare(pElement->GetName(), FALSE))
                    {
                        bFoundMatchingEndTag = TRUE;
                        bContinue = FALSE;
                        break;
                    }

                    if (IsEndTagMissing(pElement->GetName(), 
						strEndTag, TRUE))
                    {
                        // Pretend we never saw this tag, and just quit as if
                        // we had reached an end tag
                        RestoreBufferPos(pos);
                        bFoundMatchingEndTag = TRUE;
                        bContinue = FALSE;
                        break;
                    }

                    ReportError(ERROR_MISSING_END_TAG, 
                                TEXT("Expecting end tag '%s'. Found end tag '%s' instead."),
                                pElement->GetName(), (LPCTSTR) strEndTag);

                    if (m_bErrorOnMissingTag)
                        bContinue = bResult = FALSE;
                }
                break;

            default:
                ReportError(ERROR_UNEXPECTED_TOKEN, TEXT("Unexpected token."));
                //ReportError(ERROR_UNEXPECTED_TOKEN, TEXT("Unexpected token '%s'."), 
                //            m_Token.GetText());
                bResult = bContinue = FALSE;
        } 

        if (bResult)
            AddObjectToElement(pElement, pObject);

        SaveBufferPos(pos);

    } while (bContinue);

    // Error?
    if (!bResult)
    {
        delete pObject;
        return FALSE;
    }

    // Will only get this far if all tags for all elements have been closed, or
    // if the trailing end tags for elements are missing

    // If this is the root element, then there is no need to check for missing end tags
    if (nLevel == 0)
        return TRUE;
    else
    {
        // Derived classes may wish to allow missing end tags 
        if (!bFoundMatchingEndTag && !IsEndTagMissing(pElement->GetName(), NULL, TRUE))
        {
            ReportError(ERROR_MISSING_END_TAG, TEXT("Missing end tag '%s'."), 
                        pElement->GetText());
            return FALSE;
        }
        else 
            return TRUE;
    }
}

BOOL COXParser::ParseFile(LPCTSTR szFile)
{
    LPTSTR ptr = LoadFile(szFile);
    if (!ptr)
        return FALSE;

    BOOL bResult = Parse(ptr);

    GlobalFree(ptr);

    return bResult;
}

//////////////////////////////////////////////////////////////////////
// File handling routines
//////////////////////////////////////////////////////////////////////

BOOL COXParser::WriteFile(LPCTSTR szFile)
{
    if (!Root() || !Root()->NumObjects())
        return FALSE;

    HANDLE hFile = CreateFile(szFile, GENERIC_WRITE, 
                              0, NULL, CREATE_ALWAYS, 
                              FILE_ATTRIBUTE_NORMAL, 
                              NULL);

    if (INVALID_HANDLE_VALUE == hFile)
        return FALSE;

    for (int i = 0; i < Root()->NumObjects(); i++)
        WriteObject(hFile, Root()->Object(i), 0);

    CloseHandle(hFile);

    return TRUE;
}

BOOL COXParser::WriteTabs(HANDLE hFile, int nLevel)
{
    USES_CONVERSION;

    DWORD nCount;
    for (int i = 0; i < nLevel; i++)
    {
        if (!::WriteFile(hFile, T2A((LPTSTR) m_szTab), 
				_tcslen(m_szTab), &nCount, NULL))
            return FALSE;
    }
    return TRUE;
}

BOOL COXParser::WriteAttributes(HANDLE hFile, 
								COXParserElement* pElement)
{
    USES_CONVERSION;

    static char buffer[512];
    static DWORD nCount;

    for (int i = 0; i < pElement->NumAttributes(); i++)
    {
        COXAttribute* pAttribute = pElement->Attribute(i);
        if (!pAttribute) continue;
        
		UGStr::sprintf(buffer, 512, " %s=", T2A((LPTSTR) pAttribute->GetName()));
        if (!::WriteFile(hFile, buffer, strlen(buffer), &nCount, NULL))
            return FALSE;
        
        if (pAttribute->GetAttributeType() == COXAttribute::ATTR_STRING)
            UGStr::sprintf(buffer, 512, "\"%s\"", T2A((LPTSTR) pAttribute->GetStringValue()));
        else if (pAttribute->GetAttributeType() == COXAttribute::ATTR_INTEGER)
            UGStr::sprintf(buffer, 512, "%d", pAttribute->GetIntValue());
        else
            UGStr::sprintf(buffer, 512, "\"\"");
        
        if (!::WriteFile(hFile, buffer, strlen(buffer), &nCount, NULL))
            return FALSE;
    }

    return TRUE;
}

BOOL COXParser::WriteCData(HANDLE hFile, COXParserObject* pObject, 
						   int nLevel)
{   
    USES_CONVERSION;

    if (pObject->GetType() != COXParserObject::CDATA)
        return FALSE;

    if (!WriteTabs(hFile, nLevel))
        return FALSE;

    DWORD nCount;
    if (!::WriteFile(hFile, "<![CDATA[", 9, &nCount, NULL))
        return FALSE;

    if (!::WriteFile(hFile, T2A((LPTSTR)pObject->GetText()), 
                     _tcslen(pObject->GetText()), &nCount, NULL))
        return FALSE;

    if (!::WriteFile(hFile, "]]>\r\n", 5, &nCount, NULL))
        return FALSE;

    return TRUE;
}

BOOL COXParser::WriteComment(HANDLE hFile, COXParserObject* pObject, 
							 int nLevel)
{   
    USES_CONVERSION;

    if (pObject->GetType() != COXParserObject::COMMENT)
        return FALSE;

    if (!WriteTabs(hFile, nLevel))
        return FALSE;

    DWORD nCount;
    if (!::WriteFile(hFile, "<!--", 4, &nCount, NULL))
        return FALSE;

    if (!::WriteFile(hFile, T2A((LPTSTR)pObject->GetText()), 
                     _tcslen(pObject->GetText()), &nCount, NULL))
        return FALSE;

    if (!::WriteFile(hFile, "-->\r\n", 5, &nCount, NULL))
        return FALSE;

    return TRUE;
}

BOOL COXParser::WriteElement(HANDLE hFile, COXParserElement* pElement, 
							 int nLevel)
{   
    USES_CONVERSION;

    static char buffer[512];
    static DWORD nCount;

    if (pElement->GetType() != COXParserObject::ELEMENT)
        return FALSE;

    if (!WriteTabs(hFile, nLevel))
        return FALSE;

	UGStr::sprintf(buffer, 512, "<%s", T2A((LPTSTR)pElement->GetName()));
    if (!::WriteFile(hFile, buffer, strlen(buffer), &nCount, NULL))
        return FALSE;
    
    if (!WriteAttributes(hFile, pElement))
        return FALSE;
    
    if (pElement->NumObjects() == 0)   // empty tag
    {
        if (!::WriteFile(hFile, "/>\r\n", 4, &nCount, NULL))
            return FALSE;
    }
    else
    {
        if (!::WriteFile(hFile, ">\r\n", 3, &nCount, NULL))
            return FALSE;
        
        for (int i = 0; i < pElement->NumObjects(); i++)
            WriteObject(hFile, pElement->Object(i), nLevel+1);
        
        if (!WriteTabs(hFile, nLevel))
            return FALSE;
        
        UGStr::sprintf(buffer, 512, "</%s>\r\n", T2A((LPTSTR)pElement->GetName()));
        if (!::WriteFile(hFile, buffer, strlen(buffer), &nCount, NULL))
            return FALSE;
    }

    return TRUE;
}

BOOL COXParser::WriteMarkup(HANDLE hFile, COXParserObject* pObject, 
							int nLevel)
{   
    USES_CONVERSION;

    if (pObject->GetType() != COXParserObject::MARKUP)
        return FALSE;

    if (!WriteTabs(hFile, nLevel))
        return FALSE;

    DWORD nCount;
    if (!::WriteFile(hFile, "<!", 2, &nCount, NULL))
        return FALSE;

    if (!::WriteFile(hFile, T2A((LPTSTR)pObject->GetText()), 
                     _tcslen(pObject->GetText()), &nCount, NULL))
        return FALSE;

    if (!::WriteFile(hFile, ">\r\n", 3, &nCount, NULL))
        return FALSE;

    return TRUE;
}

BOOL COXParser::WriteProcessingInstruction(HANDLE hFile, 
							COXParserObject* pObject, int nLevel)
{   
    USES_CONVERSION;

    if (pObject->GetType() != COXParserObject::PROCINSTR)
        return FALSE;

    if (!WriteTabs(hFile, nLevel))
        return FALSE;

    DWORD nCount;
    if (!::WriteFile(hFile, "<?", 2, &nCount, NULL))
        return FALSE;

    if (!::WriteFile(hFile, T2A((LPTSTR)pObject->GetText()), 
                     _tcslen(pObject->GetText()), &nCount, NULL))
        return FALSE;

    if (!::WriteFile(hFile, "?>\r\n", 4, &nCount, NULL))
        return FALSE;

    return TRUE;
}

BOOL COXParser::WriteText(HANDLE hFile, COXParserObject* pObject, 
						  int nLevel)
{   
    USES_CONVERSION;

    if (pObject->GetType() != COXParserObject::PLAINTEXT &&
		pObject->GetType() != COXParserObject::RAWTEXT )
        return FALSE;

	COXQuickString str;
	if ( pObject->GetType() == COXParserObject::RAWTEXT )
		str = pObject->GetText();
	else
		str = EncodeText(pObject->GetText());

    str.Trim();
    if (str.IsEmpty())
        return FALSE;

    LPCTSTR ptr = str.GetString();
    COXQuickString strLine;
    LPCTSTR pStart;

    while (*ptr)
    {
        strLine.Empty();

        BOOL bContinue = TRUE;
        while (bContinue)
        {
            pStart = ptr;

            // Search for the next white space
            while (*ptr && !_istspace(*ptr)) ptr++;
            //if (*ptr) ptr++;

            int nCharsStepped = ptr - pStart + 1;

            // If we have less than a lines worth, or if we have more than a lines 
            // worth and have not added anything previously, add to the current line
            if ( strLine.GetLength() + nCharsStepped < m_nLineLength ||
                 strLine.IsEmpty() )
            {
                strLine.AddString(pStart, nCharsStepped);

                // If we've still got room on the line, and we are not at EOF or EOL
                // then continue on
                bContinue = (strLine.GetLength() < m_nLineLength && 
                             *ptr && *ptr != TEXT('\n'));

                if (*ptr) ptr++;

                bContinue = (bContinue && *ptr);
            }
            else
            {
                // We could not add this section - so go back to the start of it
                // and print out what we already have.
                ptr = pStart;
                bContinue = FALSE;
            }
        }
            
        if (!WriteTabs(hFile, nLevel))
            return FALSE;

        DWORD nCount;
        if (!::WriteFile(hFile, T2A((LPTSTR)strLine.GetString()), 
                         strLine.GetLength(), &nCount, NULL))
            return FALSE;

        if (!::WriteFile(hFile, "\r\n", 2, &nCount, NULL))
            return FALSE;   
    }

    return TRUE;
}

BOOL COXParser::WriteObject(HANDLE hFile, COXParserObject* pObject, 
							int nLevel)
{
    BOOL bResult = FALSE;
    switch (pObject->GetType())
    {
        case COXParserObject::CDATA:
            bResult = WriteCData(hFile, pObject, nLevel);
            break;

       case COXParserObject::COMMENT:
            bResult = WriteComment(hFile, pObject, nLevel);
            break;

        case COXParserObject::ELEMENT:
            bResult = WriteElement(hFile, (COXParserElement*) pObject, 
				nLevel);
            break;

        case COXParserObject::MARKUP:
            bResult = WriteMarkup(hFile, pObject, nLevel);
            break;

        case COXParserObject::PLAINTEXT:
		case COXParserObject::RAWTEXT:
            bResult = WriteText(hFile, pObject, nLevel);
            break;

        case COXParserObject::PROCINSTR:
            bResult = WriteProcessingInstruction(hFile, pObject, nLevel);
            break;

        default: /*nothing*/;
    }

    return bResult;
}

LPTSTR COXParser::LoadFile(LPCTSTR szFile)
{
    HANDLE hFile = CreateFile(szFile, GENERIC_READ, 
                              0, NULL, OPEN_EXISTING, 
                              FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS, 
                              NULL);

    if (INVALID_HANDLE_VALUE == hFile)
        return NULL;

    DWORD size = GetFileSize(hFile, NULL);
    if (-1 == size) 
    {
        CloseHandle(hFile);
        return NULL;
    }

    LPSTR ptr = (LPSTR) ::GlobalAlloc(GMEM_FIXED, size + 1);

    DWORD nCount;
    if (!ReadFile(hFile, ptr, size, &nCount, NULL))
    {
        CloseHandle(hFile);
        return NULL;
    }
    CloseHandle(hFile);

    ptr[nCount] = '\0';

#ifdef _UNICODE
    LPTSTR tptr = (LPTSTR) ::GlobalAlloc(GMEM_FIXED, 
		(nCount + 1) * sizeof(TCHAR));
	UGStr::mbstowcs(tptr, nCount+1, ptr, nCount);
    ::GlobalFree(ptr);

    tptr[nCount] = m_chNULL;

    return tptr;
#else
    return ptr;
#endif
}

//////////////////////////////////////////////////////////////////////
// Error handling routines
//////////////////////////////////////////////////////////////////////

BOOL COXParser::ReportError(UINT nErrorCode, LPCTSTR fmt, ...)
{
    va_list args;
    TCHAR buffer[512];

    va_start(args, fmt);
#if _MSC_VER >= 1400
    _vstprintf_s(buffer, 512, fmt, args);
#else
    _vstprintf(buffer, fmt, args);
#endif
    va_end(args);

    if (m_pfnErrorFn)
        return (*m_pfnErrorFn)(nErrorCode, buffer, m_nLine, 
			m_nColumn, m_dwErrData);
    else
        return DefErrorHandler(nErrorCode, buffer, m_nLine, 
			m_nColumn, m_dwErrData);
}

BOOL COXParser::DefErrorHandler(UINT nErrorCode, LPCTSTR szError, 
								int nLine, int nColumn, 
								DWORD dwData)
{
    UNUSED_ALWAYS(dwData);
    UNUSED(nErrorCode);
    UNUSED(szError);
    UNUSED(nLine);
    UNUSED(nColumn);

#ifdef _DEBUG
#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning(disable:4127)  // conditional expression is constant
    if (ERROR_FIRST < nErrorCode && nErrorCode < ERROR_LAST)
    {
	    _RPT4(_CRT_WARN, "COXParser: Error (%d) at line %d, col %d: %s\n",
              nErrorCode, nLine, nColumn, szError);
    }
    else if (WARNING_FIRST < nErrorCode && nErrorCode < WARNING_LAST)
    {
	    _RPT4(_CRT_WARN, "COXParser: Warning (%d) at line %d, col %d: %s\n",
              nErrorCode, nLine, nColumn, szError);
    }
    else
	    _RPT4(_CRT_WARN, "COXParser: line %d, col %d: %s\n",
              nErrorCode, nLine, nColumn, szError);
#if _MSC_VER >= 1200
#pragma warning(pop)
#else
#pragma warning(default:4127)
#endif
#endif

    return FALSE;
}

LPCTSTR COXParser::TranslateErrorCode(int nErrorCode)
{
    switch (nErrorCode)
    {
        case ERROR_NULL_BUFFER:          
			return TEXT("NULL buffer passed in");
        case ERROR_END_OF_BUFFER:        
			return TEXT("Unexpected end of buffer");
        case ERROR_OUT_OF_MEMORY:        
			return TEXT("Out of memory");
        case ERROR_BAD_TOKEN:            
			return TEXT("Unable to retrieve a token");
        case ERROR_ILLEGAL_CHAR:         
			return TEXT("Illegal characters encountered in token");
        case ERROR_UNEXPECTED_TOKEN:     
			return TEXT("Unexpected token type");
        case ERROR_MISSING_END_TAG:      
			return TEXT("Missing end tag");
        case ERROR_BAD_ENTITY:           
			return TEXT("Bad entity string");
        case ERROR_BAD_INTEGER:          
			return TEXT("Bad integer value");
        case ERROR_MISSING_END_BRACKET:  
			return TEXT("Missing end bracket in tag");
        case WARNING_UNEXPECTED_END_TAG: 
			return TEXT("Unexpected end tag");

        default:
            return TEXT("Unknown Error");
    }
}


void COXParser::InsertEntityValue(COXQuickString& str, 
								  LPCTSTR lpszEntity)
{
	LPCTSTR lpszSeek=lpszEntity;
	TCHAR chSpace=TEXT(' ');
	while(*(lpszSeek) && *(lpszSeek)!=m_chEndDelim && *(lpszSeek)!=chSpace)
	{
		str.Append(*lpszSeek);
		lpszSeek++;
	}
}
