// CellTypeOutlook.cpp: implementation of the CCellTypeOutlook class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "CellTypeOutlook.h"

#include "UGStrOp.h"
#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CCellTypeOutlook,CUGCtrl)
	//{{AFX_MSG_MAP(CCellTypeOutlook)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include "OXBitmapMenu.h"
#include <sstream>

namespace
{
	// Define an inserter for CString so I can use ostringstream below without having to constantly reproduce this code.
	template<class charT, class Traits>
std::basic_ostream<charT, Traits> &
operator << (std::basic_ostream<charT, Traits> & os, 
            CString & cstr)
{
    //Check stream state first

    if (!os.good()) return os;

    // Create sentry for prefix operations ( it's destructor will 
    // carry out postfix operations )

    typename std::basic_ostream<charT, Traits>::sentry opfx(os);

    if (opfx)
    {
        os << cstr.GetBuffer(cstr.GetLength());
		cstr.ReleaseBuffer();
    }

    return os;
}

}

CCellTypeOutlook::CCellTypeOutlook()
{
	m_bMarkedAsUnread = false;
	m_pMailWindow = NULL;
	m_bShowGroups = true;
	m_nExpandIndex = m_nHeaderIndex = m_nMailIndex = m_nMailSortIndex = 0;
}

CCellTypeOutlook::~CCellTypeOutlook()
{
}

