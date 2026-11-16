#pragma once

#include <string_view>

#include "mswlua/common/structs.hpp"


struct lua_State;

class LEGACY_func_call{
    lua_State* m_state = nullptr;
    const char* m_tablePath;
    int m_argCount = 0;
    int m_funcIdx = -1;

    // void findByPath(std::string_view tablePath);
    void findAndRefFunc();
public:
    LEGACY_func_call(lua_State* state, const char* tablePath);
    ~LEGACY_func_call();

    LEGACY_func_call& arg(int num);
    void exec(void* resultVar=nullptr);

    void reload();
};

class funcCall{
public:
    funcCall(lua_State* L, std::string_view tablePath);
    ~funcCall() { clearStack(); clearRef(); }

    // PUSHERS
    funcCall& push(bool   val);
    funcCall& push(int    val);
    funcCall& push(float  val);
    funcCall& push(double val);
    funcCall& push(std::string_view val);

    // RUN
    funcCall& runFunc();

    // GETTERS
    funcCall& get(bool&   var);
    funcCall& get(int&    var);
    funcCall& get(float&  var);
    funcCall& get(double& var);
    funcCall& get(std::string& var);

    void clearStack();
    void clearRef();

    funcCall(const funcCall&) = delete;
    funcCall& operator=(const funcCall&) = delete;
private:
    void _beforePush();

    lua_State* m_L = nullptr;
    int m_nargs    = 0;
    int m_oldTop   = 0;
    int m_funcRef  = -2; // LUA_NOREF in lauxlib.h
    int m_readOffset = 1;
    bool m_isValid = false;
};