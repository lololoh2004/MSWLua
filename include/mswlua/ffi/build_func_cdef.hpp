#pragma once

#include <string>
#include <string_view>


// Mangling will be taken into account in the future
enum funcStandardType{
    StandardC,
    GNU_CXX
};

class funcBuilder{
    std::string m_funcName;
    std::string m_cdefResult;
    std::string m_bindResult;

    funcStandardType m_funcType = StandardC;
    size_t m_argCount = 0;
public:
    funcBuilder()  = default;
    ~funcBuilder() = default;

    funcBuilder& createFunc(std::string_view name, void* directPtr = nullptr);
    funcBuilder& commitAll();

    funcBuilder& setFuncType(funcStandardType type) { m_funcType = type; return *this; }
    funcBuilder& returnType(std::string_view type);
    funcBuilder& arg(std::string_view type, std::string_view name);


    std::string getCDefContent() { return m_cdefResult; }
};
