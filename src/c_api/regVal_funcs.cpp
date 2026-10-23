#include "mswlua/c_api/path_funcs.hpp"
extern "C"{
#include "lua.h"
}

static void regVal_SharedStart(lua_State* state, std::string_view tablePath){
    // Small QoL addition
    if (tablePath.back() == '.')
        tablePath.remove_suffix(1);

    // Find <path> and <variable name> parts

    // Find dot char. separating the <path> and <variable name>
    // Example - "api.debug.num_var"
    size_t lastDotPos = tablePath.find_last_of('.');

    // Find <path> part
    // FROM example - "api.debug"
    std::string_view pathToVar = (lastDotPos == std::string_view::npos)
        ? std::string_view{}
        : tablePath.substr(0, lastDotPos);

    // Find <variable name> part
    // FROM example - "num_var"
    std::string_view varName = (lastDotPos == std::string_view::npos)
        ? tablePath
        : tablePath.substr(lastDotPos + 1);

    // Check if a path exists or ONLY <variable name>
    if (pathToVar.empty()){
        lua_pushvalue(state, LUA_GLOBALSINDEX);
    } else {
        createPath(state, pathToVar);
    }

    lua_pushlstring(state, varName.data(), varName.size());
}

static void regVal_SharedEnd(lua_State* L){
    // Creating a table
    lua_settable(L, -3);
    lua_pop(L, 1);
}

void regVal(lua_State* L, int num, std::string_view tablePath){
    // Call to the regVal_Shared function
    regVal_SharedStart(L, tablePath);

    // Pushing an <int> onto the Lua stack
    // ( THIS IS THE ONLY WAY function overloads differ )
    lua_pushinteger(L, num);

    // Creating a table
    regVal_SharedEnd(L);
}
void regVal(lua_State* L, float fl, std::string_view tablePath){
    regVal_SharedStart(L, tablePath);

    lua_pushnumber(L, fl);

    regVal_SharedEnd(L);
}
void regVal(lua_State* L, double db, std::string_view tablePath){
    regVal_SharedStart(L, tablePath);

    lua_pushnumber(L, db);

    regVal_SharedEnd(L);
}
void regVal(lua_State* L, const char* str, std::string_view tablePath){
    regVal_SharedStart(L, tablePath);

    lua_pushstring(L, str);

    regVal_SharedEnd(L);
}
void regVal(lua_State* L, std::string_view str, std::string_view tablePath){
    regVal_SharedStart(L, tablePath);

    lua_pushlstring(L, str.data(), str.size());

    regVal_SharedEnd(L);
}
void regVal(lua_State* L, bool bl, std::string_view tablePath) {
    regVal_SharedStart(L, tablePath);

    lua_pushboolean(L, bl);

    regVal_SharedEnd(L);
}
