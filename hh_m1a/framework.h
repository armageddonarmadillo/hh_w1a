// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define GROUND 800
#define GRAVITY 2
#define PSPEED 10
#define ESPEED (PSPEED / 2)
#define gscale 1
#define gcellw 32 * gscale
#define gcellh 32 * gscale
#define gsw 700
#define gsh 550
extern int mpos, plx, php; //map position, player x position
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <atlstr.h>
#include <atlimage.h>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#define list std::list
#define string std::string
#define add push_back

#define lineout( s ) {						\
	std::wostringstream os;					\
	os << s << "\n";						\
	OutputDebugStringW(os.str().c_str());   \
}