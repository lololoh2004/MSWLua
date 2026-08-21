#include "mswlua_common.hpp"
#include "_include/state_class.hpp"

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
    {mswlua::lib::base,    luaopen_base},
    {mswlua::lib::debug,   luaopen_debug},
    {mswlua::lib::ffi,     luaopen_ffi},
    {mswlua::lib::io,      luaopen_io},
    {mswlua::lib::math,    luaopen_math},
    {mswlua::lib::os,      luaopen_os},
    {mswlua::lib::package, luaopen_package},
    {mswlua::lib::string,  luaopen_string},
    {mswlua::lib::table,   luaopen_table},
};

luaState::luaState(){
    m_state = luaL_newstate();
    luaL_openlibs(m_state);
}

void luaState::openLibs(){
    luaL_openlibs(m_state);
}

void luaState::openLibs(unsigned int flags){
    if (flags & mswlua::lib::_all){
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