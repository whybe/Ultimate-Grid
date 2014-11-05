// EditStylesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XP Theme Demo.h"
#include "EditStylesDlg.h"
#include "UGCtrl.h"
#include "UGXPThemes.h"

#include <comutil.h>
#include <ATLConv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditStylesDlg dialog

CEditStylesDlg::CEditStylesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditStylesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditStylesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	// Add WINDOW parts
	m_themeToParts["Window"].push_back("Caption");
	m_themeAndPartToStates["WindowCaption"].push_back("Active");
	m_themeAndPartToStates["WindowCaption"].push_back("Inactive");
	m_themeAndPartToStates["WindowCaption"].push_back("Disabled");
	m_themePartStateToIDs["WindowCaptionActive"] = std::pair<int, int>(1, 1);
	m_themePartStateToIDs["WindowCaptionInactive"] = std::pair<int, int>(1, 2);
	m_themePartStateToIDs["WindowCaptionDisabled"] = std::pair<int, int>(1, 3);
	m_themeToParts["Window"].push_back("SmallCaption");
	m_themePartStateToIDs["WindowSmallCaption"] = std::pair<int, int>(2, 0);
	m_themeToParts["Window"].push_back("MinCaption");
	m_themeAndPartToStates["WindowMinCaption"].push_back("Active");
	m_themeAndPartToStates["WindowMinCaption"].push_back("Inactive");
	m_themeAndPartToStates["WindowMinCaption"].push_back("Disabled");
	m_themePartStateToIDs["WindowMinCaptionActive"] = std::pair<int, int>(3, 1);
	m_themePartStateToIDs["WindowMinCaptionInactive"] = std::pair<int, int>(3, 2);
	m_themePartStateToIDs["WindowMinCaptionDisabled"] = std::pair<int, int>(3, 3);
	m_themeToParts["Window"].push_back("SmallMinCaption");
	m_themePartStateToIDs["WindowSmallMinCaption"] = std::pair<int, int>(4, 0);
	m_themeToParts["Window"].push_back("MaxCaption");
	m_themeAndPartToStates["WindowMaxCaption"].push_back("Active");
	m_themeAndPartToStates["WindowMaxCaption"].push_back("Inactive");
	m_themeAndPartToStates["WindowMaxCaption"].push_back("Disabled");
	m_themePartStateToIDs["WindowMaxCaptionActive"] = std::pair<int, int>(5, 1);
	m_themePartStateToIDs["WindowMaxCaptionInactive"] = std::pair<int, int>(5, 2);
	m_themePartStateToIDs["WindowMaxCaptionDisabled"] = std::pair<int, int>(5, 3);
	m_themeToParts["Window"].push_back("SmallMaxCaption");
	m_themePartStateToIDs["WindowSmallMaxCaption"] = std::pair<int, int>(6, 0);
	m_themeToParts["Window"].push_back("FrameLeft");
	m_themePartStateToIDs["WindowFrameLeft"] = std::pair<int, int>(7, 0);
	m_themeToParts["Window"].push_back("FrameRight");
	m_themePartStateToIDs["WindowFrameRight"] = std::pair<int, int>(8, 0);
	m_themeToParts["Window"].push_back("FrameBottom");
	m_themePartStateToIDs["WindowFrameBottom"] = std::pair<int, int>(9, 0);
	m_themeToParts["Window"].push_back("SmallFrameLeft");
	m_themePartStateToIDs["WindowSmallFrameLeft"] = std::pair<int, int>(10, 0);
	m_themeToParts["Window"].push_back("SmallFrameRight");
	m_themePartStateToIDs["WindowSmallFrameRight"] = std::pair<int, int>(11, 0);
	m_themeToParts["Window"].push_back("SmallFrameBottom");
	m_themePartStateToIDs["WindowSmallFrameBottom"] = std::pair<int, int>(12, 0);
	m_themeToParts["Window"].push_back("SysButton");
	m_themeAndPartToStates["WindowSysButton"].push_back("Normal");
	m_themeAndPartToStates["WindowSysButton"].push_back("Hot");
	m_themeAndPartToStates["WindowSysButton"].push_back("Pushed");
	m_themeAndPartToStates["WindowSysButton"].push_back("Disabled");
	m_themePartStateToIDs["WindowSysButtonNormal"] = std::pair<int, int>(13, 1);
	m_themePartStateToIDs["WindowSysButtonHot"] = std::pair<int, int>(13, 2);
	m_themePartStateToIDs["WindowSysButtonPushed"] = std::pair<int, int>(13, 3);
	m_themePartStateToIDs["WindowSysButtonDisabled"] = std::pair<int, int>(13, 4);
	m_themeToParts["Window"].push_back("MDISysButton");
	m_themePartStateToIDs["WindowMDISysButton"] = std::pair<int, int>(14, 0);
	m_themeToParts["Window"].push_back("MinButton");
	m_themeAndPartToStates["WindowMinButton"].push_back("Normal");
	m_themeAndPartToStates["WindowMinButton"].push_back("Hot");
	m_themeAndPartToStates["WindowMinButton"].push_back("Pushed");
	m_themeAndPartToStates["WindowMinButton"].push_back("Disabled");
	m_themePartStateToIDs["WindowMinButtonNormal"] = std::pair<int, int>(15, 1);
	m_themePartStateToIDs["WindowMinButtonHot"] = std::pair<int, int>(15, 2);
	m_themePartStateToIDs["WindowMinButtonPushed"] = std::pair<int, int>(15, 3);
	m_themePartStateToIDs["WindowMinButtonDisabled"] = std::pair<int, int>(15, 4);
	m_themeToParts["Window"].push_back("MDIMinButton");
	m_themePartStateToIDs["WindowMDIMinButton"] = std::pair<int, int>(16, 0);
	m_themeToParts["Window"].push_back("MaxButton");
	m_themeAndPartToStates["WindowMaxButton"].push_back("Normal");
	m_themeAndPartToStates["WindowMaxButton"].push_back("Hot");
	m_themeAndPartToStates["WindowMaxButton"].push_back("Pushed");
	m_themeAndPartToStates["WindowMaxButton"].push_back("Disabled");
	m_themePartStateToIDs["WindowMaxButtonNormal"] = std::pair<int, int>(17, 1);
	m_themePartStateToIDs["WindowMaxButtonHot"] = std::pair<int, int>(17, 2);
	m_themePartStateToIDs["WindowMaxButtonPushed"] = std::pair<int, int>(17, 3);
	m_themePartStateToIDs["WindowMaxButtonDisabled"] = std::pair<int, int>(17, 4);
	m_themeToParts["Window"].push_back("CloseButton");
	m_themeAndPartToStates["WindowCloseButton"].push_back("Normal");
	m_themeAndPartToStates["WindowCloseButton"].push_back("Hot");
	m_themeAndPartToStates["WindowCloseButton"].push_back("Pushed");
	m_themeAndPartToStates["WindowCloseButton"].push_back("Disabled");
	m_themePartStateToIDs["WindowCloseButtonNormal"] = std::pair<int, int>(18, 1);
	m_themePartStateToIDs["WindowCloseButtonHot"] = std::pair<int, int>(18, 2);
	m_themePartStateToIDs["WindowCloseButtonPushed"] = std::pair<int, int>(18, 3);
	m_themePartStateToIDs["WindowCloseButtonDisabled"] = std::pair<int, int>(18, 4);
	m_themeToParts["Window"].push_back("SmallCloseButton");
	m_themePartStateToIDs["WindowSmallCloseButton"] = std::pair<int, int>(19, 0);
	m_themeToParts["Window"].push_back("MDICloseButton");
	m_themePartStateToIDs["WindowMDICloseButton"] = std::pair<int, int>(20, 0);
	m_themeToParts["Window"].push_back("RestoreButton");
	m_themeAndPartToStates["WindowRestoreButton"].push_back("Normal");
	m_themeAndPartToStates["WindowRestoreButton"].push_back("Hot");
	m_themeAndPartToStates["WindowRestoreButton"].push_back("Pushed");
	m_themeAndPartToStates["WindowRestoreButton"].push_back("Disabled");
	m_themePartStateToIDs["WindowRestoreButtonNormal"] = std::pair<int, int>(21, 1);
	m_themePartStateToIDs["WindowRestoreButtonHot"] = std::pair<int, int>(21, 2);
	m_themePartStateToIDs["WindowRestoreButtonPushed"] = std::pair<int, int>(21, 3);
	m_themePartStateToIDs["WindowRestoreButtonDisabled"] = std::pair<int, int>(21, 4);
	m_themeToParts["Window"].push_back("MDIRestoreButton");
	m_themePartStateToIDs["WindowMDIRestoreButton"] = std::pair<int, int>(22, 0);
	m_themeToParts["Window"].push_back("HelpButton");
	m_themeAndPartToStates["WindowHelpButton"].push_back("Normal");
	m_themeAndPartToStates["WindowHelpButton"].push_back("Hot");
	m_themeAndPartToStates["WindowHelpButton"].push_back("Pushed");
	m_themeAndPartToStates["WindowHelpButton"].push_back("Disabled");
	m_themePartStateToIDs["WindowHelpButtonNormal"] = std::pair<int, int>(23, 1);
	m_themePartStateToIDs["WindowHelpButtonHot"] = std::pair<int, int>(23, 2);
	m_themePartStateToIDs["WindowHelpButtonPushed"] = std::pair<int, int>(23, 3);
	m_themePartStateToIDs["WindowHelpButtonDisabled"] = std::pair<int, int>(23, 4);
	m_themeToParts["Window"].push_back("MDIHelpButton");
	m_themePartStateToIDs["WindowMDIHelpButton"] = std::pair<int, int>(24, 0);
	m_themeToParts["Window"].push_back("HorzScrollButton");
	m_themeAndPartToStates["WindowHorzScrollButton"].push_back("Normal");
	m_themeAndPartToStates["WindowHorzScrollButton"].push_back("Hot");
	m_themeAndPartToStates["WindowHorzScrollButton"].push_back("Pushed");
	m_themeAndPartToStates["WindowHorzScrollButton"].push_back("Disabled");
	m_themePartStateToIDs["WindowHorzScrollButtonNormal"] = std::pair<int, int>(25, 1);
	m_themePartStateToIDs["WindowHorzScrollButtonHot"] = std::pair<int, int>(25, 2);
	m_themePartStateToIDs["WindowHorzScrollButtonPushed"] = std::pair<int, int>(25, 3);
	m_themePartStateToIDs["WindowHorzScrollButtonDisabled"] = std::pair<int, int>(25, 4);
	m_themeToParts["Window"].push_back("HorzThumbButton");
	m_themeAndPartToStates["WindowHorzThumbButton"].push_back("Normal");
	m_themeAndPartToStates["WindowHorzThumbButton"].push_back("Hot");
	m_themeAndPartToStates["WindowHorzThumbButton"].push_back("Pushed");
	m_themeAndPartToStates["WindowHorzThumbButton"].push_back("Disabled");
	m_themePartStateToIDs["WindowHorzThumbButtonNormal"] = std::pair<int, int>(26, 1);
	m_themePartStateToIDs["WindowHorzThumbButtonHot"] = std::pair<int, int>(26, 2);
	m_themePartStateToIDs["WindowHorzThumbButtonPushed"] = std::pair<int, int>(26, 3);
	m_themePartStateToIDs["WindowHorzThumbButtonDisabled"] = std::pair<int, int>(26, 4);
	m_themeToParts["Window"].push_back("VertScrollButton");
	m_themeAndPartToStates["WindowVertScrollButton"].push_back("Normal");
	m_themeAndPartToStates["WindowVertScrollButton"].push_back("Hot");
	m_themeAndPartToStates["WindowVertScrollButton"].push_back("Pushed");
	m_themeAndPartToStates["WindowVertScrollButton"].push_back("Disabled");
	m_themePartStateToIDs["WindowVertScrollButtonNormal"] = std::pair<int, int>(27, 1);
	m_themePartStateToIDs["WindowVertScrollButtonHot"] = std::pair<int, int>(27, 2);
	m_themePartStateToIDs["WindowVertScrollButtonPushed"] = std::pair<int, int>(27, 3);
	m_themePartStateToIDs["WindowVertScrollButtonDisabled"] = std::pair<int, int>(27, 4);
	m_themeToParts["Window"].push_back("VertThumbButton");
	m_themeAndPartToStates["WindowVertThumbButton"].push_back("Normal");
	m_themeAndPartToStates["WindowVertThumbButton"].push_back("Hot");
	m_themeAndPartToStates["WindowVertThumbButton"].push_back("Pushed");
	m_themeAndPartToStates["WindowVertThumbButton"].push_back("Disabled");
	m_themePartStateToIDs["WindowVertThumbButtonNormal"] = std::pair<int, int>(28, 1);
	m_themePartStateToIDs["WindowVertThumbButtonHot"] = std::pair<int, int>(28, 2);
	m_themePartStateToIDs["WindowVertThumbButtonPushed"] = std::pair<int, int>(28, 3);
	m_themePartStateToIDs["WindowVertThumbButtonDisabled"] = std::pair<int, int>(28, 4);
	m_themeToParts["Window"].push_back("Dialog");
	m_themePartStateToIDs["WindowDialog"] = std::pair<int, int>(29, 0);
	m_themeToParts["Window"].push_back("CaptionSizingTemplate");
	m_themePartStateToIDs["WindowCaptionSizingTemplate"] = std::pair<int, int>(30, 0);
	m_themeToParts["Window"].push_back("SmallCaptionSizingTemplate");
	m_themePartStateToIDs["WindowSmallCaptionSizingTemplate"] = std::pair<int, int>(31, 0);
	m_themeToParts["Window"].push_back("FrameLeftSizingTemplate");
	m_themePartStateToIDs["WindowFrameLeftSizingTemplate"] = std::pair<int, int>(32, 0);
	m_themeToParts["Window"].push_back("SmallFrameLeftSizingTemplate");
	m_themePartStateToIDs["WindowSmallFrameLeftSizingTemplate"] = std::pair<int, int>(33, 0);
	m_themeToParts["Window"].push_back("FrameRightSizingTemplate");
	m_themePartStateToIDs["WindowFrameRightSizingTemplate"] = std::pair<int, int>(34, 0);
	m_themeToParts["Window"].push_back("SmallFrameRightSizingTemplate");
	m_themePartStateToIDs["WindowSmallFrameRightSizingTemplate"] = std::pair<int, int>(35, 0);
	m_themeToParts["Window"].push_back("FrameBottomSizingTemplate");
	m_themePartStateToIDs["WindowFrameBottomSizingTemplate"] = std::pair<int, int>(36, 0);
	m_themeToParts["Window"].push_back("SmallFrameBottomSizingTemplate");
	m_themePartStateToIDs["WindowSmallFrameBottomSizingTemplate"] = std::pair<int, int>(37, 0);

	// Add Button parts
	m_themeToParts["Button"].push_back("PushButton");
	m_themeAndPartToStates["ButtonPushButton"].push_back("Normal");
	m_themeAndPartToStates["ButtonPushButton"].push_back("Hot");
	m_themeAndPartToStates["ButtonPushButton"].push_back("Pressed");
	m_themeAndPartToStates["ButtonPushButton"].push_back("Disabled");
	m_themeAndPartToStates["ButtonPushButton"].push_back("Defaulted");
	m_themePartStateToIDs["ButtonPushButtonNormal"] = std::pair<int, int>(1, 1);
	m_themePartStateToIDs["ButtonPushButtonHot"] = std::pair<int, int>(1, 2);
	m_themePartStateToIDs["ButtonPushButtonPressed"] = std::pair<int, int>(1, 3);
	m_themePartStateToIDs["ButtonPushButtonDisabled"] = std::pair<int, int>(1, 4);
	m_themePartStateToIDs["ButtonPushButtonDefaulted"] = std::pair<int, int>(1, 5);
	m_themeToParts["Button"].push_back("RadioButton");
	m_themeAndPartToStates["ButtonRadioButton"].push_back("UncheckedNormal");
	m_themeAndPartToStates["ButtonRadioButton"].push_back("UncheckedHot");
	m_themeAndPartToStates["ButtonRadioButton"].push_back("UncheckedPressed");
	m_themeAndPartToStates["ButtonRadioButton"].push_back("UncheckedDisabled");
	m_themeAndPartToStates["ButtonRadioButton"].push_back("CheckedNormal");
	m_themeAndPartToStates["ButtonRadioButton"].push_back("CheckedHot");
	m_themeAndPartToStates["ButtonRadioButton"].push_back("CheckedPressed");
	m_themeAndPartToStates["ButtonRadioButton"].push_back("CheckedDisabled");
	m_themePartStateToIDs["ButtonRadioButtonUncheckedNormal"] = std::pair<int, int>(2, 1);
	m_themePartStateToIDs["ButtonRadioButtonUncheckedHot"] = std::pair<int, int>(2, 2);
	m_themePartStateToIDs["ButtonRadioButtonUncheckedPressed"] = std::pair<int, int>(2, 3);
	m_themePartStateToIDs["ButtonRadioButtonUncheckedDisabled"] = std::pair<int, int>(2, 4);
	m_themePartStateToIDs["ButtonRadioButtonCheckedNormal"] = std::pair<int, int>(2, 5);
	m_themePartStateToIDs["ButtonRadioButtonCheckedHot"] = std::pair<int, int>(2, 6);
	m_themePartStateToIDs["ButtonRadioButtonCheckedPressed"] = std::pair<int, int>(2, 7);
	m_themePartStateToIDs["ButtonRadioButtonCheckedDisabled"] = std::pair<int, int>(2, 8);
	m_themeToParts["Button"].push_back("CheckBox");
	m_themeAndPartToStates["ButtonCheckBox"].push_back("UNCheckedNormal");
	m_themeAndPartToStates["ButtonCheckBox"].push_back("UNCheckedHot");
	m_themeAndPartToStates["ButtonCheckBox"].push_back("UNCheckedPressed");
	m_themeAndPartToStates["ButtonCheckBox"].push_back("UNCheckedDisabled");
	m_themeAndPartToStates["ButtonCheckBox"].push_back("CheckedNormal");
	m_themeAndPartToStates["ButtonCheckBox"].push_back("CheckedHot");
	m_themeAndPartToStates["ButtonCheckBox"].push_back("CheckedPressed");
	m_themeAndPartToStates["ButtonCheckBox"].push_back("CheckedDisabled");
	m_themeAndPartToStates["ButtonCheckBox"].push_back("MixedNormal");
	m_themeAndPartToStates["ButtonCheckBox"].push_back("MixedHot");
	m_themeAndPartToStates["ButtonCheckBox"].push_back("MixedPressed");
	m_themeAndPartToStates["ButtonCheckBox"].push_back("MixedDisabled");
	m_themePartStateToIDs["ButtonCheckBoxUNCheckedNormal"] = std::pair<int, int>(3, 1);
	m_themePartStateToIDs["ButtonCheckBoxUNCheckedHot"] = std::pair<int, int>(3, 2);
	m_themePartStateToIDs["ButtonCheckBoxUNCheckedPressed"] = std::pair<int, int>(3, 3);
	m_themePartStateToIDs["ButtonCheckBoxUNCheckedDisabled"] = std::pair<int, int>(3, 4);
	m_themePartStateToIDs["ButtonCheckBoxCheckedNormal"] = std::pair<int, int>(3, 5);
	m_themePartStateToIDs["ButtonCheckBoxCheckedHot"] = std::pair<int, int>(3, 6);
	m_themePartStateToIDs["ButtonCheckBoxCheckedPressed"] = std::pair<int, int>(3, 7);
	m_themePartStateToIDs["ButtonCheckBoxCheckedDisabled"] = std::pair<int, int>(3, 8);
	m_themePartStateToIDs["ButtonCheckBoxMixedNormal"] = std::pair<int, int>(3, 9);
	m_themePartStateToIDs["ButtonCheckBoxMixedHot"] = std::pair<int, int>(3, 10);
	m_themePartStateToIDs["ButtonCheckBoxMixedPressed"] = std::pair<int, int>(3, 11);
	m_themePartStateToIDs["ButtonCheckBoxMixedDisabled"] = std::pair<int, int>(3, 12);
	m_themeToParts["Button"].push_back("GroupBox");
	m_themeAndPartToStates["ButtonGroupBox"].push_back("Normal");
	m_themeAndPartToStates["ButtonGroupBox"].push_back("Disabled");
	m_themePartStateToIDs["ButtonGroupBoxNormal"] = std::pair<int, int>(4, 1);
	m_themePartStateToIDs["ButtonGroupBoxDisabled"] = std::pair<int, int>(4, 2);
	m_themeToParts["Button"].push_back("UserButton");
	m_themePartStateToIDs["ButtonUserButton"] = std::pair<int, int>(5, 0);

	// Add Rebar parts
	m_themeToParts["Rebar"].push_back("Gripper");
	m_themePartStateToIDs["RebarGripper"] = std::pair<int, int>(1, 0);
	m_themeToParts["Rebar"].push_back("GripperVert");
	m_themePartStateToIDs["RebarGripperVert"] = std::pair<int, int>(2, 0);
	m_themeToParts["Rebar"].push_back("Band");
	m_themeAndPartToStates["RebarBand"].push_back("Normal");
	m_themeAndPartToStates["RebarBand"].push_back("Hot");
	m_themeAndPartToStates["RebarBand"].push_back("Pressed");
	m_themeAndPartToStates["RebarBand"].push_back("Disabled");
	m_themeAndPartToStates["RebarBand"].push_back("Checked");
	m_themeAndPartToStates["RebarBand"].push_back("HotChecked");
	m_themePartStateToIDs["RebarBandNormal"] = std::pair<int, int>(3, 1);
	m_themePartStateToIDs["RebarBandHot"] = std::pair<int, int>(3, 2);
	m_themePartStateToIDs["RebarBandPressed"] = std::pair<int, int>(3, 3);
	m_themePartStateToIDs["RebarBandDisabled"] = std::pair<int, int>(3, 4);
	m_themePartStateToIDs["RebarBandChecked"] = std::pair<int, int>(3, 5);
	m_themePartStateToIDs["RebarBandHotChecked"] = std::pair<int, int>(3, 6);
	m_themeToParts["Rebar"].push_back("Chevron");
	m_themeAndPartToStates["RebarChevron"].push_back("Normal");
	m_themeAndPartToStates["RebarChevron"].push_back("Hot");
	m_themeAndPartToStates["RebarChevron"].push_back("Pressed");
	m_themePartStateToIDs["RebarChevronNormal"] = std::pair<int, int>(4, 1);
	m_themePartStateToIDs["RebarChevronHot"] = std::pair<int, int>(4, 2);
	m_themePartStateToIDs["RebarChevronPressed"] = std::pair<int, int>(4, 3);
	m_themeToParts["Rebar"].push_back("ChevronVert");
	m_themePartStateToIDs["RebarChevronVert"] = std::pair<int, int>(5, 0);

	// Add ToolBar parts
	m_themeToParts["Toolbar"].push_back("Button");
	m_themePartStateToIDs["ToolbarButton"] = std::pair<int, int>(1, 0);
	m_themeToParts["Toolbar"].push_back("DropRightButton");
	m_themePartStateToIDs["ToolbarDropRightButton"] = std::pair<int, int>(2, 0);
	m_themeToParts["Toolbar"].push_back("SplitButton");
	m_themePartStateToIDs["ToolbarSplitButton"] = std::pair<int, int>(3, 0);
	m_themeToParts["Toolbar"].push_back("SplitButtonDropRight");
	m_themePartStateToIDs["ToolbarSplitButtonDropRight"] = std::pair<int, int>(4, 0);
	m_themeToParts["Toolbar"].push_back("Separator");
	m_themePartStateToIDs["ToolbarSeparator"] = std::pair<int, int>(5, 0);
	m_themeToParts["Toolbar"].push_back("SeparatorVert");
	m_themePartStateToIDs["ToolbarSeparatorVert"] = std::pair<int, int>(6, 0);

	// Add Status parts
	m_themeToParts["Status"].push_back("Pane");
	m_themePartStateToIDs["StatusPane"] = std::pair<int, int>(1, 0);
	m_themeToParts["Status"].push_back("GripperPane");
	m_themePartStateToIDs["StatusGripperPane"] = std::pair<int, int>(2, 0);
	m_themeToParts["Status"].push_back("Gripper");
	m_themePartStateToIDs["StatusGripper"] = std::pair<int, int>(3, 0);

	// Add listview parts
	m_themeToParts["ListView"].push_back("ListItem");
	m_themeAndPartToStates["ListViewListItem"].push_back("Normal");
	m_themeAndPartToStates["ListViewListItem"].push_back("Hot");
	m_themeAndPartToStates["ListViewListItem"].push_back("Selected");
	m_themeAndPartToStates["ListViewListItem"].push_back("Disabled");
	m_themeAndPartToStates["ListViewListItem"].push_back("SelectedNoFocus");
	m_themePartStateToIDs["ListViewListItemNormal"] = std::pair<int, int>(1, 1);
	m_themePartStateToIDs["ListViewListItemHot"] = std::pair<int, int>(1, 2);
	m_themePartStateToIDs["ListViewListItemSelected"] = std::pair<int, int>(1, 3);
	m_themePartStateToIDs["ListViewListItemDisabled"] = std::pair<int, int>(1, 4);
	m_themePartStateToIDs["ListViewListItemSelectedNoFocus"] = std::pair<int, int>(1, 5);
	m_themeToParts["ListView"].push_back("ListGroup");
	m_themePartStateToIDs["ListViewListGroup"] = std::pair<int, int>(2, 0);
	m_themeToParts["ListView"].push_back("ListDetail");
	m_themePartStateToIDs["ListViewListDetail"] = std::pair<int, int>(3, 0);
	m_themeToParts["ListView"].push_back("ListSortedDetail");
	m_themePartStateToIDs["ListViewListSortedDetail"] = std::pair<int, int>(4, 0);
	m_themeToParts["ListView"].push_back("EmptyText");
	m_themePartStateToIDs["ListViewEmptyText"] = std::pair<int, int>(5, 0);

	// Add Header parts
	m_themeToParts["Header"].push_back("HeaderItem");
	m_themeAndPartToStates["HeaderHeaderItem"].push_back("Normal");
	m_themeAndPartToStates["HeaderHeaderItem"].push_back("Hot");
	m_themeAndPartToStates["HeaderHeaderItem"].push_back("Pressed");
	m_themePartStateToIDs["HeaderHeaderItemNormal"] = std::pair<int, int>(1, 1);
	m_themePartStateToIDs["HeaderHeaderItemHot"] = std::pair<int, int>(1, 2);
	m_themePartStateToIDs["HeaderHeaderItemPressed"] = std::pair<int, int>(1, 3);
	m_themeToParts["Header"].push_back("HeaderItemLeft");
	m_themeAndPartToStates["HeaderHeaderItemLeft"].push_back("Normal");
	m_themeAndPartToStates["HeaderHeaderItemLeft"].push_back("Hot");
	m_themeAndPartToStates["HeaderHeaderItemLeft"].push_back("Pressed");
	m_themePartStateToIDs["HeaderHeaderItemLeftNormal"] = std::pair<int, int>(2, 1);
	m_themePartStateToIDs["HeaderHeaderItemLeftHot"] = std::pair<int, int>(2, 2);
	m_themePartStateToIDs["HeaderHeaderItemLeftPressed"] = std::pair<int, int>(2, 3);
	m_themeToParts["Header"].push_back("HeaderItemRight");
	m_themeAndPartToStates["HeaderHeaderItemRight"].push_back("Normal");
	m_themeAndPartToStates["HeaderHeaderItemRight"].push_back("Hot");
	m_themeAndPartToStates["HeaderHeaderItemRight"].push_back("Pressed");
	m_themePartStateToIDs["HeaderHeaderItemRightNormal"] = std::pair<int, int>(3, 1);
	m_themePartStateToIDs["HeaderHeaderItemRightHot"] = std::pair<int, int>(3, 2);
	m_themePartStateToIDs["HeaderHeaderItemRightPressed"] = std::pair<int, int>(3, 3);
	m_themeToParts["Header"].push_back("HeaderSortArrow");
	m_themeAndPartToStates["HeaderHeaderSortArrow"].push_back("SortedUp");
	m_themeAndPartToStates["HeaderHeaderSortArrow"].push_back("SortedRight");
	m_themePartStateToIDs["HeaderHeaderSortArrowSortedUp"] = std::pair<int, int>(4, 1);
	m_themePartStateToIDs["HeaderHeaderSortArrowSortedRight"] = std::pair<int, int>(4, 2);

	// Add Progress parts
	m_themeToParts["Progress"].push_back("Bar");
	m_themeAndPartToStates["ProgressBar"].push_back("Normal");
	m_themePartStateToIDs["ProgressBarNormal"] = std::pair<int, int>(1, 1);
	m_themeToParts["Progress"].push_back("BarVert");
	m_themePartStateToIDs["ProgressBarVert"] = std::pair<int, int>(2, 0);
	m_themeToParts["Progress"].push_back("Chunk");
	m_themePartStateToIDs["ProgressChunk"] = std::pair<int, int>(3, 0);
	m_themeToParts["Progress"].push_back("ChunkVert");
	m_themePartStateToIDs["ProgressChunkVert"] = std::pair<int, int>(4, 0);

	// Add Tab Items
	m_themeToParts["Tab"].push_back("TabItem");
	m_themeAndPartToStates["TabTabItem"].push_back("Normal");
	m_themeAndPartToStates["TabTabItem"].push_back("Hot");
	m_themeAndPartToStates["TabTabItem"].push_back("Selected");
	m_themeAndPartToStates["TabTabItem"].push_back("Disabled");
	m_themeAndPartToStates["TabTabItem"].push_back("SelectedNoFocus");
	m_themePartStateToIDs["TabTabItemNormal"] = std::pair<int, int>(1, 1);
	m_themePartStateToIDs["TabTabItemHot"] = std::pair<int, int>(1, 2);
	m_themePartStateToIDs["TabTabItemSelected"] = std::pair<int, int>(1, 3);
	m_themePartStateToIDs["TabTabItemDisabled"] = std::pair<int, int>(1, 4);
	m_themePartStateToIDs["TabTabItemSelectedNoFocus"] = std::pair<int, int>(1, 5);
	m_themeToParts["Tab"].push_back("TabItemLeftEdge");
	m_themeAndPartToStates["TabTabItemLeftEdge"].push_back("Normal");
	m_themeAndPartToStates["TabTabItemLeftEdge"].push_back("Hot");
	m_themeAndPartToStates["TabTabItemLeftEdge"].push_back("Selected");
	m_themeAndPartToStates["TabTabItemLeftEdge"].push_back("Disabled");
	m_themeAndPartToStates["TabTabItemLeftEdge"].push_back("SelectedNoFocus");
	m_themePartStateToIDs["TabTabItemLeftEdgeNormal"] = std::pair<int, int>(2, 1);
	m_themePartStateToIDs["TabTabItemLeftEdgeHot"] = std::pair<int, int>(2, 2);
	m_themePartStateToIDs["TabTabItemLeftEdgeSelected"] = std::pair<int, int>(2, 3);
	m_themePartStateToIDs["TabTabItemLeftEdgeDisabled"] = std::pair<int, int>(2, 4);
	m_themePartStateToIDs["TabTabItemLeftEdgeSelectedNoFocus"] = std::pair<int, int>(2, 5);
	m_themeToParts["Tab"].push_back("TabItemRightEdge");
	m_themeAndPartToStates["TabTabItemRightEdge"].push_back("Normal");
	m_themeAndPartToStates["TabTabItemRightEdge"].push_back("Hot");
	m_themeAndPartToStates["TabTabItemRightEdge"].push_back("Selected");
	m_themeAndPartToStates["TabTabItemRightEdge"].push_back("Disabled");
	m_themeAndPartToStates["TabTabItemRightEdge"].push_back("SelectedNoFocus");
	m_themePartStateToIDs["TabTabItemRightEdgeNormal"] = std::pair<int, int>(3, 1);
	m_themePartStateToIDs["TabTabItemRightEdgeHot"] = std::pair<int, int>(3, 2);
	m_themePartStateToIDs["TabTabItemRightEdgeSelected"] = std::pair<int, int>(3, 3);
	m_themePartStateToIDs["TabTabItemRightEdgeDisabled"] = std::pair<int, int>(3, 4);
	m_themePartStateToIDs["TabTabItemRightEdgeSelectedNoFocus"] = std::pair<int, int>(3, 5);
	m_themeToParts["Tab"].push_back("TabItemBothEdge");
	m_themePartStateToIDs["TabTabItemBothEdge"] = std::pair<int, int>(4, 0);
	m_themeToParts["Tab"].push_back("TopTabItem");
	m_themeAndPartToStates["TabTopTabItem"].push_back("Normal");
	m_themeAndPartToStates["TabTopTabItem"].push_back("Hot");
	m_themeAndPartToStates["TabTopTabItem"].push_back("Selected");
	m_themeAndPartToStates["TabTopTabItem"].push_back("Disabled");
	m_themeAndPartToStates["TabTopTabItem"].push_back("SelectedNoFocus");
	m_themePartStateToIDs["TabTopTabItemNormal"] = std::pair<int, int>(5, 1);
	m_themePartStateToIDs["TabTopTabItemHot"] = std::pair<int, int>(5, 2);
	m_themePartStateToIDs["TabTopTabItemSelected"] = std::pair<int, int>(5, 3);
	m_themePartStateToIDs["TabTopTabItemDisabled"] = std::pair<int, int>(5, 4);
	m_themePartStateToIDs["TabTopTabItemSelectedNoFocus"] = std::pair<int, int>(5, 5);
	m_themeToParts["Tab"].push_back("TopTabItemLeftEdge");
	m_themeAndPartToStates["TabTopTabItemLeftEdge"].push_back("Normal");
	m_themeAndPartToStates["TabTopTabItemLeftEdge"].push_back("Hot");
	m_themeAndPartToStates["TabTopTabItemLeftEdge"].push_back("Selected");
	m_themeAndPartToStates["TabTopTabItemLeftEdge"].push_back("Disabled");
	m_themeAndPartToStates["TabTopTabItemLeftEdge"].push_back("SelectedNoFocus");
	m_themePartStateToIDs["TabTopTabItemLeftEdgeNormal"] = std::pair<int, int>(6, 1);
	m_themePartStateToIDs["TabTopTabItemLeftEdgeHot"] = std::pair<int, int>(6, 2);
	m_themePartStateToIDs["TabTopTabItemLeftEdgeSelected"] = std::pair<int, int>(6, 3);
	m_themePartStateToIDs["TabTopTabItemLeftEdgeDisabled"] = std::pair<int, int>(6, 4);
	m_themePartStateToIDs["TabTopTabItemLeftEdgeSelectedNoFocus"] = std::pair<int, int>(6, 5);
	m_themeToParts["Tab"].push_back("TopTabItemRightEdge");
	m_themeAndPartToStates["TabTopTabItemRightEdge"].push_back("Normal");
	m_themeAndPartToStates["TabTopTabItemRightEdge"].push_back("Hot");
	m_themeAndPartToStates["TabTopTabItemRightEdge"].push_back("Selected");
	m_themeAndPartToStates["TabTopTabItemRightEdge"].push_back("Disabled");
	m_themeAndPartToStates["TabTopTabItemRightEdge"].push_back("SelectedNoFocus");
	m_themePartStateToIDs["TabTopTabItemRightEdgeNormal"] = std::pair<int, int>(7, 1);
	m_themePartStateToIDs["TabTopTabItemRightEdgeHot"] = std::pair<int, int>(7, 2);
	m_themePartStateToIDs["TabTopTabItemRightEdgeSelected"] = std::pair<int, int>(7, 3);
	m_themePartStateToIDs["TabTopTabItemRightEdgeDisabled"] = std::pair<int, int>(7, 4);
	m_themePartStateToIDs["TabTopTabItemRightEdgeSelectedNoFocus"] = std::pair<int, int>(7, 5);
	m_themeToParts["Tab"].push_back("TopTabItemBothEdge");
	m_themePartStateToIDs["TabTopTabItemBothEdge"] = std::pair<int, int>(8, 0);

	// add TrackBar parts
	m_themeToParts["Trackbar"].push_back("Track");
	m_themeAndPartToStates["TrackbarTrack"].push_back("Normal");
	m_themePartStateToIDs["TrackbarTrackNormal"] = std::pair<int, int>(1, 1);
	m_themeToParts["Trackbar"].push_back("TrackVert");
	m_themeAndPartToStates["TrackbarTrackVert"].push_back("Normal");
	m_themePartStateToIDs["TrackbarTrackVertNormal"] = std::pair<int, int>(2, 1);
	m_themeToParts["Trackbar"].push_back("Thumb");
	m_themeAndPartToStates["TrackbarThumb"].push_back("Normal");
	m_themeAndPartToStates["TrackbarThumb"].push_back("Hot");
	m_themeAndPartToStates["TrackbarThumb"].push_back("Pressed");
	m_themeAndPartToStates["TrackbarThumb"].push_back("Focused");
	m_themeAndPartToStates["TrackbarThumb"].push_back("Disabled");
	m_themePartStateToIDs["TrackbarThumbNormal"] = std::pair<int, int>(3, 1);
	m_themePartStateToIDs["TrackbarThumbHot"] = std::pair<int, int>(3, 2);
	m_themePartStateToIDs["TrackbarThumbPressed"] = std::pair<int, int>(3, 3);
	m_themePartStateToIDs["TrackbarThumbFocused"] = std::pair<int, int>(3, 4);
	m_themePartStateToIDs["TrackbarThumbDisabled"] = std::pair<int, int>(3, 5);
	m_themeToParts["Trackbar"].push_back("ThumbBottom");
	m_themeAndPartToStates["TrackbarThumbBottom"].push_back("Normal");
	m_themeAndPartToStates["TrackbarThumbBottom"].push_back("Hot");
	m_themeAndPartToStates["TrackbarThumbBottom"].push_back("Pressed");
	m_themeAndPartToStates["TrackbarThumbBottom"].push_back("Focused");
	m_themeAndPartToStates["TrackbarThumbBottom"].push_back("Disabled");
	m_themePartStateToIDs["TrackbarThumbBottomNormal"] = std::pair<int, int>(4, 1);
	m_themePartStateToIDs["TrackbarThumbBottomHot"] = std::pair<int, int>(4, 2);
	m_themePartStateToIDs["TrackbarThumbBottomPressed"] = std::pair<int, int>(4, 3);
	m_themePartStateToIDs["TrackbarThumbBottomFocused"] = std::pair<int, int>(4, 4);
	m_themePartStateToIDs["TrackbarThumbBottomDisabled"] = std::pair<int, int>(4, 5);
	m_themeToParts["Trackbar"].push_back("ThumbTop");
	m_themeAndPartToStates["TrackbarThumbTop"].push_back("Normal");
	m_themeAndPartToStates["TrackbarThumbTop"].push_back("Hot");
	m_themeAndPartToStates["TrackbarThumbTop"].push_back("Pressed");
	m_themeAndPartToStates["TrackbarThumbTop"].push_back("Focused");
	m_themeAndPartToStates["TrackbarThumbTop"].push_back("Disabled");
	m_themePartStateToIDs["TrackbarThumbTopNormal"] = std::pair<int, int>(5, 1);
	m_themePartStateToIDs["TrackbarThumbTopHot"] = std::pair<int, int>(5, 2);
	m_themePartStateToIDs["TrackbarThumbTopPressed"] = std::pair<int, int>(5, 3);
	m_themePartStateToIDs["TrackbarThumbTopFocused"] = std::pair<int, int>(5, 4);
	m_themePartStateToIDs["TrackbarThumbTopDisabled"] = std::pair<int, int>(5, 5);
	m_themeToParts["Trackbar"].push_back("ThumbVert");
	m_themeAndPartToStates["TrackbarThumbVert"].push_back("Normal");
	m_themeAndPartToStates["TrackbarThumbVert"].push_back("Hot");
	m_themeAndPartToStates["TrackbarThumbVert"].push_back("Pressed");
	m_themeAndPartToStates["TrackbarThumbVert"].push_back("Focused");
	m_themeAndPartToStates["TrackbarThumbVert"].push_back("Disabled");
	m_themePartStateToIDs["TrackbarThumbVertNormal"] = std::pair<int, int>(6, 1);
	m_themePartStateToIDs["TrackbarThumbVertHot"] = std::pair<int, int>(6, 2);
	m_themePartStateToIDs["TrackbarThumbVertPressed"] = std::pair<int, int>(6, 3);
	m_themePartStateToIDs["TrackbarThumbVertFocused"] = std::pair<int, int>(6, 4);
	m_themePartStateToIDs["TrackbarThumbVertDisabled"] = std::pair<int, int>(6, 5);
	m_themeToParts["Trackbar"].push_back("ThumbLeft");
	m_themeAndPartToStates["TrackbarThumbLeft"].push_back("Normal");
	m_themeAndPartToStates["TrackbarThumbLeft"].push_back("Hot");
	m_themeAndPartToStates["TrackbarThumbLeft"].push_back("Pressed");
	m_themeAndPartToStates["TrackbarThumbLeft"].push_back("Focused");
	m_themeAndPartToStates["TrackbarThumbLeft"].push_back("Disabled");
	m_themePartStateToIDs["TrackbarThumbLeftNormal"] = std::pair<int, int>(7, 1);
	m_themePartStateToIDs["TrackbarThumbLeftHot"] = std::pair<int, int>(7, 2);
	m_themePartStateToIDs["TrackbarThumbLeftPressed"] = std::pair<int, int>(7, 3);
	m_themePartStateToIDs["TrackbarThumbLeftFocused"] = std::pair<int, int>(7, 4);
	m_themePartStateToIDs["TrackbarThumbLeftDisabled"] = std::pair<int, int>(7, 5);
	m_themeToParts["Trackbar"].push_back("ThumbRight");
	m_themeAndPartToStates["TrackbarThumbRight"].push_back("Normal");
	m_themeAndPartToStates["TrackbarThumbRight"].push_back("Hot");
	m_themeAndPartToStates["TrackbarThumbRight"].push_back("Pressed");
	m_themeAndPartToStates["TrackbarThumbRight"].push_back("Focused");
	m_themeAndPartToStates["TrackbarThumbRight"].push_back("Disabled");
	m_themePartStateToIDs["TrackbarThumbRightNormal"] = std::pair<int, int>(8, 1);
	m_themePartStateToIDs["TrackbarThumbRightHot"] = std::pair<int, int>(8, 2);
	m_themePartStateToIDs["TrackbarThumbRightPressed"] = std::pair<int, int>(8, 3);
	m_themePartStateToIDs["TrackbarThumbRightFocused"] = std::pair<int, int>(8, 4);
	m_themePartStateToIDs["TrackbarThumbRightDisabled"] = std::pair<int, int>(8, 5);
	m_themeToParts["Trackbar"].push_back("Tics");
	m_themeAndPartToStates["TrackbarTics"].push_back("Normal");
	m_themePartStateToIDs["TrackbarTicsNormal"] = std::pair<int, int>(9, 1);
	m_themeToParts["Trackbar"].push_back("TicsVert");
	m_themeAndPartToStates["TrackbarTicsVert"].push_back("Normal");
	m_themePartStateToIDs["TrackbarTicsVertNormal"] = std::pair<int, int>(10, 1);


	// Add ToolTip parts
	m_themeToParts["Tooltip"].push_back("Standard");
	m_themeAndPartToStates["TooltipStandard"].push_back("Normal");
	m_themeAndPartToStates["TooltipStandard"].push_back("Link");
	m_themePartStateToIDs["TooltipStandardNormal"] = std::pair<int, int>(1, 1);
	m_themePartStateToIDs["TooltipStandardLink"] = std::pair<int, int>(1, 2);
	m_themeToParts["Tooltip"].push_back("StandardTitle");
	m_themePartStateToIDs["TooltipStandardTitle"] = std::pair<int, int>(2, 0);
	m_themeToParts["Tooltip"].push_back("Balloon");
	m_themeAndPartToStates["TooltipBalloon"].push_back("Normal");
	m_themeAndPartToStates["TooltipBalloon"].push_back("Link");
	m_themePartStateToIDs["TooltipBalloonNormal"] = std::pair<int, int>(3, 1);
	m_themePartStateToIDs["TooltipBalloonLink"] = std::pair<int, int>(3, 2);
	m_themeToParts["Tooltip"].push_back("BalloonTitle");
	m_themePartStateToIDs["TooltipBalloonTitle"] = std::pair<int, int>(4, 0);
	m_themeToParts["Tooltip"].push_back("Close");
	m_themeAndPartToStates["TooltipClose"].push_back("Normal");
	m_themeAndPartToStates["TooltipClose"].push_back("Hot");
	m_themeAndPartToStates["TooltipClose"].push_back("Pressed");
	m_themePartStateToIDs["TooltipCloseNormal"] = std::pair<int, int>(5, 1);
	m_themePartStateToIDs["TooltipCloseHot"] = std::pair<int, int>(5, 2);
	m_themePartStateToIDs["TooltipClosePressed"] = std::pair<int, int>(5, 3);

	// Add Treeview items
	m_themeToParts["TreeView"].push_back("Treeitem");
	m_themeAndPartToStates["TreeViewTreeitem"].push_back("Normal");
	m_themeAndPartToStates["TreeViewTreeitem"].push_back("Hot");
	m_themeAndPartToStates["TreeViewTreeitem"].push_back("Selected");
	m_themeAndPartToStates["TreeViewTreeitem"].push_back("Disabled");
	m_themeAndPartToStates["TreeViewTreeitem"].push_back("SelectedNotFocus");
	m_themePartStateToIDs["TreeViewTreeitemNormal"] = std::pair<int, int>(1, 1);
	m_themePartStateToIDs["TreeViewTreeitemHot"] = std::pair<int, int>(1, 2);
	m_themePartStateToIDs["TreeViewTreeitemNSelected"] = std::pair<int, int>(1, 3);
	m_themePartStateToIDs["TreeViewTreeitemDisabled"] = std::pair<int, int>(1, 4);
	m_themePartStateToIDs["TreeViewTreeitemSelectedNotFocus"] = std::pair<int, int>(1, 5);
	m_themeToParts["TreeView"].push_back("Glyph");
	m_themeAndPartToStates["TreeViewGlyph"].push_back("Closed");
	m_themeAndPartToStates["TreeViewGlyph"].push_back("Opened");
	m_themePartStateToIDs["TreeViewGlyphClosed"] = std::pair<int, int>(2, 1);
	m_themePartStateToIDs["TreeViewGlyphOpened"] = std::pair<int, int>(2, 2);
	m_themeToParts["TreeView"].push_back("TreeitemBranch");
	m_themePartStateToIDs["TreeViewTreeitemBranch"] = std::pair<int, int>(3, 0);

	// Add Spin items
	m_themeToParts["Spin"].push_back("Up");
	m_themeAndPartToStates["SpinUp"].push_back("Normal");
	m_themeAndPartToStates["SpinUp"].push_back("Hot");
	m_themeAndPartToStates["SpinUp"].push_back("Pressed");
	m_themeAndPartToStates["SpinUp"].push_back("Disabled");
	m_themePartStateToIDs["SpinUpNormal"] = std::pair<int, int>(1, 1);
	m_themePartStateToIDs["SpinUpHot"] = std::pair<int, int>(1, 2);
	m_themePartStateToIDs["SpinUpPressed"] = std::pair<int, int>(1, 3);
	m_themePartStateToIDs["SpinUpDisabled"] = std::pair<int, int>(1, 4);
	m_themeToParts["Spin"].push_back("Right");
	m_themeAndPartToStates["SpinRight"].push_back("Normal");
	m_themeAndPartToStates["SpinRight"].push_back("Hot");
	m_themeAndPartToStates["SpinRight"].push_back("Pressed");
	m_themeAndPartToStates["SpinRight"].push_back("Disabled");
	m_themePartStateToIDs["SpinRightNormal"] = std::pair<int, int>(2, 1);
	m_themePartStateToIDs["SpinRightHot"] = std::pair<int, int>(2, 2);
	m_themePartStateToIDs["SpinRightPressed"] = std::pair<int, int>(2, 3);
	m_themePartStateToIDs["SpinRightDisabled"] = std::pair<int, int>(2, 4);
	m_themeToParts["Spin"].push_back("UpHorz");
	m_themeAndPartToStates["SpinUpHorz"].push_back("Normal");
	m_themeAndPartToStates["SpinUpHorz"].push_back("Hot");
	m_themeAndPartToStates["SpinUpHorz"].push_back("Pressed");
	m_themeAndPartToStates["SpinUpHorz"].push_back("Disabled");
	m_themePartStateToIDs["SpinUpHorzNormal"] = std::pair<int, int>(3, 1);
	m_themePartStateToIDs["SpinUpHorzHot"] = std::pair<int, int>(3, 2);
	m_themePartStateToIDs["SpinUpHorzPressed"] = std::pair<int, int>(3, 3);
	m_themePartStateToIDs["SpinUpHorzDisabled"] = std::pair<int, int>(3, 4);
	m_themeToParts["Spin"].push_back("RightHorz");
	m_themeAndPartToStates["SpinRightHorz"].push_back("Normal");
	m_themeAndPartToStates["SpinRightHorz"].push_back("Hot");
	m_themeAndPartToStates["SpinRightHorz"].push_back("Pressed");
	m_themeAndPartToStates["SpinRightHorz"].push_back("Disabled");
	m_themePartStateToIDs["SpinRightHorzNormal"] = std::pair<int, int>(4, 1);
	m_themePartStateToIDs["SpinRightHorzHot"] = std::pair<int, int>(4, 2);
	m_themePartStateToIDs["SpinRightHorzPressed"] = std::pair<int, int>(4, 3);
	m_themePartStateToIDs["SpinRightHorzDisabled"] = std::pair<int, int>(4, 4);

		// Add scrollbar items
		m_themeToParts["ScrollBar"].push_back("ArrowBtn");
		m_themeAndPartToStates["ScrollBarArrowBtn"].push_back("UpNormal");
		m_themeAndPartToStates["ScrollBarArrowBtn"].push_back("UpHot");
		m_themeAndPartToStates["ScrollBarArrowBtn"].push_back("UpPressed");
		m_themeAndPartToStates["ScrollBarArrowBtn"].push_back("UpDisabled");
		m_themeAndPartToStates["ScrollBarArrowBtn"].push_back("DownNormal");
		m_themeAndPartToStates["ScrollBarArrowBtn"].push_back("DownHot");
		m_themeAndPartToStates["ScrollBarArrowBtn"].push_back("DownPressed");
		m_themeAndPartToStates["ScrollBarArrowBtn"].push_back("DownDisabled");
		m_themeAndPartToStates["ScrollBarArrowBtn"].push_back("LeftNormal");
		m_themeAndPartToStates["ScrollBarArrowBtn"].push_back("LeftHot");
		m_themeAndPartToStates["ScrollBarArrowBtn"].push_back("LeftPressed");
		m_themeAndPartToStates["ScrollBarArrowBtn"].push_back("LeftDisabled");
		m_themeAndPartToStates["ScrollBarArrowBtn"].push_back("RightNormal");
		m_themeAndPartToStates["ScrollBarArrowBtn"].push_back("RightHot");
		m_themeAndPartToStates["ScrollBarArrowBtn"].push_back("RightPressed");
		m_themeAndPartToStates["ScrollBarArrowBtn"].push_back("RightDisabled");	
		m_themePartStateToIDs["ScrollBarArrowBtnUpNormal"] = std::pair<int, int>(1, 1);
		m_themePartStateToIDs["ScrollBarArrowBtnUpHot"] = std::pair<int, int>(1, 2);
		m_themePartStateToIDs["ScrollBarArrowBtnUpPressed"] = std::pair<int, int>(1, 3);
		m_themePartStateToIDs["ScrollBarArrowBtnUpDisabled"] = std::pair<int, int>(1, 4);
		m_themePartStateToIDs["ScrollBarArrowBtnDownNormal"] = std::pair<int, int>(1, 5);
		m_themePartStateToIDs["ScrollBarArrowBtnDownHot"] = std::pair<int, int>(1, 6);
		m_themePartStateToIDs["ScrollBarArrowBtnDownPressed"] = std::pair<int, int>(1, 7);
		m_themePartStateToIDs["ScrollBarArrowBtnDownDisabled"] = std::pair<int, int>(1, 8);
		m_themePartStateToIDs["ScrollBarArrowBtnLeftNormal"] = std::pair<int, int>(1, 9);
		m_themePartStateToIDs["ScrollBarArrowBtnLeftHot"] = std::pair<int, int>(1, 10);
		m_themePartStateToIDs["ScrollBarArrowBtnLeftPressed"] = std::pair<int, int>(1, 11);
		m_themePartStateToIDs["ScrollBarArrowBtnLeftDisabled"] = std::pair<int, int>(1, 12);
		m_themePartStateToIDs["ScrollBarArrowBtnRightNormal"] = std::pair<int, int>(1, 13);
		m_themePartStateToIDs["ScrollBarArrowBtnRightHot"] = std::pair<int, int>(1, 14);
		m_themePartStateToIDs["ScrollBarArrowBtnRightPressed"] = std::pair<int, int>(1, 15);
		m_themePartStateToIDs["ScrollBarArrowBtnRightDisabled"] = std::pair<int, int>(1, 16);
		m_themeToParts["ScrollBar"].push_back("ThumbBtnHorz");
		m_themePartStateToIDs["ScrollBarThumbBtnHorz"] = std::pair<int, int>(2, 0);
		m_themeToParts["ScrollBar"].push_back("ThumbBtnVert");
		m_themePartStateToIDs["ScrollBarThumbBtnVert"] = std::pair<int, int>(3, 0);
		m_themeToParts["ScrollBar"].push_back("LowerTrackHorz");
		m_themePartStateToIDs["ScrollBarLowerTrackHorz"] = std::pair<int, int>(4, 0);
		m_themeToParts["ScrollBar"].push_back("UpperTrackHorz");
		m_themePartStateToIDs["ScrollBarUpperTrackHorz"] = std::pair<int, int>(5, 0);
		m_themeToParts["ScrollBar"].push_back("LowerTrackVert");
		m_themePartStateToIDs["ScrollBarLowerTrackVert"] = std::pair<int, int>(6, 0);
		m_themeToParts["ScrollBar"].push_back("UpperTrackVert");
		m_themePartStateToIDs["ScrollBarUpperTrackVert"] = std::pair<int, int>(7, 0);
		m_themeToParts["ScrollBar"].push_back("GripperHorz");
		m_themePartStateToIDs["ScrollBarGripperHorz"] = std::pair<int, int>(8, 0);
		m_themeToParts["ScrollBar"].push_back("GripperVert");
		m_themePartStateToIDs["ScrollBarGripperVert"] = std::pair<int, int>(9, 0);
		m_themeToParts["ScrollBar"].push_back("SizeBox");
		m_themeAndPartToStates["ScrollBarSizeBox"].push_back("RightAlign");
		m_themeAndPartToStates["ScrollBarSizeBox"].push_back("LeftAlign");
		m_themePartStateToIDs["ScrollBarSizeBoxRightAlign"] = std::pair<int, int>(10, 1);
		m_themePartStateToIDs["ScrollBarSizeBoxLeftAlign"] = std::pair<int, int>(10, 2);
		
		// add Edit styles
		m_themeToParts["Edit"].push_back("EditText");
		m_themeAndPartToStates["EditEditText"].push_back("Normal");
		m_themeAndPartToStates["EditEditText"].push_back("Hot");
		m_themeAndPartToStates["EditEditText"].push_back("Selected");
		m_themeAndPartToStates["EditEditText"].push_back("Disabled");
		m_themeAndPartToStates["EditEditText"].push_back("Focused");
		m_themeAndPartToStates["EditEditText"].push_back("ReadOnly");
		m_themeAndPartToStates["EditEditText"].push_back("Assist");
		m_themePartStateToIDs["EditEditTextNormal"] = std::pair<int, int>(1, 1);
		m_themePartStateToIDs["EditEditTextHot"] = std::pair<int, int>(1, 2);
		m_themePartStateToIDs["EditEditTextSelected"] = std::pair<int, int>(1, 3);
		m_themePartStateToIDs["EditEditTextDisabled"] = std::pair<int, int>(1, 4);
		m_themePartStateToIDs["EditEditTextFocused"] = std::pair<int, int>(1, 5);
		m_themePartStateToIDs["EditEditTextReadOnly"] = std::pair<int, int>(1, 6);
		m_themePartStateToIDs["EditEditTextAssist"] = std::pair<int, int>(1, 7);
		m_themeToParts["Edit"].push_back("Caret");
		m_themePartStateToIDs["EditCaret"] = std::pair<int, int>(2, 0);

		// Add Combobox style
		m_themeToParts["Combobox"].push_back("DropDownButton");
		m_themePartStateToIDs["ComboboxDropDownButton"] = std::pair<int, int>(1, 0);

		// Add taskbar styles
		m_themeToParts["TaskBar"].push_back("BackgroundBottom");
		m_themePartStateToIDs["TaskBarBackgroundBottom"] = std::pair<int, int>(1, 0);
		m_themeToParts["TaskBar"].push_back("BackgroundRight");
		m_themePartStateToIDs["TaskBarBackgroundRight"] = std::pair<int, int>(2, 0);
		m_themeToParts["TaskBar"].push_back("BackgroundTop");
		m_themePartStateToIDs["TaskBarBackgroundTop"] = std::pair<int, int>(3, 0);
		m_themeToParts["TaskBar"].push_back("BackgroundLeft");
		m_themePartStateToIDs["TaskBarBackgroundLeft"] = std::pair<int, int>(4, 0);
		m_themeToParts["TaskBar"].push_back("SizingBarBottom");
		m_themePartStateToIDs["TaskBarSizingBarBottom"] = std::pair<int, int>(5, 0);
		m_themeToParts["TaskBar"].push_back("SizingBarRight");
		m_themePartStateToIDs["TaskBarSizingBarRight"] = std::pair<int, int>(6, 0);
		m_themeToParts["TaskBar"].push_back("SizingBarTop");
		m_themePartStateToIDs["TaskBarSizingBarTop"] = std::pair<int, int>(7, 0);
		m_themeToParts["TaskBar"].push_back("SizingBarLeft");
		m_themePartStateToIDs["TaskBarSizingBarLeft"] = std::pair<int, int>(8, 0);

		// Add taskband styles
		m_themeToParts["TaskBand"].push_back("GroupCount");
		m_themePartStateToIDs["TaskBandGroupCount"] = std::pair<int, int>(1, 0);
		m_themeToParts["TaskBand"].push_back("FlashButton");
		m_themePartStateToIDs["TaskBandFlashButton"] = std::pair<int, int>(2, 0);
		m_themeToParts["TaskBand"].push_back("FlashButtonGroupMenu");
		m_themePartStateToIDs["TaskBandFlashButtonGroupMenu"] = std::pair<int, int>(3, 0);


		// Add startpanel styles
		m_themeToParts["StartPanel"].push_back("UserPane");
		m_themePartStateToIDs["StartPanelUserPane"] = std::pair<int, int>(1, 0);
		m_themeToParts["StartPanel"].push_back("MorePrograms");
		m_themePartStateToIDs["StartPanelMorePrograms"] = std::pair<int, int>(2, 0);
		m_themeToParts["StartPanel"].push_back("MoreProgramsArrow");
		m_themeAndPartToStates["StartPanelMoreProgramsArrow"].push_back("Normal");
		m_themeAndPartToStates["StartPanelMoreProgramsArrow"].push_back("Hot");
		m_themeAndPartToStates["StartPanelMoreProgramsArrow"].push_back("Pressed");
		m_themePartStateToIDs["StartPanelMoreProgramsArrowNormal"] = std::pair<int, int>(3, 1);
		m_themePartStateToIDs["StartPanelMoreProgramsArrowHot"] = std::pair<int, int>(3, 2);
		m_themePartStateToIDs["StartPanelMoreProgramsArrowPressed"] = std::pair<int, int>(3, 3);
		m_themeToParts["StartPanel"].push_back("ProgList");
		m_themePartStateToIDs["StartPanelProgList"] = std::pair<int, int>(4, 0);
		m_themeToParts["StartPanel"].push_back("ProgListSeparator");
		m_themePartStateToIDs["StartPanelProgListSeparator"] = std::pair<int, int>(5, 0);
		m_themeToParts["StartPanel"].push_back("PlacesList");
		m_themePartStateToIDs["StartPanelPlacesList"] = std::pair<int, int>(6, 0);
		m_themeToParts["StartPanel"].push_back("PlacesListSeparator");
		m_themePartStateToIDs["StartPanelPlacesListSeparator"] = std::pair<int, int>(7, 0);
		m_themeToParts["StartPanel"].push_back("LogOff");
		m_themePartStateToIDs["StartPanelLogOff"] = std::pair<int, int>(8, 0);
		m_themeToParts["StartPanel"].push_back("LogOffButtons");
		m_themeAndPartToStates["StartPanelLogOffButtons"].push_back("Normal");
		m_themeAndPartToStates["StartPanelLogOffButtons"].push_back("Hot");
		m_themeAndPartToStates["StartPanelLogOffButtons"].push_back("Pressed");
		m_themePartStateToIDs["StartPanelLogOffButtonsNormal"] = std::pair<int, int>(9, 1);
		m_themePartStateToIDs["StartPanelLogOffButtonsHot"] = std::pair<int, int>(9, 2);
		m_themePartStateToIDs["StartPanelLogOffButtonsPressed"] = std::pair<int, int>(9, 3);
		m_themeToParts["StartPanel"].push_back("UserPicture");
		m_themePartStateToIDs["StartPanelUserPicture"] = std::pair<int, int>(10, 0);
		m_themeToParts["StartPanel"].push_back("Preview");
		m_themePartStateToIDs["StartPanelPreview"] = std::pair<int, int>(11, 0);

		// Add Explorerbar items ( last one !!! )
		m_themeToParts["ExplorerBar"].push_back("HeaderBackground");
		m_themePartStateToIDs["ExplorerBarHeaderBackground"] = std::pair<int, int>(1, 0);
		m_themeToParts["ExplorerBar"].push_back("HeaderClose");
		m_themeAndPartToStates["ExplorerBarHeaderClose"].push_back("Normal");
		m_themeAndPartToStates["ExplorerBarHeaderClose"].push_back("Hot");
		m_themeAndPartToStates["ExplorerBarHeaderClose"].push_back("Pressed");
		m_themePartStateToIDs["ExplorerBarHeaderCloseNormal"] = std::pair<int, int>(2, 1);
		m_themePartStateToIDs["ExplorerBarHeaderCloseHot"] = std::pair<int, int>(2, 2);
		m_themePartStateToIDs["ExplorerBarHeaderClosePressed"] = std::pair<int, int>(2, 3);
		m_themeToParts["ExplorerBar"].push_back("HeaderPin");
		m_themeAndPartToStates["ExplorerBarHeaderPin"].push_back("Normal");
		m_themeAndPartToStates["ExplorerBarHeaderPin"].push_back("Hot");
		m_themeAndPartToStates["ExplorerBarHeaderPin"].push_back("Pressed");
		m_themeAndPartToStates["ExplorerBarHeaderPin"].push_back("SelectedNormal");
		m_themeAndPartToStates["ExplorerBarHeaderPin"].push_back("SelectedHot");
		m_themeAndPartToStates["ExplorerBarHeaderPin"].push_back("SelectedPressed");
		m_themePartStateToIDs["ExplorerBarHeaderPinNormal"] = std::pair<int, int>(3, 1);
		m_themePartStateToIDs["ExplorerBarHeaderPinHot"] = std::pair<int, int>(3, 2);
		m_themePartStateToIDs["ExplorerBarHeaderPinPressed"] = std::pair<int, int>(3, 3);
		m_themePartStateToIDs["ExplorerBarHeaderPinSelectedNormal"] = std::pair<int, int>(3, 4);
		m_themePartStateToIDs["ExplorerBarHeaderPinSelectedHot"] = std::pair<int, int>(3, 5);
		m_themePartStateToIDs["ExplorerBarHeaderPinSelectedPressed"] = std::pair<int, int>(3, 6);
		m_themeToParts["ExplorerBar"].push_back("IEBarMenu");
		m_themeAndPartToStates["ExplorerBarIEBarMenu"].push_back("Normal");
		m_themeAndPartToStates["ExplorerBarIEBarMenu"].push_back("Hot");
		m_themeAndPartToStates["ExplorerBarIEBarMenu"].push_back("Pressed");
		m_themePartStateToIDs["ExplorerBarIEBarMenuNormal"] = std::pair<int, int>(4, 1);
		m_themePartStateToIDs["ExplorerBarIEBarMenuHot"] = std::pair<int, int>(4, 2);
		m_themePartStateToIDs["ExplorerBarIEBarMenuPressed"] = std::pair<int, int>(4, 3);
		m_themeToParts["ExplorerBar"].push_back("NormalGroupBackground");
		m_themePartStateToIDs["ExplorerBarNormalGroupBackground"] = std::pair<int, int>(5, 0);
		m_themeToParts["ExplorerBar"].push_back("NormalGroupCollapse");
		m_themeAndPartToStates["ExplorerBarNormalGroupCollapse"].push_back("Normal");
		m_themeAndPartToStates["ExplorerBarNormalGroupCollapse"].push_back("Hot");
		m_themeAndPartToStates["ExplorerBarNormalGroupCollapse"].push_back("Pressed");
		m_themePartStateToIDs["ExplorerBarNormalGroupCollapseNormal"] = std::pair<int, int>(6, 1);
		m_themePartStateToIDs["ExplorerBarNormalGroupCollapseHot"] = std::pair<int, int>(6, 2);
		m_themePartStateToIDs["ExplorerBarNormalGroupCollapsePressed"] = std::pair<int, int>(6, 3);
		m_themeToParts["ExplorerBar"].push_back("NormalGroupExpand");
		m_themeAndPartToStates["ExplorerBarNormalGroupExpand"].push_back("Normal");
		m_themeAndPartToStates["ExplorerBarNormalGroupExpand"].push_back("Hot");
		m_themeAndPartToStates["ExplorerBarNormalGroupExpand"].push_back("Pressed");
		m_themePartStateToIDs["ExplorerBarNormalGroupExpandNormal"] = std::pair<int, int>(7, 1);
		m_themePartStateToIDs["ExplorerBarNormalGroupExpandHot"] = std::pair<int, int>(7, 2);
		m_themePartStateToIDs["ExplorerBarNormalGroupExpandPressed"] = std::pair<int, int>(7, 3);
		m_themeToParts["ExplorerBar"].push_back("NormalGroupHead");
		m_themePartStateToIDs["ExplorerBarNormalGroupHead"] = std::pair<int, int>(8, 0);
		m_themeToParts["ExplorerBar"].push_back("SpecialGroupBackground");
		m_themePartStateToIDs["ExplorerBarSpecialGroupBackground"] = std::pair<int, int>(9, 0);
		m_themeToParts["ExplorerBar"].push_back("SpecialGroupCollapse");
		m_themeAndPartToStates["ExplorerBarSpecialGroupCollapse"].push_back("Normal");
		m_themeAndPartToStates["ExplorerBarSpecialGroupCollapse"].push_back("Hot");
		m_themeAndPartToStates["ExplorerBarSpecialGroupCollapse"].push_back("Pressed");
		m_themePartStateToIDs["ExplorerBarSpecialGroupCollapseNormal"] = std::pair<int, int>(10, 1);
		m_themePartStateToIDs["ExplorerBarSpecialGroupCollapseHot"] = std::pair<int, int>(10, 2);
		m_themePartStateToIDs["ExplorerBarSpecialGroupCollapsePressed"] = std::pair<int, int>(10, 3);
		m_themeToParts["ExplorerBar"].push_back("SpecialGroupExpand");
		m_themeAndPartToStates["ExplorerBarSpecialGroupExpand"].push_back("Normal");
		m_themeAndPartToStates["ExplorerBarSpecialGroupExpand"].push_back("Hot");
		m_themeAndPartToStates["ExplorerBarSpecialGroupExpand"].push_back("Pressed");
		m_themePartStateToIDs["ExplorerBarSpecialGroupExpandNormal"] = std::pair<int, int>(11, 1);
		m_themePartStateToIDs["ExplorerBarSpecialGroupExpandHot"] = std::pair<int, int>(11, 2);
		m_themePartStateToIDs["ExplorerBarSpecialGroupExpandPressed"] = std::pair<int, int>(11, 3);
		m_themeToParts["ExplorerBar"].push_back("SpecialGroupHead");
		m_themePartStateToIDs["ExplorerBarSpecialGroupHead"] = std::pair<int, int>(12, 0);
	}



void CEditStylesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditStylesDlg)
	DDX_Control(pDX, IDC_CBPARTSTATE, m_cbPartStart);
	DDX_Control(pDX, IDC_CBGRRDPART, m_cbGridPart);
	DDX_Control(pDX, IDC_COMBO3, m_cbState);
	DDX_Control(pDX, IDC_COMBO2, m_cbPart);
	DDX_Control(pDX, IDC_COMBO1, m_cbControl);
	DDX_Control(pDX, IDC_DRAW, m_DrawArea);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditStylesDlg, CDialog)
	//{{AFX_MSG_MAP(CEditStylesDlg)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnSelchangeCombo3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditStylesDlg message handlers

void CEditStylesDlg::OnSelchangeCombo1() 
{
	CString str;
	m_cbControl.GetWindowText(str);

	m_cbPart.ResetContent();

	std::vector<CString>::iterator it = m_themeToParts[str].begin();

	for(; it != m_themeToParts[str].end(); ++it)
	{
		m_cbPart.AddString((*it).GetBuffer((*it).GetLength()));
		(*it).ReleaseBuffer();
	}

	m_cbPart.SelectString(0, m_themeToParts[str][0]);
		
	OnSelchangeCombo2();
	
	Invalidate();
}

void CEditStylesDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CString str;
	m_cbControl.GetWindowText(str);

	CString str2;
	m_cbPart.GetWindowText(str2);

	CString str3;
	m_cbState.GetWindowText(str3);

	RECT rc;
	m_DrawArea.GetWindowRect(&rc);
	ScreenToClient(&rc);
	std::pair<int, int> partAndState = m_themePartStateToIDs[str+str2+str3];

	USES_CONVERSION;

	UGXPThemes::DrawBackground(*this, dc, A2W(str.GetBuffer(str.GetLength())), partAndState.first, partAndState.second, &rc, &rc, false);
	str.ReleaseBuffer();
	UGXPThemes::WriteText(*this, dc, A2T(str.GetBuffer(str.GetLength())), partAndState.first, partAndState.second, str, str.GetLength(), DT_CENTER | DT_VCENTER, &rc, false);
	str.ReleaseBuffer();
}

