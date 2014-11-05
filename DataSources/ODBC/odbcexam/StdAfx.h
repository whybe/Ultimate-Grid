// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D8C150CB_22E8_11D1_B210_002035964AAA__INCLUDED_)
#define AFX_STDAFX_H__D8C150CB_22E8_11D1_B210_002035964AAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#ifndef WINVER 
#define WINVER 0x0400
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

// need to include these here for VC6 unicode builds!
#include "sqltypes.h"
#include "sqlucode.h"

#include <afxole.h>
#include <afxdb.h>

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D8C150CB_22E8_11D1_B210_002035964AAA__INCLUDED_)
