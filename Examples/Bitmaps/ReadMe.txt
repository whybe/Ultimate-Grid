//  Read me  for example Ex30
/////////////////////////////////////
      Bitmaps within UG97
/////////////////////////////////////

This example shows the use of bitmaps within 
Ultimate Grid.  The code for this is in 
MyCug::OnSetup.
	
MyCug::OnMenuCommand(int col,long row,int section,int item);
MyCug::OnMenuStart(int col,long row,int section);
MyCug::OnCellTypeNotify(long ID,int col,long row,long msg,long param);
MyCug::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL  processed);
MyCug::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL  processed);
MyCug::OnGetDefBackColor(int section);

