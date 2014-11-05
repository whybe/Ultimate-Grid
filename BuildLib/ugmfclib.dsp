# Microsoft Developer Studio Project File - Name="ugmfclib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ugmfclib - Win32 UGDbgOleMFCStatic Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ugmfclib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ugmfclib.mak" CFG="ugmfclib - Win32 UGDbgOleMFCStatic Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ugmfclib - Win32 UGRelMFCDLL" (based on "Win32 (x86) Static Library")
!MESSAGE "ugmfclib - Win32 UGDbgMFCDLL" (based on "Win32 (x86) Static Library")
!MESSAGE "ugmfclib - Win32 UGRelOleMFCDLL" (based on "Win32 (x86) Static Library")
!MESSAGE "ugmfclib - Win32 UGDbgOleMFCDLL" (based on "Win32 (x86) Static Library")
!MESSAGE "ugmfclib - Win32 UGRelMFCStatic" (based on "Win32 (x86) Static Library")
!MESSAGE "ugmfclib - Win32 UGDbgMFCStatic" (based on "Win32 (x86) Static Library")
!MESSAGE "ugmfclib - Win32 UGDbgOleMFCStatic" (based on "Win32 (x86) Static Library")
!MESSAGE "ugmfclib - Win32 UGRelOleMFCStatic" (based on "Win32 (x86) Static Library")
!MESSAGE "ugmfclib - Win32 UGDbgMFCDLL Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "ugmfclib - Win32 UGDbgMFCStatic Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "ugmfclib - Win32 UGDbgOleMFCDLL Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "ugmfclib - Win32 UGDbgOleMFCStatic Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "ugmfclib - Win32 UGRelMFCDLL Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "ugmfclib - Win32 UGRelMFCStatic Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "ugmfclib - Win32 UGRelOleMFCDLL Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "ugmfclib - Win32 UGRelOleMFCStatic Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ugmfclib - Win32 UGRelMFCDLL"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ugmfclib___Win32_UGRelMFCDLL"
# PROP BASE Intermediate_Dir "ugmfclib___Win32_UGRelMFCDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "ugmfclib___Win32_UGRelMFCDLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Zd /O2 /I ".\\" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include" /I ".\\" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Release\ug97rndm.lib"
# ADD LIB32 /nologo /out:"..\Lib\ugrndm.lib"

!ELSEIF  "$(CFG)" == "ugmfclib - Win32 UGDbgMFCDLL"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ugmfclib___Win32_UGDbgMFCDLL"
# PROP BASE Intermediate_Dir "ugmfclib___Win32_UGDbgMFCDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "ugmfclib___Win32_UGDbgMFCDLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Zd /O2 /I "e:\ug97mfc\include" /I "e:\My Projects\MFC Projects\ugmfclib" /I ".\\" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\include" /I ".\\" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Debug\ug97dndm.lib"
# ADD LIB32 /nologo /out:"..\Lib\ugdndm.lib"

!ELSEIF  "$(CFG)" == "ugmfclib - Win32 UGRelOleMFCDLL"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ugmfclib___Win32_UGRelOleMFCDLL"
# PROP BASE Intermediate_Dir "ugmfclib___Win32_UGRelOleMFCDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "ugmfclib___Win32_UGRelOleMFCDLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Zd /O2 /I ".\\" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include" /I ".\\" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "UG_OLE" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Release\ug97rndm.lib"
# ADD LIB32 /nologo /out:"..\Lib\ugrodm.lib"

!ELSEIF  "$(CFG)" == "ugmfclib - Win32 UGDbgOleMFCDLL"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ugmfclib___Win32_UGDbgOleMFCDLL"
# PROP BASE Intermediate_Dir "ugmfclib___Win32_UGDbgOleMFCDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "ugmfclib___Win32_UGDbgOleMFCDLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Zd /O2 /I "e:\ug97mfc\include" /I "e:\My Projects\MFC Projects\ugmfclib" /I ".\\" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\include" /I ".\\" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "UG_OLE" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Debug\ug97dndm.lib"
# ADD LIB32 /nologo /out:"..\Lib\ugdodm.lib"

!ELSEIF  "$(CFG)" == "ugmfclib - Win32 UGRelMFCStatic"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ugmfclib___Win32_UGRelMFCStatic"
# PROP BASE Intermediate_Dir "ugmfclib___Win32_UGRelMFCStatic"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "ugmfclib___Win32_UGRelMFCStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Zd /O2 /I ".\\" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\include" /I ".\\" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Release\ug97rndm.lib"
# ADD LIB32 /nologo /out:"..\Lib\ugrnsm.lib"

