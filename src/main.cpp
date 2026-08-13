#include "dll_agent.hpp"

struct lua_State;

namespace dl_src{
lua_State* (*luaL_newstate)() = nullptr;

void (*lua_close)(struct lua_State* L) = nullptr;
int (*luaL_loadstring)(struct lua_State* L, const char* s) = nullptr;
int (*lua_pcall)(struct lua_State* L, int nargs, int nresults, int errfunc) = nullptr;

void (*luaL_openlibs)(struct lua_State* L) = nullptr;
}

int main(){
    const char* type = "jit2";
    const char* ver = "51";
    std::string lib_name = "liblua" + std::string(type) + std::string(ver);
    const char* clib_name = lib_name.c_str();

    std::printf("Hello, World ! ");
    std::printf("Lib name : %s/n", clib_name);

    dlib::reg_func(clib_name, "luaL_newstate",   dl_src::luaL_newstate);
    dlib::reg_func(clib_name, "luaL_openlibs",   dl_src::luaL_openlibs);
    dlib::reg_func(clib_name, "luaL_loadstring", dl_src::luaL_loadstring);
    dlib::reg_func(clib_name, "lua_pcall",       dl_src::lua_pcall);
    dlib::reg_func(clib_name, "lua_close",       dl_src::lua_close);
    dlib::print_all_libs();

    lua_State* L = dl_src::luaL_newstate();
    if (L){
        dl_src::luaL_openlibs(L);
        std::printf("Lua state created\n");

        const char* script = "print('=== Lua " TYPE " works !! ===')";
        if (dl_src::luaL_loadstring(L, script) == 0){
            if (dl_src::lua_pcall(L, 0, 0, 0) != 0) {
                std::printf("Lua error\n");
            }
        }

        dl_src::lua_close(L);
    }
    return 0;
}