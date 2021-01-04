#pragma once

#ifdef WIN32
	#ifdef SDLGX_EXPORTS
		#define SDLGX_API __declspec(dllexport)
	#else
		#define SDLGX_API __declspec(dllimport)
	#endif
#else
	#ifdef SDLGX_EXPORTS
		#define SDLGX_API
	#endif
#endif


// SDL Definitions
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>
#include <vector>

#define SAFE_DELETE( obj ) { if( obj ) { delete obj; obj = NULL; } }
#define SAFE_DELETE_ARRAY( obj ) { if( obj ) { delete[] obj; obj = NULL; } }


#define MAX_PATH_LEN	260