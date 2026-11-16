#pragma once

#include <string_view>
#include <string>

#include "mswlua/common/structs.hpp"


struct lua_State;

class strScript{
public:
    strScript(lua_State* L, std::string_view script,
              const char* chunkName="mswlua_run_fn", const char* mode=nullptr
    );
    ~strScript() { clear(); }

    strScript(const strScript&) = delete;
    strScript& operator=(const strScript&) = delete;

    // PUSHERS
    strScript& push(bool   val);
    strScript& push(int    val);
    strScript& push(float  val);
    strScript& push(double val);
    strScript& push(std::string_view val);

    // RUN
    strScript& runScript();

    // GETTERS
    strScript& get(bool&   var);
    strScript& get(int&    var);
    strScript& get(float&  var);
    strScript& get(double& var);
    strScript& get(std::string& var);

    void clear();
private:
    lua_State* m_L = nullptr;
    int  m_nargs  = 0;
    int  m_oldTop = 0;
    int  m_readOffset = 1;
    bool m_hasRun  = false;
    bool m_isValid = false;
};

