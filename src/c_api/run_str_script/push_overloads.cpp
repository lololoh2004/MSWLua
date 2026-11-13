#include "mswlua/c_api/run_str_script.hpp"

extern "C"{
#include <lua.h>
}


strScript& strScript::pushNum(int val){
    if (m_success == false) return *this;

    lua_pushinteger(m_L, val);
    m_pcallArgs.nargs++;
    return *this;
}
strScript& strScript::pushNum(float val){
    if (m_success == false) return *this;

    lua_pushnumber(m_L, val);
    m_pcallArgs.nargs++;
    return *this;
}
strScript& strScript::pushNum(double val){
    if (m_success == false) return *this;

    lua_pushnumber(m_L, val);
    m_pcallArgs.nargs++;
    return *this;
}
strScript& strScript::pushStr(std::string_view val){
    if (m_success == false) return *this;

    lua_pushlstring(m_L, val.data(), val.size());
    m_pcallArgs.nargs++;
    return *this;
}