#pragma once

#include "mswlua/common.hpp"
#include <string_view>

struct lua_State;
enum class scriptSrc{
    FilePath,
    RawText
};

class luaState{
protected:
    lua_State* m_state;

    void reportErr() const;
    [[nodiscard]] bool doScript() const;
public:
    luaState();
    ~luaState();

    luaState(const luaState& other) = delete;
    luaState& operator=(const luaState& other) = delete;

    void openLibs();
    void openLibs(unsigned int flags);

    // Val. funcs.
    // Registration funcs.
    void regVal(int num, const char* name);
    void regVal(float fl, const char* name);
    void regVal(double db, const char* name);
    void regVal(const char* str, const char* name);
    void regVal(bool bl, const char* name);
    // Getter funcs.
    // LATER-ME PLEASE ADD SEARCH IN TABLES
    // ALSO PUT THAT SHI ALGORITHM FROM funcCall IN COMMON
    // AND REWORK COMMON FILE ARCH.
    void getVal(int& var, const char* tablePath) const;
    void getVal(float& var, const char* tablePath) const;
    void getVal(bool& var, const char* tablePath) const;
    void getVal(std::string& var, const char* tablePath) const;

    bool doScriptPath(std::string_view content);
    bool doScriptStr(std::string_view content);

    [[nodiscard]] lua_State* getRawState() const noexcept { return m_state; }
};

#define regValDefine(def) regVal((def), #def)