extern "C"{
#include "lua.h"
#include "lauxlib.h"
}

lua_State* getLuaState(){
    return luaL_newstate();
}

void closeLuaState(lua_State* L){
    if (L) lua_close(L);
}