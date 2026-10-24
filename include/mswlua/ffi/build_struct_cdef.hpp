#pragma once

#include <string>
#include <string_view>
#include <vector>


class structBuilder{
    std::string m_cdefResult;
    std::string m_bindResult;

    std::string m_structName;
    std::vector<std::string> m_methods;

    size_t m_fieldCount    = 0;
    bool m_hasMethods      = false;
    bool m_isStructStarted = false;

    void endStruct();
public:
    structBuilder()  = default;
    ~structBuilder() = default;

    structBuilder& createStruct(std::string_view name);
    structBuilder& commitAll();

    structBuilder& var(std::string_view type, std::string_view name);
    // Methods have not yet been implemented, but in the future it will be cdata + metatype
    structBuilder& method(std::string_view methodName, std::string_view funcPath);

    std::string getCDefContent() { return m_cdefResult; }
    std::string getBindContent() { return m_bindResult; }
};
