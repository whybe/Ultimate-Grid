//  Read me  for example 3
/////////////////////////////////////
       Advanced Editing
/////////////////////////////////////

This example demonstrates advanced editing
in Ultimate Grid 97, with use of MaskEdit controls.

You can use your own edit class.

Using the advanced editing ability of the grid is as simple as 1,2,3

1) Create your own edit class by deriving from CEdit or any class that derives from it,
   (e.g. CUGEdit).

2) Using the class wizard Add message handlers for the following functions.
			
			OnKillFocus(CWnd* pNewWnd);
			int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
			void OnSetFocus(CWnd* pOldWnd);
			void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
			void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
			UINT OnGetDlgCode();
			int OnCreate(LPCREATESTRUCT lpCreateStruct);
			void OnUpdate();

3) In OnEditStart() of the grid control replace the grid edit pointer with your own 

