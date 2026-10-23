#include "mswlua/c_api/openLib_funcs.hpp"
extern "C"{
#include "lua.h"
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

void openLibs(lua_State* L){
    luaL_openlibs(L);
}

void openLibs(lua_State* L, unsigned int flags){
    if (flags & AllLuaLibs){
        luaL_openlibs(L);
        return;
    }
    for (const auto& lib : libMap){
        if (lib.flag & flags)
            lib.open_func(L);
    }
}