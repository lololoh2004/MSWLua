#pragma once

#include "mswlua_common.hpp"

struct lua_State;

class luaState{
protected:
    lua_State* m_state;
public:
    luaState();
    ~luaState();

    luaState(const luaState& other) = delete;
    luaState& operator=(const luaState& other) = delete;

    void openLibs();
    void openLibs(unsigned int flags);

    // BROKEN
    bool runStrScript(const char* scriptContent, bool secure=false, void* returnVal=nullptr);

    [[nodiscard]] lua_State* getRawState() const noexcept { return m_state; }
};