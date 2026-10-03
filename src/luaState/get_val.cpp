#include "mswlua/luaState/state.hpp"
extern "C"{
#include "lua.h"
}
#include "mswlua/common/find_by_path.h"
#include <string>


void luaState::getVal(int& outputVar, const char* tablePath) const{
    findByPath(m_state, tablePath);
    if (lua_isnumber(m_state, -1)){
        outputVar = static_cast<int>(lua_tointeger(m_state, -1));
    }
    lua_pop(m_state, 1);
}
void luaState::getVal(float& outputVar, const char* tablePath) const{
    findByPath(m_state, tablePath);
    if (lua_isnumber(m_state, -1)){
        outputVar = static_cast<float>(lua_tonumber(m_state, -1));
    }
    lua_pop(m_state, 1);
}
void luaState::getVal(bool& outputVar, const char* tablePath) const{
    findByPath(m_state, tablePath);
    if (lua_isboolean(m_state, -1)){
        outputVar = (lua_toboolean(m_state, -1) == 1);
    }
    lua_pop(m_state, 1);
}
void luaState::getVal(std::string& outputVar, const char* tablePath) const{
    findByPath(m_state, tablePath);
    if (lua_isstring(m_state, -1)){
        outputVar = lua_tostring(m_state, -1);
    }
    lua_pop(m_state, 1);
}
