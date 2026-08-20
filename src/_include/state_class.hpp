#pragma once

struct lua_State;

class luaState{
protected:
    lua_State* m_state;
public:
    luaState();
    //luaState(lua_State* L);
    ~luaState();

    luaState(const luaState& other) = delete;
    luaState& operator=(const luaState& other) = delete;

    lua_State* getRawState() { return m_state; }
};