void CEditStylesDlg::OnSelchangeCombo2() 
{
	CString str;
	m_cbControl.GetWindowText(str);

	CString str2;
	m_cbPart.GetWindowText(str2);

	m_cbState.ResetContent();

	str += str2;

	std::vector<CString>::iterator it = m_themeAndPartToStates[str].begin();

	for(; it != m_themeAndPartToStates[str].end(); ++it)
	{
		if ((*it).GetLength() > 0)
		{
			m_cbState.AddString((*it).GetBuffer((*it).GetLength()));
			(*it).ReleaseBuffer();
		}
	}

	if (m_themeAndPartToStates[str].size() > 0)
		m_cbState.SelectString(0, m_themeAndPartToStates[str][0]);

	Invalidate();
}

void CEditStylesDlg::OnSelchangeCombo3() 
{
	Invalidate();	
}

BOOL CEditStylesDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWinRIGHTame, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	BOOL ret = CDialog::Create(IDD, pParentWnd);


	return ret;
}

BOOL CEditStylesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_cbControl.SelectString(0, "Window");
	OnSelchangeCombo1();

	m_cbGridPart.SelectString(0, "XPCellTypeData");
	m_cbPartStart.SelectString(0, "ThemeStateNormal");

	m_DrawArea.ShowWindow(SW_HIDE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditStylesDlg::OnOK() 
{
	CString part;
	m_cbGridPart.GetWindowText(part);
	CString stateStr;
	m_cbPartStart.GetWindowText(stateStr);

	CString str;
	m_cbControl.GetWindowText(str);

	CString str2;
	m_cbPart.GetWindowText(str2);

	CString str3;
	m_cbState.GetWindowText(str3);

	std::pair<int, int> partAndState = m_themePartStateToIDs[str+str2+str3];

	UGXPCellType type;

	if (part == "XPCellTypeData") type = XPCellTypeData;
	else if (part == "XPCellTypeTopCol") type = XPCellTypeTopCol;
	else if (part == "XPCellTypeLeftCol") type = XPCellTypeLeftCol;
	else if (part == "XPCellTypeBorder") type = XPCellTypeBorder;
	else if (part == "XPCellTypeCombo") type = XPCellTypeCombo;
	else if (part == "XPCellTypeCheck") type = XPCellTypeCheck;
	else if (part == "XPCellTypeCheckYes") type = XPCellTypeCheckYes;
	else if (part == "XPCellTypeCheckNo") type = XPCellTypeCheckNo;
	else if (part == "XPCellTypeRadio") type = XPCellTypeRadio;
	else if (part == "XPCellTypeRadioYes") type = XPCellTypeRadioYes;
	else if (part == "XPCellTypeRadioNo") type = XPCellTypeRadioNo;
	else if (part == "XPCellTypeSpinUp") type = XPCellTypeSpinUp;
	else if (part == "XPCellTypeButton") type = XPCellTypeButton;
	else if (part == "XPCellTypeSpinDown") type = XPCellTypeSpinDown;
	else if (part == "XPCellTypeProgressSelected") type = XPCellTypeProgressSelected;
	else if (part == "XPCellTypeProgressUnselected") type = XPCellTypeProgressUnselected;


	UGXPThemeState state;
	if (stateStr == "ThemeStateNormal") state = ThemeStateNormal;
	else if (stateStr == "ThemeStateCurrent") state = ThemeStateCurrent;
	else if (stateStr == "ThemeStateSelected") state = ThemeStateSelected;
	else if (stateStr == "ThemeStateTriState") state = ThemeStateTriState;
	else if (stateStr == "ThemeStatePressed") state = ThemeStatePressed;

	USES_CONVERSION;

	UGXPThemes::SetXPTheme(type, state, A2W(str.GetBuffer(str.GetLength())), partAndState.first, partAndState.second);
   	str.ReleaseBuffer();
	
	CDialog::OnOK();
}
