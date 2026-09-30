#include "mswlua/ffi/build_func_cdef.hpp"
#include <format>

#define TAB_LEN 4


void funcBuilder::endFunc_ByCDef(){
    // Tab.
    m_cdefResult += std::string(TAB_LEN * 1, ' ');
    // Just return type, name and '('
    m_cdefResult += m_funcReturn.empty() ? "void" : m_funcReturn;
    m_cdefResult += " " + m_funcName + " ( ";

    // Adding args.
    if (m_argCount > 0){
        if (m_funcArgs.length() >= 2)
            m_funcArgs.erase(m_funcArgs.length() - 2);
        m_cdefResult += m_funcArgs;
    } else {
        m_cdefResult += "void";
    }
    m_cdefResult += " );\n";

    // TablePath to func.
    if (m_funcPath.empty()){
        m_funcPath += "_G.";
    } else {
        if (m_funcPath.back() != '.')
            m_funcPath += ".";
    }
    m_bindResult += m_funcPath + m_funcName + " = ffi.C." + m_funcName + "\n";
}
void funcBuilder::endFunc_ByCast(){
    // Tab.
    m_cdefResult += std::string(TAB_LEN * 1, ' ');
    // Just return type, proto. name and '('
    m_cdefResult += "typedef ";
    m_cdefResult += m_funcReturn.empty() ? "void" : m_funcReturn;
    m_cdefResult += " ( *" + m_funcName + " )( ";

    // Adding args.
    if (m_argCount > 0){
        if (m_funcArgs.length() >= 2)
            m_funcArgs.erase(m_funcArgs.length() - 2);
        m_cdefResult += m_funcArgs;
    } else {
        m_cdefResult += "void";
    }
    m_cdefResult += " );\n";

    // Func. address cast
    std::string castedFuncName = "casted_" + m_funcName;
    m_bindResult +=
        "local " + castedFuncName + " = " +
        "ffi.cast('" + m_funcName + "', "  + std::format("{}", m_funcPtr) +
        ")\n";

    // TablePath to func.
    if (m_funcPath.empty()){
        m_funcPath += "_G.";
    } else {
        if (m_funcPath.back() != '.')
            m_funcPath += ".";
    }
    // Cast part
    m_bindResult += m_funcPath + m_funcName + " = " + castedFuncName + "\n";
}

void funcBuilder::endFunc(){
    if (m_funcPtr != nullptr){
        endFunc_ByCast();
    } else {
        endFunc_ByCDef();
    }
    // Reset class buf.
    m_funcArgs.clear();
    m_funcReturn.clear();
    m_funcPath.clear();
    m_isFuncStarted = false;
}

funcBuilder& funcBuilder::createFunc(std::string_view name, void* directPtr){
    if (m_isFuncStarted)
        endFunc();

    m_funcName = name;
    m_argCount = 0;
    m_isFuncStarted = true;

    return *this;
}
funcBuilder& funcBuilder::returnType(std::string_view type){
    if (!m_isFuncStarted) return *this;

    m_funcReturn = type;

    return *this;
}
funcBuilder& funcBuilder::arg(std::string_view type, std::string_view name){
    if (!m_isFuncStarted) return *this;

    m_funcArgs += std::string(type) + " " + std::string(name) + ", ";
    m_argCount++;

    return *this;
}

funcBuilder& funcBuilder::commitAll(){
    if (m_isFuncStarted)
        endFunc();

    return *this;
}