#include "mswlua/common.hpp"
#include "mswlua/class/state.hpp"

extern "C"{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

struct libMapStruct{
    unsigned int flag;
    int (*open_func)(lua_State*);
};
static constexpr libMapStruct libMap[] {
    {BaseLuaLib,    luaopen_base},
    {DebugLuaLib,   luaopen_debug},
    {FFILuaLib,     luaopen_ffi},
    {IOLuaLib,      luaopen_io},
    {MathLuaLib,    luaopen_math},
    {OSLuaLib,      luaopen_os},
    {PkgLuaLib,     luaopen_package},
    {StringLuaLib,  luaopen_string},
    {TableLuaLib,   luaopen_table},
};

luaState::luaState(){
    m_state = luaL_newstate();
    luaL_openlibs(m_state);
}

void luaState::openLibs(){
    luaL_openlibs(m_state);
}

void luaState::openLibs(unsigned int flags){
    if (flags & AllLuaLibs){
        luaL_openlibs(m_state);
        return;
    }
    for (const auto& lib : libMap){
        if (lib.flag & flags)
            lib.open_func(m_state);
    }
}

luaState::~luaState(){
    if (m_state) lua_close(m_state);
}