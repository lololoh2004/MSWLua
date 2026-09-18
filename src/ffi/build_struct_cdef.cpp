#include "mswlua/ffi/build_struct_cdef.hpp"
#define TAB_LEN 4


void structBuilder::endStruct(){
    m_cdefResult += std::string(TAB_LEN * 1, ' ');
    m_cdefResult += "} " + m_structName + ";\n";
    m_isStructStarted = false;
    m_fieldCount = 0;
}

structBuilder& structBuilder::createStruct(std::string_view name){
    if (m_isStructStarted)
        endStruct();

    m_structName  = name;
    m_cdefResult += std::string(TAB_LEN * 1, ' ');
    m_cdefResult += "typedef struct {\n";

    m_isStructStarted = true;

    return *this;
}
structBuilder& structBuilder::var(std::string_view type, std::string_view name){
    if (!m_isStructStarted) return *this;

    m_cdefResult += std::string(TAB_LEN * 2, ' ');
    m_cdefResult += type;
    m_cdefResult += " ";
    m_cdefResult += name;
    m_cdefResult += ";\n";

    m_fieldCount++;

    return *this;
}
structBuilder& structBuilder::commitAll(){
    if (m_fieldCount == 0)
        var("void*", "PLACEHOLDER");
    if (m_isStructStarted)
        endStruct();

    return *this;
}