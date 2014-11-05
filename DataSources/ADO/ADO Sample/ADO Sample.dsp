# Microsoft Developer Studio Project File - Name="ADO Sample" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ADO Sample - Win32 UNICODE Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ADO Sample.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ADO Sample.mak" CFG="ADO Sample - Win32 UNICODE Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ADO Sample - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ADO Sample - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "ADO Sample - Win32 UNICODE Debug" (based on "Win32 (x86) Application")
!MESSAGE "ADO Sample - Win32 UNICODE Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ADO Sample - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\Include\\" /I "..\..\..\CellTypes\\" /I "..\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ADO Sample - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\Include\\" /I "..\..\..\CellTypes\\" /I "..\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "ADO Sample - Win32 UNICODE Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ADO_Sample___Win32_UNICODE_Debug"
# PROP BASE Intermediate_Dir "ADO_Sample___Win32_UNICODE_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ADO_Sample___Win32_UNICODE_Debug"
# PROP Intermediate_Dir "ADO_Sample___Win32_UNICODE_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\Include\\" /I "..\..\..\CellTypes\\" /I "..\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\Include\\" /I "..\..\..\CellTypes\\" /I "..\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /D "UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "ADO Sample - Win32 UNICODE Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ADO_Sample___Win32_UNICODE_Release"
# PROP BASE Intermediate_Dir "ADO_Sample___Win32_UNICODE_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ADO_Sample___Win32_UNICODE_Release"
# PROP Intermediate_Dir "ADO_Sample___Win32_UNICODE_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\Include\\" /I "..\..\..\CellTypes\\" /I "..\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\Include\\" /I "..\..\..\CellTypes\\" /I "..\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /D "UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "ADO Sample - Win32 Release"
# Name "ADO Sample - Win32 Debug"
# Name "ADO Sample - Win32 UNICODE Debug"
# Name "ADO Sample - Win32 UNICODE Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=".\ADO Sample.cpp"
# End Source File
# Begin Source File

SOURCE=".\ADO Sample.rc"
# End Source File
# Begin Source File

SOURCE=".\ADO SampleDoc.cpp"
# End Source File
# Begin Source File

SOURCE=".\ADO SampleView.cpp"
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ConnectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\SqlEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=".\ADO Sample.h"
# End Source File
# Begin Source File

SOURCE=".\ADO SampleDoc.h"
# End Source File
# Begin Source File

SOURCE=".\ADO SampleView.h"
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ConnectDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SqlEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\ADO Sample.ico"
# End Source File
# Begin Source File

SOURCE=".\res\ADO Sample.rc2"
# End Source File
# Begin Source File

SOURCE=".\res\ADO SampleDoc.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Ultimate Grid"

# PROP Default_Filter ""
# Begin Group "Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Source\UGCBType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGCell.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGCelTyp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGCnrBtn.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGCTarrw.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGDLType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGDrgDrp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGDrwHnt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGDtaSrc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGEditBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ugformat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\uggdinfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGGrid.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGHint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ughscrol.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ugLstBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGMEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGMemMan.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGMultiS.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ugprint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ugptrlst.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ugsidehd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGStrOp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ugtab.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGTopHdg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\ugvscrol.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Source\UGXPThemes.cpp
# End Source File
# End Group
# Begin Group "CellTypes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\CellTypes\UGCTsarw.cpp
# End Source File
# End Group
# Begin Group "ADO Datasource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ADOImpDatasource.cpp
# End Source File
# Begin Source File

SOURCE=..\ADOImpDatasource.h
# End Source File
# Begin Source File

SOURCE=..\UpdatedRow.cpp
# End Source File
# Begin Source File

SOURCE=..\UpdatedRow.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\MyCUG.cpp
# End Source File
# Begin Source File

SOURCE=.\MyCUG.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
