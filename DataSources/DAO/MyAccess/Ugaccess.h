/***********************************************
	Ultimate Grid version 7.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.

	Class 
		CUGAccessCtrl
	Purpose
		This class is derived from the grid's main
		base class CUGCtrl. 

************************************************/

#include "ugctrl.h"

#include "ugdao.h"

//#include "accesstophdng.h"
//#include "accesssidehdng.h"


class CUGAccessCtrl:public CUGCtrl
{

public:

	CFont			   m_hintFont;
//	CAccessTopHdng	   * m_pTopHdg;		// just for set cursor
//	CAccessSideHdng	   * m_pSideHdg;

	CFont m_font;
	CFont m_thFont;			// font for top headings...

	BOOL  m_bUpdateFailed;	// set to true in OnDataSourceNotify if 
							// ds says an update failed
	long  m_nExtraRow;
	BOOL m_arrowCursor;
	HCURSOR m_excelArrow;
	HCURSOR m_excelWEResize;
	HCURSOR m_excelNSResize;

					
	CUGAccessCtrl();
	~CUGAccessCtrl();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUGAccessCtrl)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(CUGAccessCtrl)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();

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
	
	virtual void OnColChange(int oldcol,int newcol);
	virtual void OnRowChange(long oldrow,long newrow);
	virtual void OnCellChange(int oldcol,int newcol,long oldrow,long newrow);
	virtual void OnLeftColChange(int oldcol,int newcol);
	virtual void OnTopRowChange(long oldrow,long newrow);

	//mouse and key strokes
	virtual void OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed);
	virtual void OnRClicked(int col,long row,int updn,RECT *rect,POINT *point,int processed);
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,int processed);
	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
	virtual void OnTH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
	virtual void OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	virtual void OnSH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
	virtual void OnSH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
	virtual void OnSH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	virtual void OnCB_LClicked(int updn,RECT *rect,POINT *point,BOOL processed);
	virtual void OnCB_RClicked(int updn,RECT *rect,POINT *point,BOOL processed);
	virtual void OnCB_DClicked(RECT *rect,POINT *point,BOOL processed);
	virtual void OnMouseMove(int col,long row,POINT *point,UINT nFlags,BOOL processed);
	
	virtual void OnKeyDown(UINT *vcKey,int processed);
	virtual void OnCharDown(UINT *vcKey,int processed);

	// hints
	virtual int OnVScrollHint(long row,CString *string);

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
	virtual int OnEditVerify(int col,long row,UINT *vcKey,LPCTSTR string,int pos);
	virtual int OnEditFinish(int col, long row,CWnd *edit,LPCSTR string,BOOL cancelFlag);
	virtual int OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow);

	//menu notifications
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int  OnMenuStart(int col,long row,int section);

	//hints
	//virtual int OnHint(int col,long row,CUGHint *hint);
	//virtual int OnVScrollHint(long row,int percent,CUGHint *hint);
	//virtual int OnHScrollHint(int col,int percent,CUGHint *hint);

	//drag and drop
	#ifdef UG_ENABLE_DRAGDROP
		virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject);
		virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject,int col,long row);
		virtual DROPEFFECT OnDragDrop(COleDataObject* pDataObject,int col,long row);
	#endif

	// new member functions
	virtual void OnScreenDCSetup(CDC *dc,int section);

	virtual void OnTabSelected(int ID);

	virtual BOOL OnColSwapStart(int col);

	void OnDrawFocusRect(CDC *dc,RECT *rect);

	virtual COLORREF OnGetDefBackColor(int section);

};