!ELSEIF  "$(CFG)" == "ugmfclib - Win32 UGDbgMFCStatic"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ugmfclib___Win32_UGDbgMFCStatic"
# PROP BASE Intermediate_Dir "ugmfclib___Win32_UGDbgMFCStatic"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "ugmfclib___Win32_UGDbgMFCStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Zd /O2 /I "e:\ug97mfc\include" /I "e:\My Projects\MFC Projects\ugmfclib" /I ".\\" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\include" /I ".\\" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Debug\ug97dndm.lib"
# ADD LIB32 /nologo /out:"..\Lib\ugdnsm.lib"

!ELSEIF  "$(CFG)" == "ugmfclib - Win32 UGDbgOleMFCStatic"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ugmfclib___Win32_UGDbgOleMFCStatic"
# PROP BASE Intermediate_Dir "ugmfclib___Win32_UGDbgOleMFCStatic"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "ugmfclib___Win32_UGDbgOleMFCStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Zd /O2 /I "e:\ug97mfc\include" /I "e:\My Projects\MFC Projects\ugmfclib" /I ".\\" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\include" /I ".\\" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "UG_OLE" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Debug\ug97dndm.lib"
# ADD LIB32 /nologo /out:"..\Lib\ugdosm.lib"

!ELSEIF  "$(CFG)" == "ugmfclib - Win32 UGRelOleMFCStatic"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ugmfclib___Win32_UGRelOleMFCStatic"
# PROP BASE Intermediate_Dir "ugmfclib___Win32_UGRelOleMFCStatic"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "ugmfclib___Win32_UGRelOleMFCStatic"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Zd /O2 /I ".\\" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\include" /I ".\\" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "UG_OLE" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Release\ug97rndm.lib"
# ADD LIB32 /nologo /out:"..\Lib\ugrosm.lib"

!ELSEIF  "$(CFG)" == "ugmfclib - Win32 UGDbgMFCDLL Unicode"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ugmfclib___Win32_UGDbgMFCDLL_Unicode"
# PROP BASE Intermediate_Dir "ugmfclib___Win32_UGDbgMFCDLL_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "ugmfclib___Win32_UGDbgMFCDLL_Unicode"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Zd /O2 /I "e:\ug97mfc\include" /I "e:\My Projects\MFC Projects\ugmfclib" /I ".\\" /I "..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\include" /I ".\\" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Libraries\ug97dndm.lib"
# ADD LIB32 /nologo /out:"..\Lib\ugdndu.lib"

!ELSEIF  "$(CFG)" == "ugmfclib - Win32 UGDbgMFCStatic Unicode"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ugmfclib___Win32_UGDbgMFCStatic_Unicode"
# PROP BASE Intermediate_Dir "ugmfclib___Win32_UGDbgMFCStatic_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "ugmfclib___Win32_UGDbgMFCStatic_Unicode"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /GX /Zd /O2 /I "e:\ug97mfc\include" /I "e:\My Projects\MFC Projects\ugmfclib" /I ".\\" /I "..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\include" /I ".\\" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Libraries\ug97dnsm.lib"
# ADD LIB32 /nologo /out:"..\Lib\ugdnsu.lib"

!ELSEIF  "$(CFG)" == "ugmfclib - Win32 UGDbgOleMFCDLL Unicode"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ugmfclib___Win32_UGDbgOleMFCDLL_Unicode"
# PROP BASE Intermediate_Dir "ugmfclib___Win32_UGDbgOleMFCDLL_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "ugmfclib___Win32_UGDbgOleMFCDLL_Unicode"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Zd /O2 /I "e:\ug97mfc\include" /I "e:\My Projects\MFC Projects\ugmfclib" /I ".\\" /I "..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "UG_OLE" /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\include" /I ".\\" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "UG_OLE" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Libraries\ug97dodm.lib"
# ADD LIB32 /nologo /out:"..\Lib\ugdodu.lib"

!ELSEIF  "$(CFG)" == "ugmfclib - Win32 UGDbgOleMFCStatic Unicode"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ugmfclib___Win32_UGDbgOleMFCStatic_Unicode"
# PROP BASE Intermediate_Dir "ugmfclib___Win32_UGDbgOleMFCStatic_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "ugmfclib___Win32_UGDbgOleMFCStatic_Unicode"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /GX /Zd /O2 /I "e:\ug97mfc\include" /I "e:\My Projects\MFC Projects\ugmfclib" /I ".\\" /I "..\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "UG_OLE" /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\include" /I ".\\" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "UG_OLE" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Libraries\ug97dosm.lib"
# ADD LIB32 /nologo /out:"..\Lib\ugdosu.lib"

