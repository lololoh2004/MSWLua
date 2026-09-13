#pragma once

#include <string>
#include <string_view>

#include "cdef_common.hpp"


class funcBuilder{
    std::string   m_funcName;
    std::string   m_cdefResult;
    cdefStateEnum      m_cdefState = NoCDefStarted;
    curObjectStateEnum m_funcState = ObjectNotStarted;

    void createCDefStart();
public:
    funcBuilder()  = default;
    ~funcBuilder() = default;

    funcBuilder* createFunc(std::string_view name);
    funcBuilder* commitFunc();

    funcBuilder* returnVal(std::string_view type);
    funcBuilder* arg(std::string_view type, std::string_view name);

    void endBuilding();

    std::string getCDefContent() { return m_cdefResult; }
};