/***************************************************
OnSetup
	This function is called just after the grid window 
	is created or attached to a dialog item.
	It can be used to initially setup the grid
****************************************************/
void CCellTypeOutlook::OnSetup()
{
	UseHints(TRUE);

	CUGCell cell;
//	int rows,cols;
//	int row;

	//setup the fonts
	m_defFont.CreateFont( 14, 0, 0, 0, 500, 0, 0, 0, 0, 0, 0, 0, 0, _T( "Arial" ) );
	m_boldFont.CreateFont( 14, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, _T( "MS Sans Serif" ) );
	m_smFont.CreateFont( 10, 0, 0, 0, 500, 0, 0, 0, 0, 0, 0, 0, 0, _T( "Arial" ) );	
	m_medFont.CreateFont( 16, 0, 0, 0, 500, 0, 0, 0, 0, 0, 0, 0, 0, _T( "MS Sans Serif" ) );
	m_medBoldFont.CreateFont( 16, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, _T( "MS Sans Serif" ) );
	m_lrgFont.CreateFont( 20, 0, 0, 0, 600, 0, 0, 0, 0, 0, 0, 0, 0, _T( "Times New Roman" ) );	
	SetDefFont( &m_defFont );

	//SETUP ALL OF THE CELL TYPES
	m_nExpandIndex = AddCellType(&m_expand);
	m_nHeaderIndex = AddCellType(&m_header);
	m_nMailIndex = AddCellType(&m_mail);
	m_nMailSortIndex = AddCellType(&m_mailSort);

	CBitmap bmp;
	bmp.LoadBitmap(IDB_BMENVOPEN);
	m_mail.AddImage(&bmp, CUGCTMail::left);
	::DeleteObject(bmp.Detach());
	bmp.LoadBitmap(IDB_BMENVCLOSED);
	m_mail.AddImage(&bmp, CUGCTMail::left);
	::DeleteObject(bmp.Detach());
	bmp.LoadBitmap(IDB_BMENVREP);
	m_mail.AddImage(&bmp, CUGCTMail::left);
	::DeleteObject(bmp.Detach());
	bmp.LoadBitmap(IDB_BMATTACHMENT);
	m_mail.SetAttachmentImage((HBITMAP)bmp.Detach());

	m_mail.AddImageList(IDB_BMFLAGS, 19, CUGCTMail::right, CLR_NONE);
	m_mail.SetCheckIndex(7);
	m_mail.SetDefaultFlagIndex(1);

	//setup the grid widths and heights
	SetSH_Width(0);
	SetNumberCols( 1 );
	SetNumberRows( 19 );
	SetTH_NumberRows( 2 );
	SetTH_Height( 56 );
	SetTH_RowHeight( -1, 20 );
	SetTH_RowHeight( -2, 36 );
	
	SetDoubleBufferMode(TRUE);
	SetUserSizingMode(0);

	GetHeadingDefault(&cell);
	cell.SetFont(&m_medBoldFont);
	cell.SetText(_T("Inbox"));
	cell.SetTextColor(RGB(255, 255, 255));
	cell.SetCellType(m_nHeaderIndex);
	SetHeadingDefault(&cell);
	
	SetColWidth(0,230);
	int height = 24;
	OnRowSizing(-2,&height);
	SetRowHeight(-2,height);

	this->SetVScrollMode(UG_SCROLLTRACKING);

	// Sort cell
	{

		GetCell(0,-1,&cell);
		cell.SetCellType(m_nMailSortIndex);
		cell.UseThemes(true);
		cell.SetText(_T("Today"));
		SetCell(0,-1,&cell);
	}

	// Expand
	{
		height = 36;

		GetCell(0,0,&cell);
		cell.SetCellType(m_nExpandIndex);
		cell.UseThemes(true);
		cell.SetText(_T("Today"));
		OnRowSizing(0,&height);
		SetRowHeight(0,height);
		SetCell(0,0,&cell);

		GetCell(0,5,&cell);
		cell.SetCellType(m_nExpandIndex);
		cell.SetText(_T("Yesterday"));
		cell.UseThemes(true);
		OnRowSizing(5,&height);
		SetRowHeight(5,height);
		SetCell(0,5,&cell);
	}

	// Mail
	{
		height = 36;

		CUGCTMail::mailItem item;
		time_t ltime;
		time(&ltime);

		CTime dateNow(ltime);

		CTime date(dateNow.GetYear(), dateNow.GetMonth(), dateNow.GetDay(), 10, 11, 2);

		item.leftIcon = 0;
		item.sender = "Nish";
		item.subject = "Have you seen the Ultimate Grid ?";
		item.mail = "In response to your question, the Ultimate Gird is the best MFC grid on the market today, you should give it a try.";
		item.isRead = true;
		item.rightIcon = 3;
		date -= CTimeSpan(0, 0, 12, 17);
		item.date = date;
		item.size = 8191;
		item.attachmentPath = "Ultimate Grid demo.zip";
		
		GetCell(0,1,&cell);
		cell.SetCellType(m_nMailIndex);
		cell.UseThemes(true);
		CUGCTMail::SetString(item, 0, 1, &cell, this);
		OnRowSizing(1,&height);
		SetRowHeight(1,height);

		item.leftIcon = 2;
		item.sender = "Chris Maunder";
		item.subject = "Check out www.codeproject.com";
		item.mail = "For the best group of developers on the web, an an ever growing number of articles on .NET and MFC development, you can't go wrong.";
		item.isRead = true;
		item.rightIcon = 4;
		date -= CTimeSpan(0, 0, 22, 36);
		item.date = date;
		item.size = 2000;
		item.attachmentPath = "";


		GetCell(0,2,&cell);
		cell.SetCellType(m_nMailIndex);
		cell.UseThemes(true);
		CUGCTMail::SetString(item, 0, 2, &cell, this);
		OnRowSizing(2,&height);
		SetRowHeight(2,height);

		item.leftIcon = 1;
		item.sender = "Igor";
		item.subject = "Master, the monster is moving !!";
		item.mail = "Run for your life !!!";
		item.isRead = false;
		item.rightIcon = 5;
		date -= CTimeSpan(0, 0, 8, 1);
		item.date = date;
		item.size = 750;

		GetCell(0,3,&cell);
		cell.SetCellType(m_nMailIndex);
		cell.UseThemes(true);
		CUGCTMail::SetString(item, 0, 3, &cell, this);
		OnRowSizing(3,&height);
		SetRowHeight(3,height);

		item.leftIcon = 0;
		item.sender = "Christian Graus";
		item.subject = "re: Outlook UI in MFC ?";
		item.mail = "If you want an Outlook style UI in your MFC app, check out the Ultimate Toolkit !!!";
		item.isRead = true;
		item.rightIcon = 0;
		date -= CTimeSpan(0, 1, 15, 43);
		item.date = date;
		item.size = 12;
		item.attachmentPath = "Ultimate Toolkit demo.zip";

		GetCell(0,4,&cell);
		cell.SetCellType(m_nMailIndex);
		cell.UseThemes(true);
		CUGCTMail::SetString(item, 0, 4, &cell, this);
		OnRowSizing(4,&height);
		SetRowHeight(4,height);

		item.leftIcon = 1;
		item.sender = "William Grates";
		item.subject = "re: How do I just use the expanding cell type ?";
		item.mail = "Thanks for your help !!! I followed your instructions and it is working well. \r\n"  
			"\r\n"
			"> The Outlook demo shows the capabilities of a number of new  cell types, \r\n"
			"> however at it's core it's a demo to show one possible use of a new, general \r\n"
			"> purpose cell type, which is called CUGCTExpand.  For the Outlook demo, this \r\n" 
			"> class needed access to information from the CUGCTMail cell type, so we've added\r\n"
			"> a #define, if you don't #define UGEXPANDUSEMAIL, the expanding cell type will compile\r\n"
			"> with no dependancy on the other cell type classes used in the Outlook demo.  To\r\n"
			"> use it, simply add the cell type to your project, and place the expanding cells\r\n"
			"> within the same column, on rows that you add to define areas to expand.  The\r\n"
			"> default behaviour is to expand/contract all cells to the next expanding cell, but \r\n"
			"> the SetNumberOfRows method can be used to set how many rows to expand/contract,\r\n"
			"> if needed.  If you require a grid that supports sorting, then you will need to\r\n"
			"> copy some code out of the Outlook sample, but otherwise, I'd estimate it would take\r\n"
			"> less than 10 minutes to add expanding/contracting cells to your existing project.\r\n"
			">\r\n"
			"> Let us know if you require any further information\r\n"
			">\r\n"
			"> Christian\r\n"
			">\r\n"
			">>  Hi guys,\r\n"
			">>           I've seen the outlook demo for the grid, and it looks great,\r\n"
			">> but I just want to add expanding cells to a project that's NOT like \r\n"
			">> Outlook.  Can I do that, or do your new cells only work for projects\r\n"
			">> that mimic Outlook ?\r\n"
			">> Thanks for any help,\r\n"
			">> Bill\r\n";
		item.isRead = false;
		item.rightIcon = 1;
		date -= CTimeSpan(0, 12, 15, 43);
		item.date = date;
		item.size = 150;
		item.attachmentPath = "";

		GetCell(0,6,&cell);
		cell.SetCellType(m_nMailIndex);
		cell.UseThemes(true);
		CUGCTMail::SetString(item, 0, 6, &cell, this);
		OnRowSizing(6,&height);
		SetRowHeight(6,height);

		item.leftIcon = 1;
		item.sender = "William Grates";
		item.subject = "How do I just use the expanding cell type ?";
		item.mail = "  Hi guys,\r\n"
			"           I've seen the outlook demo for the grid, and it looks great,\r\n"
			" but I just want to add expanding cells to a project that's NOT like \r\n"
			" Outlook.  Can I do that, or do your new cells only work for projects\r\n"
			" that mimic Outlook ?\r\n"
			" Thanks for any help,\r\n"
			" Bill\r\n";

		item.isRead = true;
		item.rightIcon = 0;
		date -= CTimeSpan(0, 0, 8, 1);
		item.date = date;
		item.size = 999;

		GetCell(0,7,&cell);
		cell.SetCellType(m_nMailIndex);
		cell.UseThemes(true);
		CUGCTMail::SetString(item, 0, 7, &cell, this);
		OnRowSizing(7,&height);
		SetRowHeight(7,height);

		item.leftIcon = 1;
		item.sender = "Stephen Bamah";
		item.subject = "re: Using mail type with different graphics ?";
		item.mail = 	"\r\n"
			"That's great news, thanks.\r\n"
            "\r\n"                                                                
			">  Hi, Steve.  \r\n"                                                                
			"> \r\n"                                                                
			"> Although the OutlookStyle demo was written mostly as a showcase for the\r\n"                                                                
			"> new Expanding cell type, every effort was made to ensure that the other new\r\n"                                                                
			"> cell types would be written as generically as possible, for possible reuse.\r\n"                                                                
			"> The CUGCTMail class contains two image lists, one of which is used to draw \r\n"                                                                
			"> icons on the left edge, and the other on the right.  A user who didn't want\r\n"                                                                
			"> to display images could simply leave these image lists empty, or you can fill\r\n"                                                                
			"> them with whatever images you would prefer.  All the text is drawn to fit around\r\n"                                                                
			"> the images, and the icon for an attachment is also stored as a bitmap, which\r\n"                                                                
			"> can simply be left empty if desired.  Therefore, if you have a use for the cell\r\n"                                                                
			"> type, which does do a good job of drawing itself when resized, you can set it\r\n"                                                                
			"> up to use whatever graphics you like.\r\n"                                                                
			"> \r\n"                                                                
			"> If this does not fully answer your question, let me know what additional information\r\n"                                                                
			"> you require, and we'll do our best to provide it.\r\n"                                                                
			"> \r\n"                                                                
			"> Christian\r\n"                                                                
			"> \r\n"                                                                
			"> \r\n"                                                                
			">> Hi - I've just seen your Outlook demo, and I'm wondering if it's possible to\r\n"                                                                
			">> replace the graphics used by the mail cell, or if the cell is only useful for \r\n"                                                                
			">> displaying exactly the graphics used by Outlook ? I'd like to use your grid to \r\n"                                                                
			">> display data which would be well suited to an outlook style such as yours, but \r\n"                                                                
			">> as it won't be an email program, I really don't want those envelopes and so on.\r\n"                                                                
			">> \r\n"                                                                
			">> Can that be done ?\r\n"                                                                
			">> \r\n"                                                                
			">> Stephen Bamah\r\n"                                                                
			">> \r\n"                                                                
			">>";
		item.isRead = false;
		item.rightIcon = 0;
		date -= CTimeSpan(0, 1, 12, 47);
		item.date = date;
		item.size = 76;

		GetCell(0,8,&cell);
		cell.SetCellType(m_nMailIndex);
		cell.UseThemes(true);
		CUGCTMail::SetString(item, 0, 8, &cell, this);
		OnRowSizing(8,&height);
		SetRowHeight(8,height);

		item.leftIcon = 0;
		item.sender = "Stephen Bamah";
		item.subject = "Using mail type with different graphics ?";
		item.mail = "\r\n"
			"Hi - I've just seen your Outlook demo, and I'm wondering if it's possible to\r\n"
			"replace the graphics used by the mail cell, or if the cell is only useful for \r\n"
			"displaying exactly the graphics used by Outlook ? I'd like to use your grid to \r\n"
			"display data which would be well suited to an outlook style such as yours, but \r\n"
			"as it won't be an email program, I really don't want those envelopes and so on.\r\n"
			"\r\n"
			"Can that be done ?\r\n"
			"\r\n"
			"Stephen Bamah\r\n"
			"\r\n";
		item.isRead = true;
		item.rightIcon = 0;
		date -= CTimeSpan(0, 0, 8, 1);
		item.date = date;
		item.size = 8;
		
		GetCell(0,9,&cell);
		cell.SetCellType(m_nMailIndex);
		cell.UseThemes(true);
		CUGCTMail::SetString(item, 0, 9, &cell, this);
		OnRowSizing(9,&height);
		SetRowHeight(9,height);

		item.leftIcon = 0;
		item.sender = "Bill Fleming";
		item.subject = "re: Sort order in Outlook style grid";
		item.mail = "\r\n"
			"Sounds great, thanks !!!\r\n"
			">\r\n"
			"> Hi, Bill.\r\n"
			">\r\n"
			"> The grid itself has exposed sorting functionality for some time.  The Outlook\r\n"
			"> cell types use this functionality for sorting, which means that all code that\r\n"
			"> enforces sort order is in the grid derived class.  The grid classes also expose\r\n"
			"> a callback which is used to centralise menus.  This means that the contents of the\r\n"
			"> sorting menu and the sorting behaviour are defined in your grid derived class, and\r\n"
			"> can be changed from project to project without changing almost any of the cell types. \r\n"
			"> The MailSort cell contains an enum of all possible sort types, this enum can be added \r\n"
			"> to with any sort types you may want to use, and then this will be used to display the\r\n"
			"> sort type that is being used in it's paint method.  This is only used to display the\r\n"
			"> current sort order, so any sort orders you add to the enum do not need to be removed\r\n"
			"> for projects that do not use them.\r\n"
			">\r\n"
			"> There is some additional code required to insert header fields after a sort occurs, \r\n"
			"> this is quite simple and is demonstrated in the grid derived class for the Outlook\r\n"
			"> sample.  Overall, the classes have been written with this sort of expansion in mind,\r\n"
			"> and where-ever possible, the user generated code is placed in the grid derived class,\r\n"
			"> and not within the cell classes.\r\n"
			">\r\n"
			"> Christian\r\n"
			">\r\n"
			">\r\n"
			">>\r\n"
			">> I've seen the Outlook style demo, and I'd like to use a similar approach\r\n"
			">> in my own program, but I want to change the different ways that mail can\r\n"
			">> be sorted, including adding some new options.  How hard is this to do ? \r\n"
			">> Would I be better off starting from scratch, or can I easily plug new \r\n"
			">> sorting criteria to your sample ?\r\n"
			">>\r\n"
			">> Bill Fleming\r\n"
			">>\r\n"
			">>\r\n ";
		item.isRead = true;
		item.rightIcon = 1;
		date -= CTimeSpan(0, 2, 40, 13);
		item.date = date;
		item.size = 9;

		GetCell(0,10,&cell);
		cell.SetCellType(m_nMailIndex);
		cell.UseThemes(true);
		CUGCTMail::SetString(item, 0, 10, &cell, this);
		OnRowSizing(10,&height);
		SetRowHeight(10,height);

		item.leftIcon = 1;
		item.sender = "Bill Fleming";
		item.subject = "Sort order in Outlook style grid";
		item.mail = 			">>\r\n"
			" I've seen the Outlook style demo, and I'd like to use a similar approach\r\n"
			" in my own program, but I want to change the different ways that mail can\r\n"
			" be sorted, including adding some new options.  How hard is this to do ? \r\n"
			" Would I be better off starting from scratch, or can I easily plug new \r\n"
			" sorting criteria to your sample ?\r\n"
			"\r\n"
			" Bill Fleming\r\n";
		item.isRead = false;
		item.rightIcon = 1;
		date -= CTimeSpan(0, 0, 15, 43);
		item.date = date;
		item.size = 2;

		GetCell(0,11,&cell);
		cell.SetCellType(m_nMailIndex);
		cell.UseThemes(true);
		CUGCTMail::SetString(item, 0, 11, &cell, this);
		OnRowSizing(11,&height);
		SetRowHeight(11,height);

		item.sender = "Bill Fleming";
		item.subject = "Sort order in Outlook style grid";
		item.mail = 			">>\r\n"
			" I've seen the Outlook style demo, and I'd like to use a similar approach\r\n"
			" in my own program, but I want to change the different ways that mail can\r\n"
			" be sorted, including adding some new options.  How hard is this to do ? \r\n"
			" Would I be better off starting from scratch, or can I easily plug new \r\n"
			" sorting criteria to your sample ?\r\n"
			"\r\n"
			" Bill Fleming\r\n";

		date -= CTimeSpan(0, 0, 15, 43);
		item.date = date;
		item.size = 3;

		GetCell(0,12,&cell);
		cell.SetCellType(m_nMailIndex);
		cell.UseThemes(true);
		CUGCTMail::SetString(item, 0, 12, &cell, this);
		OnRowSizing(12,&height);
		SetRowHeight(12,height);

		date -= CTimeSpan(0, 0, 15, 43);
		item.date = date;

		GetCell(0,13,&cell);
		cell.SetCellType(m_nMailIndex);
		cell.UseThemes(true);
		CUGCTMail::SetString(item, 0, 13, &cell, this);
		OnRowSizing(13,&height);
		SetRowHeight(13,height);

		item.rightIcon = 0;
		date -= CTimeSpan(0, 0, 15, 43);
		item.date = date;
		item.size = 6;

		GetCell(0,14,&cell);
		cell.SetCellType(m_nMailIndex);
		cell.UseThemes(true);
		CUGCTMail::SetString(item, 0, 14, &cell, this);
		OnRowSizing(14,&height);
		SetRowHeight(14,height);

		date -= CTimeSpan(0, 0, 15, 43);
		item.date = date;

		GetCell(0,15,&cell);
		cell.SetCellType(m_nMailIndex);
		cell.UseThemes(true);
		CUGCTMail::SetString(item, 0, 15, &cell, this);
		OnRowSizing(15,&height);
		SetRowHeight(15,height);

		item.rightIcon = 1;
		date -= CTimeSpan(0, 0, 15, 43);
		item.date = date;

		GetCell(0,16,&cell);
		cell.SetCellType(m_nMailIndex);
		cell.UseThemes(true);
		CUGCTMail::SetString(item, 0, 16, &cell, this);
		OnRowSizing(16,&height);
		SetRowHeight(16,height);

		item.rightIcon = 0;
		date -= CTimeSpan(0, 0, 15, 43);
		item.date = date;
		item.size = 5;

		GetCell(0,17,&cell);
		cell.SetCellType(m_nMailIndex);
		cell.UseThemes(true);
		CUGCTMail::SetString(item, 0, 17, &cell, this);
		OnRowSizing(17,&height);
		SetRowHeight(17,height);

		date -= CTimeSpan(0, 0, 15, 43);
		item.date = date;

		GetCell(0,18,&cell);
		cell.SetCellType(m_nMailIndex);
		cell.UseThemes(true);
		CUGCTMail::SetString(item, 0, 18, &cell, this);
		OnRowSizing(18,&height);
		SetRowHeight(18,height);
	}
}

