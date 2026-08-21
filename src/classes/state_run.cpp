#include "_include/state_class.hpp"

extern "C"{
#include "lua.h"
// #include "lauxlib.h"
// #include "lualib.h"
#include "term.h"
}

#include <string>
#include <string_view>

#define COMMENT_SIGN_LENGHT 2

struct LuaReaderData{
    std::string code;
    bool is_used = false;
};

std::string cutFirstComment(std::string_view scriptContent){
    if (scriptContent.empty()){
        termMsgC("No content in script code", "MSWLUA", COLOR_RED);
        return "no_name_script";
    }
    std::string nameComment = "no_name_script";
    if (scriptContent[0] == '-' && scriptContent[1] == '-'){
        size_t endIdx = scriptContent.find('\n');
        if (endIdx != std::string_view::npos)
            nameComment = scriptContent.substr(COMMENT_SIGN_LENGHT, endIdx-COMMENT_SIGN_LENGHT);
        else
            nameComment = scriptContent.substr(COMMENT_SIGN_LENGHT);
        return nameComment;
    }
    return nameComment;
}

const char* strReader(lua_State* L, void* data, size_t* size){
    auto* readerData = static_cast<LuaReaderData*>(data);
    if (readerData->is_used){
        *size = 0;
        return nullptr;
    }
    readerData->is_used = true;
    *size = readerData->code.size();
    return readerData->code.c_str();
}

// BROKEN
bool luaState::runStrScript(const char* scriptContent, bool secure, void* returnVal){
    if (!m_state || !scriptContent) return false;

    LuaReaderData readerData{
        .code = scriptContent,
        .is_used = false};

    std::string firstLine = cutFirstComment(readerData.code);

    if (lua_load(m_state, strReader, &readerData, firstLine.c_str()) != LUA_OK){
        lua_pop(m_state, 1);
        return false;
    }
    if (secure){
        if (lua_pcall(m_state, 0, 1, 0) != 0) {
            lua_pop(m_state, 1);
            return false;
        }
    } else{
        lua_call(m_state, 0, 1);
    }

    auto returnType = lua_type(m_state, -1);
    if (returnVal == nullptr){
        lua_pop(m_state, 1);
        return true;
    }

    switch (returnType){
        case LUA_TNUMBER:
            *static_cast<double*>(returnVal) = lua_tonumber(m_state, -1);
            break;
        case LUA_TBOOLEAN:
            *static_cast<bool*>(returnVal) = lua_toboolean(m_state, -1);
            break;
        case LUA_TSTRING:
            *static_cast<std::string*>(returnVal) = lua_tostring(m_state, -1);
            break;
        default:
            break;
    }

    lua_pop(m_state, 1);
    return true;
}
