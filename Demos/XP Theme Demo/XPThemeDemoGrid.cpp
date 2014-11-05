// XPThemeDemoGrid.cpp: implementation of the CXPThemeDemoGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "XP Theme Demo.h"
#include "XPThemeDemoGrid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MSG_USE_THEMES				15101
#define MSG_DONT_USE_THEMES			15102
#define MSG_USE_THEMES_ALL			15103
#define MSG_DONT_USE_THEMES_ALL		15104


BEGIN_MESSAGE_MAP(CXPThemeDemoGrid,CUGCtrl)
	//{{AFX_MSG_MAP(CXPThemeDemoGrid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXPThemeDemoGrid::CXPThemeDemoGrid()
{

}

CXPThemeDemoGrid::~CXPThemeDemoGrid()
{

}


/***************************************************
OnSetup
	This function is called just after the grid window 
	is created or attached to a dialog item.
	It can be used to initially setup the grid
****************************************************/
void CXPThemeDemoGrid::OnSetup()
{
	

	CUGCell cell;
	int rows,cols;
	int row;

	//setup the fonts
	m_defFont.CreateFont( 14, 0, 0, 0, 500, 0, 0, 0, 0, 0, 0, 0, 0, _T( "Arial" ) );
	m_boldFont.CreateFont( 14, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, _T( "MS Sans Serif" ) );
	m_smFont.CreateFont( 10, 0, 0, 0, 500, 0, 0, 0, 0, 0, 0, 0, 0, _T( "Arial" ) );	
	m_medFont.CreateFont( 16, 0, 0, 0, 500, 0, 0, 0, 0, 0, 0, 0, 0, _T( "MS Sans Serif" ) );
	m_medBoldFont.CreateFont( 16, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, _T( "MS Sans Serif" ) );
	m_lrgFont.CreateFont( 20, 0, 0, 0, 600, 0, 0, 0, 0, 0, 0, 0, 0, _T( "Times New Roman" ) );	
	SetDefFont( &m_defFont );

	//setup the bitmaps
//	m_noteBitmap.LoadBitmap(MAKEINTRESOURCE(IDB_NOTEBITMAP));
//	m_folderBitmap.LoadBitmap(MAKEINTRESOURCE(IDB_FOLDERBITMAP));


	//setup the grid widths and heights
	SetSH_Width( 105 );
	
	SetNumberCols( NUM_COLS );
	SetNumberRows( NUM_ROWS );

	SetDoubleBufferMode(TRUE);
	this->SetUserSizingMode(2);

	GetHeadingDefault(&cell);
	cell.SetFont(&m_medBoldFont);
	SetHeadingDefault(&cell);

	SetColWidth(0,30);

	this->SetVScrollMode(UG_SCROLLTRACKING);

	CUGEdit* editClass = (CUGEdit*)this->GetEditClass();
	editClass->SetAutoSize(FALSE);


	//SETUP ALL OF THE CELL TYPES

	//Radio button cell type
	m_nRadioIndex = AddCellType(&m_radio);
	//Date Time Picker cell type
	m_nDateTimeIndex = AddCellType(&m_dateTime);
	//Push Button cell type
	m_nButtonIndex = AddCellType(&m_button);
	//Ellipsis Button cell type
	m_nEllipsisIndex = AddCellType(&m_ellipsis);
	//Spin Button cell type
	m_nSpinIndex = AddCellType(&m_spin);
	//Slider cell type
	m_nSliderIndex = AddCellType(&m_slider);
	//Sort Arrow cell type
	m_nSortArrowIndex = AddCellType(&m_sortArrow);
	//Progress bar cell types
	m_nProgressIndex = AddCellType(&m_progress);
	m_nAdvProressIndex1 = AddCellType(&m_advProress1);
	m_nAdvProressIndex2 = AddCellType(&m_advProress2);
	m_nAdvProressIndex3 = AddCellType(&m_advProress3);
	//Multi-font cell type
	m_nMultiFontIndex = AddCellType(&m_multiFont);
	//Auto-font cell type
	m_nAutoFontIndex = AddCellType(&m_autoFont);
	//Note cell type
	m_nNoteIndex = AddCellType(&m_note);
	//Labeled cell type
	m_nLabeledIndex = AddCellType(&m_labeled);
	//Marquee cell type
	m_nMarqueeIndex = AddCellType(&m_marquee);
	//Pie Chart cell type
	m_nPieChartIndex = AddCellType(&m_pieChart);


	//STANDARD ====================================================
	{
		row = STANDARD_ROW;
		SetupSection(row, "Standard");
		SetRowHeight(row+1,10);
		SetRowHeight(row+2,30);
		SetRowHeight(row+3,30);
		SetRowHeight(row+4,30);
			
		//cell.ClearAll();
		//cell.SetParam(CELLTYPE_IS_EDITABLE);
		//QuickSetRange(1,row+2,8,row+5,&cell);

		//default
		QuickSetText(1,row,"Basic");
		JoinCells(1,row,4,row);
		QuickSetText(1,row+2,"Text");
		QuickSetText(1,row+3,"Text");
		QuickSetFont(1,row+3,&m_medFont);
		QuickSetText(1,row+4,"Text");
		QuickSetFont(1,row+4,&m_lrgFont);
		QuickSetText(1,row+5,"Fully Supports Cell Overlapping");

		GetCell(1,row+6,&cell);
		cell.SetText("Full bitmap support");
//		cell.SetBitmap(&m_folderBitmap);
		SetCell(1,row+6,&cell);
		JoinCells(1,row+6,2,row+6);
		QuickSetText(3,row+6," ");
		
		QuickSetText(2,row+2,"Text");
		QuickSetTextColor(2,row+2,RGB(255,0,0));
		QuickSetText(2,row+3,"Text");
		QuickSetTextColor(2,row+3,RGB(0,255,0));
		QuickSetText(2,row+4,"Text");
		QuickSetBackColor(2,row+4,RGB(0,0,255));

		QuickSetText(3,row+2,"Left");
		QuickSetText(3,row+3,"Center");
		QuickSetAlignment(3,row+3,UG_ALIGNCENTER);
		QuickSetText(3,row+4,"Right");
		QuickSetAlignment(3,row+4,UG_ALIGNRIGHT);
		
		QuickSetText(4,row+2,"Left Bottom");
		QuickSetAlignment(4,row+2,UG_ALIGNCENTER|UG_ALIGNBOTTOM);
		QuickSetText(4,row+3,"Center");
		QuickSetAlignment(4,row+3,UG_ALIGNCENTER|UG_ALIGNVCENTER);
		QuickSetText(4,row+4,"Right Center");
		QuickSetAlignment(4,row+4,UG_ALIGNRIGHT|UG_ALIGNVCENTER);

		//multi-line
		QuickSetText(6,row,"Multi-line");
		QuickSetCellTypeEx(6,row+2,UGCT_NORMALMULTILINE);
		QuickSetText(6,row+2,"Fully Supports\nMulti-line Text");
		QuickSetCellTypeEx(6,row+3,UGCT_NORMALMULTILINE);
		QuickSetAlignment(6,row+3,UG_ALIGNCENTER);
		QuickSetText(6,row+3,"Multi\nline");
		QuickSetCellTypeEx(6,row+4,UGCT_NORMALMULTILINE);
		QuickSetAlignment(6,row+4,UG_ALIGNRIGHT);
		QuickSetText(6,row+4,"Multi\nline");
		
		//ellipsis
		QuickSetText(8,row,"Ellipsis");
		QuickSetCellTypeEx(8,row+2,UGCT_NORMALELLIPSIS);
		QuickSetText(8,row+2,"Shows Ellipsis if text is too long");
		QuickSetAlignment(8,row+2,UG_ALIGNTOP);

		QuickSetCellTypeEx(8,row+3,UGCT_NORMALELLIPSIS);
		QuickSetFont(8,row+3,&m_medFont);
		QuickSetText(8,row+3,"Shows Ellipsis if text is too long");
		QuickSetAlignment(8,row+3,UG_ALIGNVCENTER);

		QuickSetCellTypeEx(8,row+4,UGCT_NORMALELLIPSIS);
		QuickSetFont(8,row+4,&m_lrgFont);
		QuickSetText(8,row+4,"Shows Ellipsis if text is too long");
		QuickSetAlignment(8,row+4,UG_ALIGNBOTTOM);
	}


	//DROPLIST ====================================================
	{
		row = DROPLIST_ROW;
		SetupSection(row, "Droplist");
		SetRowHeight(row+1,10);
		SetRowHeight(row+5,24);

		//default
		QuickSetText(1,row,"Basic");
		cell.ClearAll();
		cell.SetCellType(UGCT_DROPLIST);
		QuickSetRange(1,row+2,1,row+5,&cell);

		QuickSetLabelText(1,row+2,"One\nTwo\nThree\n");
		QuickSetText(1,row+2,"One");
		QuickSetAlignment(1,row+3,UG_ALIGNCENTER|UG_ALIGNVCENTER);
		QuickSetLabelText(1,row+3,"One\nTwo\nThree\nFour\nFive\nSix\nSeven\nEight\nNine\nTen\nElevn\nTwelve\nThirteen\nFourteen\nFifteen\nSixteen\nSeventeen\nEighteen\nNineteen\nTwenty\n");
		QuickSetText(1,row+3,"Two");
		QuickSetFont(1,row+4,&m_medFont);
		QuickSetAlignment(1,row+4,UG_ALIGNRIGHT);
		QuickSetLabelText(1,row+4,"One\nTwo\nThree\nFour\nFive\n");
		QuickSetText(1,row+4,"Three");

		QuickSetLabelText(1,row+5,"Image\nBitmap\nGraphic\n");
		QuickSetText(1,row+5,"Image");
//		QuickSetBitmap(1,row+5,&m_noteBitmap);

		//hide button
		QuickSetText(3,row,"Hide");
		cell.ClearAll();
		cell.SetCellType(UGCT_DROPLIST);
		cell.SetCellTypeEx(UGCT_DROPLISTHIDEBUTTON);	
		QuickSetRange(3,row+2,3,row+4,&cell);

		QuickSetLabelText(3,row+2,"One\nTwo\nThree\n");
		QuickSetText(3,row+2,"One");
		QuickSetBackColor(3,row+3,RGB(0,255,0));
		QuickSetLabelText(3,row+3,"One\nTwo\nThree\nFour\nFive\nSix\nSeven\nEight\nNine\nTen\nElevn\nTwelve\nThirteen\nFourteen\nFifteen\nSixteen\nSeventeen\nEighteen\nNineteen\nTwenty\n");
		QuickSetText(3,row+3,"Two");
		QuickSetTextColor(3,row+4,RGB(255,0,0));
		QuickSetLabelText(3,row+4,"One\nTwo\nThree\nFour\nFive\n");
		QuickSetText(3,row+4,"Three");

		//dynamic load
		QuickSetText(5,row,"Dynamic");

		GetCell(5,row+2,&cell);
		cell.SetParam(DROPLIST_DYNAMIC_LOAD);
		cell.SetCellType(UGCT_DROPLIST);
		SetCell(5,row+2,&cell);

		GetCell(5,row+3,&cell);
		cell.SetParam(DROPLIST_DYNAMIC_LOAD2);
		cell.SetCellType(UGCT_DROPLIST);
		cell.SetText("Red");
		SetCell(5,row+3,&cell);

		//change
		QuickSetText(7,row,"Change");

		GetCell(7,row+2,&cell);
		cell.SetParam(DROPLIST_CHANGE_SELECTION);
		cell.SetCellType(UGCT_DROPLIST);
		cell.SetLabelText("1\n2\n3\n");
		cell.SetText("One");
		SetCell(7,row+2,&cell);

		GetCell(7,row+3,&cell);
		cell.SetParam(DROPLIST_CHANGE_SELECTION2);
		cell.SetCellType(UGCT_DROPLIST);
		cell.SetText("<state>");
		SetCell(7,row+3,&cell);

		//editable
		QuickSetText(9,row,"Editable");

		GetCell(9,row+2,&cell);
		cell.SetLabelText("One\nTwo\nThree\n");
		cell.SetText("One");
		cell.SetCellType(UGCT_DROPLIST);
		cell.SetParam(CELLTYPE_IS_EDITABLE);
		SetCell(9,row+2,&cell);

	}

	//CHECKBOX ====================================================
	{
		row = CHECKBOX_ROW;
		SetupSection(row, "Checkbox");
		SetRowHeight(row+1,10);
		SetRowHeight(row+4,30);
		SetRowHeight(row+7,30);
		SetRowHeight(row+8,30);

		//basic styles
		QuickSetText(1,row,"Basic Styles");
		JoinCells(1,row,4,row);

		row+=2;

			
		int checkBoxLookFlags[] = {UGCT_CHECKBOXFLAT,UGCT_CHECKBOX3DRECESS,UGCT_CHECKBOX3DRAISED};
		int checkBoxFlags[] = {0,UGCT_NORMALMULTILINE, UGCT_CHECKBOXCHECKMARK,
			UGCT_CHECKBOX3STATE,UGCT_CHECKBOXUSEALIGN,0};
		LPSTR checkBoxTitles[] = {"Normal","MultiLine","Checkmark","Tri-State","Alignment",""};
		int checkBoxAlign[] = {UG_ALIGNLEFT,UG_ALIGNCENTER,UG_ALIGNRIGHT};
		int checkBoxAlign2[] = {UG_ALIGNTOP,UG_ALIGNVCENTER,UG_ALIGNBOTTOM};

		QuickSetText(2,row,"Flat");
		QuickSetFont(2,row,&m_boldFont);
		QuickSetText(3,row,"3D Recess");
		QuickSetFont(3,row,&m_boldFont);
		QuickSetText(4,row,"3D Raised");
		QuickSetFont(4,row,&m_boldFont);

		for(rows = 0; rows< sizeof(checkBoxFlags)/sizeof(int*); rows++){
			QuickSetText(1,row+1+ rows,checkBoxTitles[rows]);
			QuickSetFont(1,row+1+ rows,&m_boldFont);

			for(cols = 0; cols < sizeof(checkBoxLookFlags)/sizeof(int*); cols++){			
				QuickSetLabelText(cols+2,row+1+ rows,"Checkbox");
				if(rows == 1)
					QuickSetLabelText(cols+2,row+1+ rows,"Checkbox\nText");
				QuickSetCellType(cols+2,row+1+rows,UGCT_CHECKBOX);			
				QuickSetCellTypeEx(cols+2,row+1+rows,
					checkBoxLookFlags[cols]|
					checkBoxFlags[rows]);
				if(rows == 4 || rows == 5){
					QuickSetLabelText(cols+2,row+1+ rows,"Text");
					QuickSetAlignment(cols+2,row+1+rows,checkBoxAlign[cols]|checkBoxAlign2[cols]);
				}
			}
		}

		//More styles
		row -= 2;
		QuickSetText(6,row,"More Styles");
		JoinCells(6,row,7,row);

		QuickSetCellType(6,row+2,UGCT_CHECKBOX);			
		QuickSetCellTypeEx(6,row+2,UGCT_CHECKBOXCHECKMARK|UGCT_CHECKBOX3DRAISED|UGCT_CHECKBOX3STATE);
		QuickSetBackColor(6,row+2,GetSysColor(COLOR_BTNFACE));
		QuickSetLabelText(6,row+2,"Checkbox");

		QuickSetCellType(6,row+3,UGCT_CHECKBOX);			
		QuickSetCellTypeEx(6,row+3,UGCT_CHECKBOX3DRECESS);
		QuickSetFont(6,row+3,&m_medFont);
		QuickSetLabelText(6,row+3,"Fonts");
		QuickSetTextColor(6,row+3,RGB(0,255,0));
		QuickSetAlignment(6,row+3,UG_ALIGNCENTER);
		GetCell(6,row+3,&cell);
		cell.SetParam(CHECKBOX_CHANGEFONT);
		SetCell(6,row+3,&cell);

		GetCell(6,row+4,&cell);
		cell.SetText("1");
		cell.SetLabelText("A Long Line Of Text");
		cell.SetCellTypeEx(UGCT_NORMALELLIPSIS);
		cell.SetCellType(UGCT_CHECKBOX);
		cell.SetAlignment(UG_ALIGNVCENTER);
		SetCell(6,row+4,&cell);

		GetCell(6,row+4,&cell);
		cell.SetText("1");
		cell.SetLabelText("Image");
		cell.SetCellType(UGCT_CHECKBOX);
//		cell.SetBitmap(&m_folderBitmap);
		SetCell(6,row+4,&cell);

	}
	
	//RADIO BUTTON ====================================================
	{
		row = RADIOBTN_ROW;
		SetupSection(row, "Radio Button");
		SetRowHeight(row+1,10);
		SetRowHeight(row+2,48);
		SetRowHeight(row+3,63);

		//Default
		QuickSetText(1,row,"Basic");

		GetCell(1,row+2,&cell);
		cell.SetText("1");
		cell.SetLabelText("One\nTwo\nThree\n");
		cell.SetCellType(m_nRadioIndex);
		SetCell(1,row+2,&cell);

		GetCell(1,row+3,&cell);
		cell.SetText("1");
		cell.SetAlignment(UG_ALIGNCENTER);
		cell.SetLabelText("Mr.\nMrs.\nMs.\nDr.\n");
		cell.SetCellType(m_nRadioIndex);
		SetCell(1,row+3,&cell);

		GetCell(2,row+2,&cell);
		cell.SetText("1");
		cell.SetAlignment(UG_ALIGNRIGHT);
		cell.SetLabelText("Apple\nOrange\n");
		cell.SetFont(&m_medFont);
		cell.SetCellType(m_nRadioIndex);
		SetCell(2,row+2,&cell);

		GetCell(2,row+3,&cell);
		cell.SetText("1");
		cell.SetAlignment(UG_ALIGNRIGHT);
		cell.SetLabelText("Toronto\nNew York\nLosAngles\nSeatle\n");
		cell.SetBackColor(RGB(222,222,222));
		cell.SetTextColor(RGB(0,0,222));
		cell.SetCellType(m_nRadioIndex);
		SetCell(2,row+3,&cell);
	}

	//DATE TIME ====================================================
	{
		row = DATETIME_ROW;
		SetupSection(row, "Date Time");
		SetRowHeight(row+1,10);

		//basic
		QuickSetText(1,row,"Basic");

		GetCell(1,row+2,&cell);
		cell.SetText(COleDateTime::GetCurrentTime().Format(VAR_DATEVALUEONLY));
		cell.SetCellType(m_nDateTimeIndex);
		SetCell(1,row+2,&cell);

		GetCell(1,row+3,&cell);
		cell.SetText(COleDateTime::GetCurrentTime().Format(VAR_DATEVALUEONLY));
		cell.SetAlignment(UG_ALIGNRIGHT);
		cell.SetCellType(m_nDateTimeIndex);
		SetCell(1,row+3,&cell);


		//Editable
		QuickSetText(3,row,"Editable");

		GetCell(3,row+2,&cell);
		cell.SetText(COleDateTime::GetCurrentTime().Format(VAR_DATEVALUEONLY));
		cell.SetLabelText("CELLTYPE_IS_EDITABLE");
		cell.SetCellType(m_nDateTimeIndex);
		SetCell(3,row+2,&cell);

		GetCell(3,row+3,&cell);
		cell.SetText(COleDateTime::GetCurrentTime().Format(VAR_DATEVALUEONLY));
		cell.SetAlignment(UG_ALIGNRIGHT);
		cell.SetLabelText("CELLTYPE_IS_EDITABLE");
		cell.SetCellType(m_nDateTimeIndex);
		SetCell(3,row+3,&cell);

		//Advanced
		QuickSetText(5,row,"Advanced");

		GetCell(5,row+2,&cell);
		cell.SetText(COleDateTime::GetCurrentTime().Format(VAR_DATEVALUEONLY));
		//cell.SetParam(CELLTYPE_IS_EDITABLE);
		cell.SetCellType(m_nDateTimeIndex);
		cell.SetCellTypeEx(UGCT_DROPLISTHIDEBUTTON);
		SetCell(5,row+2,&cell);

		GetCell(5,row+3,&cell);
		cell.SetText(COleDateTime::GetCurrentTime().Format(VAR_DATEVALUEONLY));
		cell.SetAlignment(UG_ALIGNRIGHT);
		cell.SetCellType(m_nDateTimeIndex);
		SetCell(5,row+3,&cell);

		

	}

	//PUSH BUTTON ====================================================
	{
		row = PUSHBTN_ROW;
		SetupSection(row, "Push Button");
		SetRowHeight(row+1,10);
		SetRowHeight(row+3,30);

		//basic
		QuickSetText(1,row,"Basic");

		GetCell(1,row+2,&cell);
		cell.SetText("Button");
		cell.SetCellType(m_nButtonIndex);
		cell.SetCellTypeEx(UGCT_BUTTONNOFOCUS);
		cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
		SetCell(1,row+2,&cell);

		GetCell(1,row+3,&cell);
		cell.SetText("Button");
		cell.SetCellType(m_nButtonIndex);
		cell.SetCellTypeEx(UGCT_BUTTONNOFOCUS);
		cell.SetAlignment(UG_ALIGNCENTER|UG_ALIGNVCENTER);
		cell.SetFont(&m_boldFont);
		cell.SetTextColor(RGB(0,0,128));
		cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
		SetCell(1,row+3,&cell);

		GetCell(1,row+4,&cell);
		cell.SetText("Button");
		cell.SetCellType(m_nButtonIndex);
		cell.SetAlignment(UG_ALIGNRIGHT);
		cell.SetBackColor(RGB(100,100,220));
		SetCell(1,row+4,&cell);

		//More styles
		QuickSetText(3,row,"More Styles");
		JoinCells(3,row,4,row);

		GetCell(3,row+2,&cell);
		cell.SetText("Click Here For The Calculator");
		cell.SetCellType(m_nButtonIndex);
		cell.SetCellTypeEx(UGCT_BUTTONNOFOCUS|UGCT_NORMALELLIPSIS);
		cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
		cell.SetParam(BUTTON_CLICK1);
		SetCell(3,row+2,&cell);

		GetCell(3,row+3,&cell);
		cell.SetText("Multi\nLine");
		cell.SetCellType(m_nButtonIndex);
		cell.SetCellTypeEx(UGCT_BUTTONNOFOCUS|UGCT_NORMALMULTILINE);
		cell.SetAlignment(UG_ALIGNCENTER|UG_ALIGNVCENTER);
		cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
		cell.SetParam(BUTTON_CLICK2);
		SetCell(3,row+3,&cell);
		
	}

	//ELLIPSIS BUTTON ====================================================
	{
		row = ELLIPSIS_ROW;
		SetupSection(row, "Ellipsis Button");
		SetRowHeight(row+1,10);
		SetRowHeight(row+3,30);
	
		//CUGEllipsisType		m_ellipsis;
		//int					m_nEllipsisIndex;

		//basic
		QuickSetText(1,row,"Basic");

		GetCell(1,row+2,&cell);
		cell.SetText("Text");
		cell.SetCellType(m_nEllipsisIndex);
		SetCell(1,row+2,&cell);

		GetCell(1,row+3,&cell);
		cell.SetText("Text");
		cell.SetAlignment(UG_ALIGNCENTER|UG_ALIGNVCENTER);
		cell.SetTextColor(RGB(220,0,0));
		cell.SetCellType(m_nEllipsisIndex);
		SetCell(1,row+3,&cell);

		GetCell(1,row+4,&cell);
		cell.SetText("Text");
		cell.SetAlignment(UG_ALIGNRIGHT);
		cell.SetBackColor(RGB(220,240,240));
		cell.SetFont(&m_medBoldFont);
		cell.SetCellType(m_nEllipsisIndex);
		SetCell(1,row+4,&cell);

		//More styles
		QuickSetText(3,row,"More Styles");
		JoinCells(3,row,4,row);

		GetCell(3,row+2,&cell);
		cell.SetText("Run The Calculator");
		cell.SetCellType(m_nEllipsisIndex);
		cell.SetCellTypeEx(UGCT_NORMALELLIPSIS);
		cell.SetParam(ELLIPSISBUTTON_CLICK1);
		SetCell(3,row+2,&cell);

		GetCell(3,row+3,&cell);
		cell.SetText("Note\nPad");
		cell.SetCellType(m_nEllipsisIndex);
		cell.SetCellTypeEx(UGCT_NORMALMULTILINE);
		cell.SetParam(ELLIPSISBUTTON_CLICK2);
		SetCell(3,row+3,&cell);

		GetCell(3,row+4,&cell);
		cell.SetText("Raised");
		cell.SetCellType(m_nEllipsisIndex);
		cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
		cell.SetBorder(UG_BDR_RAISED);
		SetCell(3,row+4,&cell);

		GetCell(4,row+2,&cell);
		cell.SetText("Editable");
		cell.SetCellType(m_nEllipsisIndex);
		cell.SetParam(CELLTYPE_IS_EDITABLE);
		SetCell(4,row+2,&cell);

	}


	//SPIN BUTTON ====================================================
	{
		row = SPINBTN_ROW;
		SetupSection(row, "Spin Button");
		SetRowHeight(row+1,10);

		//	CUGSpinButtonType	m_spin;
		//	int					m_nSpinIndex;

		//basic
		QuickSetText(1,row,"Basic");
		JoinCells(1,row,2,row);

		GetCell(1,row+2,&cell);
		cell.SetText("1");
		cell.SetCellType(m_nSpinIndex);
		cell.SetParam(SPIN_TYPE1);
		SetCell(1,row+2,&cell);

		GetCell(1,row+3,&cell);
		cell.SetText("One");
		cell.SetParam(SPIN_TYPE2);
		cell.SetAlignment(UG_ALIGNCENTER);
		cell.SetCellType(m_nSpinIndex);
		SetCell(1,row+3,&cell);

		GetCell(2,row+2,&cell);
		cell.SetText("Mr");
		cell.SetParam(SPIN_TYPE3);
		cell.SetAlignment(UG_ALIGNRIGHT);
		cell.SetCellType(m_nSpinIndex);
		SetCell(2,row+2,&cell);

		GetCell(2,row+3,&cell);
		cell.SetParam(SPIN_TYPE4);
		cell.SetBackColor(RGB(255,0,0));
		cell.SetCellType(m_nSpinIndex);
		SetCell(2,row+3,&cell);

		//More Styles
		QuickSetText(4,row,"More Styles");
		JoinCells(4,row,5,row);

		GetCell(4,row+2,&cell);
		cell.SetText("A Long Piece of Text");
		cell.SetCellType(m_nSpinIndex);
		cell.SetParam(SPIN_TYPE5);
		cell.SetCellTypeEx(UGCT_NORMALELLIPSIS);
		SetCell(4,row+2,&cell);

		GetCell(4,row+3,&cell);
		cell.SetText("Editable");
		cell.SetParam(CELLTYPE_IS_EDITABLE);		
		cell.SetCellType(m_nSpinIndex);
		SetCell(4,row+3,&cell);

	}

	//SLIDER ====================================================
	{
		row = SLIDERS_ROW;
		SetupSection(row, "Slider");
		SetRowHeight(row+1,10);

		// CUGSliderType		m_slider;
		// int					m_nSliderIndex;

		//basic
		QuickSetText(1,row,"Basic");
		JoinCells(1,row,2,row);

		GetCell(1,row+2,&cell);
		cell.SetText("1");
		cell.SetCellType(m_nSliderIndex);
		SetCell(1,row+2,&cell);

		//advanced
		QuickSetText(3,row,"Advanced");
		JoinCells(3,row,2,row);

		GetCell(3,row+2,&cell);
		cell.SetText("30");
		cell.SetCellType(m_nSliderIndex);
		cell.SetParam(SLIDER_TYPE1);
		SetCell(3,row+2,&cell);

		GetCell(4,row+2,&cell);
		cell.SetText("0");
		cell.SetCellType(m_nSliderIndex);
		cell.SetParam(SLIDER_TYPE2);
		SetCell(4,row+2,&cell);

		GetCell(5,row+2,&cell);
		cell.SetText("0");
		cell.SetCellType(m_nSliderIndex);
		cell.SetParam(SLIDER_TYPE3);
		SetCell(5,row+2,&cell);

		GetCell(6,row+2,&cell);
		cell.SetText("0");
		cell.SetCellType(m_nSliderIndex);
		cell.SetParam(SLIDER_TYPE4);
		SetCell(6,row+2,&cell);

		GetCell(5, row+3, &cell);
		cell.UseThemes(false);
		SetCell(5, row+3, &cell);

		QuickSetBackColor(5,row+3,RGB(0,0,0));
	}

	//ARROW ====================================================
	{
		row = ARROWS_ROW;
		SetupSection(row, "Arrow");
		SetRowHeight(row+1,10);


		//basic
		QuickSetText(1,row,"Basic");
		JoinCells(1,row,4,row);

		GetCell(1,row+2,&cell);
		cell.SetCellType(UGCT_ARROW);
		cell.SetCellTypeEx(UGCT_ARROWLEFT);
		SetCell(1,row+2,&cell);

		GetCell(2,row+2,&cell);
		cell.SetCellType(UGCT_ARROW);
		cell.SetCellTypeEx(UGCT_ARROWRIGHT);
		SetCell(2,row+2,&cell);

		GetCell(3,row+2,&cell);
		cell.SetCellType(UGCT_ARROW);
		cell.SetCellTypeEx(UGCT_ARROWDRIGHT);
		SetCell(3,row+2,&cell);

		GetCell(4,row+2,&cell);
		cell.SetCellType(UGCT_ARROW);
		cell.SetCellTypeEx(UGCT_ARROWDLEFT);
		SetCell(4,row+2,&cell);

		//More Styles
		QuickSetText(6,row,"More Styles");
		JoinCells(6,row,8,row);

		GetCell(6,row+2,&cell);
		cell.SetCellType(UGCT_ARROW);
		cell.SetCellTypeEx(UGCT_ARROWLEFT);
		cell.SetBackColor(RGB(220,220,255));
		cell.SetTextColor(RGB(100,100,100));
		SetCell(6,row+2,&cell);

		GetCell(7,row+2,&cell);
		cell.SetCellType(UGCT_ARROW);
		cell.SetCellTypeEx(UGCT_ARROWRIGHT);
		cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
		cell.SetBorder(UG_BDR_RAISED);
		cell.SetTextColor(RGB(255,255,255));
		SetCell(7,row+2,&cell);

		GetCell(8,row+2,&cell);
		cell.SetCellType(UGCT_ARROW);
		cell.SetCellTypeEx(UGCT_ARROWDRIGHT);
		cell.SetBackColor(RGB(220,220,110));
		cell.SetBorder(UG_BDR_RECESSED);
		SetCell(8,row+2,&cell);
	}

	//SORT ARROW ====================================================
	{
		row = SORTARROW_ROW;
		SetupSection(row, "Sort Arrow");
		SetRowHeight(row+1,10);

		// CUGSortArrowType	m_sortArrow;
		// int				m_nSortArrowIndex;

		//basic
		QuickSetText(1,row,"Basic");
		JoinCells(1,row,2,row);

		GetCell(1,row+2,&cell);
		cell.SetCellType(m_nSortArrowIndex);
		cell.SetCellTypeEx(UGCT_SORTARROWUP);
		cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
		cell.SetBorder(UG_BDR_RAISED);
		cell.SetText("Sort Up");
		SetCell(1,row+2,&cell);

		GetCell(2,row+2,&cell);
		cell.SetCellType(m_nSortArrowIndex);
		cell.SetCellTypeEx(UGCT_SORTARROWUP);
		cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
		cell.SetBorder(UG_BDR_RAISED);
		cell.SetText("Sort Down");
		SetCell(2,row+2,&cell);

		//more styles
		QuickSetText(4,row,"More Styles");
		JoinCells(4,row,6,row);

		GetCell(4,row+2,&cell);
		cell.SetCellType(m_nSortArrowIndex);
		cell.SetCellTypeEx(UGCT_SORTARROWUP);
		cell.SetBackColor(RGB(0,0,220));
		cell.SetText("Text");
		cell.SetTextColor(RGB(255,255,255));
		cell.SetAlignment(UG_ALIGNCENTER);
		SetCell(4,row+2,&cell);

		GetCell(5,row+2,&cell);
		cell.SetCellType(m_nSortArrowIndex);
		cell.SetBorder(UG_BDR_RECESSED);
		cell.SetBackColor(RGB(0,220,220));
		cell.SetText("Text");
		cell.SetAlignment(UG_ALIGNRIGHT);
		cell.SetCellTypeEx(UGCT_SORTARROWUP);
		SetCell(5,row+2,&cell);
	}

	//PROGRESS ====================================================
	{
		row = PROGRESS_ROW;
		SetupSection(row, "Progress Bars");
		SetRowHeight(row+1,10);

		// CUGProgressType		m_progress;
		// int					m_nProgressIndex;
		// CUGAdvProgressType	m_advProress1;
		// int					m_nAdvProressIndex1;

		//basic
		QuickSetText(1,row,"Basic");
		JoinCells(1,row,2,row);

		GetCell(1,row+2,&cell);
		cell.SetCellType(m_nProgressIndex);
		cell.SetText("30");
		cell.SetParam(3);
		cell.UseThemes(true);
		SetCell(1,row+2,&cell);
		
		GetCell(1,row+3,&cell);
		cell.SetCellType(m_nProgressIndex);
		cell.SetHBackColor(RGB(255,0,0));
		cell.SetText("40");
		cell.SetParam(0);
		cell.UseThemes(true);
		cell.SetAlignment(UG_ALIGNCENTER|UG_ALIGNVCENTER);
		SetCell(1,row+3,&cell);

		GetCell(1,row+4,&cell);
		cell.SetCellType(m_nProgressIndex);
		cell.SetHBackColor(RGB(0,220,0));
		cell.SetText("60");
		cell.SetLabelText("Progress");
		cell.SetParam(5);
		cell.UseThemes(true);
		cell.SetAlignment(UG_ALIGNRIGHT|UG_ALIGNVCENTER);
		cell.SetCellTypeEx(UGCT_PROGRESSUSELABEL);
		SetCell(1,row+4,&cell);

		GetCell(1,row+5,&cell);
		cell.SetCellType(m_nProgressIndex);
		cell.SetHBackColor(RGB(100,0,0));
		cell.SetBackColor(RGB(250,250,220));
		cell.SetTextColor(RGB(0,0,100));
		cell.SetHTextColor(RGB(250,220,250));
		cell.SetText("70");
		cell.SetFont(&m_medBoldFont);
		cell.SetAlignment(UG_ALIGNCENTER|UG_ALIGNVCENTER);
		cell.SetParam(5);
		cell.UseThemes(true);
		SetCell(1,row+5,&cell);
		JoinCells(1,row+5,2,row+6);

		//More Styles
		QuickSetText(4,row,"More Styles");
		JoinCells(4,row,5,row);

		GetCell(4,row+2,&cell);
		cell.SetCellType(m_nAdvProressIndex1);
		cell.SetText("30");
		cell.SetParam(3);
		cell.UseThemes(true);
		SetCell(4,row+2,&cell);
		JoinCells(4,row+2,5,row+3);

		m_advProress2.SetNumberSections(100);
		for (int i=0;i<100;i++){
			m_advProress2.SetSectionPercent(i,i+1);
			m_advProress2.SetSectionColor(99-i,RGB(255-i, 200-i*2, 20+i));
		}
		GetCell(4,row+4,&cell);
		cell.SetCellType(m_nAdvProressIndex2);
		cell.SetText("30");
		cell.UseThemes(true);
		cell.SetParam(3);
		SetCell(4,row+4,&cell);
		JoinCells(4,row+4,5,row+6);

		m_advProress3.SetDirection(UGCT_PROGRESS_BOTTOM);
		GetCell(6,row+2,&cell);
		cell.SetCellType(m_nAdvProressIndex3);
		cell.UseThemes(true);
		cell.SetText("30");
		cell.SetParam(3);
		SetCell(6,row+2,&cell);
		JoinCells(6,row+2,6,row+6);
	}

	//MULTI-FONT ====================================================
	//	<:F,name,size,[weight]>
	//	<:C,r,g,b>
	{
		row = MULTIFONT_ROW;
		SetupSection(row, "Multi-Font");
		SetRowHeight(row+1,10);

		// CUGMultiFontType	m_multiFont;
		// int				m_nMultiFontIndex;

		//basic
		QuickSetText(1,row,"Basic");
		JoinCells(1,row,2,row);


		GetCell(1,row+2,&cell);
		cell.SetCellType(m_nMultiFontIndex);
		cell.SetText("<:F,Arial,12,300>sm <:F,Arial,16,600>Med <:F,Arial,20,900>Lrg <:F,Arial,24,1000>Huge!");
		cell.SetAlignment(UG_ALIGNBOTTOM);
		SetCell(1,row+2,&cell);
		JoinCells(1,row+2,2,row+3);

		GetCell(1,row+4,&cell);
		cell.SetCellType(m_nMultiFontIndex);
		cell.SetText("<:F,Arial,15,400>The<:F,Arial,15,800> <:C,255,0,0>Red<:C,0,0,0> <:F,Arial,15,400>Truck was <:F,Arial,24,1000>BIG");
		SetCell(1,row+4,&cell);
		JoinCells(1,row+4,2,row+5);

		GetCell(4,row+2,&cell);
		cell.SetCellType(m_nMultiFontIndex);
		cell.SetText("<:F,Arial,15,800>Value:<:C,0,0,220> <:F,Arial,15,400>643.54");
		SetCell(4,row+2,&cell);
		JoinCells(4,row+2,5,row+2);

		GetCell(4,row+3,&cell);
		cell.SetCellType(m_nMultiFontIndex);
		cell.SetText("<:F,Arial,15,800>Temp<:C,220,0,0> <:F,Arial,15,400>276K");
		cell.SetAlignment(UG_ALIGNRIGHT);
		SetCell(4,row+3,&cell);
		JoinCells(4,row+3,5,row+3);

		GetCell(4,row+4,&cell);
		cell.SetCellType(m_nMultiFontIndex);
		cell.SetText("<:C,0,100,0>8234<:F,Arial,15,800> <:C,0,0,0>Units");
		cell.SetBorder(UG_BDR_RAISED);
		cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
		cell.SetAlignment(UG_ALIGNVCENTER);
		SetCell(4,row+4,&cell);
		JoinCells(4,row+4,5,row+4);

		GetCell(4,row+5,&cell);
		cell.SetCellType(m_nMultiFontIndex);
		cell.SetText("<:F,Arial,12,300>Amount<:F,Arial,19,800> <:C,220,0,0>235,456.76");
		cell.SetBackColor(RGB(240,240,170));
		SetCell(4,row+5,&cell);
		JoinCells(4,row+5,5,row+5);
	}

	//AUTO-FONT ====================================================
	{
		row = AUTOFONT_ROW;
		SetupSection(row, "Auto Size Font");
		SetRowHeight(row+1,10);

		// CUGAutoFontType		m_autoFont;
		//int					m_nAutoFontIndex;

		//basic
		QuickSetText(1,row,"Basic");
		JoinCells(1,row,2,row);

		GetCell(1,row+2,&cell);
		cell.SetCellType(m_nAutoFontIndex);
		cell.SetText("Automatic Font Sizing");
		SetCell(1,row+2,&cell);
		JoinCells(1,row+2,2,row+2);

		GetCell(1,row+3,&cell);
		cell.SetCellType(m_nAutoFontIndex);
		cell.SetText("Auto-Font");
		cell.SetTextColor(RGB(0,0,255));
		cell.SetAlignment(UG_ALIGNVCENTER);
		SetCell(1,row+3,&cell);
		JoinCells(1,row+3,2,row+4);

		GetCell(3,row+2,&cell);
		cell.SetCellType(m_nAutoFontIndex);
		cell.SetText("Best-Fit Text");
		SetCell(3,row+2,&cell);

		GetCell(3,row+3,&cell);
		cell.SetCellType(m_nAutoFontIndex);
		cell.SetText("Size Me!");
		cell.SetBorder(UG_BDR_RAISED);
		cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
		cell.SetAlignment(UG_ALIGNVCENTER);
		SetCell(3,row+3,&cell);
	}

	//NOTE ====================================================
	{
		row = NOTE_ROW;
		SetupSection(row, "Note");
		SetRowHeight(row+1,10);


		// CUGNoteType			m_note;
		// int					m_nNoteIndex;

		//basic
		QuickSetText(1,row,"Basic");
		JoinCells(1,row,2,row);

		GetCell(1,row+2,&cell);
		cell.SetCellType(m_nNoteIndex);
		cell.SetText("A Note");
		cell.SetLabelText("Create a detailed note\r\nfor a cell that requires\r\nmore detailed information.");
		SetCell(1,row+2,&cell);

		GetCell(1,row+3,&cell);
		cell.SetCellType(m_nNoteIndex);
		cell.SetText("More Info");
		cell.SetAlignment(UG_ALIGNCENTER);
		cell.SetLabelText("The size of the note window is adjusted to fit the text within it.\r\n\r\nTherefore all of the details required can be fit inside of this note!!");
		SetCell(1,row+3,&cell);

		//more styles
		QuickSetText(3,row,"More Styles");
		JoinCells(3,row,4,row);		

		GetCell(3,row+2,&cell);
		cell.SetCellType(m_nNoteIndex);
		cell.SetText("Aother Note With Details");
		cell.SetCellTypeEx(UGCT_NORMALELLIPSIS);
		cell.SetLabelText("The note cell type can use all of the display styles supported by the Standard cell type.");
		cell.SetTextColor(RGB(255,0,0));
		SetCell(3,row+2,&cell);

		GetCell(3,row+3,&cell);
		cell.SetCellType(m_nNoteIndex);
		cell.SetText("Aother\nNote");
		cell.SetFont(&m_medFont);
		cell.SetCellTypeEx(UGCT_NORMALMULTILINE);
		cell.SetLabelText("The note cell type can use all of the display styles supported by the Standard cell type.");
		SetCell(3,row+3,&cell);
		JoinCells(3,row+3,3,row+4);

		GetCell(4,row+2,&cell);
		cell.SetCellType(m_nNoteIndex);
		cell.SetText("ABC 123");
		cell.SetCellTypeEx(UGCT_NORMALELLIPSIS);
		cell.SetLabelText("The note cell type can use all of the display styles supported by the Standard cell type.");
		cell.SetTextColor(RGB(255,255,255));
		cell.SetBorder(UG_BDR_RAISED);
		cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
		cell.SetAlignment(UG_ALIGNVCENTER);
		SetCell(4,row+2,&cell);
	}

	//LABELED ====================================================
	{
		row = LABELED_ROW;
		SetupSection(row, "Labeled");
		SetRowHeight(row+1,10);
		SetRowHeight(row+2,30);
		SetRowHeight(row+3,30);

		// CUGLabeledType		m_labeled;
		// int					m_nLabeled;

		//basic
		QuickSetText(1,row,"Basic");
		JoinCells(1,row,2,row);

		GetCell(1,row+2,&cell);
		cell.SetCellType(m_nLabeledIndex);
		cell.SetText("Smith");
		cell.SetLabelText("Last");
		cell.SetFont(&m_medBoldFont);
		SetCell(1,row+2,&cell);

		GetCell(1,row+3,&cell);
		cell.SetCellType(m_nLabeledIndex);
		cell.SetText("John");
		cell.SetLabelText("First");
		cell.SetFont(&m_medBoldFont);
		cell.SetTextColor(RGB(0,0,120));
		SetCell(1,row+3,&cell);

		//more styles
		QuickSetText(4,row,"More Styles");
		JoinCells(4,row,5,row);

		GetCell(4,row+2,&cell);
		cell.SetCellType(m_nLabeledIndex);
		cell.SetText("JohnSmith@domain.com");
		cell.SetFont(&m_medBoldFont);
		cell.SetBackColor(RGB(240,240,180));
		cell.SetCellTypeEx(UGCT_NORMALELLIPSIS);
		cell.SetLabelText("Email");
		SetCell(4,row+2,&cell);

		GetCell(4,row+3,&cell);
		cell.SetCellType(m_nLabeledIndex);
		cell.SetText("$128.95");
		cell.SetAlignment(UG_ALIGNRIGHT|UG_ALIGNVCENTER);
		cell.SetFont(&m_medBoldFont);
		cell.SetLabelText("Amount");
		SetCell(4,row+3,&cell);

		GetCell(5,row+2,&cell);
		cell.SetCellType(m_nLabeledIndex);
		cell.SetFont(&m_medBoldFont);
		cell.SetText("abcdefg");
		cell.SetLabelText("Editable");
		cell.SetCellTypeEx(UGCT_NORMALELLIPSIS);
		cell.SetParam(CELLTYPE_IS_EDITABLE);
		SetCell(5,row+2,&cell);
	}

	//MARQUEE ====================================================
	{
		row = MARQUEE_ROW;
		SetupSection(row, "Marquee");
		SetRowHeight(row+1,10);

		// CUGMarqueeType		m_marquee;
		// int					m_nMarqueeIndex;

		//basic
		QuickSetText(1,row,"Basic");
		JoinCells(1,row,2,row);

		GetCell(1,row+2,&cell);
		cell.SetCellType(m_nMarqueeIndex);
		cell.SetText("Scroll large amounts of text...");
		SetCell(1,row+2,&cell);
		
		GetCell(1,row+3,&cell);
		cell.SetCellType(m_nMarqueeIndex);
		cell.SetTextColor(RGB(220,0,0));
		cell.SetAlignment(UG_ALIGNVCENTER);
		cell.SetFont(&m_medFont);
		cell.SetText("  Great for real-time data");
		SetCell(1,row+3,&cell);

		//basic
		QuickSetText(3,row,"Advanced");

		GetCell(3,row+2,&cell);
		cell.SetCellType(m_nMarqueeIndex);
		cell.SetText("This one is editable...");
		cell.SetLabelText("CELLTYPE_IS_EDITABLE");
		SetCell(3,row+2,&cell);

		GetCell(3,row+3,&cell);
		cell.SetCellType(m_nMarqueeIndex);
		cell.SetText("Uses many standard display settings");
				cell.SetBorder(UG_BDR_RAISED);
		cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
		cell.SetAlignment(UG_ALIGNVCENTER);
		SetCell(3,row+3,&cell);
	
	}

	//PIE CHART ====================================================
	{
		row = PIECHART_ROW;
		SetupSection(row, "Pie Chart");
		SetRowHeight(row+1,10);
	
		// CUGPieChartType		m_pieChart;
		// int					m_nPieChartIndex;

		//basic
		QuickSetText(1,row,"Basic");
		JoinCells(1,row,3,row);

		GetCell(1,row+2,&cell);
		cell.SetCellType(m_nPieChartIndex);
		cell.SetCellTypeEx(UGCT_PIECHARTDATA);
		cell.SetText("40");
		cell.SetHBackColor(RGB(220,0,0));
		SetCell(1,row+2,&cell);

		GetCell(1,row+3,&cell);
		cell.SetCellType(m_nPieChartIndex);
		cell.SetCellTypeEx(UGCT_PIECHARTDATA);
		cell.SetText("70");
		cell.SetHBackColor(RGB(0,0,220));
		SetCell(1,row+3,&cell);

		GetCell(1,row+4,&cell);
		cell.SetCellType(m_nPieChartIndex);
		cell.SetCellTypeEx(UGCT_PIECHARTDATA);
		cell.SetHBackColor(RGB(0,220,0));
		cell.SetText("30");
		SetCell(1,row+4,&cell);

		GetCell(1,row+5,&cell);
		cell.SetCellType(m_nPieChartIndex);
		cell.SetCellTypeEx(UGCT_PIECHARTDATA);
		cell.SetHBackColor(RGB(0,220,220));
		cell.SetText("60");
		SetCell(1,row+5,&cell);

		GetCell(2,row+2,&cell);
		cell.SetCellType(m_nPieChartIndex);
		CString string;
		string.Format("1\n%ld\n1\n%ld\n",(long)row+2,(long)row+5);
		cell.SetText(string);
		SetCell(2,row+2,&cell);
		JoinCells(2,row+2,3,row+5);

		//advanced
		QuickSetText(5,row,"Editable Values");
		JoinCells(5,row,7,row);

		GetCell(5,row+2,&cell);
		cell.SetCellType(m_nPieChartIndex);
		cell.SetCellTypeEx(UGCT_PIECHARTDATA|UGCT_PIECHARTDATARIGHT|UGCT_NORMALLABELTEXT);
		cell.SetText("200");
		cell.SetLabelText("Widgets");	
		cell.SetHBackColor(RGB(200,200,0));
		cell.SetParam(CELLTYPE_IS_EDITABLE);
		cell.SetMask("999");
		SetCell(5,row+2,&cell);

		GetCell(5,row+3,&cell);
		cell.SetCellType(m_nPieChartIndex);
		cell.SetCellTypeEx(UGCT_PIECHARTDATA|UGCT_PIECHARTDATARIGHT|UGCT_NORMALLABELTEXT);
		cell.SetText("600");
		cell.SetLabelText("Stuff");	
		cell.SetHBackColor(RGB(200,0,200));
		cell.SetParam(CELLTYPE_IS_EDITABLE);
		cell.SetMask("999");
		SetCell(5,row+3,&cell);

		GetCell(5,row+4,&cell);
		cell.SetCellType(m_nPieChartIndex);
		cell.SetCellTypeEx(UGCT_PIECHARTDATA|UGCT_PIECHARTDATARIGHT|UGCT_NORMALLABELTEXT);
		cell.SetText("300");
		cell.SetLabelText("Things");	
		cell.SetHBackColor(RGB(0,50,240));
		cell.SetParam(CELLTYPE_IS_EDITABLE);
		cell.SetMask("999");
		SetCell(5,row+4,&cell);

		GetCell(5,row+5,&cell);
		cell.SetCellType(m_nPieChartIndex);
		cell.SetCellTypeEx(UGCT_PIECHARTDATA|UGCT_PIECHARTDATARIGHT|UGCT_NORMALLABELTEXT);
		cell.SetText("800");
		cell.SetLabelText("Gadgets");	
		cell.SetHBackColor(RGB(0,220,220));
		cell.SetParam(CELLTYPE_IS_EDITABLE);
		cell.SetMask("999");
		SetCell(5,row+5,&cell);

		GetCell(6,row+2,&cell);
		cell.SetCellType(m_nPieChartIndex);
		string.Format("5\n%ld\n5\n%ld\n",(long)row+2,(long)row+5);
		cell.SetText(string);
		SetCell(6,row+2,&cell);
		JoinCells(6,row+2,7,row+5);
	}

	SetMultiSelectMode(TRUE);
	EnableMenu( TRUE );
}


