#include "mswlua/c_api/run_funcs.hpp"

extern "C"{
#include <lauxlib.h>
#include <lua.h>
}

#include "mswlua/log_hook.hpp"


static int internal_loadBuf(
    lua_State* L,
    std::string_view codeStr,
    const char* chunkName="mswlua_run_fn",
    const char* mode=nullptr
) {
    return luaL_loadbufferx(L, codeStr.data(), codeStr.size(), chunkName, mode);
}

static bool internal_runStr(lua_State* L, std::string_view codeStr, pCallArgs args = {}){
    if (internal_loadBuf(L, codeStr) != LUA_OK){
        const char* top = lua_tostring(L, -1);
        MSWLuaLog("LUA", "Lua error during code loading (str) : %s", top ? top : "NON_STR_ERR_OBJ");
        return false;
    }
    if (lua_pcall(L, 0, 0, 0) != LUA_OK){
        MSWLuaLog("LUA", "Lua error during code execution (str) : %s", lua_tostring(L, -1));
        return false;
    }
    return true;
}

bool runStr(lua_State* L, std::string_view codeStr){
    return internal_runStr(L, codeStr, { 0, 0, 0 });
}
bool evalStr(lua_State* L, std::string_view codeStr){
    if (internal_loadBuf(L, codeStr) != LUA_OK){
        // TOMOROW ME : HERE HERE HERE HERE HERE HERE HERE
        // HERE  HERE HERE HERE HERE HERE HERE HERE HERE
    }
}