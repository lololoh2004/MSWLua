#pragma once

#include <string_view>


struct lua_State;

class funcCall{
    lua_State* m_state = nullptr;
    const char* m_tablePath;
    int m_argCount = 0;
    int m_funcIdx = -1;

    void findByPath(std::string_view tablePath);
    void findAndRefFunc();
public:
    funcCall(lua_State* state, const char* tablePath);
    ~funcCall();

    funcCall& arg(int num);
    void exec(void* resultVar=nullptr);

    void reload();
};