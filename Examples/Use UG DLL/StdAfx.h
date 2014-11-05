// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__E1B9B597_76CC_4D01_B0AE_9DFBDA5B663F__INCLUDED_)
#define AFX_STDAFX_H__E1B9B597_76CC_4D01_B0AE_9DFBDA5B663F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxole.h>

#ifdef _DEBUG
	#ifdef _UNICODE
		#pragma message("Automatically linking with UGMFCDU.lib - please make sure this file is built.")
		#pragma comment(lib, "..\\..\\DLLs\\UGMFCDU.lib")
	#else // not unicode	
		#pragma message("Automatically linking with UGMFCD.lib - please make sure this file is built.")
		#pragma comment(lib, "..\\..\\DLLs\\UGMFCD.lib")
	#endif // _UNICODE
#else // RELEASE
	#ifdef _UNICODE
		#pragma message("Automatically linking with UGMFCU.lib - please make sure this file is built.")
		#pragma comment(lib, "..\\..\\DLLs\\UGMFCU.lib")
	#else // not unicode	
		#pragma message("Automatically linking with UGMFC.lib - please make sure this file is built.")
		#pragma comment(lib, "..\\..\\DLLs\\UGMFC.lib")
	#endif // _UNICODE
#endif // _DEBUG


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E1B9B597_76CC_4D01_B0AE_9DFBDA5B663F__INCLUDED_)
