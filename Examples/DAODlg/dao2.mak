# Microsoft Developer Studio Generated NMAKE File, Based on dao2.dsp
!IF "$(CFG)" == ""
CFG=dao2 - Win32 Release
!MESSAGE No configuration specified. Defaulting to dao2 - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "dao2 - Win32 Release" && "$(CFG)" != "dao2 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dao2 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\dao2.exe"

!ELSE 

ALL : "$(OUTDIR)\dao2.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\dao2.obj"
	-@erase "$(INTDIR)\dao2.pch"
	-@erase "$(INTDIR)\dao2.res"
	-@erase "$(INTDIR)\dao2Dlg.obj"
	-@erase "$(INTDIR)\MyCug.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\UGCBType.obj"
	-@erase "$(INTDIR)\UGCell.obj"
	-@erase "$(INTDIR)\UGCelTyp.obj"
	-@erase "$(INTDIR)\UGCnrBtn.obj"
	-@erase "$(INTDIR)\UGCTarrw.obj"
	-@erase "$(INTDIR)\UGCtrl.obj"
	-@erase "$(INTDIR)\UGDAO.obj"
	-@erase "$(INTDIR)\UGDLType.obj"
	-@erase "$(INTDIR)\UGDrgDrp.obj"
	-@erase "$(INTDIR)\UGDrwHnt.obj"
	-@erase "$(INTDIR)\UGDtaSrc.obj"
	-@erase "$(INTDIR)\UGEdit.obj"
	-@erase "$(INTDIR)\ugexcel.obj"
	-@erase "$(INTDIR)\ugformat.obj"
	-@erase "$(INTDIR)\uggdinfo.obj"
	-@erase "$(INTDIR)\UGGrid.obj"
	-@erase "$(INTDIR)\ughscrol.obj"
	-@erase "$(INTDIR)\ugLstBox.obj"
	-@erase "$(INTDIR)\UGMemMan.obj"
	-@erase "$(INTDIR)\UGMultiS.obj"
	-@erase "$(INTDIR)\ugprint.obj"
	-@erase "$(INTDIR)\ugptrlst.obj"
	-@erase "$(INTDIR)\ugsidehd.obj"
	-@erase "$(INTDIR)\UGTab.obj"
	-@erase "$(INTDIR)\UGTopHdg.obj"
	-@erase "$(INTDIR)\ugvscrol.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\dao2.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)\dao2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dao2.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dao2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\dao2.pdb" /machine:I386 /out:"$(OUTDIR)\dao2.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\dao2.obj" \
	"$(INTDIR)\dao2.res" \
	"$(INTDIR)\dao2Dlg.obj" \
	"$(INTDIR)\MyCug.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UGCBType.obj" \
	"$(INTDIR)\UGCell.obj" \
	"$(INTDIR)\UGCelTyp.obj" \
	"$(INTDIR)\UGCnrBtn.obj" \
	"$(INTDIR)\UGCTarrw.obj" \
	"$(INTDIR)\UGCtrl.obj" \
	"$(INTDIR)\UGDAO.obj" \
	"$(INTDIR)\UGDLType.obj" \
	"$(INTDIR)\UGDrgDrp.obj" \
	"$(INTDIR)\UGDrwHnt.obj" \
	"$(INTDIR)\UGDtaSrc.obj" \
	"$(INTDIR)\UGEdit.obj" \
	"$(INTDIR)\ugexcel.obj" \
	"$(INTDIR)\ugformat.obj" \
	"$(INTDIR)\uggdinfo.obj" \
	"$(INTDIR)\UGGrid.obj" \
	"$(INTDIR)\ughscrol.obj" \
	"$(INTDIR)\ugLstBox.obj" \
	"$(INTDIR)\UGMemMan.obj" \
	"$(INTDIR)\UGMultiS.obj" \
	"$(INTDIR)\ugprint.obj" \
	"$(INTDIR)\ugptrlst.obj" \
	"$(INTDIR)\ugsidehd.obj" \
	"$(INTDIR)\UGTab.obj" \
	"$(INTDIR)\UGTopHdg.obj" \
	"$(INTDIR)\ugvscrol.obj"

