#include "mswlua/c_api/path_funcs.hpp"

extern "C"{
#include "lua.h"
}

#include <string>


void pushByPath(lua_State* L, std::string_view tablePath){
    // If one of the args. is null
    if (L == nullptr)      return;
    if (tablePath.empty()) { lua_pushnil(L); return; }

    if (tablePath.back() == '.') tablePath.remove_suffix(1);
    if (tablePath.empty())       { lua_pushnil(L); return; }

    size_t curDotPos = tablePath.find('.');
    std::string_view curToken = tablePath.substr(0, curDotPos);

    // First iteration
    lua_pushlstring(L, curToken.data(), curToken.size());
    lua_gettable(L, LUA_GLOBALSINDEX);

    if (lua_istable(L, -1) == false){
        if (curDotPos != std::string_view::npos){
            lua_pop(L, 1);
            lua_pushnil(L);
        }
        return;
    }

    // Other iterations
    while (curDotPos != std::string_view::npos){
        tablePath.remove_prefix(curDotPos + 1);

        curDotPos = tablePath.find('.');
        curToken  = tablePath.substr(0, curDotPos);

        lua_pushlstring(L, curToken.data(), curToken.size());
        lua_gettable(L, -2);
        lua_remove(L, -2);

        if (lua_istable(L, -1) == false){
            if (curDotPos != std::string_view::npos){
                lua_pop(L, 1);
                lua_pushnil(L);
            }
            return;
        }
    }
}


bool tryPushByPath(lua_State* L, std::string_view tablePath){
    if (L == nullptr) return false;
    pushByPath(L, tablePath);
    if (lua_isnil(L, -1)){
        lua_pop(L, 1);
        return false;
    }
    return true;
}

bool pushByPathAndCheck(lua_State* L, std::string_view tablePath, int luaT){
    if (L == nullptr) return false;
    pushByPath(L, tablePath);
    if (lua_type(L, -1) != luaT) {
        lua_pop(L, 1);
        return false;
    }
    return true;
}