#include "../../include/mswlua/c_api/func_call.hpp"

#include "mswlua/log_hook.hpp"
#include "mswlua/c_api/path_funcs.hpp"

extern "C"{
#include "lua.h"
#include "lauxlib.h"
}


void func_call::findAndRefFunc(){
    findByPath(m_state, m_tablePath);

    if (lua_isnil(m_state, -1)){
        MSWLuaLog("Path is invalid", "MSWLUA");
        lua_pop(m_state, 1);
        return;
    }
    m_funcIdx = luaL_ref(m_state, LUA_REGISTRYINDEX);
}
func_call::func_call(lua_State* state, const char* tablePath){
    m_state = state;
    m_tablePath = tablePath;

    findAndRefFunc();
}
func_call::~func_call(){
    if (m_funcIdx != -1) {
        luaL_unref(m_state, LUA_REGISTRYINDEX, m_funcIdx);
    }
}

void func_call::reload(){
    if (m_funcIdx != -1) {
        luaL_unref(m_state, LUA_REGISTRYINDEX, m_funcIdx);
    }
    findAndRefFunc();
}
