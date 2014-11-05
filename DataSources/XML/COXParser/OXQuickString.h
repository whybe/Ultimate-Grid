// QuickString.h: interface for the COXQuickString class.
//
// This is a very simple CString replacement class. Limited heap
// reuse is offered to improve performance.
//
//////////////////////////////////////////////////////////////////////

// Product Version: 7.51


#if !defined(AFX_QUICKSTRING_H__61FEC104_12FC_11D3_AA06_A8978A000000__INCLUDED_)
#define AFX_QUICKSTRING_H__61FEC104_12FC_11D3_AA06_A8978A000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <tchar.h>

#ifndef ASSERT
#ifdef _DEBUG
    #include <assert.h>
    #define ASSERT(expr)	assert(expr)
#else
    #define ASSERT(expr)
#endif
#endif


// Some ATL A2T and T2A replacement plugins. These are defined as inlines
// (instead of static QS member functions) so QuickString can be used inside
// a DLL, and the A2T helpers used without the need for a _declspec(dllexport)

#ifndef USES_CONVERSION

#ifdef _UNICODE
#include <malloc.h>

// Converts a TCHAR string to a CHAR string
inline LPSTR QuickString_T2Ahelper(LPSTR szAscii, LPCWSTR szWide, int nBufferLength)
{
    ASSERT(szWide && szAscii);
    ::WideCharToMultiByte(0,0, szWide,-1, szAscii, nBufferLength, NULL, NULL);
    return szAscii;
}

// Converts a CHAR string to a TCHAR string
inline LPCWSTR COXQuickString_A2Thelper(LPWSTR szWide, LPCSTR szAscii, int nBufferLength)
{
    ASSERT(szWide && szAscii);
    ::MultiByteToWideChar(0,0, szAscii,-1, szWide, nBufferLength);
    return szWide;
}

#define USES_CONVERSION int _nConvertSize=0; _nConvertSize;

#   define T2A(szWide)                        \
      (!szWide? NULL : _nConvertSize = (lstrlenW(szWide)+1)*2, \
       QuickString_T2Ahelper((LPSTR) _alloca(_nConvertSize), szWide, _nConvertSize))
#   define A2T(szAscii)                        \
      (!szAscii? NULL : _nConvertSize = (lstrlenA(szAscii)+1)*2, \
       COXQuickString_A2Thelper((LPTSTR)_alloca(_nConvertSize), szAscii, _nConvertSize))

#else   // No UNICODE, so no need for conversions
#   define USES_CONVERSION
#   define T2A(szWide)  szWide
#   define A2T(szAscii) szAscii
#endif

#endif // USES_CONVERSION

class COXQuickString  
{
// Construction/Destruction
public:
	COXQuickString();
    COXQuickString::COXQuickString(LPCTSTR szText);
    COXQuickString::COXQuickString(const COXQuickString& str);
    virtual ~COXQuickString();

// Operations
public:

	// --- In  : szText - the new string to be copied
	// --- Out :
	// --- Returns : TRUE on success
	// --- Effect : Allocates memory for a new string and copies over the contents of
	//              szValue
    BOOL SetString(LPCTSTR szText);


	// --- In  : szText - the new string to be copied
	//           nCount - the maximum number of characters to copy over
	// --- Out :
	// --- Returns : TRUE on success
	// --- Effect : Allocates memory for a new string and copies over the contents of
	//              szValue
   BOOL SetString(LPCTSTR szText, int nCount);

    // --- In  : ch - the character to be added to the current string
	// --- Out :
	// --- Returns : TRUE on success
	// --- Effect : Appends a character onto the end of the string
	//              m_szText may be changed to point to new memory
	BOOL Append(TCHAR ch);

    // --- In  : szText - the string to be added to the current string
	// --- Out :
	// --- Returns : TRUE on success
	// --- Effect : Concatenates the contents of szText onto the end of the string
	//              m_szText may be changed to point to new memory
	BOOL AddString(LPCTSTR szText);
    
	// --- In  : szText - the string to be added to the current string
	//           nCount - the maximum number of characters to add
	// --- Out :
	// --- Returns : TRUE on success
	// --- Effect : Concatenates the contents of szText onto the end of the string
	//              m_szText may be changed to point to new memory. Only up to nCount
	//              characters will be added
	BOOL AddString(LPCTSTR szText, int nCount);
    
	// --- In  : 
	// --- Out :
	// --- Returns : A pointer to the string buffer
	// --- Effect : 
	LPCTSTR GetString() const;

	// --- In  : 
	// --- Out :
	// --- Returns : 
	// --- Effect : Releases alll memory associated with this object
    void Empty();

	// --- In  : 
	// --- Out :
	// --- Returns : TRUE on success, FALSE otherwise
	// --- Effect : Strips out multiple spaces and end of line\tab characters.
	//              m_szText may be changed due to reallocation of memory
    BOOL Strip();

    // --- In  : 
	// --- Out :
	// --- Returns : TRUE on success, FALSE otherwise
	// --- Effect : Trims excess whitespace off the end of the string
	BOOL TrimRight();

	// --- In  : 
	// --- Out :
	// --- Returns : TRUE on success, FALSE otherwise
	// --- Effect : Trims excess whitespace from the beginning and end of the string
    BOOL Trim();

