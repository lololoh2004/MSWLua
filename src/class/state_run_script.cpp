#include "mswlua/class/state.hpp"

extern "C"{
#include "lua.h"
#include "lauxlib.h"
}

#include <string>
#include <string_view>


bool luaState::doScript() const{
    int callStatus = lua_pcall(m_state, 0, LUA_MULTRET, 0);
    if (callStatus != LUA_OK){
        reportErr(); return false;
    }
    return true;
}
bool luaState::doScriptPath(std::string_view content){
    std::string content_str(content);

    int loadStatus = luaL_loadfile(m_state, content_str.c_str());
    if (loadStatus != LUA_OK) {
        reportErr(); return false;
    }
    return doScript();
}
bool luaState::doScriptStr(std::string_view content){
    std::string content_str(content);

    int loadStatus = luaL_loadstring(m_state, content_str.c_str());
    if (loadStatus != LUA_OK) {
        reportErr(); return false;
    }
    return doScript();
}