"$(OUTDIR)\dao2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dao2 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\dao2.exe"

!ELSE 

ALL : "$(OUTDIR)\dao2.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AboutDlg.obj"
	-@erase "$(INTDIR)\dao2.obj"
	-@erase "$(INTDIR)\dao2.pch"
	-@erase "$(INTDIR)\dao2.res"
	-@erase "$(INTDIR)\dao2Dlg.obj"
	-@erase "$(INTDIR)\MyCug.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\UGCBType.obj"
	-@erase "$(INTDIR)\UGCell.obj"
	-@erase "$(INTDIR)\UGCelTyp.obj"
	-@erase "$(INTDIR)\UGCnrBtn.obj"
	-@erase "$(INTDIR)\UGCTarrw.obj"
	-@erase "$(INTDIR)\UGCtrl.obj"
	-@erase "$(INTDIR)\UGDAO.obj"
	-@erase "$(INTDIR)\UGDLType.obj"
	-@erase "$(INTDIR)\UGDrgDrp.obj"
	-@erase "$(INTDIR)\UGDrwHnt.obj"
	-@erase "$(INTDIR)\UGDtaSrc.obj"
	-@erase "$(INTDIR)\UGEdit.obj"
	-@erase "$(INTDIR)\ugexcel.obj"
	-@erase "$(INTDIR)\ugformat.obj"
	-@erase "$(INTDIR)\uggdinfo.obj"
	-@erase "$(INTDIR)\UGGrid.obj"
	-@erase "$(INTDIR)\ughscrol.obj"
	-@erase "$(INTDIR)\ugLstBox.obj"
	-@erase "$(INTDIR)\UGMemMan.obj"
	-@erase "$(INTDIR)\UGMultiS.obj"
	-@erase "$(INTDIR)\ugprint.obj"
	-@erase "$(INTDIR)\ugptrlst.obj"
	-@erase "$(INTDIR)\ugsidehd.obj"
	-@erase "$(INTDIR)\UGTab.obj"
	-@erase "$(INTDIR)\UGTopHdg.obj"
	-@erase "$(INTDIR)\ugvscrol.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\dao2.exe"
	-@erase "$(OUTDIR)\dao2.ilk"
	-@erase "$(OUTDIR)\dao2.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\dao2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dao2.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dao2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\dao2.pdb" /debug /machine:I386 /out:"$(OUTDIR)\dao2.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AboutDlg.obj" \
	"$(INTDIR)\dao2.obj" \
	"$(INTDIR)\dao2.res" \
	"$(INTDIR)\dao2Dlg.obj" \
	"$(INTDIR)\MyCug.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UGCBType.obj" \
	"$(INTDIR)\UGCell.obj" \
	"$(INTDIR)\UGCelTyp.obj" \
	"$(INTDIR)\UGCnrBtn.obj" \
	"$(INTDIR)\UGCTarrw.obj" \
	"$(INTDIR)\UGCtrl.obj" \
	"$(INTDIR)\UGDAO.obj" \
	"$(INTDIR)\UGDLType.obj" \
	"$(INTDIR)\UGDrgDrp.obj" \
	"$(INTDIR)\UGDrwHnt.obj" \
	"$(INTDIR)\UGDtaSrc.obj" \
	"$(INTDIR)\UGEdit.obj" \
	"$(INTDIR)\ugexcel.obj" \
	"$(INTDIR)\ugformat.obj" \
	"$(INTDIR)\uggdinfo.obj" \
	"$(INTDIR)\UGGrid.obj" \
	"$(INTDIR)\ughscrol.obj" \
	"$(INTDIR)\ugLstBox.obj" \
	"$(INTDIR)\UGMemMan.obj" \
	"$(INTDIR)\UGMultiS.obj" \
	"$(INTDIR)\ugprint.obj" \
	"$(INTDIR)\ugptrlst.obj" \
	"$(INTDIR)\ugsidehd.obj" \
	"$(INTDIR)\UGTab.obj" \
	"$(INTDIR)\UGTopHdg.obj" \
	"$(INTDIR)\ugvscrol.obj"

