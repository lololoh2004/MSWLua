#include "mswlua/luaState/state.hpp"

extern "C"{
#include "lua.h"
}

#include "lo_utils/cxx_wrap/term.hpp"


void luaState::reportErr() const{
    term::msg(lua_tostring(m_state, -1), "LUALIB", COLOR_RED);
    lua_pop(m_state, 1);
}