int CCellTypeOutlook::OnCellTypeNotify(long ID,int col,long row,long msg,long param)
{
	if(ID == m_nMailIndex)
	{
		switch(msg)
		{
		case 0: // Show flag menu
			{
				POINT * pos = (POINT*) param;

				COXBitmapMenu menu;
				menu.LoadMenu(IDR_CONTEXTFLAGS);
				CMenu* pMenuPopup = menu.GetSubMenu(0);

				int defaultFlagIndex = m_mail.GetDefaultFlagIndex();

				CMenu* pMenuDefault = menu.GetSubMenu(0);

				pMenuDefault->RemoveMenu((defaultFlagIndex ==1 ) ? IDD_DEFAULTRED : IDD_DEFAULTSELRED, MF_BYCOMMAND);
				pMenuDefault->RemoveMenu((defaultFlagIndex ==2 ) ? IDD_DEFAULTBLUE : IDD_DEFAULTSELBLUE, MF_BYCOMMAND);
				pMenuDefault->RemoveMenu((defaultFlagIndex ==3 ) ? IDD_DEFAULTYELLOW : IDD_DEFAULTSELYELLOW, MF_BYCOMMAND);
				pMenuDefault->RemoveMenu((defaultFlagIndex ==4 ) ? IDD_DEFAULTGREEN : IDD_DEFAULTSELGREEN, MF_BYCOMMAND);
				pMenuDefault->RemoveMenu((defaultFlagIndex ==5 ) ? IDD_DEFAULTORANGE : IDD_DEFAULTSELORANGE, MF_BYCOMMAND);
				pMenuDefault->RemoveMenu((defaultFlagIndex ==6 ) ? IDD_DEFAULTPURPLE : IDD_DEFAULTSELPURPLE, MF_BYCOMMAND);
		
				m_lastMenuRow = row;

				POINT p = *pos;

				ClientToScreen(&p);

				pMenuPopup->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, AfxGetMainWnd());
			}
			break;
		case 1: // Show mail menu
			{
				POINT * pos = (POINT*) param;

				COXBitmapMenu menu;
				menu.LoadMenu(IDR_CONTEXTMAIL);
				CMenu* pMenuPopup = menu.GetSubMenu(0);

				m_lastMenuRow = row;

				CUGCell cell;
				GetCell(0, m_lastMenuRow, &cell);

				CUGCTMail::mailItem item = CUGCTMail::ParseString(&cell);

				if (item.isRead)
				{
					pMenuPopup->ModifyMenu(0, MF_BYPOSITION | MF_STRING, ID_CHANGEREAD, _T("Mark as &Unread"));
				}

				POINT p = *pos;

				ClientToScreen(&p);

				pMenuPopup->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, AfxGetMainWnd());
			}
			break;
		case 2: // The flag has been changed
			{
				if (m_mailSort.GetSortOrder() == CUGCTMailSort::sortByFlag)
				{
					DoSort();
				}
			}
			break;
		}
	}
	else if (ID == m_nMailSortIndex)
	{
		switch(msg)
		{
			// Show menu for sorting
		case 0:
			{
				POINT * pos = (POINT*) param;

				COXBitmapMenu menu;
				menu.LoadMenu(IDR_CONTEXTSORT);
				CMenu* pMenuPopup = menu.GetSubMenu(0);

				POINT p = *pos;

				ClientToScreen(&p);

				pMenuPopup->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, AfxGetMainWnd());

			}
			break;
			// The sort order has reversed.
		case 1:
			{
				DoSort();
			}
			break;
		}
	}
	else if (ID == m_nExpandIndex)
	{
		m_lastMenuRow = row;

		POINT * pos = (POINT*) param;

		COXBitmapMenu menu;
		menu.LoadMenu(IDR_CONTEXTGROUP);
		CMenu* pMenuPopup = menu.GetSubMenu(0);

		POINT p = *pos;

		ClientToScreen(&p);

		pMenuPopup->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, AfxGetMainWnd());
	}

	return TRUE;
}

