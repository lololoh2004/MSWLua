#include "mswlua/c_api/func_call.hpp"

extern "C"{
#include "lua.h"
}

void funcCall::_beforePush(){
    if (m_nargs > 0) return;
    clearStack();
    m_oldTop = lua_gettop(m_L);
    lua_rawgeti(m_L, LUA_REGISTRYINDEX, m_funcRef);
}


funcCall& funcCall::push(bool val){
    if (m_isValid == false) return *this;
    _beforePush();

    lua_pushboolean(m_L, val);
    m_nargs++;

    return *this;
}
funcCall& funcCall::push(int val){
    if (m_isValid == false) return *this;
    _beforePush();

    lua_pushinteger(m_L, val);
    m_nargs++;

    return *this;
}
funcCall& funcCall::push(float val){
    if (m_isValid == false) return *this;
    _beforePush();

    lua_pushnumber(m_L, val);
    m_nargs++;

    return *this;
}
funcCall& funcCall::push(double val){
    if (m_isValid == false) return *this;
    _beforePush();

    lua_pushnumber(m_L, val);
    m_nargs++;

    return *this;
}
funcCall& funcCall::push(std::string_view val){
    if (m_isValid == false) return *this;
    _beforePush();

    lua_pushlstring(m_L, val.data(), val.size());
    m_nargs++;

    return *this;
}

