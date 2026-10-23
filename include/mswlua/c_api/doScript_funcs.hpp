#pragma once

#include <string_view>


struct lua_State;

bool doScriptPath(lua_State* L, std::string_view content);
bool doScriptStr(lua_State* L, std::string_view content);
[[nodiscard]] bool doScript(lua_State* L);