void CCellTypeOutlook::SetFlag(int index)
{
	CUGCell cell;
	GetCell(0, m_lastMenuRow, &cell);

	if (cell.GetCellType() == m_nMailIndex)
	{
		CUGCTMail::mailItem item = CUGCTMail::ParseString(&cell);

		item.rightIcon = index;

		CUGCTMail::SetString(item, 0, m_lastMenuRow, &cell, this);

		if (m_mailSort.GetSortOrder() == CUGCTMailSort::sortByFlag)
		{
			DoSort();
		}

		this->RedrawAll();
	}
}

void CCellTypeOutlook::SetDefaultFlag(int index)
{
	m_mail.SetDefaultFlagIndex(index);
}

void CCellTypeOutlook::ChangeReadFlag()
{
	CUGCell cell;
	GetCell(0, m_lastMenuRow, &cell);

	if (cell.GetCellType() == m_nMailIndex)
	{

		CUGCTMail::mailItem item = CUGCTMail::ParseString(&cell);

		item.isRead = !item.isRead;

		if (item.isRead)
		{
			if (item.leftIcon == 1) item.leftIcon = 0;
		}
		else
		{
			m_bMarkedAsUnread = true;
			if (item.leftIcon == 0) item.leftIcon = 1;
		}

		CUGCTMail::SetString(item, 0, m_lastMenuRow, &cell, this);

		this->RedrawAll();
	}
}

