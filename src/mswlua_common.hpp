#pragma once

#ifdef MSWLUA_SHARED
    #ifdef _WIN32
        #define MSWLUA_API __declspec(dllexport)
    #else
        #define MSWLUA_API __attribute__((visibility("default")))
    #endif
#else
    #define MSWLUA_API
#endif
