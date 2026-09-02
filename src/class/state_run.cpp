#include "mswlua/class/state.hpp"

extern "C"{
#include "lua.h"
#include "lauxlib.h"
}

#include "lo_utils/term.h"
#include <string>
#include <string_view>

void luaState::reportErr(){
    termMsg(lua_tostring(m_state, -1), "LUALIB", COLOR_RED);

    lua_pop(m_state, 1);
}

bool luaState::doScript(std::string_view content, ScriptSrc srcType){
    std::string content_str(content);

    int loadStatus = srcType == ScriptSrc::FilePath
        ? luaL_loadfile(m_state, content_str.c_str())
        : luaL_loadstring(m_state, content_str.c_str());
    if (loadStatus != 0) {
        reportErr(); return false;
    }

    int callStatus = lua_pcall(m_state, 0, LUA_MULTRET, 0);
    if (callStatus != 0){
        reportErr(); return false;
    }
    return false;
}