"$(OUTDIR)\dao2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(CFG)" == "dao2 - Win32 Release" || "$(CFG)" == "dao2 - Win32 Debug"
SOURCE=.\AboutDlg.cpp
DEP_CPP_ABOUT=\
	".\AboutDlg.h"\
	".\dao2.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\AboutDlg.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"


SOURCE=.\dao2.cpp
DEP_CPP_DAO2_=\
	".\dao2.h"\
	".\dao2Dlg.h"\
	".\mycug.h"\
	".\StdAfx.h"\
	".\UGDAO.h"\
	
NODEP_CPP_DAO2_=\
	".\TrackWnd.h"\
	".\ugctrl.h"\
	

"$(INTDIR)\dao2.obj" : $(SOURCE) $(DEP_CPP_DAO2_) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"


SOURCE=.\dao2.rc
DEP_RSC_DAO2_R=\
	".\res\cursor1.cur"\
	".\res\dao2.ico"\
	".\res\dao2.rc2"\
	

"$(INTDIR)\dao2.res" : $(SOURCE) $(DEP_RSC_DAO2_R) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\dao2Dlg.cpp
DEP_CPP_DAO2D=\
	".\AboutDlg.h"\
	".\dao2.h"\
	".\dao2Dlg.h"\
	".\mycug.h"\
	".\StdAfx.h"\
	".\UGDAO.h"\
	
NODEP_CPP_DAO2D=\
	".\TrackWnd.h"\
	".\ugctrl.h"\
	

"$(INTDIR)\dao2Dlg.obj" : $(SOURCE) $(DEP_CPP_DAO2D) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"


SOURCE=.\MyCug.cpp
DEP_CPP_MYCUG=\
	".\mycug.h"\
	".\StdAfx.h"\
	
NODEP_CPP_MYCUG=\
	".\TrackWnd.h"\
	".\ugctrl.h"\
	

"$(INTDIR)\MyCug.obj" : $(SOURCE) $(DEP_CPP_MYCUG) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "dao2 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)\dao2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\dao2.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "dao2 - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\dao2.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\dao2.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\code\UGCBType.cpp
DEP_CPP_UGCBT=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\UGCBType.obj" : $(SOURCE) $(DEP_CPP_UGCBT) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\UGCell.cpp
DEP_CPP_UGCEL=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\UGCell.obj" : $(SOURCE) $(DEP_CPP_UGCEL) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\UGCelTyp.cpp
DEP_CPP_UGCELT=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\UGCelTyp.obj" : $(SOURCE) $(DEP_CPP_UGCELT) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\UGCnrBtn.cpp
DEP_CPP_UGCNR=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\UGCnrBtn.obj" : $(SOURCE) $(DEP_CPP_UGCNR) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\UGCTarrw.cpp
DEP_CPP_UGCTA=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\UGCTarrw.obj" : $(SOURCE) $(DEP_CPP_UGCTA) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\UGCtrl.cpp
DEP_CPP_UGCTR=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\UGCtrl.obj" : $(SOURCE) $(DEP_CPP_UGCTR) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Ugdao.cpp
DEP_CPP_UGDAO=\
	".\StdAfx.h"\
	".\UGDAO.h"\
	
NODEP_CPP_UGDAO=\
	".\ugctrl.h"\
	

"$(INTDIR)\UGDAO.obj" : $(SOURCE) $(DEP_CPP_UGDAO) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"


