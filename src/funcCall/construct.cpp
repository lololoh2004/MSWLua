#include "mswlua/funcCall/funcCall.hpp"
#include <lo_utils/cxx20/parse.hpp>
#include <lo_utils/cxx_wrap/term.hpp>

extern "C"{
#include "lua.h"
#include "lauxlib.h"
}

#include <vector>
#include <string>
#include <string_view>


// bool findByPath(lua_State* state, std::string_view tablePath){
//     auto tokens = splitStrToTokens(tablePath);
//     if (tokens.empty())
//         return false;
//
//     std::string firstToken(tokens[0]);
//     lua_getglobal(state, firstToken.c_str());
//     if (lua_isnil(state, -1)){
//         lua_pop(state, 1);
//         return false;
//     }
//
//
//     for (int i = 1; i < tokens.size(); ++i){
//         std::string token(tokens[i]);
//
//         lua_getfield(state, -1, token.c_str());
//         lua_remove(state, -2);
//
//         if (lua_isnil(state, -1))
//             return false;
//     }
//
//     return true;
// }

// Proto just for easy debug
void funcCall::findProto(std::string_view tablePath){
    // I KNOW ABOUT '/0' ITS JUST PROTO
    lua_getglobal(m_state, tablePath.data());
}

funcCall::funcCall(lua_State* state, const char* tablePath){
    m_state = state;
    m_oldTopIdx = lua_gettop(state);

    findProto(tablePath);

    if (lua_isnil(state, -1)){
        term::msg("Path is invalid", "MSWLUA");
        return;
    }
    m_funcIdx = luaL_ref(m_state, LUA_REGISTRYINDEX);
}
funcCall::~funcCall(){
    luaL_unref(m_state, LUA_REGISTRYINDEX, m_funcIdx);
}