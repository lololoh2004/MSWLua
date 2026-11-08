#pragma once

#include <string>
#include <string_view>


enum funcMangling{
    StandardC = 0,
    GNU_CXX
};

class funcBuilder{
    funcMangling m_mangling = StandardC;
    std::string m_funcName;
    std::string m_funcPath;
    void*       m_funcPtr = nullptr;
    std::string m_funcReturn;
    std::string m_funcArgs;
    std::string m_funcMangledArgs;

    size_t m_argCount = 0;
    bool m_isFuncStarted = false;

    std::string m_cdefResult;
    std::string m_bindResult;


    std::string _getMangledName();
    [[nodiscard]] std::string _getMangledType(std::string_view type) const;
    std::string _getLuaPath();

    void _addArgs();

    void _endFuncCDef();
    void _endFuncCast();
    void endFunc();
public:
    funcBuilder()  = default;
    ~funcBuilder() = default;

    funcBuilder(const funcBuilder&) = delete;
    funcBuilder& operator=(const funcBuilder&) = delete;

    funcBuilder& mangling(funcMangling type)    { m_mangling = type; return *this; }
    funcBuilder& luaPath(std::string_view path) { m_funcPath = path; return *this; }

    funcBuilder& createFunc(std::string_view name);
    funcBuilder& commitAll();

    funcBuilder& cPtr(void* ptr)                { m_funcPtr  = ptr; return *this; }
    funcBuilder& returnType(std::string_view type);
    funcBuilder& arg(std::string_view type, std::string_view name);

    [[nodiscard]] const std::string& getCDefContent() const noexcept{ return m_cdefResult; }
    [[nodiscard]] const std::string& getBindContent() const noexcept{ return m_bindResult; }
};
