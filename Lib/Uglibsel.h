
/*****************************************************

Selective library loader for Ultimate Grid Entry level
Edition.  This file will select the appropriate library
based on the compiler settings entered by the developer.

The library will then be added as a "standard library",
and need not be listed specifically in the project.


Library naming convention:

 Debug/Release (d/r)	
  |     DLL/Static (d/s)*
   \   /     
ugxxxx .lib
     |  \         
     |    \______
 Ole / non-ole (o/n)	     Multi-thread(m)
							 Unicode (u)
eg.

  ugdndm.lib      debug, non-OLE, dll, multithreaded 

  ugrosm.lib      release,OLE, static, multithread

*DLL indicates linking to MFC with shared DLL
******************************************************/





#ifndef _WIN32
	#error This library can only be used for 32 bit Intel development, the professional edition is required for development in other platforms.
#endif

// check for Windows CE use and state non-compliance.

#ifdef _WIN32_WCE
	#error This library cannot be used for CE development.  Call Dundas Software for information on Ultimate pocketGrid for CE development.
#endif

#ifndef _UNICODE
	#ifdef __AFXOLE_H__

		#ifdef _MT
			#ifdef _AFXDLL
				#ifdef _DEBUG
					#pragma comment( lib, "ugdodm.lib")
				#else
					#pragma comment( lib, "ugrodm.lib")
				#endif
			#endif
			#ifndef _AFXDLL
				#ifdef _DEBUG
					#pragma comment( lib, "ugdosm.lib")
				#else
					#pragma comment( lib, "ugrosm.lib")
				#endif
			#endif
		#endif

		#ifndef _MT
			#error ug single-thread libraries unavailable
		#endif
	#endif


	#ifndef __AFXOLE_H__

		#ifdef _MT
			#ifdef _AFXDLL
				#ifdef _DEBUG
					#pragma comment( lib, "ugdndm.lib")
				#else
					#pragma comment( lib, "ugrndm.lib")
				#endif
			#endif
			#ifndef _AFXDLL
				#ifdef _DEBUG
					#pragma comment( lib, "ugdnsm.lib")
				#else
					#pragma comment( lib, "ugrnsm.lib")
				#endif
			#endif
		#endif

		#ifndef _MT
			#error ug single-thread libraries unavailable
		#endif
	#endif
#endif		// non-unicode


///////////////////////////////
#ifdef _UNICODE
	#ifdef __AFXOLE_H__

		#ifdef _MT
			#ifdef _AFXDLL
				#ifdef _DEBUG
					#pragma comment( lib, "ugdodu.lib")
				#else
					#pragma comment( lib, "ugrodu.lib")
				#endif
			#endif
			#ifndef _AFXDLL
				#ifdef _DEBUG
					#pragma comment( lib, "ugdosu.lib")
				#else
					#pragma comment( lib, "ugrosu.lib")
				#endif
			#endif
		#endif

		#ifndef _MT
			#error ug single-thread libraries unavailable
		#endif
	#endif


	#ifndef __AFXOLE_H__

		#ifdef _MT
			#ifdef _AFXDLL
				#ifdef _DEBUG
					#pragma comment( lib, "ugdndu.lib")
				#else
					#pragma comment( lib, "ugrndu.lib")
				#endif
			#endif
			#ifndef _AFXDLL
				#ifdef _DEBUG
					#pragma comment( lib, "ugdnsu.lib")
				#else
					#pragma comment( lib, "ugrnsu.lib")
				#endif
			#endif
		#endif

		#ifndef _MT
			#error ug single-thread libraries unavailable
		#endif
	#endif
#endif		// unicode

