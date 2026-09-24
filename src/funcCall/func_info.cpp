#include "mswlua/funcCall/funcCall.hpp"

extern "C"{
#include "lua.h"
}

// === LEGACY ===
// void funcCall::clearArgs(){
//     if (m_argCount == 0) return;
//     lua_pop(m_state, m_argCount);
//     m_argCount = 0;
// }

funcCall& funcCall::arg(int num){
    lua_pushnumber(m_state, num);
    m_argCount++;

    return *this;
}