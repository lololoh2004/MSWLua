#pragma once

#include <string>
#include <string_view>


// Mangling will be taken into account in the future
// enum funcMangling{
//     StandardC = 0,
//     GNU_CXX
// };

class funcBuilder{
    // funcMangling m_mangling;
    std::string m_funcName;
    std::string m_funcPath;
    void*       m_funcPtr = nullptr;
    std::string m_funcReturn;
    std::string m_funcArgs;

    std::string m_cdefResult;
    std::string m_bindResult;

    size_t m_argCount = 0;
    bool m_isFuncStarted = false;

    void endFunc_ByCDef();
    void endFunc_ByCast();
    // void simulateMangling();
    void endFunc();
public:
    funcBuilder()  = default;
    ~funcBuilder() = default;

    funcBuilder& createFunc(std::string_view name, void* directPtr = nullptr);
    funcBuilder& commitAll();

    // funcBuilder& mangling(funcMangling type)    { m_mangling = type; return *this; }
    funcBuilder& luaPath(std::string_view path) { m_funcPath = path; return *this; }
    funcBuilder& cPtr(void* ptr)                { m_funcPtr = ptr; return *this; }
    funcBuilder& returnType(std::string_view type);
    funcBuilder& arg(std::string_view type, std::string_view name);

    std::string getCDefContent() { return m_cdefResult; }
    std::string getBindContent() { return m_bindResult; }
};
