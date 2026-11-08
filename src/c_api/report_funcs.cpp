#include "mswlua/c_api/report_funcs.hpp"

#include "mswlua/log_hook.hpp"

extern "C"{
#include "lua.h"
}


void reportErr(lua_State* L){
    MSWLuaLog(lua_tostring(L, -1), "LUALIB");
    lua_pop(L, 1);
}