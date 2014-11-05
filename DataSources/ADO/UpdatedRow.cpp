/*************************************************************************
				Class Declaration : CUpdatedRow
**************************************************************************
	Source file : UpdatedRow.cpp
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
*************************************************************************/
#include "stdafx.h"
#include "UGCtrl.h"
#include "UpdatedRow.h"

/***************************************************
	Standard construction/desrtuction
***************************************************/
CUpdatedRow::CUpdatedRow()
{
	m_pColListHead = NULL;
	m_rowNumber = -1;
}

CUpdatedRow::~CUpdatedRow()
{
	Empty();
}

/***************************************************
IsUpdated
	This function will return TRUE/FALSE to help determine if
	column in question is located in the link list.
Params:
	col			- column of interest
Returns:
	TRUE or FALSE indicating if given column is found or not found
	in the link list.
***************************************************/
BOOL CUpdatedRow::IsUpdated( int col )
{
	ColList *pTempItem = m_pColListHead;

	while ( pTempItem != NULL )
	{
		if ( pTempItem->colNumber == col )
		{
			return TRUE;
		}
		pTempItem = pTempItem->next;
	}

	return FALSE;
}

/***************************************************
Count
	function returns number of items in the list.
Params:
	<none>
Returns:
	number of items in the list
*****************************************************/
int CUpdatedRow::Count()
{
	int nCount = 0;
	ColList *pTempItem = m_pColListHead;

	while ( pTempItem != NULL )
	{
		nCount ++;
		pTempItem = pTempItem->next;
	}

	return nCount;
}

/***************************************************
GetUpdatedVal
	function loops through all items in the link list and if
	it finds item representing given column, than it will
	storred value.
Params:
	col			- column number to look for
Returns:
	VARIANT containing storred value
*****************************************************/
_variant_t CUpdatedRow::GetUpdatedVal( int col )
{
	ColList *pTempItem = m_pColListHead;

	while ( pTempItem != NULL )
	{
		if ( pTempItem->colNumber == col )
		{
			return pTempItem->newVal;
		}
		pTempItem = pTempItem->next;
	}

	_variant_t var;
	var.vt = VT_ERROR;
	return var;
}

/***************************************************
UpdateCell
	function is used to provide new value for given column.
Params:
	col			- column 
	newVal		- new value
Returns:
	UG_SUCCESS
	UG_ERROR	- when could not allocate memory
*****************************************************/
int CUpdatedRow::UpdateCell( int col, _variant_t newVal )
{
	ColList *pTempItem = m_pColListHead;

	if ( pTempItem == NULL )
	{
		pTempItem = new ColList;
		m_pColListHead = pTempItem;
	}
	else
	{
		while ( pTempItem->next != NULL && pTempItem->colNumber != col )
		{
			pTempItem = pTempItem->next;
		}

		if ( pTempItem->next == NULL && pTempItem->colNumber != col )
		{
			// end of the list was reached, and this row was not referenced,
			// create new list item.
			pTempItem->next = new ColList;
			pTempItem = pTempItem->next;
		}
	}

	if ( pTempItem == NULL )
		// could not allocate memory successfuly
		return UG_ERROR;

	pTempItem->colNumber = col;
	pTempItem->newVal = newVal;

	return UG_SUCCESS;
}

/***************************************************
RemoveNewVal
	function is used to remove an item from the link list,
	this function is called during creation process of a
	SAFEARRAY of values to be saved in the database.
Params:
	col			- column to look for
Returns:
	UG_SUCCESS
	UG_ERROR	- when item was not found
*****************************************************/
int CUpdatedRow::RemoveNewVal( int col )
{
	ColList *pTempItem = m_pColListHead;
	ColList *pDeleteItem = NULL;

	if ( pTempItem == NULL )
		return UG_ERROR;

	// check if the column we are looking for is in the list head
	if ( pTempItem->colNumber == col )
	{
		pDeleteItem = pTempItem;

		pTempItem = pDeleteItem->next;
		m_pColListHead = pTempItem;
		delete pDeleteItem;
		
		return UG_SUCCESS;
	}

	while ( pTempItem->next != NULL )
	{
		if ( pTempItem->next->colNumber == col )
		{
			pDeleteItem = pTempItem->next;
			pTempItem = pDeleteItem->next;
			delete pDeleteItem;
			
			return UG_SUCCESS;
		}
		pTempItem = pTempItem->next;
	}

	return UG_ERROR;
}

/***************************************************
Empty
	Release all list items.
Params:
	<none>
Returns:
	UG_SUCCESS, this function will never fail.
*****************************************************/
int CUpdatedRow::Empty()
{
	ColList *pTempItem = m_pColListHead;
	ColList *pDeleteItem = NULL;

	while ( pTempItem != NULL )
	{
		pDeleteItem = pTempItem;
		pTempItem = pTempItem->next;
		delete pDeleteItem;
	}

	m_pColListHead = NULL;
	m_rowNumber = -1;

	return UG_SUCCESS;
}
