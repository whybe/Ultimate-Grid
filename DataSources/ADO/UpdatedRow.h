/*************************************************************************
				Class Declaration : CUpdatedRow
**************************************************************************
	Source file : UpdatedRow.cpp
	Header file : UpdatedRow.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Purpose
		The CUpdatedRow class is a helper class of the ADO datasource which
		is used to temporarly store changes user makes to a single row.  These
		changes will later be set to the database when user moves off the record
		in the database, or closes the Ultimate Grid window.
*************************************************************************/

#ifndef _UpdatedRow_H_
#define _UpdatedRow_H_

class CUpdatedRow  
{
public:
	CUpdatedRow();
	virtual ~CUpdatedRow();

	// access functions used to set and get information
	// on row number that is currently updated
	inline long GetUpdateRowNumber(){	return m_rowNumber;	}
	inline void SetUpdateRowNumber( long row )
	{
		if ( m_rowNumber != row )
			Empty();

		m_rowNumber = row;
	}
	// access function used to determine if there is new
	// value for given column
	BOOL IsUpdated( int col );
	// function to retrieve count of new values in the list
	int Count();
	// access function used to retrieve new cell' data
	_variant_t GetUpdatedVal( int col );
	// function used to set new value
	int UpdateCell( int col, _variant_t newVal );
	// function to remove given 
	int RemoveNewVal( int col );
	// delete all items in the list
	int Empty();
private:
	typedef struct _tagColList
	{
		int			colNumber;
		_variant_t	newVal;
		// pointer to next element in the list
		struct _tagColList *next;

		// default constractor
		_tagColList()
		{
			next = NULL;
		}
	}ColList;

protected:
	ColList	*m_pColListHead;
	int m_rowNumber;
};

#endif // _UpdatedRow_H_
