#include "mswlua/luaState/state.hpp"
extern "C"{
#include "lua.h"
}
#include <string>


void luaState::getVal(int& var, const char* tablePath) const{
    lua_getglobal(m_state, tablePath);
    if (lua_isnumber(m_state, -1)){
        var = static_cast<int>(lua_tointeger(m_state, -1));
    }
    lua_pop(m_state, 1);
}
void luaState::getVal(float& var, const char* tablePath) const{
    lua_getglobal(m_state, tablePath);
    if (lua_isnumber(m_state, -1)){
        var = static_cast<float>(lua_tonumber(m_state, -1));
    }
    lua_pop(m_state, 1);
}
void luaState::getVal(bool& var, const char* tablePath) const{
    lua_getglobal(m_state, tablePath);
    if (lua_isboolean(m_state, -1)){
        var = (lua_toboolean(m_state, -1) == 1);
    }
    lua_pop(m_state, 1);
}
void luaState::getVal(std::string& var, const char* tablePath) const{
    lua_getglobal(m_state, tablePath);
    if (lua_isstring(m_state, -1)){
        var = lua_tostring(m_state, -1);
    }
    lua_pop(m_state, 1);
}
