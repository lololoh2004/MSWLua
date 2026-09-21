#include "mswlua/class/state.hpp"

extern "C"{
#include "lua.h"
}

#include <string>
#include <string_view>
#include <vector>

std::vector<std::string_view> splitStrToTokens(std::string_view content){
    if (content.back() == '.')
        content.remove_suffix(1);
    std::vector<std::string_view> result;

    size_t startPos = 0;
    size_t endPos = content.find('.');

    while (endPos != std::string_view::npos){
        result.emplace_back(content.data() + startPos, endPos - startPos);

        startPos = endPos + 1;
        endPos = content.find('.', startPos);
    }
    result.emplace_back(content.data() + startPos, content.size() - startPos);

    return result;
}
bool findByPath(lua_State* state, std::string_view tablePath){
    for (const auto token : splitStrToTokens(tablePath)){
    }
    return true;

    // if (tablePath.empty()) {
    //     return false;
    // }
    // std::string path(tablePath);
    // if (path.back() == '.')
    //     path.pop_back();
    //
    // size_t startPos = 0;
    // size_t dotPos = path.find('.');
    //
    // std::string firstKey = path.substr(0, dotPos);
    // lua_getglobal(state, firstKey.c_str());
    //
    // while (dotPos != std::string::npos) {
    //     if (!lua_istable(state, -1)) {
    //         lua_pop(state, 1);
    //         return false;
    //     }
    //     startPos = dotPos + 1;
    //     dotPos = path.find('.', startPos);
    //
    //     std::string keyName = std::string(path.substr(startPos, dotPos - startPos));
    //
    //     lua_getfield(state, -1, keyName.c_str());
    //     lua_remove(state, -2);
    // }
    // return true;
}
// bool findByPath(lua_State* state, std::string_view tablePath){
//     if (tablePath.empty()) {
//         return false;
//     }
//     std::string path(tablePath);
//     if (path.back() == '.')
//         path.pop_back();
//
//     size_t startPos = 0;
//     size_t dotPos = path.find('.');
//
//     std::string firstKey = path.substr(0, dotPos);
//     lua_getglobal(state, firstKey.c_str());
//
//     while (dotPos != std::string::npos) {
//         if (!lua_istable(state, -1)) {
//             lua_pop(state, 1);
//             return false;
//         }
//         startPos = dotPos + 1;
//         dotPos = path.find('.', startPos);
//
//         std::string keyName = std::string(path.substr(startPos, dotPos - startPos));
//
//         lua_getfield(state, -1, keyName.c_str());
//         lua_remove(state, -2);
//     }
//     return true;
// }

void luaState::delTempArgs(){
    if (tempArgCount == 0) return;
    lua_pop(m_state, tempArgCount);
    tempArgCount = 0;
}
luaState& luaState::addTempArg(int num){
    lua_pushnumber(m_state, num);
    tempArgCount++;
    return *this;
}

bool luaState::callFunc(std::string_view tablePath){
    findByPath(m_state, tablePath);
    if (!lua_isfunction(m_state, -1)){
        lua_pop(m_state, 1);
        return false;
    }

    if (lua_pcall(m_state, tempArgCount, 0, 0) != LUA_OK){
        reportErr(); return false;
    }
    return true;
}


bool luaState::doFunc(std::string_view tablePath){
    std::string path = std::string(tablePath);
    if (path.back() == '.')
        path.erase(path.size() - 1);

    size_t startPos = 0;
    size_t dotPos = path.find('.');

    std::string firstKey = std::string(path.substr(0, dotPos));
    lua_getglobal(m_state, firstKey.c_str());

    while (dotPos != std::string::npos) {
        if (!lua_istable(m_state, -1)) {
            lua_pop(m_state, 1);
            return false;
        }
        startPos = dotPos + 1;
        dotPos = path.find('.', startPos);

        std::string keyName = std::string(path.substr(startPos, dotPos - startPos));
        lua_getfield(m_state, -1, keyName.c_str());
        lua_remove(m_state, -2);
    }
    if (!lua_isfunction(m_state, -1)){
        lua_pop(m_state, 1);
        return false;
    }

    if (lua_pcall(m_state, 0, 0, 0) != LUA_OK){
        reportErr(); return false;
    }
    return true;
}