!ELSEIF  "$(CFG)" == "ugmfclib - Win32 UGRelMFCDLL Unicode"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ugmfclib___Win32_UGRelMFCDLL_Unicode"
# PROP BASE Intermediate_Dir "ugmfclib___Win32_UGRelMFCDLL_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "ugmfclib___Win32_UGRelMFCDLL_Unicode"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Zd /O2 /I ".\\" /I "..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include" /I ".\\" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Libraries\ug97rndm.lib"
# ADD LIB32 /nologo /out:"..\Lib\ugrndu.lib"

!ELSEIF  "$(CFG)" == "ugmfclib - Win32 UGRelMFCStatic Unicode"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ugmfclib___Win32_UGRelMFCStatic_Unicode"
# PROP BASE Intermediate_Dir "ugmfclib___Win32_UGRelMFCStatic_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "ugmfclib___Win32_UGRelMFCStatic_Unicode"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /Zd /O2 /I ".\\" /I "..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\include" /I ".\\" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Libraries\ug97rnsm.lib"
# ADD LIB32 /nologo /out:"..\Lib\ugrnsu.lib"

!ELSEIF  "$(CFG)" == "ugmfclib - Win32 UGRelOleMFCDLL Unicode"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ugmfclib___Win32_UGRelOleMFCDLL_Unicode"
# PROP BASE Intermediate_Dir "ugmfclib___Win32_UGRelOleMFCDLL_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "ugmfclib___Win32_UGRelOleMFCDLL_Unicode"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Zd /O2 /I ".\\" /I "..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "UG_OLE" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include" /I ".\\" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "UG_OLE" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Libraries\ug97rodm.lib"
# ADD LIB32 /nologo /out:"..\Lib\ugrodu.lib"

!ELSEIF  "$(CFG)" == "ugmfclib - Win32 UGRelOleMFCStatic Unicode"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ugmfclib___Win32_UGRelOleMFCStatic_Unicode"
# PROP BASE Intermediate_Dir "ugmfclib___Win32_UGRelOleMFCStatic_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Lib"
# PROP Intermediate_Dir "ugmfclib___Win32_UGRelOleMFCStatic_Unicode"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /Zd /O2 /I ".\\" /I "..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "UG_OLE" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\include" /I ".\\" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "UG_OLE" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\Libraries\ug97rosm.lib"
# ADD LIB32 /nologo /out:"..\Lib\ugrosu.lib"

!ENDIF 

# Begin Target

# Name "ugmfclib - Win32 UGRelMFCDLL"
# Name "ugmfclib - Win32 UGDbgMFCDLL"
# Name "ugmfclib - Win32 UGRelOleMFCDLL"
# Name "ugmfclib - Win32 UGDbgOleMFCDLL"
# Name "ugmfclib - Win32 UGRelMFCStatic"
# Name "ugmfclib - Win32 UGDbgMFCStatic"
# Name "ugmfclib - Win32 UGDbgOleMFCStatic"
# Name "ugmfclib - Win32 UGRelOleMFCStatic"
# Name "ugmfclib - Win32 UGDbgMFCDLL Unicode"
# Name "ugmfclib - Win32 UGDbgMFCStatic Unicode"
# Name "ugmfclib - Win32 UGDbgOleMFCDLL Unicode"
# Name "ugmfclib - Win32 UGDbgOleMFCStatic Unicode"
# Name "ugmfclib - Win32 UGRelMFCDLL Unicode"
# Name "ugmfclib - Win32 UGRelMFCStatic Unicode"
# Name "ugmfclib - Win32 UGRelOleMFCDLL Unicode"
# Name "ugmfclib - Win32 UGRelOleMFCStatic Unicode"
# Begin Group "Source"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\Source\UGCBType.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGCell.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGCelTyp.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGCnrBtn.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGCTarrw.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGDLType.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGDrgDrp.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGDrwHnt.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGDtaSrc.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGEditBase.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\ugformat.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\uggdinfo.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGGrid.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGHint.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\ughscrol.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\ugLstBox.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGMEdit.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGMemMan.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGMultiS.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\ugprint.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\ugptrlst.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\ugsidehd.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGStrOp.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\ugtab.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGTopHdg.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\ugvscrol.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\UGXPThemes.cpp
# End Source File
# End Group
# Begin Group "include"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\Include\UGCBType.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGCell.h
# End Source File
# Begin Source File

SOURCE=..\Include\UGCelTyp.h
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
# End Group
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Target
# End Project
