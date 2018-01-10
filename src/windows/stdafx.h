// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

// TODO: reference additional headers your program requires here
#ifdef _WIN32
#define _WIN32_DCOM
#using <OpenHardwareMonitorLib.dll>
//#include <boost/test/test_tools.hpp>
#include <comdef.h>
#include <wbemidl.h>
#include <tchar.h>
#pragma comment(lib, "wbemuuid.lib")
#endif
#include <stdexcept>