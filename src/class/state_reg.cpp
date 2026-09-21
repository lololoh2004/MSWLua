#include "mswlua/class/state.hpp"
extern "C"{
#include "lua.h"
}

void luaState::regVal(int num, const char* name){
    lua_pushinteger(m_state, num);
    lua_setglobal(m_state, name);
}
void luaState::regVal(float fl, const char* name){
    lua_pushnumber(m_state, fl);
    lua_setglobal(m_state, name);
}
void luaState::regVal(double db, const char* name){
    lua_pushnumber(m_state, db);
    lua_setglobal(m_state, name);
}
void luaState::regVal(const char* str, const char* name){
    lua_pushstring(m_state, str);
    lua_setglobal(m_state, name);
}
void luaState::regVal(bool bl, const char* name){
    lua_pushboolean(m_state, bl);
    lua_setglobal(m_state, name);
}