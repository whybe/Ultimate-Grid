# Microsoft Developer Studio Project File - Name="MyAccess" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MyAccess - Win32 Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MyAccess.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MyAccess.mak" CFG="MyAccess - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MyAccess - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MyAccess - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "MyAccess - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "MyAccess - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MyAccess - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".\\" /I "..\..\..\include" /I "..\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "MyAccess - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\\" /I ".\\" /I "..\..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX"StdAfx.h" /FD /c
# SUBTRACT CPP /Fr
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

!ELSEIF  "$(CFG)" == "MyAccess - Win32 Unicode Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MyAccess"
# PROP BASE Intermediate_Dir "MyAccess"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "MyAccess"
# PROP Intermediate_Dir "MyAccess"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /MDd /W3 /Gm /GX /Zi /Od /I "..\\" /I ".\\" /I "..\..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FD /c
# SUBTRACT BASE CPP /nologo /Fr /YX /Yc /Yu
# ADD CPP /MDd /W3 /Gm /GX /ZI /Od /I "..\\" /I ".\\" /I "..\..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /YX"stdafx.h" /FD /c
# SUBTRACT CPP /nologo /Fr
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

!ELSEIF  "$(CFG)" == "MyAccess - Win32 Unicode Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "MyAcces0"
# PROP BASE Intermediate_Dir "MyAcces0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "MyAcces0"
# PROP Intermediate_Dir "MyAcces0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I ".\\" /I "..\..\..\include" /I "..\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".\\" /I "..\..\..\include" /I "..\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "MyAccess - Win32 Release"
# Name "MyAccess - Win32 Debug"
# Name "MyAccess - Win32 Unicode Debug"
# Name "MyAccess - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\MyAccess.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\MyAccess.rc
# End Source File
# Begin Source File

SOURCE=.\MyAccessDoc.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\MyAccessView.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\MYSQLDLG.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MyAccess.h
# End Source File
# Begin Source File

SOURCE=.\MyAccessDoc.h
# End Source File
# Begin Source File

SOURCE=.\MyAccessView.h
# End Source File
# Begin Source File

SOURCE=.\MYSQLDLG.h
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

SOURCE=.\res\arrow.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor4.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor5.cur
# End Source File
# Begin Source File

SOURCE=.\res\MyAccess.ico
# End Source File
# Begin Source File

SOURCE=.\res\MyAccess.rc2
# End Source File
# Begin Source File

SOURCE=.\res\MyAccessDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\nsresize.cur
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\weresize.cur
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
# Begin Group "DAO Datasource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Ugdao.cpp
# End Source File
# Begin Source File

SOURCE=..\Ugdao.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ugaccess.cpp
# End Source File
# Begin Source File

SOURCE=.\ugaccess.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\myaccess.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\variant.txt
# End Source File
# End Target
# End Project
