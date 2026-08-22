#pragma once

#include "mswlua_common.hpp"
#include <string_view>

struct lua_State;
enum class ScriptSrc{
    FilePath,
    RawText
};

class luaState{
protected:
    lua_State* m_state;
    void reportErr();
public:
    luaState();
    ~luaState();

    luaState(const luaState& other) = delete;
    luaState& operator=(const luaState& other) = delete;

    void openLibs();
    void openLibs(unsigned int flags);

    bool doScript(std::string_view content, ScriptSrc srcType = ScriptSrc::FilePath);

    [[nodiscard]] lua_State* getRawState() const noexcept { return m_state; }
};