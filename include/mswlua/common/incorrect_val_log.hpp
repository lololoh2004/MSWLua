#pragma once

extern "C"{
#include <lua.h>
}
#include "mswlua/log_hook.hpp"


inline void incorrectValLog(lua_State* L, int idx){
    MSWLuaLog("MSWLUA", "BUG DETECTED - cant get correct VALUE at idx %d (got %s); skipping",
        idx, lua_typename(L, lua_type(L, idx))
    );
}