// DataMatrix.h: interface for the CDataMatrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAMATRIX_H__B8D72671_BB05_4B3B_A727_C0EEBC62EEC7__INCLUDED_)
#define AFX_DATAMATRIX_H__B8D72671_BB05_4B3B_A727_C0EEBC62EEC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataMatrix  
{
public:
	int GetValue( int col, int row );
	void UpdateValue( int col, int row, int newVal );
	int GetNumberCols();
	int GetNumberRows();
	void PopulateMatrix( int cols, int rows );
	CDataMatrix();
	virtual ~CDataMatrix();

protected:
	int **m_dataArray;
	int m_numberCols;
	int m_numberRows;
};

#endif // !defined(AFX_DATAMATRIX_H__B8D72671_BB05_4B3B_A727_C0EEBC62EEC7__INCLUDED_)
