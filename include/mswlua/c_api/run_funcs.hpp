#pragma once

#include <string_view>


struct lua_State;

struct pcallArgs{
    int nargs    = 0;
    int nresults = 0;
    int errfunc  = 0;
};

class strScript{
public:
    strScript(lua_State* L, std::string_view script,
              const char* chunkName="mswlua_run_fn", const char* mode=nullptr
    );
    ~strScript(){
        clearAll();
    }

    strScript(const strScript&) = delete;
    strScript& operator=(const strScript&) = delete;

    // PUSHERS
    strScript& pushNum(int val);
    strScript& pushNum(float val);
    strScript& pushNum(double val);
    strScript& pushStr(std::string_view val);

    // RUN
    strScript& runScript();

    // GETTERS
    strScript& getNum(int& var);
    strScript& getNum(float& var);
    strScript& getNum(double& var);
    strScript& getStr(std::string& var);

    void clearAll();
private:
    lua_State* m_L;
    pcallArgs m_pcallArgs = {0, -1, 0}; // -1 is MULTRET define in lua.h
    int m_oldTop;
    int m_readOffset = 1;
    bool m_success = true;
};

// bool runStr(lua_State* L, std::string_view codeStr);


