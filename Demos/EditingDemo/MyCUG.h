// MyCUG.h : interface of the MyCug class
//
/////////////////////////////////////////////////////////////////////////////
#include "ugctrl.h"
#include "UGCTRado.h"
#include "UGCTelps.h"
#include "UGCTLabeled.h"
#include "UGCTMarquee.h"
#include "UTEdit.h"
#include "UTMaskedEdit.h"

#define	LABEL_BACK		RGB(100,150,200)
#define SUBLABEL_BACK	RGB(220,200,180)

#define MY_SEPARATOR		10
#define USE_UPPER			1001
#define USE_LOWER			1002
#define USE_PASSWORD		1003
#define USE_CHARLIMIT		1004
#define USE_NUMLIMIT		1005
#define USE_FINISHTEST		1006
#define USE_SETMASK			1007
#define USE_SETCOXMASK		1008
#define USE_SETCOXNUMBER	1009
#define USE_SETCOXCURRENCY	1010

#define FLEXEDIT_ID			320001
#define COXMASK_ID			320002
#define COXNUMBER_ID		320003
#define COXCURRENCY_ID		320004

class MyCug:public CUGCtrl
{
public:
	MyCug();
	~MyCug();

protected:
	// celltypes
	CUGRadioType m_radioType;
	CUGEllipsisType m_ellipType;
	CUGLabeledType m_labeledType;
	CUGMarqueeType m_marqueeType;

	// additional edit controls
	CUTMaskedEdit	m_cutMaskEdit;
	CUTNumericEdit	m_cutNumeric;
	CUTCurrencyEdit	m_cutCurrency;

	// font functions
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

	CFont * m_defFont;
	CFont * m_smallFont;
	CFont * m_largeFont;

	BOOL ShowFontDlg( CUGCell &cell, LOGFONT &selectedLogFont, COLORREF &textColor );
	CFont* CreateFont( int nHeight, int nWidth, int nEscapement, int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline, BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision, BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily, LPCTSTR lpszFacename );
	CFont* CreateFontIndirect( LOGFONT newLogFont );

	// additional edit controls
	CUGEdit m_myCUGEdit;

private:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

	
	//{{AFX_MSG(MyCug)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();
	//mouse and key strokes
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	
	virtual void OnKeyDown(UINT *vcKey,BOOL processed);
	virtual void OnCharDown(UINT *vcKey,BOOL processed);
	
	//SetCell notification
	virtual void OnSetCell(int col,long row,CUGCell *cell);
	
	//cell type notifications
	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,long param);

	//editing
	virtual int OnEditStart(int col, long row,CWnd **edit);
	virtual int OnEditVerify(int col,long row,CWnd *edit,UINT *vcKey);
	virtual int OnEditFinish(int col, long row,CWnd *edit,LPCTSTR string,BOOL cancelFlag);
	virtual int OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow);

	virtual COLORREF OnGetDefBackColor(int section);
};
