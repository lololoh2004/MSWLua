#include "mswlua/ffi/build_struct_cdef.hpp"


void structBuilder::createCDefStart(){
    ::createCDefStart(m_cdefResult, m_cdefState);
}
void structBuilder::endBuilding(){
    if (m_cdefState == CDefHasStarted){
        m_cdefResult += "]]\n";
        m_cdefState = NoCDefStarted;
    }
}

structBuilder* structBuilder::createStruct(std::string_view name){
    if (m_cdefState == NoCDefStarted) createCDefStart();

    m_structName  = name;
    m_cdefResult += std::string(1 * 4, ' ');
    m_cdefResult += "typedef struct {\n";
    m_structState = ObjectStarted;

    return this;
}
structBuilder* structBuilder::var(std::string_view type, std::string_view name){
    if (m_structState != ObjectStarted) return this;

    m_cdefResult += std::string(2 * 4, ' ');
    m_cdefResult += type;
    m_cdefResult += " ";
    m_cdefResult += name;
    m_cdefResult += ";\n";

    return this;
}
structBuilder* structBuilder::commitStruct(){
    m_cdefResult += std::string(1 * 4, ' ');
    m_cdefResult += "} " + m_structName + ";\n";
    m_structState = ObjectNotStarted;

    return this;
}