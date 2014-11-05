@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by CONTEXTSENSITIVEGRID.HPJ. >"hlp\ContextSensitiveGrid.hm"
echo. >>"hlp\ContextSensitiveGrid.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\ContextSensitiveGrid.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\ContextSensitiveGrid.hm"
echo. >>"hlp\ContextSensitiveGrid.hm"
echo // Prompts (IDP_*) >>"hlp\ContextSensitiveGrid.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\ContextSensitiveGrid.hm"
echo. >>"hlp\ContextSensitiveGrid.hm"
echo // Resources (IDR_*) >>"hlp\ContextSensitiveGrid.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\ContextSensitiveGrid.hm"
echo. >>"hlp\ContextSensitiveGrid.hm"
echo // Dialogs (IDD_*) >>"hlp\ContextSensitiveGrid.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\ContextSensitiveGrid.hm"
echo. >>"hlp\ContextSensitiveGrid.hm"
echo // Frame Controls (IDW_*) >>"hlp\ContextSensitiveGrid.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\ContextSensitiveGrid.hm"
REM -- Make help for Project CONTEXTSENSITIVEGRID


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\ContextSensitiveGrid.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\ContextSensitiveGrid.hlp" goto :Error
if not exist "hlp\ContextSensitiveGrid.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\ContextSensitiveGrid.hlp" Debug
if exist Debug\nul copy "hlp\ContextSensitiveGrid.cnt" Debug
if exist Release\nul copy "hlp\ContextSensitiveGrid.hlp" Release
if exist Release\nul copy "hlp\ContextSensitiveGrid.cnt" Release
echo.
goto :done

:Error
echo hlp\ContextSensitiveGrid.hpj(1) : error: Problem encountered creating help file

:done
echo.
