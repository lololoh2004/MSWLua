#include "mswlua/c_api/run_funcs.hpp"

extern "C"{
#include <lua.h>
}


void runStr(lua_State* L, std::string_view codeStr){
    lua_pcall(L, );
}