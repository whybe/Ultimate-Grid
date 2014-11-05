// QuickString.cpp: implementation of the COXQuickString class.
//
//////////////////////////////////////////////////////////////////////
// Product Version: 7.51


#include "stdafx.h"
#include "OXQuickString.h"

#include "UGStrOp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COXQuickString::COXQuickString()
{
    Init();
}

COXQuickString::COXQuickString(LPCTSTR szText)
{
    Init();
    SetString(szText);
}

COXQuickString::COXQuickString(const COXQuickString& str)
{
    Init();
    SetString(str.GetString());
}

COXQuickString::~COXQuickString()
{
    Empty();
}

//////////////////////////////////////////////////////////////////////
// Operations
//////////////////////////////////////////////////////////////////////

void COXQuickString::Empty()
{
    delete [] m_szText;
    
    Init();
}

void COXQuickString::Init()
{
    m_szText      = NULL;
    m_nBufferSize = 0;
    m_nLength     = 0;
    m_nGrowBy     = 10;
}

LPTSTR COXQuickString::AllocBuffer(UINT nBufferSize)
{
    return new TCHAR[nBufferSize];
}

BOOL COXQuickString::IsEmpty() const
{
    return (!m_szText || !(*m_szText));
}

BOOL COXQuickString::SetString(LPCTSTR szText)
{
    // We do a fresh memory allocation when setting the string.
    Empty();

    if (!szText)
        return TRUE;

    m_nLength = _tcslen(szText);
    m_nBufferSize = m_nLength + 1;

    m_szText = AllocBuffer(m_nBufferSize);
    if (!m_szText)
        return FALSE;

	UGStr::tcscpy(m_szText, m_nBufferSize, szText);

    return TRUE;
}

BOOL COXQuickString::SetString(LPCTSTR szText, int nCount)
{
    // We do a fresh memory allocation when setting the string.
    Empty();

    if (!szText || nCount <= 0)
        return TRUE;

    m_nLength = min(_tcslen(szText), (UINT)nCount);
    m_nBufferSize = m_nLength + 1;

    m_szText = AllocBuffer(m_nBufferSize);
    if (!m_szText)
        return FALSE;

	UGStr::tcsncpy(m_szText, m_nBufferSize, szText, m_nLength+1);
    m_szText[m_nLength] = TEXT('\0');

    return TRUE;
}

BOOL COXQuickString::Append(TCHAR ch)
{
    UINT nLength = m_nLength + 1;

    // We reuse memory (if possible) when adding to the string.
    if (nLength+1 > m_nBufferSize)
    {   
        LPTSTR tmp = AllocBuffer(nLength+m_nGrowBy);
        if (!tmp)
            return FALSE;
        tmp[0] = TEXT('\0');
        
        m_nBufferSize = m_nLength + m_nGrowBy;
        
        if (m_szText)
        {
			UGStr::tcscpy(tmp, nLength + m_nGrowBy, m_szText);
            delete [] m_szText;
        }
        m_szText = tmp;
    }

    m_szText[m_nLength++] = ch;
    m_szText[m_nLength] = TEXT('\0');

    return TRUE;
}

BOOL COXQuickString::AddString(LPCTSTR szText)
{
    if (!szText)
        return FALSE;

    UINT nLength = m_nLength + _tcslen(szText);

    // We reuse memory (if possible) when adding to the string.
    if (nLength+1 > m_nBufferSize)
    {   
        LPTSTR tmp = AllocBuffer(nLength+1);
        if (!tmp)
            return FALSE;
        tmp[0] = TEXT('\0');
        
        m_nBufferSize = m_nLength + 1;
        
        if (m_szText)
        {
            UGStr::tcscpy(tmp, nLength + 1, m_szText);
            delete [] m_szText;
        }
        m_szText = tmp;
    }

	UGStr::tcscat(m_szText, nLength+1, szText);
    m_nLength = nLength;

    return TRUE;
}