void CCellTypeOutlook::OnCellChange(int oldcol,int newcol,long oldrow,long newrow)
{
	CUGCell cell;
	GetCell(oldcol, oldrow, &cell);

	if (cell.GetCellType() == m_nMailIndex)
	{
		CUGCTMail::mailItem item = CUGCTMail::ParseString(&cell);

		if (!item.isRead && !m_bMarkedAsUnread)
		{
			item.isRead = true;
			if (item.leftIcon == 1) item.leftIcon = 0;
			CUGCTMail::SetString(item, oldcol, oldrow, &cell, this);
			this->RedrawAll();
		}

		m_bMarkedAsUnread = false;
	}

	GetCell(newcol, newrow, &cell);

	if (cell.GetCellType() == m_nMailIndex)
	{
		CUGCTMail::mailItem newItem = CUGCTMail::ParseString(&cell);

		if (m_pMailWindow)
		{
			m_pMailWindow->SetReadOnly(false);

			DWORD len = 255;
			TCHAR name[256];
			::GetUserName(name, &len);

#ifdef _UNICODE
			std::wstringstream ss;
#else
			std::ostringstream ss;
#endif
			ss << newItem.subject << std::endl;
			ss << newItem.sender << std::endl;
			ss << "To: " << name << std::endl;
			if (newItem.attachmentPath.GetLength())
			{
				ss << "Attachments: " << newItem.attachmentPath << std::endl;
			}

			ss << std::endl;

			ss << newItem.mail;

			m_pMailWindow->SetWindowText(ss.str().c_str());

			m_pMailWindow->SetSel(0, newItem.subject.GetLength());

			CHARFORMAT cf;
			cf.dwMask = CFM_STRIKEOUT|CFM_BOLD;
			cf.dwEffects = CFE_BOLD;
			m_pMailWindow->SetSelectionCharFormat(cf);

			m_pMailWindow->SetSel(newItem.subject.GetLength() + 1, m_pMailWindow->GetTextLength());
			cf.dwEffects = CFE_AUTOCOLOR;
			m_pMailWindow->SetSelectionCharFormat(cf);

			FINDTEXTEX fte;
			fte.chrg.cpMin = 0;
			fte.chrg.cpMax = -1;
			fte.lpstrText = _T("To:");

			cf.crTextColor = RGB(144, 153, 174);
			cf.dwEffects = cf.dwEffects & ~CFE_AUTOCOLOR;
			cf.dwMask = CFM_COLOR;

			int pos = m_pMailWindow->FindText(FR_WHOLEWORD, &fte);
			if (pos > -1)
			{
				m_pMailWindow->SetSel(pos, pos + 3);
				m_pMailWindow->SetSelectionCharFormat(cf);
			}

			fte.lpstrText = _T("Attachments:");
			pos = m_pMailWindow->FindText(FR_WHOLEWORD, &fte);
			if (pos > -1)
			{
				m_pMailWindow->SetSel(pos, pos + 12);
				m_pMailWindow->SetSelectionCharFormat(cf);
			}

			m_pMailWindow->SetReadOnly(true);
			m_pMailWindow->Invalidate(FALSE);
		}
	}
}

