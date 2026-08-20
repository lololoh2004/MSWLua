#pragma once

#include "mswlua_common.hpp"

typedef struct lua_State lua_State;

MSWLUA_API void initLuaStates(lua_State** svState, lua_State** clState);