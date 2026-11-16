#include "mswlua/c_api/func_call.hpp"

#include "mswlua/c_api/path_funcs.hpp"
extern "C"{
#include "lua.h"
#include <lauxlib.h>
}


funcCall::funcCall(lua_State* L, std::string_view tablePath){
    if (L == nullptr) return;
    m_L = L;

    if (pushByPathAndCheck(L, tablePath, LUA_TFUNCTION) == false) return;
    m_isValid = true;

    m_funcRef = luaL_ref(L, LUA_REGISTRYINDEX);
    m_oldTop  = lua_gettop(L);
}

void funcCall::clearStack(){
    if (m_isValid == false) return;

    lua_settop(m_L, m_oldTop);
    m_nargs = 0;
}
void funcCall::clearRef(){
    if (m_isValid == false) return;

    clearStack();
    luaL_unref(m_L, LUA_REGISTRYINDEX, m_funcRef);

    m_funcRef = LUA_NOREF;
    m_isValid = false;
}
