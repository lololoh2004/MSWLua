extern "C"{
#include "lua.h"
}
#include "mswlua/c_api/path_funcs.hpp"
#include <string>


void getVal(lua_State* L, int& outputVar, const char* tablePath){
    findByPath(L, tablePath);
    if (lua_isnumber(L, -1)){
        outputVar = static_cast<int>(lua_tointeger(L, -1));
    }
    lua_pop(L, 1);
}
void getVal(lua_State* L, float& outputVar, const char* tablePath){
    findByPath(L, tablePath);
    if (lua_isnumber(L, -1)){
        outputVar = static_cast<float>(lua_tonumber(L, -1));
    }
    lua_pop(L, 1);
}
void getVal(lua_State* L, bool& outputVar, const char* tablePath){
    findByPath(L, tablePath);
    if (lua_isboolean(L, -1)){
        outputVar = (lua_toboolean(L, -1) == 1);
    }
    lua_pop(L, 1);
}
void getVal(lua_State* L, std::string& outputVar, const char* tablePath){
    findByPath(L, tablePath);
    if (lua_isstring(L, -1)){
        outputVar = lua_tostring(L, -1);
    }
    lua_pop(L, 1);
}
