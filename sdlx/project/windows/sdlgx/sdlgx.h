// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SDLGX_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SDLGX_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SDLGX_EXPORTS
#define SDLGX_API __declspec(dllexport)
#else
#define SDLGX_API __declspec(dllimport)
#endif

// This class is exported from the sdlgx.dll
class SDLGX_API Csdlgx {
public:
	Csdlgx(void);
	// TODO: add your methods here.
};

extern SDLGX_API int nsdlgx;

SDLGX_API int fnsdlgx(void);
