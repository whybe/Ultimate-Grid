// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//



#if !defined(AFX_STDAFX_H__6E6BFE79_5152_11D1_B265_002035964AAA__INCLUDED_)
#define AFX_STDAFX_H__6E6BFE79_5152_11D1_B265_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#ifndef WINVER 
#define WINVER 0x0400
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#include <afxole.h>

#pragma warning (disable : 4995)	// disable DAO deprecation warnings


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__6E6BFE79_5152_11D1_B265_002035964AAA__INCLUDED_)
