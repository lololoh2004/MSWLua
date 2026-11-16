#include "mswlua/c_api/run_str_script.hpp"

extern "C"{
#include <lua.h>
}


strScript& strScript::push(bool val){
    if (m_isValid == false) return *this;

    lua_pushboolean(m_L, val);
    m_nargs++;
    return *this;
}

strScript& strScript::push(int val){
    if (m_isValid == false) return *this;

    lua_pushinteger(m_L, val);
    m_nargs++;
    return *this;
}

strScript& strScript::push(float val){
    if (m_isValid == false) return *this;

    lua_pushnumber(m_L, val);
    m_nargs++;
    return *this;
}

strScript& strScript::push(double val){
    if (m_isValid == false) return *this;

    lua_pushnumber(m_L, val);
    m_nargs++;
    return *this;
}

strScript& strScript::push(std::string_view val){
    if (m_isValid == false) return *this;

    lua_pushlstring(m_L, val.data(), val.size());
    m_nargs++;
    return *this;
}