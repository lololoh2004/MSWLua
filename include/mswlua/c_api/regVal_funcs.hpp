#pragma once

#include <string_view>


struct lua_State;

void regVal(lua_State* L, int num, std::string_view tablePath);
void regVal(lua_State* L, float fl, std::string_view tablePath);
void regVal(lua_State* L, double db, std::string_view tablePath);
void regVal(lua_State* L, const char* str, std::string_view tablePath);
void regVal(lua_State* L, std::string_view str, std::string_view tablePath);
void regVal(lua_State* L, bool bl, std::string_view tablePath);