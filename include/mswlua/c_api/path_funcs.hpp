#pragma once

#include <string_view>


struct lua_State;

void pushByPath(lua_State* L, std::string_view tablePath);
bool pushByPathAndCheck(lua_State* L, std::string_view tablePath, int luaT);
bool tryPushByPath(lua_State* L, std::string_view tablePath);
[[deprecated("Use pushByPath instead")]]
void findByPath(lua_State* L, std::string_view tablePath);
void createPath(lua_State* L, std::string_view tablePath);