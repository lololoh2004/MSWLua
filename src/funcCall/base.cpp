#include "mswlua/funcCall/funcCall.hpp"
#include <lo_utils/cxx_wrap/term.hpp>

extern "C"{
#include "lua.h"
#include "lauxlib.h"
}

#include <string>
#include <string_view>


void funcCall::findByPath(std::string_view tablePath){
    // Small QoL addition
    if (tablePath.back() == '.')
        tablePath.remove_suffix(1);

    // Variables
    size_t startPos = 0;
    size_t endPos = tablePath.find('.');

    std::string token;
    token = tablePath.substr(startPos, endPos - startPos);

    // First iteration ( via lua_getglobal )
    lua_getglobal(m_state, token.c_str());

    // Another iterations ( via lua_getfield )
    while (endPos != std::string_view::npos){
        startPos = endPos + 1;
        endPos = tablePath.find('.', startPos);

        token = tablePath.substr(startPos, endPos - startPos);
        lua_getfield(m_state, -1, token.c_str());
        lua_remove(m_state, -2);
    }
}

void funcCall::findAndRefFunc(){
    findByPath(m_tablePath);

    if (lua_isnil(m_state, -1)){
        term::msg("Path is invalid", "MSWLUA");
        lua_pop(m_state, 1);
        return;
    }
    m_funcIdx = luaL_ref(m_state, LUA_REGISTRYINDEX);
}
funcCall::funcCall(lua_State* state, const char* tablePath){
    m_state = state;
    m_tablePath = tablePath;

    findAndRefFunc();
}
funcCall::~funcCall(){
    if (m_funcIdx != -1) {
        luaL_unref(m_state, LUA_REGISTRYINDEX, m_funcIdx);
    }
}

void funcCall::reload(){
    if (m_funcIdx != -1) {
        luaL_unref(m_state, LUA_REGISTRYINDEX, m_funcIdx);
    }
    findAndRefFunc();
}
