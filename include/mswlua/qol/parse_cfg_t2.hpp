#pragma once
#include <string>

class luaState;
struct lua_State;

class cfgParserFFI{
    lua_State* m_state;
    std::string path;
public:
    cfgParserFFI(luaState& state);
};
