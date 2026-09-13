#include "mswlua/ffi/build_func_cdef.hpp"


void funcBuilder::createCDefStart(){
    ::createCDefStart(m_cdefResult, m_cdefState);
}

funcBuilder* funcBuilder::createFunc(std::string_view name){
    if (m_cdefState == NoCDefStarted)
        createCDefStart();

    m_funcName   = name;
    m_cdefResult += std::string(1 * 4, ' ');
    m_funcState = ObjectStarted;

    return this;
}
