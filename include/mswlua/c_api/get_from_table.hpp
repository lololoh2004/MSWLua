#pragma once

#include <string>
#include <string_view>


struct lua_State;

void getVal(lua_State* L, int& outputVar,   std::string_view tablePath);
void getVal(lua_State* L, float& outputVar, std::string_view tablePath);
void getVal(lua_State* L, bool& outputVar,  std::string_view tablePath);
void getVal(lua_State* L, std::string& outputVar, std::string_view tablePath);