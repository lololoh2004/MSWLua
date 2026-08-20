#include "_include/state_class.hpp"

#include "lauxlib.h"
#include "lualib.h"

luaState::luaState(){
    m_state = luaL_newstate();
    luaL_openlibs(m_state);
}

// luaState::luaState(lua_State* L){
//     m_state = L;
// }

luaState::~luaState(){
    if (m_state) lua_close(m_state);
}
