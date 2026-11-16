#include "mswlua/c_api/func_call.hpp"

extern "C"{
#include "lua.h"
}

#include "mswlua/log_hook.hpp"


funcCall& funcCall::runFunc(){
    if (m_isValid == false) return *this;
    if (m_nargs == 0) _beforePush();

    int status = lua_pcall(m_L, m_nargs, LUA_MULTRET, 0);
    m_nargs = 0;

    if (status != LUA_OK){
        const char* top = lua_tostring(m_L, -1);
        MSWLuaLog(""
            "LUA", "Error in lua runtime (lua func. call) : %s",
            top ? top : "NON_STR_ERR_OBJ"
        );
        clearStack();
    }

    return *this;
}