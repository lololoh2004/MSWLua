#pragma once


struct lua_State;

enum luaLibEnum : unsigned int {
    BaseLuaLib    = 1 << 0,
    MathLuaLib    = 1 << 1,
    StringLuaLib  = 1 << 2,
    TableLuaLib   = 1 << 3,
    FFILuaLib     = 1 << 4,
    IOLuaLib      = 1 << 5,
    OSLuaLib      = 1 << 6,
    PkgLuaLib     = 1 << 7,
    DebugLuaLib   = 1 << 8,

    AllLuaLibs    = 0xFFFFFFFF
};

void openLibs(lua_State* L);
void openLibs(lua_State* L, unsigned int flags);