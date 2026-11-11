#pragma once

#include <string_view>


struct lua_State;

void runStr(lua_State* L, std::string_view codeStr);
