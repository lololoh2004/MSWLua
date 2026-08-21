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

#include <variant>
#include <string>

struct lua_State;

namespace mswlua{

using luaDynamibT = std::variant<std::monostate, bool, double, std::string>;

namespace lib{
enum lib : unsigned int {
    base    = 1 << 0,
    math    = 1 << 1,
    string  = 1 << 2,
    table   = 1 << 3,
    ffi     = 1 << 4,
    io      = 1 << 5,
    os      = 1 << 6,
    package = 1 << 7,
    debug   = 1 << 8,

    _all    = 0xFFFFFFFF
};
}

}