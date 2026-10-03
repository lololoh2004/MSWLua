#pragma once

#include <string_view>


struct lua_State;

void findByPath(lua_State* state, std::string_view tablePath);