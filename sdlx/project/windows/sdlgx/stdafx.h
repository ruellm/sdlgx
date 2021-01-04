// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifdef WIN32
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#ifdef SDLGX_EXPORTS
#define SDLGX_API __declspec(dllexport)
#else
#define SDLGX_API __declspec(dllimport)
#endif

#endif

// TODO: reference additional headers your program requires here
