#include "mswlua/c_api/report_funcs.hpp"

extern "C"{
#include "lua.h"
#include "lauxlib.h"
}

#include <string>
#include <string_view>


bool doScript(lua_State* L){
    int callStatus = lua_pcall(L, 0, LUA_MULTRET, 0);
    if (callStatus != LUA_OK){
        reportErr(L); return false;
    }
    return true;
}
bool doScriptPath(lua_State* L, std::string_view content){
    std::string content_str(content);

    int loadStatus = luaL_loadfile(L, content_str.c_str());
    if (loadStatus != LUA_OK) {
        reportErr(L); return false;
    }
    return doScript(L);
}
bool doScriptStr(lua_State* L, std::string_view content){
    std::string content_str(content);

    int loadStatus = luaL_loadstring(L, content_str.c_str());
    if (loadStatus != LUA_OK) {
        reportErr(L); return false;
    }
    return doScript(L);
}