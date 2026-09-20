#pragma once

#include <string>
#include <string_view>


class structBuilder{
    std::string m_structName;
    std::string m_cdefResult;
    std::string m_bindResult;

    size_t m_fieldCount    = 0;
    bool m_isStructStarted = false;

    void endStruct();
public:
    structBuilder()  = default;
    ~structBuilder() = default;

    structBuilder& createStruct(std::string_view name);
    structBuilder& commitAll();

    structBuilder& var(std::string_view type, std::string_view name);
    // Methods have not yet been implemented, but in the future it will be cdata + metatype.
    structBuilder& method();

    std::string getCDefContent() { return m_cdefResult; }
    std::string getBindContent() { return m_bindResult; }
};
