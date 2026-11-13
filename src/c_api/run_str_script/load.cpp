#include "mswlua/c_api/run_str_script.hpp"

extern "C"{
#include <lauxlib.h>
#include <lua.h>
}
#include "mswlua/log_hook.hpp"


// === INTERNAL FUNCTIONS ===

static bool internal_runStr(lua_State* L, pcallArgs args){
    if (lua_pcall(L, args.nargs, args.nresults, args.errfunc) != LUA_OK){
        const char* top = lua_tostring(L, -1);
        MSWLuaLog("LUA", "Lua error during code running (str) : %s", top ? top : "NON_STR_ERR_OBJ");
        return false;
    }
    return true;
}


// === CLASS METHODS ===

strScript::strScript(lua_State* L, std::string_view script, const char* chunkName, const char* mode){
    m_L = L;
    m_oldTop = lua_gettop(L);

    int loadBufCode = luaL_loadbufferx(L, script.data(), script.size(), chunkName, mode);
    if (loadBufCode != LUA_OK){
        const char* top = lua_tostring(L, -1);
        MSWLuaLog("LUA", "Lua error during code loading (str) : %s", top ? top : "NON_STR_ERR_OBJ");
        m_success = false;
        return;
    }
}
void strScript::clearAll(){
    lua_settop(m_L, m_oldTop);
}

strScript& strScript::runScript(){
    if (m_success == false) return *this;
    m_success = internal_runStr(m_L, m_pcallArgs);

    return *this;
}
