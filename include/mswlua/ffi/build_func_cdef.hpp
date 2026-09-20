#pragma once

#include <string>
#include <string_view>


// Mangling will be taken into account in the future
// enum funcStandardType{
//     StandardC,
//     GNU_CXX
// };
// enum funcRegistType{
//     StandardC,
//     GNU_CXX
// };

class funcBuilder{
    std::string m_funcName;
    std::string m_funcReturn;
    std::string m_funcArgs;
    std::string m_funcPath;

    std::string m_cdefResult;
    std::string m_bindResult;

    size_t m_argCount = 0;
    bool m_isFuncStarted = false;

    void endFunc();
public:
    funcBuilder()  = default;
    ~funcBuilder() = default;

    funcBuilder& createFunc(std::string_view name, void* directPtr = nullptr);
    funcBuilder& commitAll();

    funcBuilder& path(std::string_view path) { m_funcPath = path; return *this; };
    funcBuilder& returnType(std::string_view type);
    funcBuilder& arg(std::string_view type, std::string_view name);

    std::string getCDefContent() { return m_cdefResult; }
    std::string getBindContent() { return m_bindResult; }
};
