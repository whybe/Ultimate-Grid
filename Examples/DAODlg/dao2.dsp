# Microsoft Developer Studio Project File - Name="dao2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=dao2 - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dao2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dao2.mak" CFG="dao2 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dao2 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "dao2 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dao2 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\Include" /I "..\..\Datasources\DAO" /I ".\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "dao2 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\Include" /I "..\..\Datasources\DAO" /I ".\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386

!ENDIF 

# Begin Target

# Name "dao2 - Win32 Release"
# Name "dao2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\dao2.cpp
# End Source File
# Begin Source File

SOURCE=.\dao2.rc
# End Source File
# Begin Source File

SOURCE=.\dao2Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\dao2.h
# End Source File
# Begin Source File

SOURCE=.\dao2Dlg.h
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\dao2.ico
# End Source File
# Begin Source File

SOURCE=.\res\dao2.rc2
# End Source File
# End Group
# Begin Group "Ultimate Grid"

# PROP Default_Filter ""
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
# Begin Group "DAO Datasource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Datasources\dao\Ugdao.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Datasources\dao\Ugdao.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\MyCug.cpp
# End Source File
# Begin Source File

SOURCE=.\mycug.h
# End Source File
# End Group
# End Target
# End Project
