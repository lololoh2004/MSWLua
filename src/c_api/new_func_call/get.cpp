#include "mswlua/c_api/func_call.hpp"

extern "C"{
#include "lua.h"
}
#include <string>
#include "mswlua/common/incorrect_val_log.hpp"


funcCall& funcCall::get(bool& val) {
    if (!m_isValid) return *this;

    int idx = m_oldTop + m_readOffset;
    if (idx <= lua_gettop(m_L))
        val = lua_toboolean(m_L, idx);
    else
        incorrectValLog(m_L, idx);

    m_readOffset++;
    return *this;
}

funcCall& funcCall::get(int& val) {
    if (!m_isValid) return *this;

    int idx = m_oldTop + m_readOffset;
    if (idx <= lua_gettop(m_L) && lua_isnumber(m_L, idx))
        val = static_cast<int>(lua_tointeger(m_L, idx));
    else
        incorrectValLog(m_L, idx);

    m_readOffset++;
    return *this;
}

funcCall& funcCall::get(float& val) {
    if (!m_isValid) return *this;

    int idx = m_oldTop + m_readOffset;
    if (idx <= lua_gettop(m_L) && lua_isnumber(m_L, idx))
        val = static_cast<float>(lua_tonumber(m_L, idx));
    else
        incorrectValLog(m_L, idx);

    m_readOffset++;
    return *this;
}

funcCall& funcCall::get(double& val) {
    if (!m_isValid) return *this;

    int idx = m_oldTop + m_readOffset;
    if (idx <= lua_gettop(m_L) && lua_isnumber(m_L, idx))
        val = static_cast<float>(lua_tonumber(m_L, idx));
    else
        incorrectValLog(m_L, idx);

    m_readOffset++;
    return *this;
}

funcCall& funcCall::get(std::string& val) {
    if (!m_isValid) return *this;

    int idx = m_oldTop + m_readOffset;
    if (idx <= lua_gettop(m_L) && lua_type(m_L, idx) == LUA_TSTRING) {
        size_t len = 0;
        const char* str = lua_tolstring(m_L, idx, &len);
        val.assign(str, len);
    } else {
        incorrectValLog(m_L, idx);
    }
    m_readOffset++;
    return *this;
}