	// --- In  : 
	// --- Out :
	// --- Returns : TRUE on success, FALSE otherwise
	// --- Effect : Trims excess whitespace from the beginning of the string
    BOOL TrimLeft();

	// --- In  : ch - token delimiter
	// --- Out :
	// --- Returns : The number of tokens in this string
	// --- Effect : Returns the number of tokens in the string. The token separator
	//              is given by chDelimiter.
    UINT NumTokens(TCHAR chDelimiter);

	// --- In  : nIndex - Token index to return
	//           chDelimiter - Token delimiter
	// --- Out : 
	// --- Returns : Returns a pointer to the required Token, or NULL if none found
	// --- Effect : Returns the indicated Token from the string
    const COXQuickString GetToken(int nIndex, TCHAR chDelimiter) const;

// Attributes
public:
	// --- In  : 
	// --- Out :
	// --- Returns : TRUE if string is empty
	// --- Effect : 
    BOOL IsEmpty() const;
 
	// --- In  : 
	// --- Out :
	// --- Returns : The length of the string
	// --- Effect : 
	UINT GetLength() const;

	// --- In  : nLength - the new length of the string
	// --- Out :
	// --- Returns : TRUE if successful
	// --- Effect : Sets the minimum length of the string to nLength. If the current 
	//              length is greater than nLength, then a NULL char is inserted to
	//              chop off the end of the string, but no memory is free'd. If nLength
	//              is greater, then the memory is reallocated.
    BOOL SetLength(UINT nLength);

	// --- In  : nGrowBy - the amount to grow the buffer on each overflow
	// --- Out :
	// --- Returns : TRUE if the strings are equal
	// --- Effect : Sets the amount to grow the buffer on each overflow. This is only used in the
	//              Append() function.
    void SetGrowBy(UINT nGrowBy);
 
	// --- In  : 
	// --- Out :
	// --- Returns : The amount that the buffer will be grown each time it overflows (Append() only)
	// --- Effect : 
	UINT GetGrowBy() const;

    // --- In  : szText - the string to compare this string with
	//           bCaseSensitive - whether or not the comparison is case sensitive
	// --- Out :
	// --- Returns : TRUE if the strings are equal
	// --- Effect : Compares this string with the supplied string
	BOOL Compare(LPCTSTR szText, BOOL bCaseSensitive = TRUE);

// Operators
public:

	// --- In  : szText - the new string to be copied
	// --- Out :
	// --- Returns : 
	// --- Effect : Concatenates the contents of szText onto the end of the string
	//              m_szText may be changed to point to new memory
    void operator+=(LPCTSTR szText);
 
	// --- In  : str - the new string to be copied
	// --- Out :
	// --- Returns : 
	// --- Effect : Concatenates the contents of str onto the end of the string
	//              m_szText may be changed to point to new memory
	void operator+=(COXQuickString& str);


	// --- In  : szValue - the new string to be copied
	// --- Out :
	// --- Returns : 
	// --- Effect : Allocates memory for a new string and copies over the contents of
	//              szValue
    void operator=(LPCTSTR szText);

	// --- In  : str - the new string to be copied
	// --- Out :
	// --- Returns : 
	// --- Effect : Allocates memory for a new string and copies over the contents of
	//              str
    void operator=(COXQuickString& str);

	// --- In  : szText - the string to compare this string with
	// --- Out :
	// --- Returns : TRUE if the strings are equal. The comparison is case sensitive
	// --- Effect : Compares this string with the supplied string
    BOOL operator==(LPCTSTR szText);

	// --- In  : str - the string to compare this string with
	// --- Out :
	// --- Returns : TRUE if the strings are equal. The comparison is case sensitive
	// --- Effect : Compares this string with the supplied string
    BOOL operator==(COXQuickString& str);

	// --- In  : szText - the string to compare this string with
	// --- Out :
	// --- Returns : TRUE if the strings are equal. The comparison is case sensitive
	// --- Effect : Compares this string with the supplied string
    BOOL operator!=(LPCTSTR szText);

	// --- In  : str - the string to compare this string with
	// --- Out :
	// --- Returns : TRUE if the strings are equal. The comparison is case sensitive
	// --- Effect : Compares this string with the supplied string
    BOOL operator!=(COXQuickString& str);

	// --- In  : 
	// --- Out :
	// --- Returns : A pointer to the string buffer
	// --- Effect : 
    operator LPCTSTR() const;

protected:

	// --- In  : nBufferSize - size of the buffer to allocate.
	// --- Out :
	// --- Returns : A TCHAR pointer to the allocated memory block
	// --- Effect : Allocates memory
    LPTSTR AllocBuffer(UINT nBufferSize);

    // --- In  : 
	// --- Out :
	// --- Returns : 
	// --- Effect : Initialises member variables to a known state
	void   Init();

protected:
    LPTSTR m_szText;        // Pointer to text buffer
    UINT   m_nBufferSize;   // Size of this text buffer
    UINT   m_nLength;       // Length of string in buffer
    UINT   m_nGrowBy;       // Amount to grow buffer each step (only used by Append)
};

#endif // !defined(AFX_QUICKSTRING_H__61FEC104_12FC_11D3_AA06_A8978A000000__INCLUDED_)
