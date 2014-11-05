// HashTable.cpp: implementation of the COXHashTable class.
// 
// Simple hash table class based on code in K&R's "The C programming 
// language". 
//
// Author: Chris Maunder
//
//////////////////////////////////////////////////////////////////////
// Product Version: 7.51


#include "stdafx.h"
#include "OXHashTable.h"

#include <malloc.h>     // for free() (needed becuase of strdup())

// TODO: add API to traverse elements (FindFirst, FindNext and Count)

//////////////////////////////////////////////////////////////////////
// HashNode structure - auto initialise and cleanup
//////////////////////////////////////////////////////////////////////

HashNode::HashNode()
{
    szName = NULL;
    pNext = NULL;
    dwData = 0;
}

HashNode::~HashNode()
{
    if (szName)
        free(szName);
}

//////////////////////////////////////////////////////////////////////
// COXHashTable - Construction/Destruction
//////////////////////////////////////////////////////////////////////

COXHashTable::COXHashTable(int nHashTableSize)
{
    CommonConstruct(nHashTableSize);
}

COXHashTable::COXHashTable()
{
    CommonConstruct(67);
}

BOOL COXHashTable::CommonConstruct(int nHashTableSize)
{
    m_pHashTable = NULL;
    m_nHashTableSize = 0;
    m_bCaseSensitive = FALSE;

    return InitHashTable(nHashTableSize); 
}

COXHashTable::~COXHashTable()
{
    RemoveAll();
    delete [] m_pHashTable;
}

//////////////////////////////////////////////////////////////////////
// COXHashTable - Public Attributes

void COXHashTable::SetCaseSensitive(BOOL bCase)
{
    m_bCaseSensitive = bCase;
}

BOOL COXHashTable::GetCaseSensitive()
{
    return m_bCaseSensitive;
}

//////////////////////////////////////////////////////////////////////
// COXHashTable - Public Operations

BOOL COXHashTable::InitHashTable(UINT nHashSize)
{
    if (nHashSize < 1)
        return FALSE;

    RemoveAll();
    delete [] m_pHashTable;

    m_nHashTableSize = nHashSize;
    m_pHashTable = new HashNode*[m_nHashTableSize];
    if (!m_pHashTable)
        return FALSE;

    for (UINT i = 0; i < m_nHashTableSize; i++)
        m_pHashTable[i] = NULL;

    return TRUE;
}

UINT COXHashTable::GetHashTableSize() const
{
    return m_nHashTableSize;
}

void COXHashTable::RemoveAll()
{
    if (!m_pHashTable)
        return;

    for (UINT i = 0; i < m_nHashTableSize; i++)
    {
        HashNode* pPrev = NULL;
        HashNode* pNext = m_pHashTable[i];

        while (pNext)
        {
            pPrev = pNext->pNext;
            delete pNext;
            pNext = pPrev;
        }

        m_pHashTable[i] = NULL;
    }
}

BOOL COXHashTable::Add(LPCTSTR sz, DWORD dwData)
{
    HashNode *pNode = Lookup(sz);

    // Can't find entry - so add a new one
    if (pNode == NULL)
    {
        // Create a new node with the given name
        pNode = new HashNode;

        if (pNode == NULL)
            return FALSE;

        // Copy over the string
        pNode->szName = _tcsdup(sz);
        if (pNode->szName == NULL)
        {
            delete pNode;
            return FALSE;
        }

        // Find it's position in the hash table and insert it at the head of the
        // list at that point
        pNode->nHashValue = Hash(sz);
        pNode->pNext = m_pHashTable[pNode->nHashValue];
        m_pHashTable[pNode->nHashValue] = pNode;
    }

    // Set the data
    pNode->dwData = dwData;
    
    return TRUE;
}

BOOL COXHashTable::Lookup(LPCTSTR sz, DWORD& dwData) const
{
    dwData = 0;
    HashNode *pNode = Lookup(sz);
    if (!pNode)
        return FALSE;

    dwData = pNode->dwData;
    return TRUE;
}

BOOL COXHashTable::Remove(LPCTSTR sz)
{
    HashNode *pNode, *pPrev = NULL; 
    UINT nHashVal = Hash(sz);

    for (pNode = m_pHashTable[nHashVal]; pNode != NULL; pNode = pNode->pNext)
    {
        BOOL bFound = FALSE;

        if (m_bCaseSensitive)
            bFound = (_tcscmp(sz, pNode->szName) == 0);
        else
            bFound = (_tcsicmp(sz, pNode->szName) == 0);
          
        if (bFound)
            break;

        pPrev = pNode;
    }

    // No entry found
    if (pNode == NULL)
        return FALSE;

    if (pPrev == NULL)      // Entry is first entry at Hash table entry site
    {
        m_pHashTable[nHashVal] = pNode->pNext;
        delete pNode;
    }
    else    // More than one entry with this hash val - remove entry from list
    {
        pPrev->pNext = pNode->pNext;
        delete pNode;
    }

    return TRUE;
}

//////////////////////////////////////////////////////////////////////
// COXHashTable - protected implementation

UINT COXHashTable::Hash(LPCTSTR sz) const
{
    UINT nHashVal = 0;

    if (m_bCaseSensitive)
    {
        while (*sz)
            nHashVal = (nHashVal<<5) + nHashVal + *sz++;
    }
    else
    {
        while (*sz)
        {
            if (_istupper(*sz))
                nHashVal = (nHashVal<<5) + nHashVal + _tolower(*sz++);
            else
                nHashVal = (nHashVal<<5) + nHashVal + *sz++;
        }
    }

    return nHashVal % m_nHashTableSize;
}

HashNode *COXHashTable::Lookup(LPCTSTR sz) const
{
    HashNode *pNode;
    UINT nHashVal = Hash(sz);

    for (pNode = m_pHashTable[nHashVal]; pNode != NULL; pNode = pNode->pNext)
    {
        BOOL bFound = FALSE;

        if (m_bCaseSensitive)
            bFound = (_tcscmp(sz, pNode->szName) == 0);
        else
            bFound = (_tcsicmp(sz, pNode->szName) == 0);
          
        if (bFound)
            return pNode;
    }

    // Did not find.
    return NULL;
}

HASH_POS COXHashTable::GetStartPosition() const
{
    if (!m_pHashTable)
        return NULL;

    // Check there are elements
    for (UINT nNode = 0; nNode < m_nHashTableSize; nNode++)
        if (m_pHashTable[nNode])
            return HASHTABLE_START_POS;

    return NULL;
}

void COXHashTable::GetNextAssoc(HASH_POS& pos, LPCTSTR& sz, DWORD& dwData) const
{
    if (!m_pHashTable || !pos)
    {
        pos = NULL;
        return;
    }

    // If this is the first call, then find the first item
	if (pos == HASHTABLE_START_POS)
	{
        pos = NULL;
        for (UINT nNode = 0; nNode < m_nHashTableSize; nNode++)
        {
            if (m_pHashTable[nNode])
            {
                pos = m_pHashTable[nNode];
                break;
            }
        }
	}

	// fill in return data
    if (pos)
    {
        sz = pos->szName;
        dwData = pos->dwData;
    }

    // Find the next item
    if (pos)
    {
        HashNode* pNode = (HashNode*) pos;
        if (pNode->pNext == NULL)
        {
            pos = NULL;
            for (UINT nNode = pNode->nHashValue+1; nNode < m_nHashTableSize; nNode++)
            {
                if (m_pHashTable[nNode])
                {
                    pos = m_pHashTable[nNode];
                    break;
                }
            }
        }
        else
            pos = pNode->pNext;
    }
}
