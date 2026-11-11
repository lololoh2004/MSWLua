#pragma once

#include <string_view>


struct lua_State;

struct pCallArgs{
    int nargs    = 0;
    int nresults = 0;
    int errfunc  = 0;
};

bool runStr(lua_State* L, std::string_view codeStr);

