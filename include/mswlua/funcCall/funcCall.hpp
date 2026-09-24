#pragma once

#include <string_view>


struct lua_State;

class funcCall{
    lua_State* m_state;
    int m_argCount = 0;
    int m_funcIdx = 0;
    int m_oldTopIdx = 0;

    void findProto(std::string_view tablePath);
public:
    funcCall(lua_State* state, const char* tablePath);
    funcCall(lua_State* state, int funcIdx);
    ~funcCall();

    funcCall& arg(int num);
    void clearArgs() { m_argCount = 0; }

    void exec(void* resultVar);
};