bool CCellTypeOutlook::GetShowGroups()
{
	return m_bShowGroups;
}

void CCellTypeOutlook::SetShowGroups(bool show)
{
	m_bShowGroups = show;
	m_expand.ShowGroups(m_bShowGroups);
	this->RedrawAll();
}

void CCellTypeOutlook::SetMailWindow(CRichEditCtrl* pWnd)
{
	m_pMailWindow = pWnd; 
	m_pMailWindow->SetFont(&m_medFont);
	m_pMailWindow->SetReadOnly();
}

int CCellTypeOutlook::OnHint(int col,long row,int section,CString * sHint)
{
	CUGCell cell;
	GetCell(col, row, &cell);

	if (cell.GetCellType() == m_nMailIndex)
	{
		CUGCTMail::mailItem item = CUGCTMail::ParseString(&cell);

#ifdef _UNICODE
		std::wstringstream ss;
#else
		std::ostringstream ss;
#endif
		CString date = item.date.Format("%a %c");
		ss << "Received: " << date.GetBuffer(date.GetLength()) << std::endl;
		date.ReleaseBuffer();

		if (!m_mail.DoesTextFit(item))
		{
			ss << "Subject: " << item.subject.GetBuffer(item.subject.GetLength()) << std::endl;
			item.subject.ReleaseBuffer();
		}

		if (item.size < 1024)
		{
			ss << "Size: " << item.size << " KB";
		}
		else
		{
			ss << "Size: " << (int)(item.size/1024) << " MB";
		}

		*sHint = ss.str().c_str();

		return TRUE;
	}
	else if (cell.GetCellType() == m_nExpandIndex)
	{
		CString sTip;

		switch(m_mailSort.GetSortOrder())
		{
		case CUGCTMailSort::sortByDate:
			sTip = _T("Date: ");
			break;
		case CUGCTMailSort::sortByConversation:
			sTip = _T("Conversation: ");
			break;
		case CUGCTMailSort::sortBySubject:
			sTip = _T("Subject: ");
			break;
		case CUGCTMailSort::sortByFrom:
			sTip = _T("From: ");
			break;
		case CUGCTMailSort::sortByFlag:
			sTip = _T("Flag Status: ");
			break;
		case CUGCTMailSort::sortBySize:
			sTip = _T("Size: ");
			break;
		case CUGCTMailSort::sortByAttachments:
			sTip = _T("Attachments: ");
			break;
		}

		sTip += cell.GetText();
		sTip += _T(" ");

		int items = 0;
		for(++row;row < GetNumberRows(); ++row)
		{
			GetCell(col, row, &cell);
			if (cell.GetCellType() == m_nExpandIndex)
			{
				break;
			}

			++items;
		}

		sHint->Format(_T("%s %d item%s"), sTip, items, (items == 1) ? _T("") : _T("s"));

		return TRUE;
	}

	return FALSE;
}

CUGCTMailSort::sortBy CCellTypeOutlook::GetSortBy()
{
	return this->m_mailSort.GetSortOrder();
}

void CCellTypeOutlook::SetSortBy(CUGCTMailSort::sortBy sort)
{
	m_mailSort.SetSortOrder(sort);
	DoSort();
	this->RedrawAll();
}

void CCellTypeOutlook::CollapseAll()
{
	m_expand.CollapseAll(0);
}

void CCellTypeOutlook::ExpandAll()
{
	m_expand.ExpandAll(0);
}

void CCellTypeOutlook::MarkAllRead()
{
	m_expand.MarkAllRead(0, m_lastMenuRow);
}

void CCellTypeOutlook::MarkAllUnread()
{
	m_expand.MarkAllUnread(0, m_lastMenuRow);
}