/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnDrawFocusRect(CDC *dc,RECT *rect){

	CUGCtrl::OnDrawFocusRect(dc,rect);
	return;

	CPen pen;
	rect->right -=2;
	rect->bottom -=2;
	pen.CreatePen(PS_DOT,1,RGB(10,10,10));
	CPen* oldPen = dc->SelectObject(&pen);
	dc->MoveTo(rect->left,rect->top);
	dc->LineTo(rect->right,rect->top);
	dc->LineTo(rect->right,rect->bottom);
	dc->LineTo(rect->left,rect->bottom);
	dc->LineTo(rect->left,rect->top);
	dc->SelectObject(oldPen);
	//this->DrawExcelFocusRect(dc,rect);
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnCellTypeNotify(long ID,int col,long row,long msg,long param){

	if(ID == UGCT_DROPLIST){
		return OnDropList(ID, col, row, msg, param);
	}
	if(ID == UGCT_CHECKBOX){
		return OnCheckbox(ID, col, row, msg, param);
	}
	if(ID == m_nRadioIndex){
	}
	if(ID == m_nDateTimeIndex){
		return OnDateTime(ID, col, row, msg, param);		
	}
	if(ID == m_nButtonIndex){
		return OnPushButton( ID, col, row, msg, param);
	}
	if(ID == m_nEllipsisIndex){
		return OnEllipsisButton( ID, col, row, msg, param);
	}
	if(ID == m_nSpinIndex){
		return OnSpinButton( ID, col, row, msg, param);
	}
	if(ID == m_nSliderIndex){
		return OnSlider( ID, col, row, msg, param);
	}

	return TRUE;
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnDropList(long ID,int col,long row,long msg,LONG_PTR param){

	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();

	if(nParam == DROPLIST_DYNAMIC_LOAD){
		if(msg == UGCT_DROPLISTSTART){		
			CStringList* pList = (CStringList*)param;
			CString string;
			pList->AddTail("Rnd # of Items");
			srand(GetTickCount());
			int len = rand()%20 + 1;
			for(int loop = 0 ;loop < len;loop++){
				string.Format("Dyn Item %d",loop);
				pList->AddTail(string);
			}
		}
	}
	if(nParam == DROPLIST_DYNAMIC_LOAD2){
		if(msg == UGCT_DROPLISTSTART){
			CStringList* pList = (CStringList*)param;
			CString string = cell.GetText();
			if(string != "Red")
				pList->AddTail("Red");
			if(string != "Green")
				pList->AddTail("Green");
			if(string != "Blue")
				pList->AddTail("Blue");
		}
	}
	if(nParam == DROPLIST_CHANGE_SELECTION){
		if(msg == UGCT_DROPLISTSELECT){
			CString * pString = (CString*) param;
			if(*pString =="1")
				*pString = "One";
			if(*pString =="2")
				*pString = "Two";
			if(*pString =="3")
				*pString = "Three";
		}
	}
	if(nParam == DROPLIST_CHANGE_SELECTION2){
	
		LPCSTR pszLongStateNames[] = {"ALABAMA","ALASKA","ARIZONA","ARKANSAS","CALIFORNIA",
			"COLORADO","CONNECTICUT","DELAWARE","DISTRICT OF COLUMBIA","FLORIDA",
			"GEORGIA","GUAM","HAWAII","IDAHO","ILLINOIS","INDIANA","IOWA","KANSAS",
			"KENTUCKY","LOUISIANA","MAINE","MARSHALL ISLANDS","MARYLAND","MASSACHUSETTS",
			"MICHIGAN","MINNESOTA","MISSISSIPPI","MISSOURI","MONTANA","NEBRASKA",
			"NEVADA","NEW HAMPSHIRE","NEW JERSEY","NEW MEXICO","NEW YORK","NORTH CAROLINA",
			"NORTH DAKOTA","NORTHERN MARIANA ISLANDS","OHIO","OKLAHOMA","OREGON",
			"PALAU","PENNSYLVANIA","PUERTO RICO","RHODE ISLAND","SOUTH CAROLINA",
			"SOUTH DAKOTA","TENNESSEE","TEXAS","UTAH","VERMONT","VIRGIN ISLANDS",
			"VIRGINIA","WASHINGTON","WEST VIRGINIA","WISCONSIN","WYOMING"};
		LPCSTR pszShortStateNames[] = {"AL","AK","AZ","AR","CA","CO","CT","DE","DC","FL",
			"GA","GU","HI","ID","IL","IN","IA","KS","KY","LA","ME","MH","MD","MA","MI",
			"MN","MS","MO","MT","NE","NV","NH","NJ","NM","NY","NC","ND","MP","OH","OK",
			"OR","PW","PA","PR","RI","SC","SD","TN","TX","UT","VT","VI","VA","WA","WV",
			"WI","WY"};

		if(msg == UGCT_DROPLISTSTART){		
			CStringList* pList = (CStringList*)param;
			int len = sizeof(pszLongStateNames) / sizeof(LPCSTR);
			for(int loop = 0 ;loop < len;loop++){
				pList->AddTail(pszLongStateNames[loop]);
			}
		}
		if(msg == UGCT_DROPLISTSELECT){
			CString * pString = (CString*) param;
			int len = sizeof(pszLongStateNames) / sizeof(LPCSTR);
			for(int loop = 0 ;loop < len;loop++){
				if(*pString == pszLongStateNames[loop]){
					*pString = pszShortStateNames[loop];
				}
			}
		}
	}

	return TRUE;
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnCheckbox(long ID,int col,long row,long msg,long param){

	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();

	if(nParam == CHECKBOX_CHANGEFONT){
		if(cell.GetFont() == &m_medFont){
			cell.SetFont(&m_defFont);
			cell.SetTextColor(RGB(255,0,0));
		}
		else{
			cell.SetFont(&m_medFont);
			cell.SetTextColor(RGB(0,255,0));
		}
		SetCell(col,row,&cell);
		RedrawCell(col,row);
	}

	return TRUE;
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnDateTime(long ID,int col,long row,long msg,LONG_PTR param){

	if(col == 5 && row == DATETIME_ROW+3){
		if(msg == UGCT_DISPLAYMONTHCAL){
			UGCTMONTHCALSETTINGS* pmcs = (UGCTMONTHCALSETTINGS*)param;

			pmcs->szDimension.cx = 2;
			pmcs->szDimension.cy = 2;
		}
		if(msg == UGCT_CONVERTDATE){
			UGCTCONVERTDATE* cd = (UGCTCONVERTDATE*)param;
			cd->string = cd->date.Format("%b %d, %y");
		}
	}
	if(col == 5 && row == DATETIME_ROW+2){
		if(msg == UGCT_DISPLAYMONTHCAL){
			UGCTMONTHCALSETTINGS* pmcs = (UGCTMONTHCALSETTINGS*)param;

			pmcs->clrMonthBk = RGB(250,250,200);
			pmcs->clrTitleBk = RGB(220,220,180);
		}
	}
	return TRUE;
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnPushButton(long ID,int col,long row,long msg,long param){
	
	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();

	if(msg == UGCT_BUTTONCLICK){
		if(nParam == BUTTON_CLICK1){
			WinExec("calc.exe",SW_SHOW);
		}
		else if(nParam == BUTTON_CLICK2){
			WinExec("notepad.exe",SW_SHOW);
		}

		else{
			MessageBox("The button was clicked","Cell Type Notification");
		}
	}
	if(msg == UGCT_BUTTONDOWN){
		if(nParam == BUTTON_CLICK3){
			MessageBox("The button pressed","Cell Type Notification");
		}
	}

	return TRUE;
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnEllipsisButton(long ID,int col,long row,long msg,long param){
	
	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();

	if(msg == UGCT_ELLIPSISBUTTONCLICK){
		if(nParam == ELLIPSISBUTTON_CLICK1){
			WinExec("calc.exe",SW_SHOW);
		}
		else if(nParam == ELLIPSISBUTTON_CLICK2){
			WinExec("notepad.exe",SW_SHOW);
		}

		else{
			MessageBox("The button was clicked","Cell Type Notification");
		}
	}

	return TRUE;
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnSpinButton(long ID,int col,long row,long msg,long param){
	
	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();

	if(nParam == SPIN_TYPE1){
		long num;
		cell.GetNumber(&num);

		if(msg == UGCT_SPINBUTTONUP){
			num++;
			if(num > 10)
				num = 0;
		}
		if(msg == UGCT_SPINBUTTONDOWN){
			num--;
			if(num < 0)
				num = 10;
		}
		CString str;
		str.Format("%ld",num);
		cell.SetText(str);
		SetCell(col,row,&cell);
	}
	else if(nParam == SPIN_TYPE2 || nParam == CELLTYPE_IS_EDITABLE){
		LPCSTR szVals[] = {"One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten"};

		CString str = cell.GetText();
		int len = (sizeof(szVals) / sizeof(LPCSTR));
		int index = 0;

		for(int loop = 0; loop < len ; loop++){
			if(str == szVals[loop]){
				index = loop;
				break;
			}
		}

		if(msg == UGCT_SPINBUTTONUP){
			index++;
			if(index >= len)
				index = 0;
		}
		if(msg == UGCT_SPINBUTTONDOWN){
			index--;
			if(index < 0)
				index = len - 1;
		}
		cell.SetText(szVals[index]);
		SetCell(col,row,&cell);
	}

	else if(nParam == SPIN_TYPE3){

		LPCSTR szVals[] = {"Mr","Mrs","Ms","Miss","Dr"};

		CString str = cell.GetText();
		int len = (sizeof(szVals) / sizeof(LPCSTR));
		int index = 0;

		for(int loop = 0; loop < len ; loop++){
			if(str == szVals[loop]){
				index = loop;
				break;
			}
		}

		if(msg == UGCT_SPINBUTTONUP){
			index++;
			if(index >= len)
				index = 0;
		}
		if(msg == UGCT_SPINBUTTONDOWN){
			index--;
			if(index < 0)
				index = len - 1;
		}
		cell.SetText(szVals[index]);
		SetCell(col,row,&cell);
	}
	else if(nParam == SPIN_TYPE4){

		COLORREF vals[] = {(RGB(255,0,0)),(RGB(255,255,0)),(RGB(0,255,0)),
			(RGB(0,255,255)),(RGB(0,0,255))	};

		COLORREF color = cell.GetBackColor();

		int len = (sizeof(vals) / sizeof(COLORREF));
		int index = 0;

		for(int loop = 0; loop < len ; loop++){
			if(color == vals[loop]){
				index = loop;
				break;
			}
		}

		if(msg == UGCT_SPINBUTTONUP){
			index++;
			if(index >= len)
				index = 0;
		}
		if(msg == UGCT_SPINBUTTONDOWN){
			index--;
			if(index < 0)
				index = len - 1;
		}
		cell.SetBackColor(vals[index]);
		SetCell(col,row,&cell);
	}
	else if(nParam == SPIN_TYPE5){

		LPCSTR szVals[] = {"A Long Piece of Text",
			"Another Piece of Text",
			"Even More Text",
			"This is the End"};

		CString str = cell.GetText();
		int len = (sizeof(szVals) / sizeof(LPCSTR));
		int index = 0;

		for(int loop = 0; loop < len ; loop++){
			if(str == szVals[loop]){
				index = loop;
				break;
			}
		}

		if(msg == UGCT_SPINBUTTONUP){
			index++;
			if(index >= len)
				index = 0;
		}
		if(msg == UGCT_SPINBUTTONDOWN){
			index--;
			if(index < 0)
				index = len - 1;
		}
		cell.SetText(szVals[index]);
		SetCell(col,row,&cell);

	}

	return TRUE;
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnSlider(long ID,int col,long row,long msg,long param){
	
	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();

	if(nParam == SLIDER_TYPE1){
		QuickSetText(col,row+1,cell.GetText());
		RedrawCell(col,row+1);
	}
	else if(nParam == SLIDER_TYPE2){
		float fVal = 255 - (float)param * (float)2.55;
		cell.SetBackColor(RGB(255,fVal,fVal));
		SetCell(col,row,&cell);

		fVal = 255 - fVal;

		GetCell(col+1,row+1,&cell);
		COLORREF color = cell.GetBackColor();
		cell.SetBackColor(RGB(fVal,GetGValue(color),GetBValue(color)));
		SetCell(col+1,row+1,&cell);
		RedrawCell(col+1,row+1);
	}
	else if(nParam == SLIDER_TYPE3){
		float fVal = 255 - (float)param * (float)2.55;
		cell.SetBackColor(RGB(fVal,255,fVal));
		SetCell(col,row,&cell);

		fVal = 255 - fVal;

		GetCell(col,row+1,&cell);
		COLORREF color = cell.GetBackColor();
		cell.SetBackColor(RGB(GetRValue(color),fVal,GetBValue(color)));
		SetCell(col,row+1,&cell);
		RedrawCell(col,row+1);
	}
	else if(nParam == SLIDER_TYPE4){
		float fVal = 255 - (float)param * (float)2.55;
		cell.SetBackColor(RGB(fVal,fVal,255));
		SetCell(col,row,&cell);

		fVal = 255 - fVal;

		GetCell(col-1,row+1,&cell);
		COLORREF color = cell.GetBackColor();
		cell.SetBackColor(RGB(GetRValue(color),GetGValue(color),fVal));
		SetCell(col-1,row+1,&cell);
		RedrawCell(col-1,row+1);
	}

	return TRUE;
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow){
	return FALSE;
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnEditFinish(int col, long row,CWnd* edit,LPCTSTR string,BOOL cancelFlag){

	CUGCell cell;
	GetCell(GetCurrentCol(),GetCurrentRow(),&cell);
	int nCellTypeIndex = cell.GetCellType();

	if(nCellTypeIndex == m_nDateTimeIndex){
		if(cancelFlag)
			return TRUE;
		COleDateTime date;
		return date.ParseDateTime(string,VAR_DATEVALUEONLY);
	}

	if(nCellTypeIndex == m_nPieChartIndex){
		InvalidateRect(NULL,FALSE);
	}

	return TRUE;
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnCharDown(UINT *vcKey,BOOL processed){

	CUGCell cell;
	GetCell(GetCurrentCol(),GetCurrentRow(),&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();
	CString string;
	if(cell.GetLabelText() != NULL)
		string = cell.GetLabelText();

	if(nParam == CELLTYPE_IS_EDITABLE || string == "CELLTYPE_IS_EDITABLE"){
		StartEdit(*vcKey);
	}

}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnGetCell(int col,long row,CUGCell *cell){

}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){

	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();

	if(nCellTypeIndex == m_nProgressIndex || nCellTypeIndex == m_nAdvProressIndex1 
		|| nCellTypeIndex == m_nAdvProressIndex2 || nCellTypeIndex == m_nAdvProressIndex3){
		long val;
		cell.GetNumber(&val);
		val +=cell.GetParam();
		if(val > 100)
			val = 0;
		cell.SetNumber(val);
		SetCell(col,row,&cell);
		RedrawCell(col,row);
	}
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnRClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){

	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();

	if(nCellTypeIndex == m_nProgressIndex || nCellTypeIndex == m_nAdvProressIndex1 
		|| nCellTypeIndex == m_nAdvProressIndex2 || nCellTypeIndex == m_nAdvProressIndex3){
		long val;
		cell.GetNumber(&val);
		val -=cell.GetParam();;
		if(val < 0)
			val = 100;
		cell.SetNumber(val);
		SetCell(col,row,&cell);
		RedrawCell(col,row);
	}
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed){
	
	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();
	CString string;
	if(cell.GetLabelText() != NULL)
		string = cell.GetLabelText();

	if(processed){
		if(cell.GetCellType() == m_nSpinIndex)
			return ;
	}

	if(nParam == CELLTYPE_IS_EDITABLE || string == "CELLTYPE_IS_EDITABLE"){
		StartEdit();
	}
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnMouseMove(int col,long row,POINT *point,UINT nFlags,BOOL processed){
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){
	
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnTH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){

}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed){
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnSH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnSH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnSH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed){
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnCB_LClicked(int updn,RECT *rect,POINT *point,BOOL processed){
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnCB_RClicked(int updn,RECT *rect,POINT *point,BOOL processed){
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnCB_DClicked(RECT *rect,POINT *point,BOOL processed){
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::SetupSection(long row, LPCSTR title){

	CUGCell cell;

	cell.SetBackColor(RGB(240,240,240));
	cell.SetTextColor(RGB(0,0,128));
	cell.SetFont(&m_boldFont);
	cell.SetAlignment(UG_ALIGNVCENTER);
	QuickSetRange(0,row,GetNumberCols() - 1,row,&cell);

	QuickSetText(-1,row,title);
}

/////////////////////////////////////////////////////////////////////////////
//	OnMenuCommand
//		This notification is called when the user has selected a menu item
//		in the pop-up menu.
//	Params:
//		col, row - the cell coordinates of where the menu originated from
//		setcion - identify for which portion of the gird the menu is for.
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
//		item - ID of the menu item selected
//	Return:
//		<none>
void CXPThemeDemoGrid::OnMenuCommand(int col,long row,int section,int item)
{
//	CUGExcel::OnMenuCommand( col, row, section, item );
	// Translate column location
	col = GetColTranslation( col );

	CUGCell cell;
	GetCell(col, row, &cell);

	int type = cell.GetCellType();

    CUGCellType * cellType = GetCellType(type);
	switch(item)
	{
	case MSG_USE_THEMES:
		cellType->ResetThemes();
		cell.UseThemes(true);
		break;
	case MSG_USE_THEMES_ALL:
		cellType->UseThemes(true);
		break;
	case MSG_DONT_USE_THEMES:
		cellType->ResetThemes();
		cell.UseThemes(false);
		break;
	case MSG_DONT_USE_THEMES_ALL:
		cellType->UseThemes(false);
		break;
	}

	SetCell(col, row, &cell);

	Invalidate();
}

/////////////////////////////////////////////////////////////////////////////
//	OnMenuStart
//		Is called when the pop up menu is about to be shown
//	Params:
//		col, row	- the cell coordinates of where the menu originated from
//		setcion		- identify for which portion of the gird the menu is for.
//					possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
//	Return:
//		TRUE - to allow menu to show
//		FALSE - to prevent the menu from poping up
int CXPThemeDemoGrid::OnMenuStart(int col,long row,int section)
{
	// TODO: add your notification handling here
	UNREFERENCED_PARAMETER(row);

	int retVal = 1;
	// Translate column location
	col = GetColTranslation( col );

	CUGCell cell;
	GetCell(col, row, &cell);

	int type = cell.GetCellType();

	if (type == m_nProgressIndex || type == m_nAdvProressIndex1 || type == m_nAdvProressIndex2 || type == m_nAdvProressIndex3)
	{
		retVal = 0;
	}
	else
	{
		col = GetColTranslation( col );

		EmptyMenu();

		AddMenuItem( MSG_USE_THEMES, "Use themes for this cell" );
		AddMenuItem( MSG_DONT_USE_THEMES, "Don't use themes for this cell" );
		AddMenuItem( MSG_USE_THEMES_ALL, "Use themes for this cell type" );
		AddMenuItem( MSG_DONT_USE_THEMES_ALL, "Don't use themes for this cell type" );
	}

	return retVal;
}

