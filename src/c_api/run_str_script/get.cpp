#include "mswlua/c_api/run_str_script.hpp"

extern "C"{
#include <lua.h>
}
#include <string>
#include "mswlua/common/incorrect_val_log.hpp"


strScript& strScript::get(int& var){
    if (m_isValid == false) return *this;

    int idx = m_oldTop + m_readOffset;
    if (lua_isnumber(m_L, idx)) var = static_cast<int>(lua_tointeger(m_L, idx));
    else                        incorrectValLog(m_L, idx);

    m_readOffset++;
    return *this;
}

strScript& strScript::get(float& var){
    if (m_isValid == false) return *this;

    int idx = m_oldTop + m_readOffset;
    if (lua_isnumber(m_L, idx)) var = static_cast<float>(lua_tonumber(m_L, idx));
    else                        incorrectValLog(m_L, idx);

    m_readOffset++;
    return *this;
}

strScript& strScript::get(double& var){
    if (m_isValid == false) return *this;

    int idx = m_oldTop + m_readOffset;
    if (lua_isnumber(m_L, idx)) var = lua_tonumber(m_L, idx);
    else                        incorrectValLog(m_L, idx);

    m_readOffset++;
    return *this;
}

strScript& strScript::get(std::string& var){
    if (m_isValid == false) return *this;

    int idx = m_oldTop + m_readOffset;
    if (lua_isstring(m_L, idx)){
        size_t size = 0;
        const char* result = lua_tolstring(m_L, idx, &size);
        var.assign(result, size);
    } else {
        incorrectValLog(m_L, idx);
    }

    m_readOffset++;
    return *this;
}