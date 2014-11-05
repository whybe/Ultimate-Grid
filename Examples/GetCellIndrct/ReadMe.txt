//  Read me  for example 7
/////////////////////////////////////
Using GetCell vs Using GetCellIndirect
/////////////////////////////////////

This example illustrates the difference between 
using the GetCell() and GetCellIndirect() functions
to retrieve a cell information from Ultimate Grid.  
GetCell() will return only those properties set in 
the actual cell, while GetCellIndirect() will go 
through column defaults and style cells.

For more details see:
MyCug::OnMenuCommand()