#include "mswlua/log_hook.hpp"
#include "../../include/mswlua/c_api/func_call.hpp"

extern "C"{
#include "lua.h"
}

func_call& func_call::arg(int num){
    lua_pushnumber(m_state, num);
    m_argCount++;

    return *this;
}

void func_call::exec(void* resultVar){
    lua_rawgeti(m_state, LUA_REGISTRYINDEX, m_funcIdx);

    int funcCorrectPos = lua_gettop(m_state) - m_argCount;
    lua_insert(m_state, funcCorrectPos);

    int tempArgCount = m_argCount;
    m_argCount = 0;

    int result = lua_pcall(m_state, tempArgCount, LUA_MULTRET, 0);
    if (result != LUA_OK){
        MSWLuaLog(lua_tostring(m_state, -1), "LUA");
        return;
    }
}
