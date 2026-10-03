#include "mswlua/funcCall/funcCall.hpp"
#include <lo_utils/cxx_wrap/term.hpp>

extern "C"{
#include "lua.h"
#include "lauxlib.h"
}
#include "mswlua/common/find_by_path.h"


void funcCall::findAndRefFunc(){
    findByPath(m_state, m_tablePath);

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
