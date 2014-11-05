# Microsoft Developer Studio Project File - Name="XP Theme Demo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=XP Theme Demo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XP Theme Demo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XP Theme Demo.mak" CFG="XP Theme Demo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XP Theme Demo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "XP Theme Demo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XP Theme Demo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /I "..\..\celltypes" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc09 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 comsupp.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "XP Theme Demo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\include" /I "..\..\celltypes" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc09 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 comsupp.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "XP Theme Demo - Win32 Release"
# Name "XP Theme Demo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\EditStylesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=".\XP Theme Demo.cpp"
# End Source File
# Begin Source File

SOURCE=".\XP Theme Demo.rc"
# End Source File
# Begin Source File

SOURCE=".\XP Theme DemoDoc.cpp"
# End Source File
# Begin Source File

SOURCE=".\XP Theme DemoView.cpp"
# End Source File
# Begin Source File

SOURCE=.\XPThemeDemoGrid.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\EditStylesDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=".\XP Theme Demo.h"
# End Source File
# Begin Source File

SOURCE=".\XP Theme DemoDoc.h"
# End Source File
# Begin Source File

SOURCE=".\XP Theme DemoView.h"
# End Source File
# Begin Source File

SOURCE=.\XPThemeDemoGrid.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=".\res\XP Theme Demo.ico"
# End Source File
# Begin Source File

SOURCE=".\res\XP Theme Demo.rc2"
# End Source File
# Begin Source File

SOURCE=".\res\XP Theme DemoDoc.ico"
# End Source File
# End Group
# Begin Group "Ultimate Grid"

# PROP Default_Filter ""
# Begin Group "Source"

# PROP Default_Filter ".cpp"
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
# Begin Group "Cell Types"

# PROP Default_Filter ".cpp"
# Begin Source File

SOURCE=..\..\CellTypes\UGCTafnt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTafnt.h
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTAutoSize.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTAutoSize.h
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTbutn.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTbutn.h
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTDropGrid.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTDropGrid.h
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTdtp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTdtp.h
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\ugctelps.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\ugctelps.h
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTLabeled.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTLabeled.h
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTMarquee.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTMarquee.h
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTmfnt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTmfnt.h
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTNote.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTNote.h
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\ugctnotewnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\ugctnotewnd.h
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTpie.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTpie.h
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTpro1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTpro1.h
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTprog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTprog.h
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTRado.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTRado.h
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTsarw.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTsarw.h
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTsldr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTsldr.h
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTSpin.cpp
# End Source File
# Begin Source File

SOURCE=..\..\CellTypes\UGCTSpin.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
