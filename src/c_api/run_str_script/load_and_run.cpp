#include "mswlua/c_api/run_str_script.hpp"

extern "C"{
#include <lauxlib.h>
#include <lua.h>
}
#include "mswlua/log_hook.hpp"


strScript::strScript(lua_State* L, std::string_view script, const char* chunkName, const char* mode){
    if (L == nullptr) return;
    m_L = L;
    m_oldTop = lua_gettop(L);

    int loadBufCode = luaL_loadbufferx(L, script.data(), script.size(), chunkName, mode);
    if (loadBufCode != LUA_OK){
        const char* top = lua_tostring(L, -1);
        MSWLuaLog("LUA", "Lua error during code loading (str) : %s", top ? top : "NON_STR_ERR_OBJ");
        clear();
        return;
    }
    m_isValid = true;
}
void strScript::clear(){
    if (m_L == nullptr) return;

    lua_settop(m_L, m_oldTop);
    m_isValid = false;
    m_nargs = 0;
}

strScript& strScript::runScript(){
    if (m_isValid == false || m_hasRun) return *this;
    m_hasRun = true;

    if (lua_pcall(m_L, m_nargs, LUA_MULTRET, 0) != LUA_OK){
        const char* top = lua_tostring(m_L, -1);
        MSWLuaLog("LUA", "Lua error during code running (str) : %s", top ? top : "NON_STR_ERR_OBJ");
        clear();
        return *this;
    }

    m_nargs = 0;
    return *this;
}
