#pragma once

#include "mswlua/common.hpp"
#include <string_view>
#include <cstdint>

struct lua_State;
enum class scriptSrc{
    FilePath,
    RawText
};

class luaState{
protected:
    lua_State* m_state;

    void reportErr() const;
    bool doScript() const;
public:
    luaState();
    ~luaState();

    luaState(const luaState& other) = delete;
    luaState& operator=(const luaState& other) = delete;

    void openLibs();
    void openLibs(unsigned int flags);

    void regVal(int num, const char* name);
    void regVal(float fl, const char* name);
    void regVal(double db, const char* name);
    void regVal(const char* str, const char* name);
    void regVal(bool bl, const char* name);

    // TOMMORROW ME PLEASE FIX THIS SHIII
    bool doScriptPath(std::string_view content);
    bool doScriptStr(std::string_view content);

    [[nodiscard]] lua_State* getRawState() const noexcept { return m_state; }
};

#define regValDefine(def) regVal((def), #def)