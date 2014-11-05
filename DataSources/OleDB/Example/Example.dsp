# Microsoft Developer Studio Project File - Name="Example" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Example - Win32 Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Example.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Example.mak" CFG="Example - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Example - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Example - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Example - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "Example - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Example - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\include" /I "c:\oledbsdk\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 oledb.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Example - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\include" /I "c:\oledbsdk\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Example - Win32 Unicode Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Example___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "Example___Win32_Unicode_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Example___Win32_Unicode_Release"
# PROP Intermediate_Dir "Example___Win32_Unicode_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\include" /I "c:\oledbsdk\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\include" /I "c:\oledbsdk\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /D "UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 oledb.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 oledb.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Example - Win32 Unicode Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Example___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "Example___Win32_Unicode_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Example___Win32_Unicode_Debug"
# PROP Intermediate_Dir "Example___Win32_Unicode_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\include" /I "c:\oledbsdk\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fr /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\include" /I "c:\oledbsdk\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /D "UNICODE" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Example - Win32 Release"
# Name "Example - Win32 Debug"
# Name "Example - Win32 Unicode Release"
# Name "Example - Win32 Unicode Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Example.cpp
# End Source File
# Begin Source File

SOURCE=.\Example.rc
# End Source File
# Begin Source File

SOURCE=.\ExampleDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ExampleView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Example.h
# End Source File
# Begin Source File

SOURCE=.\ExampleDoc.h
# End Source File
# Begin Source File

SOURCE=.\ExampleView.h
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
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Example.ico
# End Source File
# Begin Source File

SOURCE=.\res\Example.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ExampleDoc.ico
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
# Begin Group "OleDB Datasource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\binds.cpp
# End Source File
# Begin Source File

SOURCE=..\binds.h
# End Source File
# Begin Source File

SOURCE=..\ugoledb.cpp
# End Source File
# Begin Source File

SOURCE=..\ugoledb.h
# End Source File
# Begin Source File

SOURCE=..\ugoledb2.cpp
# End Source File
# End Group
# Begin Group "Include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Include\UGCell.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\UGCtrl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\UGEdit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Include\UGEditBase.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Mycug.cpp
# End Source File
# Begin Source File

SOURCE=.\Mycug.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
