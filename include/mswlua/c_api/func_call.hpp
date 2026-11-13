#pragma once


struct lua_State;

class func_call{
    lua_State* m_state = nullptr;
    const char* m_tablePath;
    int m_argCount = 0;
    int m_funcIdx = -1;

    // void findByPath(std::string_view tablePath);
    void findAndRefFunc();
public:
    func_call(lua_State* state, const char* tablePath);
    ~func_call();

    func_call& arg(int num);
    void exec(void* resultVar=nullptr);

    void reload();
};