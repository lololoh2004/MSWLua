#include "mswlua/common/find_by_path.h"
extern "C"{
#include <lua.h>
}
#include <string>


void findByPath(lua_State* state, std::string_view tablePath){
    if (!state) return;
    // Small QoL addition
    if (tablePath.back() == '.')
        tablePath.remove_suffix(1);

    // Variables
    size_t startPos = 0;
    size_t endPos = tablePath.find('.');

    std::string token;
    token = tablePath.substr(startPos, endPos - startPos);

    // First iteration ( via lua_getglobal )
    lua_getglobal(state, token.c_str());

    // Another iterations ( via lua_getfield )
    while (endPos != std::string_view::npos){
        startPos = endPos + 1;
        endPos = tablePath.find('.', startPos);

        token = tablePath.substr(startPos, endPos - startPos);
        lua_getfield(state, -1, token.c_str());
        lua_remove(state, -2);
    }
}
