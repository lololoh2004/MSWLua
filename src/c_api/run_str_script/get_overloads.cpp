#include "mswlua/c_api/run_str_script.hpp"

extern "C"{
#include <lua.h>
}
#include <string>
#include "mswlua/log_hook.hpp"


static void internal_incorrectValLog(lua_State* L, int idx){
    MSWLuaLog("MSWLUA", "BUG DETECTED - cant get correct VALUE at idx %d (got %s); skipping",
        idx, lua_typename(L, lua_type(L, idx))
    );
}


strScript& strScript::getNum(int& var){
    if (m_success == false) return *this;

    int idx = m_oldTop + m_readOffset;
    if (lua_isnumber(m_L, idx)) var = static_cast<int>(lua_tointeger(m_L, idx));
    else                        internal_incorrectValLog(m_L, idx);

    m_readOffset++;
    return *this;
}
strScript& strScript::getNum(float& var){
    if (m_success == false) return *this;

    int idx = m_oldTop + m_readOffset;
    if (lua_isnumber(m_L, idx)) var = static_cast<float>(lua_tonumber(m_L, idx));
    else                        internal_incorrectValLog(m_L, idx);

    m_readOffset++;
    return *this;
}
strScript& strScript::getNum(double& var){
    if (m_success == false) return *this;

    int idx = m_oldTop + m_readOffset;
    if (lua_isnumber(m_L, idx)) var = lua_tonumber(m_L, idx);
    else                        internal_incorrectValLog(m_L, idx);

    m_readOffset++;
    return *this;
}

strScript& strScript::getStr(std::string& var){
    if (m_success == false) return *this;

    int idx = m_oldTop + m_readOffset;
    if (lua_isstring(m_L, idx)){
        size_t size = 0;
        const char* result = lua_tolstring(m_L, idx, &size);
        var.assign(result, size);
    } else {
        internal_incorrectValLog(m_L, idx);
    }

    m_readOffset++;
    return *this;
}