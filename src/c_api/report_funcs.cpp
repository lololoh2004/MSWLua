#include "mswlua/c_api/report_funcs.hpp"

extern "C"{
#include "lua.h"
}

#include "lo_utils/cxx_wrap/term.hpp"


void reportErr(lua_State* L){
    term::msg(lua_tostring(L, -1), "LUALIB", COLOR_RED);
    lua_pop(L, 1);
}