// HashTable.h: interface for the COXHashTable class.
//
// COXHashTable is a VERY simple hash table implementation.
//
//////////////////////////////////////////////////////////////////////
// Product Version: 7.51


#if !defined(AFX_HASHTABLE_H__30445BB2_1885_11D3_AA0C_F0E6D1000000__INCLUDED_)
#define AFX_HASHTABLE_H__30445BB2_1885_11D3_AA0C_F0E6D1000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <tchar.h>      // for TCHAR stuff and portable character mappings

// Each entry in the hash table is one of these...
struct HashNode
{
    HashNode();
    ~HashNode();

    HashNode* pNext;
    LPTSTR    szName;
    DWORD     dwData;
    UINT      nHashValue;
};

// For iteration
typedef HashNode* HASH_POS;
#define HASHTABLE_START_POS  ((HASH_POS)-1L)

// class wrapper for the hash table
class COXHashTable  
{
// Construction/Destruction
public:
	COXHashTable();
	COXHashTable(int nHashTableSize);
	virtual ~COXHashTable();

// Attributes
public:
    // Sets whether or not keys are treated as case sensitive
	void SetCaseSensitive(BOOL bCase);

	// Returns whether or not keys are treated as case sensitive
    BOOL GetCaseSensitive();

// Operations
public:
    // Clears contents of hash table
	void RemoveAll();

    // Initialises the hash table to the desired size. A Prime number is good. 
	// Size should be 20% bigger than largest  anticipated data set    
	BOOL InitHashTable(UINT nHashSize);

    // Returns the size of the hash table
	UINT GetHashTableSize() const;

	// Stores the given data (dwData) in the hash table using the supplied string (sz)
	// as the hash key. Returns TRUE on success.
    BOOL Add(LPCTSTR sz, DWORD dwData);
 
	// Looks up the data entry using the string 'sz' as the key, and returns the
	// stored data in the dwData reference. Returns TRUE on success.
	BOOL Lookup(LPCTSTR sz, DWORD& dwData) const;
    
	// Stores the given data (dwData) in the hash table using the supplied string (sz)
	// as the hash key
	BOOL Remove(LPCTSTR sz);

    HASH_POS GetStartPosition() const;
    void GetNextAssoc(HASH_POS& pos, LPCTSTR& sz, DWORD& dwData) const;

// Implementation
protected:
    BOOL      CommonConstruct(int nHashTableSize);
    
	// Produces a hash value for a given string
	UINT      Hash(LPCTSTR sz) const;
    
	// Looks up the hash table for a given string and returns a hash table entry
	HashNode *Lookup(LPCTSTR sz) const;

protected:
    UINT      m_nHashTableSize;
    BOOL      m_bCaseSensitive;
    HashNode** m_pHashTable;
};

#endif // !defined(AFX_HASHTABLE_H__30445BB2_1885_11D3_AA0C_F0E6D1000000__INCLUDED_)
