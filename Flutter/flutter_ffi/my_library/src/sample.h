#pragma once

#ifndef DLL_PUBLIC
    #if defined _WIN32 || defined __CYGWIN__
        #define DLL_PUBLIC __declspec(dllexport)
    #else
        #define DLL_PUBLIC __attribute__ ((visibility ("default")))
    #endif
#endif

extern "C" DLL_PUBLIC int favouriteNumber();