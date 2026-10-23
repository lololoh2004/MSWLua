#pragma once

#include <string_view>


struct lua_State;

void findByPath(lua_State* L, std::string_view tablePath);
void createPath(lua_State* L, std::string_view tablePath);