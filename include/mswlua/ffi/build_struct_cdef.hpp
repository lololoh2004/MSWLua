#pragma once

#include <string>
#include <string_view>

#include "cdef_common.hpp"


class structBuilder{
    std::string   m_structName;
    std::string   m_cdefResult;
    cdefStateEnum      m_cdefState   = NoCDefStarted;
    curObjectStateEnum m_structState = ObjectNotStarted;

    void createCDefStart();
public:
    structBuilder()  = default;
    ~structBuilder() = default;

    structBuilder* createStruct(std::string_view name);
    structBuilder* commitStruct();

    structBuilder* var(std::string_view type, std::string_view name);
    structBuilder* method();

    void endBuilding();

    std::string getCDefContent() { return m_cdefResult; }
};
