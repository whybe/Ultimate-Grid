/*************************************************************************
				Class Declaration : CUGExcel
**************************************************************************
	Source file : UGExcel.cpp
	Header file : UGExcel.h
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Purpose
		The CUGExcel class is a CUGCtrl derived class that provides graohical
		interface similar to MS Excell.  By deriving from this class you can
		easily bring this look and feel to your application.

	Main features the CUGExcel class provides:

		1. change font in any cell at any time
		2. always refer to columns by their original position.
		3. Hide/Unhide columns, when columns are hiden, they are completely
		   removed from the view.
		5. select columns and rows by dragging mouse over top and side headings
		6. selected cells are shown in a transparent highlight color
*************************************************************************/
#include "ugctrl.h"

#include "ExcelTopHdg.h"
#include "ExcelSideHdg.h"

#define MSG_HIDE_COL				15101
#define MSG_CHANGE_FONT				15102
#define MSG_CHANGE_BACKCOLOR		15103
#define MSG_CHANGE_COL_FONT			15104
#define MSG_CHANGE_COL_BACKCOLOR	15105
#define MSG_RESET_SELECTED			15106
#define MSG_UNHIDE_COL				16000

class CUGExcel:public CUGCtrl
{
protected:
	struct _tagFonts
	{
		int fontIndex;
		CFont font;
		_tagFonts *next;

		_tagFonts()
		{
			fontIndex = -1;
			next = NULL;
		}
	} *m_fontsList;

	struct _tagHiddenCols
	{
		int colNumber;
		_tagHiddenCols *next;

		_tagHiddenCols()
		{
			next = NULL;
		}
	} *m_hiddenColsList, *m_pCurEnumItem;

	BOOL m_bForceEnumRestart;

public:
	CUGExcel();
	~CUGExcel();

	int GotoCell(int col,long row);
	int BestFit(int startCol,int endCol,int CalcRange,int flag);
	int RedrawCell(int col,long row);
	int	GetCell(int col,long row,CUGCell *cell);
	int	SetCell(int col,long row,CUGCell *cell);
	int	SetColWidth(int col,int width);
	int	GetColDefault(int col,CUGCell *cell);
	int	SetColDefault(int col,CUGCell *cell);
	int Select(int col,long row);
	int SelectRange(int startCol,long startRow,int endCol,long endRow);
	BOOL IsSelected(int col,long row,int *blockNum = NULL);
	int EnumFirstSelected(int *col,long *row);
	int EnumNextSelected(int *col,long *row);
	int EnumFirstBlock(int *startCol,long *startRow,int *endCol,long *endRow);
	int EnumNextBlock(int *startCol,long *startRow,int *endCol,long *endRow);
	int	JoinCells(int startcol,long startrow,int endcol,long endrow);
	int	UnJoinCells(int col,long row);
	int RedrawCol(int col);
	int RedrawRange(int startCol,long startRow,int endCol,long endRow);
	int FitToWindow(int startCol,int endCol);
	int SortBy(int col,int flag = UG_SORT_ASCENDING);
	int SortBy(int *cols,int num,int flag = UG_SORT_ASCENDING);
	int GotoCol(int col);
	int	GetCurrentCol();
	int	GetLeftCol();
	int	GetRightCol();
	int	SetLeftCol(int col);
	int	StartEdit();
	int	StartEdit(int key);
	int	StartEdit(int col,long row,int key);
	int	InsertCol(int col);
	int	DeleteCol(int col);
	int GetColWidth(int col);
	int	GetColWidth(int col,int *width);
	int	DeleteCell(int col,long row);
	int	QuickSetText(int col,long row,LPCTSTR string);
	int	QuickSetNumber(int col,long row,double number);
	int	QuickSetMask(int col,long row,LPCTSTR string);
	int	QuickSetLabelText(int col,long row,LPCTSTR string);
	int	QuickSetTextColor(int col,long row,COLORREF color);
	int	QuickSetBackColor(int col,long row,COLORREF color);
	int	QuickSetAlignment(int col,long row,int align);
	int	QuickSetBorder(int col,long row,int border);
	int	QuickSetBorderColor(int col,long row,CPen *pen);
	int	QuickSetFont(int col,long row,CFont * font);
	int	QuickSetFont(int col,long row,int index);
	int	QuickSetBitmap(int col,long row,CBitmap * bitmap);
	int	QuickSetBitmap(int col,long row,int index);
	int	QuickSetCellType(int col,long row,long type);
	int	QuickSetCellTypeEx(int col,long row,long typeEx);
	int	QuickSetHTextColor(int col,long row,COLORREF color);
	int	QuickSetHBackColor(int col,long row,COLORREF color);
	int	QuickSetRange(int startCol,long startRow,int endCol,long endRow, CUGCell* cell);
	int	QuickGetText(int col,long row,CString *string);
	LPCTSTR	QuickGetText(int col,long row);
	int FindFirst(CString *string,int *col,long *row,long flags);
	int FindNext(CString *string,int *col,long *row,int flags);

	BOOL ShowFontDlg( CUGCell &cell, LOGFONT &selectedLogFont, COLORREF &textColor );
	CFont* CreateFont( int nHeight, int nWidth, int nEscapement, int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline, BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision, BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily, LPCTSTR lpszFacename );
	CFont* CreateFontIndirect( LOGFONT newLogFont );
	int LocateCol( int col );

	// column hiding/unhiding functions
	void HideCol(int col);
	void UnHideCol(int origColPos, int newWidth = -1);
	// enumerators of hidden columns
	int EnumHiddenCols();

protected:
	CExcelTopHdg	*m_excelTopHdg;
	CExcelSideHdg	*m_excelSideHdg;

	CFont m_defFont;
	CPen m_cellBorderPen;

	COLORREF BlendColors( COLORREF color1, COLORREF color2, double rate );

private:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(CUGExcel)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void ResetSelected();

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

	//trackig window
	virtual void OnTrackingWindowMoved(RECT *origRect,RECT *newRect);
};