int CCellTypeOutlook::OnSortEvaluate( CUGCell* pCell1, CUGCell* pCell2, int iFlags )
{
	// Make sure the mail sort cell is always on top.
	if (pCell1->GetCellType() == m_nMailSortIndex) return -1;
	if (pCell2->GetCellType() == m_nMailSortIndex) return 1;

	if( iFlags & UG_SORT_DESCENDING )
	{
		CUGCell *ptr = pCell1;
		pCell1 = pCell2;
		pCell2 = ptr;
	}
	
	CUGCTMail::mailItem item1 = CUGCTMail::ParseString(pCell1);
	CUGCTMail::mailItem item2 = CUGCTMail::ParseString(pCell2);

	if (!item1.didParseOK)
	{
		return m_mailSort.GetIsSortAscending() ? 1 : -1;
	}
	if (!item2.didParseOK)
	{
		return m_mailSort.GetIsSortAscending() ? -1 : 1;
	}

	int retval = 0;

	// , sortByConversation, sortByTo, sortBySize, sortByType, sortByAttachments, sortByImportance, sortByCategories
	switch ( m_mailSort.GetSortOrder())
	{
	case CUGCTMailSort::sortByDate:
		{
			CTimeSpan span = item1.date - item2.date;

			if (span.GetTotalSeconds() < 0)
				retval = -1;
			else if (span.GetTotalSeconds() > 0)
				retval = 1;
		}
		break;
	case CUGCTMailSort::sortByFrom:
		{
			retval = _tcscmp(item2.sender.GetBuffer(item2.sender.GetLength()),
							item1.sender.GetBuffer(item1.sender.GetLength()));
			item1.sender.ReleaseBuffer();
			item2.sender.ReleaseBuffer();
		}
		break;
	case CUGCTMailSort::sortBySubject:
		{
			CString s1 = item1.subject;
			CString s2 = item2.subject;

			if (s1.GetLength() >= 3)
			{
				CString prefix1 = s1.Left(3);
				prefix1.MakeLower();
				if (prefix1 == _T("re:"))
				{
					s1 = s1.Right(s1.GetLength() - 3);
					s1.TrimLeft();
				}
			}

			if (s2.GetLength() >= 3)
			{
				CString prefix2 = s2.Left(3);
				prefix2.MakeLower();
				if (s2.Left(3) == _T("re:"))
				{
					s2 = s2.Right(s2.GetLength() - 3);
					s2.TrimLeft();
				}
			}

			retval = _tcscmp(s2.GetBuffer(s2.GetLength()),
							s1.GetBuffer(s1.GetLength()));
			s1.ReleaseBuffer();
			s2.ReleaseBuffer();
		}
		break;
	case CUGCTMailSort::sortByFlag:
		{
			// This changes the ordering so that unflagged and complete group together,
			// with the completed ones always on top.
			if( iFlags & UG_SORT_ASCENDING )
			{
				if (item1.rightIcon == 7) item1.rightIcon = 9;
				if (item2.rightIcon == 7) item2.rightIcon = 9;
			}

			if (item1.rightIcon == 0) item1.rightIcon = 8;
			if (item2.rightIcon == 0) item2.rightIcon = 8;
			retval = item2.rightIcon - item1.rightIcon;
		}
		break;
	case CUGCTMailSort::sortBySize:
		retval = item1.size - item2.size;
		break;
	case CUGCTMailSort::sortByAttachments:
		retval = item1.attachmentPath.GetLength() - item2.attachmentPath.GetLength();
		break;
	}

	return retval;
}

void CCellTypeOutlook::DoSort()
{
	// Make sure they are all expanded first.
	m_expand.ExpandAll(0);

	// First remove the header cells
	CUGCell cell;
	const int rowCount = GetNumberRows();

	int rowsDeleted = 0;

	for(int row=0;row<rowCount;++row)
	{
		GetCell(0, row, &cell);

		if (cell.GetCellType() == m_nExpandIndex)
		{
			this->DeleteCell(0, row);
			-- row;
			++rowsDeleted;
		}
	}

	SortBy(0, (m_mailSort.GetIsSortAscending() ? UG_SORT_ASCENDING : UG_SORT_DESCENDING));

	this->SetNumberRows(m_GI->m_numberRows - rowsDeleted);

	switch(m_mailSort.GetSortOrder())
	{
		case CUGCTMailSort::sortByFlag:
			{
				InsertHeadersByFlag();
				break;
			}
		case CUGCTMailSort::sortByDate:
			{
				InsertHeadersByDate();
				break;
			}
		case CUGCTMailSort::sortBySubject:
		case CUGCTMailSort::sortByFrom:
		case CUGCTMailSort::sortByConversation:
			{
				InsertHeadersByStringProperty();
				break;
			}
		case CUGCTMailSort::sortBySize:
			{
				InsertHeadersBySize();
				break;
			}
		case CUGCTMailSort::sortByAttachments:
			{
				InsertHeadersByAttachments();
				break;
			}
			
	}

	SetShowGroups(m_bShowGroups);
	m_expand.ResetCache();
}

void CCellTypeOutlook::InsertHeadersByFlag()
{
	CUGCell cell;

	int flagIndex = -1;

	for(int row=0;row<GetNumberRows();++row)
	{
		GetCell(0, row, &cell);

		if (cell.GetCellType() == m_nMailIndex)
		{
			CUGCTMail::mailItem item = CUGCTMail::ParseString(&cell);

			// Unflagged and complete sort together and show together
			if ((item.rightIcon == 7 && flagIndex == 0) ||
				(item.rightIcon == 0 && flagIndex == 7))
			{
				continue;
			}

			if (item.rightIcon != flagIndex)
			{
				InsertRow(row);
				GetCell(0, row, &cell);
				cell.SetCellType(m_nExpandIndex);
				int height = GetRowHeight(row);
				SetRowHeight(GetNumberRows()-1, height);

				switch(item.rightIcon)
				{
				case 0:
				case 7:
					cell.SetText(_T("Unflagged"));
					break;
				case 1:
					cell.SetText(_T("Red Flag"));
					break;
				case 2:
					cell.SetText(_T("Blue Flag"));
					break;
				case 3:
					cell.SetText(_T("Yellow Flag"));
					break;
				case 4:
					cell.SetText(_T("Green Flag"));
					break;
				case 5:
					cell.SetText(_T("Orange Flag"));
					break;
				case 6:
					cell.SetText(_T("Purple Flag"));
					break;
				}

				flagIndex = item.rightIcon;

				SetCell(0, row, &cell);
			}
		}
	}
}

