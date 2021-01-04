// sdlgx.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "sdlgx.h"


// This is an example of an exported variable
SDLGX_API int nsdlgx=0;

// This is an example of an exported function.
SDLGX_API int fnsdlgx(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see sdlgx.h for the class definition
Csdlgx::Csdlgx()
{
    return;
}
