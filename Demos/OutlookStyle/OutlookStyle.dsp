# Microsoft Developer Studio Project File - Name="OutlookStyle" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=OutlookStyle - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OutlookStyle.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OutlookStyle.mak" CFG="OutlookStyle - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OutlookStyle - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "OutlookStyle - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OutlookStyle - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\include" /I "..\..\celltypes" /I "..\..\..\..\Ultimate Toolbox\working\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "OutlookStyle - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\include" /I "..\..\celltypes" /I "..\..\..\..\Ultimate Toolbox\working\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /i "..\..\..\..\Ultimate Toolbox\working\include\\" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "OutlookStyle - Win32 Release"
# Name "OutlookStyle - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\OutlookStyle.cpp
# End Source File
# Begin Source File

SOURCE=.\OutlookStyle.rc
# ADD BASE RSC /l 0xc09
# ADD RSC /l 0xc09 /i "..\..\..\..\Ultimate Toolbox\Working\include"
# End Source File
# Begin Source File

SOURCE=.\OutlookStyleDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\OutlookStyleView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\OutlookStyle.h
# End Source File
# Begin Source File

SOURCE=.\OutlookStyleDoc.h
# End Source File
# Begin Source File

SOURCE=.\OutlookStyleView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmattach.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Flags.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OutlookStyle.ico
# End Source File
# Begin Source File

SOURCE=.\res\OutlookStyle.rc2
# End Source File
# Begin Source File

SOURCE=.\res\OutlookStyleDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbarf.bmp
# End Source File
# End Group
# Begin Group "Ultimate Grid"

# PROP Default_Filter ".cpp, .h"
# Begin Group "Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Source\UGCBType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGCell.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGCelTyp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGCnrBtn.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGCTarrw.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGDLType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGDrgDrp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGDrwHnt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGDtaSrc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGEditBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\ugformat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\uggdinfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGGrid.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGHint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\ughscrol.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\ugLstBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGMEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGMemMan.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGMultiS.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\ugprint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\ugptrlst.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\ugsidehd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGStrOp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\ugtab.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGTopHdg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\ugvscrol.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Source\UGXPThemes.cpp
# End Source File
# End Group
# Begin Group "CellTypes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\CellTypes\UGCTafnt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTAutoSize.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTbutn.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTDropGrid.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTdtp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\ugctelps.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTExpand.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTLabeled.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTMail.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTMailSort.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTMarquee.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTmfnt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTNote.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\ugctnotewnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTOutlookHeader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTpie.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTpro1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTprog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTRado.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTsarw.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTsldr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTSpin.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\CellTypeOutlook.cpp
# End Source File
# Begin Source File

SOURCE=.\CellTypeOutlook.h
# End Source File
# End Group
# Begin Group "Ultimate Toolbox"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\CONVFILE.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\COPYTREE.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\CPYSTDLG.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\Crypfile.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\DIR.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\DIRLIST.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\DSTRLIST.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\FILE.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\FILELIST.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\Mdccrypt.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\MDELDLG.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\MFCToolBar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OX3DTabView.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXAdvancedAssert.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXAdvancedAssertMail.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXAppBar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXAutoComplete.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXAutoListBox.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXBackgroundPainter.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXBITBUF.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXBitmapButton.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXBitmapMenu.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXBitmapMenuOrganizer.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXBrowseColorEdit.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXBrowseDirEdit.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXBrowseDirEditList.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXButtonAppearanceDlg.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXCalculatorCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXCalculatorEdit.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXCalendar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXCalendarEdit.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXCalendarPopup.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXCaptionPainter.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXChildFrameState.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXClipPocket.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXCMPFL.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXColorPickerButton.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXColorPickerCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXComboPickerCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXCOMPR.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXContextHelpDialog.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXContextHelpPropertyPage.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXContextHelpPropertySheet.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXCoolBar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXCoolComboBox.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXCoolControlOrganizer.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXCoolCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXCoolToolBar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXCRCChk.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXCsvFile.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXDao.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXDateTimeCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXDckPPg.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXDckPSh.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXDFlHdr.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\Oxdib.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXDirDlg.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXDlgBar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXDockTabCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXDocTemplateSpy.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXDragDockContext.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXDragDropCommands.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXEdit.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXEditList.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXFileChanger.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXFileWatcher.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXFileWatchNotifier.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXFolderPickerDlg.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXFontComboBox.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXFontPickerButton.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXFrameWndDock.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXFullScreenFrame.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXGraphics.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\oxgridedit.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXGridHdr.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXGridList.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXHashTable.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXHistoryCombo.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXHistoryCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXHookWnd.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXHTMLParser.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXHyperLinkAction.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXImageListBox.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXImageViewer.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXInstanceManager.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXInteger.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXIntelliMouse.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXIPEdit.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXItemTip.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXItemTipWnd.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXIteratorService.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXLayoutManager.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXListBoxEx.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXListEdit.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXMaskedEdit.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXMDIFloatWnd.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXMenuBar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXMetaFile.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXMonthCalCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXMultiComboBox.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXNetBrowseTree.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXNotesEditView.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXOptionTreeCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXParser.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXPhysicalEdit.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXPhysicalEditEx.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXPopupBarCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXPreviewDialog.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXProcess.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXPropertiesWnd.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXPropertyDescriptionPane.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXPropertyTree.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXQuickString.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXRectTracker.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXRegExpression.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXRegistryItem.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXRegistryValFile.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXRegistryWatcher.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXRegistryWatchNotifier.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXResourceFile.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXResourceLibrary.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXRollup.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXRoundedButton.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXRulerOrganizer.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXScript.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXScrollTip.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXScrollTipOwner.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXScrollWnd.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSeparator.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXService.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXShape.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXShdWnd.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXShellFolderTree.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXShellNamespaceNavigator.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXShellObjectList.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXShortcut.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXShortcutBar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXShortkeysOrganizer.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSizeCtrlBar.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSizeDlgBar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSizeDockBar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSizeToolBar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSkinnedComboBox.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSkinnedSpinCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSkinnedTabCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSkins.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSound.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSoundCustomizeDlg.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSoundEffectManager.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSoundWnd.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSpinCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSplashWnd.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSplashWndDIB.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSplitterColRowState.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSplitterRect.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSplitterWnd.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXStatic.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXStaticHyperLink.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXStaticText.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXSzMiniDockFrmWnd.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXTabClientWnd.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXTabView.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXTaskbarIcon.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXTleBar.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXToolTipCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXTrace.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXTreeCal.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXTreeCombo.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXTreeCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXTreeEdit.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXTreeHeader.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXTreeItem.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXUNC.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXUNCStandardActor.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXURL.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXUsertl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXUUDec.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXUxTheme.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXWABook.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXWatchedDir.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\oxwebctrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\OXWorkspaceState.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\Oxzoomvw.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\Path.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\PATHITER.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\PROGRESS.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\UTBStrOp.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\WATCHBUF.CPP"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\Xstatus4.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Ultimate Toolbox\Working\source\XSTRING.CPP"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
