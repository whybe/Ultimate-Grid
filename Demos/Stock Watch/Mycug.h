// MyCug.h : interface of the MyCug class
//
/////////////////////////////////////////////////////////////////////////////
#include "ugctrl.h"

#define	MY_COLOR_BACK			RGB(0,0,60)
#define	MY_COLOR_TEXT			RGB(192,192,192)
#define	MY_COLOR_LO_TEXT		RGB(255,0,0)
#define	MY_COLOR_HI_TEXT		RGB(0,255,0)
#define	MY_COLOR_CHANGED_TEXT	RGB(0,0,0)
#define	MY_COLOR_CHANGED_BACK	RGB(0,255,255)

class ArrowCellType: public CUGCellType 
{    
protected:
	CBitmap	m_bmpUp;
	CBitmap	m_bmpDown;

public:        
	ArrowCellType() 
	{
		m_bmpUp.LoadBitmap(IDB_BITMAP_ARROW_UP);
		m_bmpDown.LoadBitmap(IDB_BITMAP_ARROW_DOWN);
	} 

	~ArrowCellType() 
	{
		m_bmpUp.DeleteObject();
		m_bmpDown.DeleteObject();
	}

	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell, int selected,int current)
	{
		// Call base class drawing
		CUGCellType::OnDraw(dc, rect, col, row, cell, selected, current);

		// Draw arrow bitmap
		CBitmap *pBmp = (cell->GetParam()) ? &m_bmpDown : &m_bmpUp;
		DrawTransparentBitmap(dc->m_hDC, (HBITMAP)*pBmp, (short)(rect->left + 1), (short)(rect->top + ((rect->bottom - rect->top) - 8)/2), RGB(0,0,0));
	}

	void DrawTransparentBitmap(HDC hdc, HBITMAP hBitmap, short xStart,
                           short yStart, COLORREF cTransparentColor)
	{
	   BITMAP     bm;
	   COLORREF   cColor;
	   HBITMAP    bmAndBack, bmAndObject, bmAndMem, bmSave;
	   HBITMAP    bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
	   HDC        hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
	   POINT      ptSize;

	   hdcTemp = CreateCompatibleDC(hdc);
	   SelectObject(hdcTemp, hBitmap);   // Select the bitmap

	   GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);
	   ptSize.x = bm.bmWidth;            // Get width of bitmap
	   ptSize.y = bm.bmHeight;           // Get height of bitmap
	   DPtoLP(hdcTemp, &ptSize, 1);      // Convert from device

										 // to logical points

	   // Create some DCs to hold temporary data.
	   hdcBack   = CreateCompatibleDC(hdc);
	   hdcObject = CreateCompatibleDC(hdc);
	   hdcMem    = CreateCompatibleDC(hdc);
	   hdcSave   = CreateCompatibleDC(hdc);

	   // Create a bitmap for each DC. DCs are required for a number of
	   // GDI functions.

	   // Monochrome DC
	   bmAndBack   = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

	   // Monochrome DC
	   bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

	   bmAndMem    = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	   bmSave      = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

	   // Each DC must select a bitmap object to store pixel data.
	   bmBackOld   = (HBITMAP)SelectObject(hdcBack, bmAndBack);
	   bmObjectOld = (HBITMAP)SelectObject(hdcObject, bmAndObject);
	   bmMemOld    = (HBITMAP)SelectObject(hdcMem, bmAndMem);
	   bmSaveOld   = (HBITMAP)SelectObject(hdcSave, bmSave);

	   // Set proper mapping mode.
	   SetMapMode(hdcTemp, GetMapMode(hdc));

	   // Save the bitmap sent here, because it will be overwritten.
	   BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	   // Set the background color of the source DC to the color.
	   // contained in the parts of the bitmap that should be transparent
	   cColor = SetBkColor(hdcTemp, cTransparentColor);

	   // Create the object mask for the bitmap by performing a BitBlt
	   // from the source bitmap to a monochrome bitmap.
	   BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0,
			  SRCCOPY);

	   // Set the background color of the source DC back to the original
	   // color.
	   SetBkColor(hdcTemp, cColor);

	   // Create the inverse of the object mask.
	   BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0,
			  NOTSRCCOPY);

	   // Copy the background of the main DC to the destination.
	   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, xStart, yStart,
			  SRCCOPY);

	   // Mask out the places where the bitmap will be placed.
	   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);

	   // Mask out the transparent colored pixels on the bitmap.
	   BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);

	   // XOR the bitmap with the background on the destination DC.
	   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);

	   // Copy the destination to the screen.
	   BitBlt(hdc, xStart, yStart, ptSize.x, ptSize.y, hdcMem, 0, 0,
			  SRCCOPY);

	   // Place the original bitmap back into the bitmap sent here.
	   BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

	   // Delete the memory bitmaps.
	   DeleteObject(SelectObject(hdcBack, bmBackOld));
	   DeleteObject(SelectObject(hdcObject, bmObjectOld));
	   DeleteObject(SelectObject(hdcMem, bmMemOld));
	   DeleteObject(SelectObject(hdcSave, bmSaveOld));

	   // Delete the memory DCs.
	   DeleteDC(hdcMem);
	   DeleteDC(hdcBack);
	   DeleteDC(hdcObject);
	   DeleteDC(hdcSave);
	   DeleteDC(hdcTemp);
   } 
};

