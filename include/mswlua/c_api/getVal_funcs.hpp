#pragma once

#include <string>


struct lua_State;

void getVal(lua_State* L, int& outputVar, const char* tablePath);
void getVal(lua_State* L, float& outputVar, const char* tablePath);
void getVal(lua_State* L, bool& outputVar, const char* tablePath);
void getVal(lua_State* L, std::string& outputVar, const char* tablePath);