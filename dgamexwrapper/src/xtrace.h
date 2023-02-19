/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * xtrace.h by Hector J. Rivas, torjo2k@hotmail.com from "ExtendedTrace"
 * by Zoltan Csizmadia, zoltan_csizmadia@yahoo.com
 * 
 * A Win32 VC++ 6.0 implementation of the __FUNCTION__ macro that works for me.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _XTRACE_H_
#define _XTRACE_H_

#pragma warning(disable : 4117)

#if defined(_DEBUG) && defined(WIN32)

#include <windows.h>
#include <tchar.h>

#pragma comment(lib, "imagehlp.lib")
#pragma warning(disable : 4172 4117 4996)			// returning address of a temp

#define BUFFERSIZE 512

//BOOL	InitSymInfo(PCSTR lpszInitialSymbolPath = NULL, BOOL bSysPath = FALSE);
BOOL	InitSymInfo(PCSTR lpszInitialSymbolPath, BOOL bSysPath);
void	InitSymPath(PSTR lpszSymbolPath, PCSTR lpszIniPath, BOOL bSysPath);
BOOL	GetFuncInfo(ULONG fnAddress, ULONG stackAddress, LPTSTR lpszSymbol);
LPCTSTR GetFuncName();
BOOL	KillSymInfo();

#define __FUNCTION__ GetFuncName()

#else
/*
#ifndef InitSymInfo
BOOL InitSymInfo(PCSTR pcstr) {};
#endif

#ifndef KillSymInfo
BOOL KillSymInfo() {};
#endif
*/
#define __FUNCTION__ ("")

#endif

#endif