class MyCug:public CUGCtrl
{
public:
	MyCug();
	~MyCug();

protected:

	ArrowCellType	m_celllArrow;
	int				m_nArrowCellIndx;

private:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(MyCug)
	// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer( UINT nIDEvent );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	virtual void OnSheetSetup(int sheetNumber);

	//movement and sizing
	virtual int  OnCanMove(int oldcol,long oldrow,int newcol,long newrow);
	virtual int  OnCanViewMove(int oldcol,long oldrow,int newcol,long newrow);
	virtual void OnHitBottom(long numrows,long rowspast,long rowsfound);
	virtual void OnHitTop(long numrows,long rowspast);
	
	virtual int  OnCanSizeCol(int col);
	virtual void OnColSizing(int col,int *width);
	virtual void OnColSized(int col,int *width);
	virtual int  OnCanSizeRow(long row);
	virtual void OnRowSizing(long row,int *height);
	virtual void OnRowSized(long row,int *height);

	virtual int  OnCanSizeTopHdg();
	virtual int  OnCanSizeSideHdg();
	virtual int  OnTopHdgSizing(int *height);
	virtual int  OnSideHdgSizing(int *width);
	virtual int  OnTopHdgSized(int *height);
	virtual int  OnSideHdgSized(int *width);
		
	virtual void OnColChange(int oldcol,int newcol);
	virtual void OnRowChange(long oldrow,long newrow);
	virtual void OnCellChange(int oldcol,int newcol,long oldrow,long newrow);
	virtual void OnLeftColChange(int oldcol,int newcol);
	virtual void OnTopRowChange(long oldrow,long newrow);

	//mouse and key strokes
	virtual void OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed);
	virtual void OnRClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed);
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	virtual void OnMouseMove(int col,long row,POINT *point,UINT nFlags,BOOL processed=0);
	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnTH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnSH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnSH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnSH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnCB_LClicked(int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnCB_RClicked(int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnCB_DClicked(RECT *rect,POINT *point,BOOL processed=0);
	
	virtual void OnKeyDown(UINT *vcKey,BOOL processed);
	virtual void OnCharDown(UINT *vcKey,BOOL processed);
	
	//GetCellIndirect notification
	virtual void OnGetCell(int col,long row,CUGCell *cell);
	//SetCell notification
	virtual void OnSetCell(int col,long row,CUGCell *cell);
	
	//data source notifications
	virtual void OnDataSourceNotify(int ID,long msg,long param);

	//cell type notifications
	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);

	//editing
	virtual int OnEditStart(int col, long row,CWnd **edit);
	virtual int OnEditVerify(int col,long row,CWnd *edit,UINT *vcKey);
	virtual int OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag);
	virtual int OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow);

	//menu notifications
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int  OnMenuStart(int col,long row,int section);

	// Context help 
	virtual DWORD OnGetContextHelpID( int col, long row, int section );

	//hints
	virtual int OnHint(int col,long row,int section,CString *string);
	virtual int OnVScrollHint(long row,CString *string);
	virtual int OnHScrollHint(int col,CString *string);


	#ifdef __AFXOLE_H__  //OLE must be included

	//drag and drop
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject,int col,long row);
	virtual DROPEFFECT OnDragDrop(COleDataObject* pDataObject,int col,long row);

	#endif

	//sorting
	virtual int OnSortEvaluate(CUGCell *cell1,CUGCell *cell2,int flags);
	
	//DC setup
	virtual void OnScreenDCSetup(CDC *dc,int section);
	
	virtual void OnAdjustComponentSizes(RECT *grid,RECT *topHdg,RECT *sideHdg,RECT *cnrBtn,
		RECT *vScroll,RECT *hScroll,RECT *tabs);

	virtual void OnTabSelected(int ID);
	
	virtual COLORREF OnGetDefBackColor(int section);

	//focus rect setup
	virtual void OnDrawFocusRect(CDC *dc,RECT *rect);
	virtual void OnSetFocus(int section);
	virtual void OnKillFocus(int section);

	//column swapping
	virtual BOOL OnColSwapStart(int col);
	virtual BOOL OnCanColSwap(int fromCol,int toCol);
	virtual void OnColSwapped(int fromCol,int toCol);

	//trackig window
	virtual void OnTrackingWindowMoved(RECT *origRect,RECT *newRect);
};
