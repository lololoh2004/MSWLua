// #include "mswlua/luaState/state.hpp"
// #include "lo_utils/cxx20/parse.hpp"
//
// extern "C"{
// #include "lua.h"
// }
//
// #include <vector>
// #include <string>
// #include <string_view>
//
//
// bool findByPath(lua_State* state, std::string_view tablePath){
//     auto tokens = splitStrToTokens(tablePath);
//     if (tokens.empty())
//         return false;
//
//     std::string firstToken(tokens[0]);
//     lua_getglobal(state, firstToken.c_str());
//     if (lua_isnil(state, -1)){
//         lua_pop(state, 1);
//         return false;
//     }
//
//
//     for (int i = 1; i < tokens.size(); ++i){
//         std::string token(tokens[i]);
//
//         lua_getfield(state, -1, token.c_str());
//         lua_remove(state, -2);
//
//         if (lua_isnil(state, -1))
//             return false;
//     }
//
//     return true;
// }
//
// luaState& luaState::addTempFunc(std::string_view tablePath){
//     delTempArgs();
//     if (!findByPath(m_state, tablePath)){
//         lua_pushnil(m_state);
//     }
//
//     return *this;
// }
// luaState& luaState::addTempArg(int num){
//     lua_pushnumber(m_state, num);
//     tempArgCount++;
//
//     return *this;
// }
// void luaState::delTempArgs(){
//     if (tempArgCount == 0) return;
//     lua_pop(m_state, tempArgCount);
//     tempArgCount = 0;
// }