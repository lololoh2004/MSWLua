#include <lo_utils/cxx_wrap/term.hpp>
#include "mswlua/funcCall/funcCall.hpp"

extern "C"{
#include "lua.h"
}

funcCall& funcCall::arg(int num){
    lua_pushnumber(m_state, num);
    m_argCount++;

    return *this;
}

void funcCall::exec(void* resultVar){
    lua_rawgeti(m_state, LUA_REGISTRYINDEX, m_funcIdx);

    int funcCorrectPos = lua_gettop(m_state) - m_argCount;
    lua_insert(m_state, funcCorrectPos);

    int tempArgCount = m_argCount;
    m_argCount = 0;

    int result = lua_pcall(m_state, tempArgCount, LUA_MULTRET, 0);
    if (result != LUA_OK){
        term::msg(lua_tostring(m_state, -1), "LUA");
        return;
    }
}
