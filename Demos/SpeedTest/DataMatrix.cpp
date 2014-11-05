// DataMatrix.cpp: implementation of the CDataMatrix class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpeedTest.h"
#include "DataMatrix.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataMatrix::CDataMatrix()
{
	m_numberCols = 50;
	m_numberRows = 10000;
	m_dataArray = NULL;
}

CDataMatrix::~CDataMatrix()
{
	if ( m_dataArray != NULL )
	{
		for ( int nIndex = 0; nIndex < m_numberCols; nIndex ++ )
		{
			delete[] m_dataArray[nIndex];
		}
		delete[] m_dataArray;
	}
}

void CDataMatrix::PopulateMatrix( int cols, int rows )
{
	if ( m_dataArray != NULL )
	{
		for ( int nIndex = 0; nIndex < m_numberCols; nIndex ++ )
		{
			delete[] m_dataArray[nIndex];
		}
		delete[] m_dataArray;
		m_dataArray = NULL;
	}

	m_numberCols = cols;
	m_numberRows = rows;

	if ( m_dataArray == NULL )
	{
		m_dataArray = new int*[m_numberCols];

		for ( int nIndex = 0; nIndex < m_numberCols; nIndex ++ )
		{
			m_dataArray[nIndex] = new int[m_numberRows];
		}
	}

	for ( int xIndex = 0; xIndex < m_numberCols; xIndex ++ )
	{
		for ( int yIndex = 0; yIndex < m_numberRows; yIndex ++ )
		{
			m_dataArray[xIndex][yIndex] = rand()%100;
		}
	}
}

int CDataMatrix::GetNumberRows()
{
	return m_numberRows;
}

int CDataMatrix::GetNumberCols()
{
	return m_numberCols;
}

void CDataMatrix::UpdateValue(int col, int row, int newVal)
{
	m_dataArray[col][row] = newVal;
}

int CDataMatrix::GetValue(int col, int row)
{
	return m_dataArray[col][row];
}