SOURCE=..\code\UGDLType.cpp
DEP_CPP_UGDLT=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\UGDLType.obj" : $(SOURCE) $(DEP_CPP_UGDLT) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\UGDrgDrp.cpp
DEP_CPP_UGDRG=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\UGDrgDrp.obj" : $(SOURCE) $(DEP_CPP_UGDRG) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\UGDrwHnt.cpp
DEP_CPP_UGDRW=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\UGDrwHnt.obj" : $(SOURCE) $(DEP_CPP_UGDRW) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\UGDtaSrc.cpp
DEP_CPP_UGDTA=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\UGDtaSrc.obj" : $(SOURCE) $(DEP_CPP_UGDTA) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\UGEdit.cpp
DEP_CPP_UGEDI=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\UGEdit.obj" : $(SOURCE) $(DEP_CPP_UGEDI) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\ugexcel.cpp
DEP_CPP_UGEXC=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugexcel.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\ugexcel.obj" : $(SOURCE) $(DEP_CPP_UGEXC) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\ugformat.cpp
DEP_CPP_UGFOR=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\ugformat.obj" : $(SOURCE) $(DEP_CPP_UGFOR) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\uggdinfo.cpp
DEP_CPP_UGGDI=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\uggdinfo.obj" : $(SOURCE) $(DEP_CPP_UGGDI) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\UGGrid.cpp
DEP_CPP_UGGRI=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\UGGrid.obj" : $(SOURCE) $(DEP_CPP_UGGRI) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\ughscrol.cpp
DEP_CPP_UGHSC=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\ughscrol.obj" : $(SOURCE) $(DEP_CPP_UGHSC) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\ugLstBox.cpp
DEP_CPP_UGLST=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\ugLstBox.obj" : $(SOURCE) $(DEP_CPP_UGLST) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\UGMemMan.cpp
DEP_CPP_UGMEM=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\UGMemMan.obj" : $(SOURCE) $(DEP_CPP_UGMEM) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\UGMultiS.cpp
DEP_CPP_UGMUL=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\UGMultiS.obj" : $(SOURCE) $(DEP_CPP_UGMUL) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\ugprint.cpp
DEP_CPP_UGPRI=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\ugprint.obj" : $(SOURCE) $(DEP_CPP_UGPRI) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\ugptrlst.cpp
DEP_CPP_UGPTR=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\ugptrlst.obj" : $(SOURCE) $(DEP_CPP_UGPTR) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\ugsidehd.cpp
DEP_CPP_UGSID=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\ugsidehd.obj" : $(SOURCE) $(DEP_CPP_UGSID) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\ugtab.cpp
DEP_CPP_UGTAB=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\UGTab.obj" : $(SOURCE) $(DEP_CPP_UGTAB) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\UGTopHdg.cpp
DEP_CPP_UGTOP=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\UGTopHdg.obj" : $(SOURCE) $(DEP_CPP_UGTOP) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\code\ugvscrol.cpp
DEP_CPP_UGVSC=\
	"..\code\stdafx.h"\
	"..\code\UGCBType.h"\
	"..\code\UGCell.h"\
	"..\code\UGCelTyp.h"\
	"..\code\UGCnrBtn.h"\
	"..\code\UGCTarrw.h"\
	"..\code\UGCtrl.h"\
	"..\code\ugdefine.h"\
	"..\code\UGDLType.h"\
	"..\code\UGDrgDrp.h"\
	"..\code\UGDrwHnt.h"\
	"..\code\UGDtaSrc.h"\
	"..\code\UGEdit.h"\
	"..\code\ugformat.h"\
	"..\code\uggdinfo.h"\
	"..\code\UGGrid.h"\
	"..\code\ughscrol.h"\
	"..\code\uglstbox.h"\
	"..\code\UGMemMan.h"\
	"..\code\UGMultiS.h"\
	"..\code\ugprint.h"\
	"..\code\ugptrlst.h"\
	"..\code\ugsidehd.h"\
	"..\code\ugstruct.h"\
	"..\code\ugtab.h"\
	"..\code\UGTopHdg.h"\
	"..\code\ugvscrol.h"\
	

"$(INTDIR)\ugvscrol.obj" : $(SOURCE) $(DEP_CPP_UGVSC) "$(INTDIR)"\
 "$(INTDIR)\dao2.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