BOOL COXQuickString::AddString(LPCTSTR szText, int nCount)
{
    if (!szText)
        return FALSE;

    UINT nLength = m_nLength + min(_tcslen(szText), (UINT)nCount);

    // We reuse memory (if possible) when adding to the string.
    if (nLength+1 > m_nBufferSize)
    {
        LPTSTR tmp = AllocBuffer(nLength+1);
        if (!tmp)
            return FALSE;
        tmp[0] = TEXT('\0');

        m_nBufferSize = nLength + 1;

        if (m_szText)
        {
			UGStr::tcscpy(tmp, nLength + 1, m_szText);
            delete [] m_szText;
        }
        m_szText = tmp;
    }

	UGStr::tcsncat(m_szText, nLength+1, szText, nCount);
    m_szText[nLength] = TEXT('\0');
    m_nLength     = nLength;

    return TRUE;
}

LPCTSTR COXQuickString::GetString() const
{
    static const char chNull = TEXT('\0');

    if (IsEmpty())
        return (LPCTSTR)&chNull;
    else
        return (LPCTSTR)m_szText;
}

UINT COXQuickString::GetLength() const
{
#ifdef _DEBUG
    UINT nLength = m_szText? _tcslen(m_szText) : 0;
    ASSERT(nLength == m_nLength);
#endif
    return m_nLength;
}

BOOL COXQuickString::SetLength(UINT nLength) 
{
    // Do easy cases and return immediately if no problems
    if (nLength == m_nBufferSize)
        return TRUE;

    if (!nLength)
    {
        Empty();
        return TRUE;
    }

    if (nLength < m_nBufferSize)
    {
        m_szText[nLength] = TEXT('\0');
        m_nLength = min(m_nLength, nLength);
        return TRUE;
    }

    // Memory (re)allocation needed

    LPTSTR pBuf = AllocBuffer(nLength);
    if (!pBuf)
        return FALSE;

    m_nBufferSize = nLength;
    if (m_szText) 
    {
        UGStr::tcscpy(pBuf, nLength, m_szText);
        delete [] m_szText;
    }
    m_szText = pBuf;
    m_szText[m_nLength] = TEXT('\0');

    return TRUE;
}

void COXQuickString::SetGrowBy(UINT nGrowBy)
{
    m_nGrowBy = nGrowBy;
}

UINT COXQuickString::GetGrowBy() const
{
    return m_nGrowBy;
}

BOOL COXQuickString::Compare(LPCTSTR szText, BOOL bCaseSensitive /*=TRUE*/)
{
    if (!szText || IsEmpty())
        return FALSE;

    BOOL bSame = FALSE;
    if (!bCaseSensitive)
        bSame = (_tcsicmp(m_szText, szText) == 0);
    else
        bSame = (_tcscmp(m_szText, szText) == 0);

    return bSame;
}

BOOL COXQuickString::operator==(LPCTSTR szText)
{
    return Compare(szText, TRUE);
}

BOOL COXQuickString::operator==(COXQuickString& str)
{
    return Compare(str.GetString(), TRUE);
}

BOOL COXQuickString::operator!=(LPCTSTR szText)
{
    return !Compare(szText, TRUE);
}

BOOL COXQuickString::operator!=(COXQuickString& str)
{
    return !Compare(str.GetString(), TRUE);
}

COXQuickString::operator LPCTSTR() const
{
    return GetString();
}

void COXQuickString::operator=(LPCTSTR szText)
{
    SetString(szText);
}

void COXQuickString::operator=(COXQuickString& str)
{
    if (this == &str) 
        return;

    SetString(str.GetString());
}

void COXQuickString::operator+=(LPCTSTR szText)
{
    AddString(szText);
}

void COXQuickString::operator+=(COXQuickString& str)
{
    AddString(str.GetString());
}

