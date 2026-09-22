#include <lo_utils/cxx_wrap/term.hpp>
#include "mswlua/class/state.hpp"

extern "C"{
#include "lua.h"
}

#include <string>
#include <string_view>


bool luaState::callFunc(){
    term::msg("Calling lua func..", "LUALIB", COLOR_GRAY);
    int funcStateIdx = -1 - tempArgCount;

    if (!lua_isfunction(m_state, funcStateIdx)){
        term::msg("The called function is not a Lua function !", "LUALIB", COLOR_RED);

        delTempArgs();
        lua_pop(m_state, 1);
        return false;
    }

    int argCount = tempArgCount;
    tempArgCount = 0;

    if (lua_pcall(m_state, argCount, 0, 0) != LUA_OK){
        reportErr();
        return false;
    }

    return true;
}


bool luaState::doFunc(std::string_view tablePath){
    std::string path = std::string(tablePath);
    if (path.back() == '.')
        path.erase(path.size() - 1);

    size_t startPos = 0;
    size_t dotPos = path.find('.');

    std::string firstKey = std::string(path.substr(0, dotPos));
    lua_getglobal(m_state, firstKey.c_str());

    while (dotPos != std::string::npos) {
        if (!lua_istable(m_state, -1)) {
            lua_pop(m_state, 1);
            return false;
        }
        startPos = dotPos + 1;
        dotPos = path.find('.', startPos);

        std::string keyName = std::string(path.substr(startPos, dotPos - startPos));
        lua_getfield(m_state, -1, keyName.c_str());
        lua_remove(m_state, -2);
    }
    if (!lua_isfunction(m_state, -1)){
        lua_pop(m_state, 1);
        return false;
    }

    if (lua_pcall(m_state, 0, 0, 0) != LUA_OK){
        reportErr(); return false;
    }
    return true;
}
