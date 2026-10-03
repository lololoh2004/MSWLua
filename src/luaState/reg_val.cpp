#include "mswlua/luaState/state.hpp"
extern "C"{
#include "lua.h"
}

void luaState::regVal(int num, const char* tablePath){
    lua_pushinteger(m_state, num);
    lua_setglobal(m_state, tablePath);
}
void luaState::regVal(float fl, const char* tablePath){
    lua_pushnumber(m_state, fl);
    lua_setglobal(m_state, tablePath);
}
void luaState::regVal(double db, const char* tablePath){
    lua_pushnumber(m_state, db);
    lua_setglobal(m_state, tablePath);
}
void luaState::regVal(const char* str, const char* tablePath){
    lua_pushstring(m_state, str);
    lua_setglobal(m_state, tablePath);
}
void luaState::regVal(bool bl, const char* tablePath){
    lua_pushboolean(m_state, bl);
    lua_setglobal(m_state, tablePath);
}