void CCellTypeOutlook::InsertHeadersByDate()
{
	CUGCell cell;

	time_t ltime;
	time(&ltime);

	CTime dateNow(ltime);

	CTime start;

	bool firstPass = true;

	for(int row=0;row<GetNumberRows();++row)
	{
		GetCell(0, row, &cell);

		if (cell.GetCellType() == m_nMailIndex)
		{
			CUGCTMail::mailItem item = CUGCTMail::ParseString(&cell);
		
			CTimeSpan span = start - item.date;
		
			if (span.GetDays() != 0 || firstPass || item.date.GetDay() != start.GetDay())
			{
				start = CTime(item.date.GetYear(), item.date.GetMonth(), item.date.GetDay(), 0, 0, 0);
				InsertRow(row);
				GetCell(0, row, &cell);
				cell.SetCellType(m_nExpandIndex);
				int height = GetRowHeight(row);
				SetRowHeight(GetNumberRows()-1, height);

				CTime dt (item.date.GetYear(), item.date.GetMonth(), item.date.GetDay(), dateNow.GetHour(), dateNow.GetMinute(), dateNow.GetSecond());
				CTimeSpan daysSinceToday = dateNow - dt;

				switch(daysSinceToday.GetDays())
				{
				case 0:
					cell.SetText(_T("Today"));
					break;
				case 1:
					cell.SetText(_T("Yesterday"));
					break;
				default:
					cell.SetText(item.date.Format(_T("%B %d, %Y")));
					break;
				}
			
				SetCell(0, row, &cell);
				firstPass = false;
			}
		}
	}
}

void CCellTypeOutlook::InsertHeadersByStringProperty()
{
	CUGCell cell;

	CString value = "";

	bool firstPass = true;
	
	for(int row=0;row<GetNumberRows();++row)
	{
		GetCell(0, row, &cell);

		if (cell.GetCellType() == m_nMailIndex)
		{
			CUGCTMail::mailItem item = CUGCTMail::ParseString(&cell);
		
			CString newVal;

			switch(m_mailSort.GetSortOrder())
			{
			case CUGCTMailSort::sortByFrom:
				newVal = item.sender;
				break;
			case CUGCTMailSort::sortByConversation:
			case CUGCTMailSort::sortBySubject:
				newVal = item.subject;
				break;
			}

			if (newVal != value || firstPass)
			{
				firstPass = false;
				value = newVal;

				InsertRow(row);
				GetCell(0, row, &cell);
				cell.SetCellType(m_nExpandIndex);
				int height = GetRowHeight(row);
				SetRowHeight(GetNumberRows()-1, height);
				cell.SetText(newVal);
				SetCell(0, row, &cell);
			}
		}
	}
}

void CCellTypeOutlook::InsertHeadersBySize()
{
	const int mailEnormous = 6;
	const int mailHuge = 5;
	const int mailVeryLarge = 4;
	const int mailLarge = 3;
	const int mailMedium = 2;
	const int mailSmall = 1;
	const int mailTiny = 0;

	CUGCell cell;

	int size = -1;

	for(int row=0;row<GetNumberRows();++row)
	{
		GetCell(0, row, &cell);

		if (cell.GetCellType() == m_nMailIndex)
		{
			CUGCTMail::mailItem item = CUGCTMail::ParseString(&cell);

			int thisSize = mailTiny;

			if (item.size > 5192)
				thisSize = mailEnormous;
			else if (item.size > 1024)
				thisSize = mailHuge;
			else if (item.size > 500)
				thisSize = mailVeryLarge;
			else if (item.size > 100)
				thisSize = mailLarge;
			else if (item.size > 25)
				thisSize = mailMedium;
			else if (item.size > 10)
				thisSize = mailSmall;

			if (size != thisSize)
			{
				size = thisSize;

				InsertRow(row);
				GetCell(0, row, &cell);
				cell.SetCellType(m_nExpandIndex);
				int height = GetRowHeight(row);
				SetRowHeight(GetNumberRows()-1, height);

				switch(size)
				{
				case mailEnormous:
					cell.SetText(_T("Enormous (> 5 MB)"));
					break;
				case mailHuge:
					cell.SetText(_T("Huge (1-5 MB)"));
					break;
				case mailVeryLarge:
					cell.SetText(_T("Very Large (500KB - 1 MB)"));
					break;
				case mailLarge:
					cell.SetText(_T("Large (100 - 500 KB)"));
					break;
				case mailMedium:
					cell.SetText(_T("Medium (25 - 100 KB)"));
					break;
				case mailSmall:
					cell.SetText(_T("Small (10 - 25 KB)"));
					break;
				case mailTiny:
					cell.SetText(_T("Tiny (< 10 KB"));
					break;
				}
				SetCell(0, row, &cell);
			}
		}
	}
}

void CCellTypeOutlook::InsertHeadersByAttachments()
{
	bool doneAttachments = false;
	bool doneNoAttachments = false;
	
	for(int row=0;row<GetNumberRows();++row)
	{
		CUGCell cell;
		GetCell(0, row, &cell);
		
		if (cell.GetCellType() == m_nMailIndex)
		{
			CUGCTMail::mailItem item = CUGCTMail::ParseString(&cell);

			if (item.attachmentPath.GetLength() && !doneAttachments)
			{
				doneAttachments = true;
				InsertRow(row);
				GetCell(0, row, &cell);
				cell.SetCellType(m_nExpandIndex);
				int height = GetRowHeight(row);
				SetRowHeight(GetNumberRows()-1, height);
				cell.SetText(_T("With Attachments"));
				SetCell(0, row, &cell);
			}
			
			if (!item.attachmentPath.GetLength() && !doneNoAttachments)
			{
				doneNoAttachments = true;
				InsertRow(row);
				GetCell(0, row, &cell);
				cell.SetCellType(m_nExpandIndex);
				int height = GetRowHeight(row);
				SetRowHeight(GetNumberRows()-1, height);
				cell.SetText(_T("No Attachments"));
				SetCell(0, row, &cell);
			}

			if (doneNoAttachments && doneAttachments)
			{
				break;
			}
		}
	}
}

void CCellTypeOutlook::OnSize(UINT nSide, int cx, int cy)
{
	this->SetColWidth(0, cx - m_GI->m_vScrollWidth);
}