BOOL COXQuickString::Strip()
{
    const TCHAR chNBSP = TEXT(' ');  // This is character 160, NOT character 32

    if (IsEmpty())
        return TRUE;

    int nLength = 0;
    LPTSTR ptr = m_szText;
    if (!ptr || !ptr[0])
        return FALSE;

    // Remove leading whitespace (keep NBSP characters)
    while (_istspace(*ptr) && *ptr != chNBSP)
    {
        ptr++;
        nLength++;
    }

    // Find how many "good" characters we have (good = are not consequetive spaces)
    LPTSTR pStart = ptr;
    int nGoodChars = 0;
    while (*ptr)
    {
        nLength++;
        if (!_istspace(*ptr) || *ptr == chNBSP)
            nGoodChars++;
        else
        {
            if (!_istspace(*(ptr+1)) || *ptr == chNBSP)
                nGoodChars++;
        }
        ptr++;
    }

    // Copy over these "good" chars over to a new buffer
    LPTSTR szNewString = AllocBuffer(nGoodChars+1);
    if (!szNewString)
        return FALSE;

    ptr = pStart;
    int nCount = 0;
    while (*ptr && nCount < nGoodChars)
    {
        if (!_istspace(*ptr) || *ptr == chNBSP)
            szNewString[nCount++] = *ptr;
        else
        {
            if ( (!_istspace(*(ptr+1)) || *ptr == chNBSP) && *(ptr+1))
                szNewString[nCount++] = TEXT(' ');
        }
        ptr++;
    }

    delete [] m_szText;

    // Return the new string
    szNewString[nCount] = TEXT('\0');

    m_szText = szNewString;
    m_nLength = nCount;
    m_nBufferSize = nGoodChars+1;

    return TRUE;
}

BOOL COXQuickString::TrimRight()
{
    if (IsEmpty())
        return TRUE;

    LPTSTR ptr = m_szText+m_nLength-1;

    while (_istspace(*ptr) && ptr >= m_szText)
        ptr--;

    m_nLength = ptr - m_szText + 1;
    m_szText[m_nLength] = TEXT('\0');

    return TRUE;
}

BOOL COXQuickString::TrimLeft()
{
    if (IsEmpty())
        return TRUE;

    LPTSTR ptr = m_szText;
    while (ptr - m_szText < (int)m_nLength && _istspace(*ptr))
        ptr++;

    if (ptr != m_szText)
    {
        int nLength = m_nLength-(ptr-m_szText);
        LPTSTR szNewString = AllocBuffer(nLength+1);
        if (!szNewString)
            return FALSE;

        UGStr::tcscpy(szNewString, nLength-1, m_szText);
        szNewString[nLength] = TEXT('\0');
        m_nLength = nLength;
        m_nBufferSize = nLength+1;

        delete [] m_szText;
        m_szText = szNewString;
    }

    return TRUE;
}

BOOL COXQuickString::Trim()
{
    return (TrimRight() && TrimLeft());
}

UINT COXQuickString::NumTokens(TCHAR chDelimiter)
{
    if (IsEmpty())
        return 0;

    int nNumTokens = 1;
    for (LPCTSTR ptr = m_szText; *ptr; ptr++)
    {
        if (*ptr == chDelimiter)
            nNumTokens++;
    }

    return nNumTokens;
}

const COXQuickString COXQuickString::GetToken(int nIndex, TCHAR chDelimiter) const
{
    COXQuickString strReturn;

    if (IsEmpty())
        return strReturn;

    LPCTSTR pstrStart  = m_szText;
    LPCTSTR pstrBuffer = pstrStart;

    int nCurrent = 0;
    int nStart = 0;
    int nEnd = 0;
    int nOldStart = 0;

    // Search for token
    while (nCurrent <= nIndex && *pstrBuffer != TEXT('\0'))
    {
        if (*pstrBuffer == chDelimiter)
        {
            nOldStart = nStart;
            nStart = nEnd+1;
            nCurrent++;
        }
        nEnd++;
        pstrBuffer++;
    }

    // May have reached the end of the string
    if (*pstrBuffer == TEXT('\0'))
    {
        nOldStart = nStart;
        nEnd++;
    }

    if (nCurrent < nIndex) 
    {
        //TRACE1("Warning: GetStringField - Couldn't find field %d.\n", nIndex);
        return strReturn;
    }

    strReturn.SetString(m_szText+nOldStart, nEnd-nOldStart-1);

    return strReturn;
}