# Microsoft Developer Studio Project File - Name="Build DLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Build DLL - Win32 Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Build DLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Build DLL.mak" CFG="Build DLL - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Build DLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Build DLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Build DLL - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Build DLL - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Build DLL - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\Include" /I "..\celltypes" /I "..\editcontrols" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_BUILD_UG_INTO_EXTDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"..\DLLs\UGMFC.dll" /implib:"..\DLLs\UGMFC.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Build DLL - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Include" /I "..\celltypes" /I "..\editcontrols" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_BUILD_UG_INTO_EXTDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\DLLs\UGMFCD.dll" /implib:"..\DLLs\UGMFCD.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Build DLL - Win32 Unicode Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Build_DLL___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "Build_DLL___Win32_Unicode_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Unicode_Debug"
# PROP Intermediate_Dir "Unicode_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_BUILD_UG_INTO_EXTDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Include" /I "..\celltypes" /I "..\editcontrols" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_BUILD_UG_INTO_EXTDLL" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\DLLs\Build DLL.dll" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\DLLs\UGMFCDU.dll" /implib:"..\DLLs\UGMFCDU.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Build DLL - Win32 Unicode Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Build_DLL___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "Build_DLL___Win32_Unicode_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Unicode_Release"
# PROP Intermediate_Dir "Unicode_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\Include" /I "..\celltypes" /I "..\editcontrols" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_BUILD_UG_INTO_EXTDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"..\DLLs\Build DLL.dll"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"..\DLLs\UGMFCU.dll" /implib:"..\DLLs\UGMFCU.lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Build DLL - Win32 Release"
# Name "Build DLL - Win32 Debug"
# Name "Build DLL - Win32 Unicode Debug"
# Name "Build DLL - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=".\Build DLL.cpp"
# End Source File
# Begin Source File

SOURCE=".\Build DLL.rc"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
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

SOURCE=".\res\Build DLL.rc2"
# End Source File
# End Group
# Begin Group "Ultimate Grid"

# PROP Default_Filter ""
# Begin Group "Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\Source\UGCBType.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\UGCell.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\UGCelTyp.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\UGCnrBtn.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\UGCTarrw.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\UGCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\UGDLType.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\UGDrgDrp.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\UGDrwHnt.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\UGDtaSrc.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\UGEdit.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\UGEditBase.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\ugformat.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\uggdinfo.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\UGGrid.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\UGHint.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\ughscrol.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\ugLstBox.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\UGMEdit.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\UGMemMan.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\UGMultiS.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\ugprint.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\ugptrlst.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\ugsidehd.cpp"
# End Source File
# Begin Source File

SOURCE=..\Source\UGStrOp.cpp
# End Source File
# Begin Source File

SOURCE="..\Source\ugtab.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\UGTopHdg.cpp"
# End Source File
# Begin Source File

SOURCE="..\Source\ugvscrol.cpp"
# End Source File
# Begin Source File

SOURCE=..\Source\UGXPThemes.cpp
# End Source File
# End Group
# Begin Group "Celltypes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\CellTypes\UGCTafnt.cpp
# End Source File
# Begin Source File

SOURCE=..\CellTypes\UGCTAutoSize.cpp
# End Source File
# Begin Source File

SOURCE=..\CellTypes\UGCTbutn.cpp
# End Source File
# Begin Source File

SOURCE=..\CellTypes\UGCTDropGrid.cpp
# End Source File
# Begin Source File

SOURCE=..\CellTypes\UGCTdtp.cpp
# End Source File
# Begin Source File

SOURCE=..\CellTypes\ugctelps.cpp
# End Source File
# Begin Source File

SOURCE=..\CellTypes\UGCTLabeled.cpp
# End Source File
# Begin Source File

SOURCE=..\CellTypes\UGCTMarquee.cpp
# End Source File
# Begin Source File

SOURCE=..\CellTypes\UGCTmfnt.cpp
# End Source File
# Begin Source File

SOURCE=..\CellTypes\UGCTNote.cpp
# End Source File
# Begin Source File

SOURCE=..\CellTypes\ugctnotewnd.cpp
# End Source File
# Begin Source File

SOURCE=..\CellTypes\UGCTpie.cpp
# End Source File
# Begin Source File

SOURCE=..\CellTypes\UGCTpro1.cpp
# End Source File
# Begin Source File

SOURCE=..\CellTypes\UGCTprog.cpp
# End Source File
# Begin Source File

SOURCE=..\CellTypes\UGCTRado.cpp
# End Source File
# Begin Source File

SOURCE=..\CellTypes\UGCTsarw.cpp
# End Source File
# Begin Source File

SOURCE=..\CellTypes\UGCTsldr.cpp
# End Source File
# Begin Source File

SOURCE=..\CellTypes\UGCTSpin.cpp
# End Source File
# End Group
# Begin Group "Edit Controls"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\EditControls\UTEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\EditControls\UTMaskedEdit.cpp
# End Source File
# End Group
# Begin Group "Include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Include\UG64Bit.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGCBType.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGCell.h
# End Source File
# Begin Source File

SOURCE=..\Include\ugceltyp.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGCnrBtn.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGCTarrw.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGCtrl.h
# End Source File
# Begin Source File

SOURCE=..\Include\ugdefine.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGDLType.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGDrgDrp.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGDrwHnt.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGDtaSrc.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGEdit.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGEditBase.h
# End Source File
# Begin Source File

SOURCE=..\Include\ugformat.h
# End Source File
# Begin Source File

SOURCE=..\Include\uggdinfo.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGGrid.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGHint.h
# End Source File
# Begin Source File

SOURCE=..\Include\ughscrol.h
# End Source File
# Begin Source File

SOURCE=..\Include\uglstbox.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGMEdit.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGMemMan.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGMultiS.h
# End Source File
# Begin Source File

SOURCE=..\Include\ugprint.h
# End Source File
# Begin Source File

SOURCE=..\Include\ugptrlst.h
# End Source File
# Begin Source File

SOURCE=..\Include\ugsidehd.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGStrOp.h
# End Source File
# Begin Source File

SOURCE=..\Include\ugstruct.h
# End Source File
# Begin Source File

SOURCE=..\Include\ugtab.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGTopHdg.h
# End Source File
# Begin Source File

SOURCE=..\Include\ugvscrol.h
# End Source File
# Begin Source File

SOURCE=..\Include\ugxpthemes.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
