#include "_include/init_lua.hpp"

extern "C"{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "term.h"
}

lua_State* initSingleState(){
    lua_State* L = luaL_newstate();
    if (!L){
        termMsg("Error creating lua state\n", "LUA");
        return NULL;
    }
    luaL_openlibs(L);
    return L;
}
void clearLuaState(lua_State** state){
    if (!state) return;
    if (*state) {
        lua_close(*state);
        *state = NULL;
    }
}
void initLuaStates(lua_State** svState, lua_State** clState){
    if (svState){
        lua_State* initResult = initSingleState();
        if (initResult){
            clearLuaState(svState);
            *svState = initResult;
        } else {
            termMsg("Lua server state was not created; the previous one is being used\n", "LUA");
        }
    }
    if (clState){
        lua_State* initResult = initSingleState();
        if (initResult){
            clearLuaState(clState);
            *clState = initResult;
        } else {
            termMsg("Lua client state was not created; the previous one is being used\n", "LUA");
        }
    }
}