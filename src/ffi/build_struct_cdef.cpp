#include "mswlua/ffi/build_struct_cdef.hpp"
#include <format>

#define TAB_LEN 4


void structBuilder::endStruct(){
    if (m_fieldCount == 0)
        var("void*", "PLACEHOLDER");
    m_cdefResult += std::format(
        "{:>{}}}} {};\n",
        "", TAB_LEN,
        m_structName
    );

    if (m_hasMethods){
        m_bindResult += std::format(
        "{0} = ffi.metatype( '{0}', {{ __index = __{0}_methods }} )\n",
        m_structName
        );
    }

    m_isStructStarted = false;
    m_hasMethods      = false;
    m_fieldCount = 0;
}

structBuilder& structBuilder::createStruct(std::string_view name){
    if (m_isStructStarted)
        endStruct();

    m_structName  = name;

    m_cdefResult += std::format(
        "{:>{}}typedef struct {{\n",
        "", TAB_LEN
    );

    m_isStructStarted = true;

    return *this;
}
structBuilder& structBuilder::var(std::string_view type, std::string_view name){
    if (!m_isStructStarted) return *this;

    m_cdefResult
        .append(TAB_LEN * 2, ' ')
        .append(type)
        .append(" ")
        .append(name)
        .append(";\n");

    m_fieldCount++;

    return *this;
}
structBuilder& structBuilder::method(std::string_view methodName, std::string_view funcPath){
    if (!m_isStructStarted) return *this;
    if (m_hasMethods == false){
        m_bindResult += std::format(
        "local __{}_methods = {{}}\n",
        m_structName
        );
    }

    m_bindResult += std::format(
        "function __{}_methods:{}(...) return {}(self, ...) end\n",
        m_structName ,methodName, funcPath
    );

    m_hasMethods = true;

    return *this;
}

structBuilder& structBuilder::commitAll(){
    if (m_isStructStarted)
        endStruct();

    return *this;
}