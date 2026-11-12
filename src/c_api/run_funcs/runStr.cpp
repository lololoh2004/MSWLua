#include "mswlua/c_api/run_funcs.hpp"

extern "C"{
#include <lauxlib.h>
#include <lua.h>
}
#include <string>
#include "mswlua/log_hook.hpp"


// === INTERNAL SECTION ===

static bool internal_runStr(lua_State* L, pcallArgs args){
    if (lua_pcall(L, args.nargs, args.nresults, args.errfunc) != LUA_OK){
        const char* top = lua_tostring(L, -1);
        MSWLuaLog("LUA", "Lua error during code running (str) : %s", top ? top : "NON_STR_ERR_OBJ");
        return false;
    }
    return true;
}

static void internal_incorrectValLog(lua_State* L, int idx){
    MSWLuaLog("MSWLUA", "BUG DETECTED - cant get correct VALUE at idx %d (got %s); skipping",
        idx, lua_typename(L, lua_type(L, idx))
    );
}


// === PUSHERS SECTION ===

strScript& strScript::pushNum(int val){
    if (m_success == false) return *this;

    lua_pushinteger(m_L, val);
    m_pcallArgs.nargs++;
    return *this;
}
strScript& strScript::pushNum(float val){
    if (m_success == false) return *this;

    lua_pushnumber(m_L, val);
    m_pcallArgs.nargs++;
    return *this;
}
strScript& strScript::pushNum(double val){
    if (m_success == false) return *this;

    lua_pushnumber(m_L, val);
    m_pcallArgs.nargs++;
    return *this;
}
strScript& strScript::pushStr(std::string_view val){
    if (m_success == false) return *this;

    lua_pushlstring(m_L, val.data(), val.size());
    m_pcallArgs.nargs++;
    return *this;
}


// === CLASS METHODS ===

strScript::strScript(lua_State* L, std::string_view script, const char* chunkName, const char* mode){
    m_L = L;
    m_oldTop = lua_gettop(L);

    int loadBufCode = luaL_loadbufferx(L, script.data(), script.size(), chunkName, mode);
    if (loadBufCode != LUA_OK){
        const char* top = lua_tostring(L, -1);
        MSWLuaLog("LUA", "Lua error during code loading (str) : %s", top ? top : "NON_STR_ERR_OBJ");
        m_success = false;
        return;
    }
}
void strScript::clearAll(){
    lua_settop(m_L, m_oldTop);
}

strScript& strScript::runScript(){
    if (m_success == false) return *this;
    m_success = internal_runStr(m_L, m_pcallArgs);

    return *this;
}


// === GETTERS SECTION ===

strScript& strScript::getNum(int& var){
    if (m_success == false) return *this;

    int idx = m_oldTop + m_readOffset;
    if (lua_isnumber(m_L, idx)) var = static_cast<int>(lua_tointeger(m_L, idx));
    else                        internal_incorrectValLog(m_L, idx);

    m_readOffset++;
    return *this;
}
strScript& strScript::getNum(float& var){
    if (m_success == false) return *this;

    int idx = m_oldTop + m_readOffset;
    if (lua_isnumber(m_L, idx)) var = static_cast<float>(lua_tonumber(m_L, idx));
    else                        internal_incorrectValLog(m_L, idx);

    m_readOffset++;
    return *this;
}
strScript& strScript::getNum(double& var){
    if (m_success == false) return *this;

    int idx = m_oldTop + m_readOffset;
    if (lua_isnumber(m_L, idx)) var = lua_tonumber(m_L, idx);
    else                        internal_incorrectValLog(m_L, idx);

    m_readOffset++;
    return *this;
}

strScript& strScript::getStr(std::string& var){
    if (m_success == false) return *this;

    int idx = m_oldTop + m_readOffset;
    if (lua_isstring(m_L, idx)){
        size_t size = 0;
        const char* result = lua_tolstring(m_L, idx, &size);
        var.append(result, size);
    } else {
        internal_incorrectValLog(m_L, idx);
    }

    m_readOffset++;
    return *this;
}
