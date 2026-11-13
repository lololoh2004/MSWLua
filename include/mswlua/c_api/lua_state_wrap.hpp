#pragma once


struct lua_State;

lua_State* getLuaState();
void closeLuaState(lua_State* L);