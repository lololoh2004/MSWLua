#include "mswlua/ffi/build_func_cdef.hpp"
#include <format>

#define TAB_LEN 4


void funcBuilder::endFunc_ByCDef(){
    // Just tab, return type, name and '('
    m_cdefResult += std::format(
    "{:>{}}{} {} ( ",
        "", TAB_LEN,
        m_funcReturn, m_funcName
    );

    // Adding args.
    if (m_argCount > 0){
        if (m_funcArgs.length() >= 2)
            m_funcArgs.erase(m_funcArgs.length() - 2);
        m_cdefResult.append(m_funcArgs);
    } else {
        m_cdefResult.append("void");
    }
    m_cdefResult.append(" );\n");

    // TablePath to func.
    if (m_funcPath.empty()){
        m_funcPath.append("_G.");
    } else {
        if (m_funcPath.back() != '.')
            m_funcPath.append(".");
    }
    m_bindResult += std::format(
        "{0}{1} = ffi.C.{1}\n",
        m_funcPath, m_funcName
    );
}
void funcBuilder::endFunc_ByCast(){
    // Just tab, return type, name and '('
    m_cdefResult += std::format(
    "{:>{}}typedef {} ( *{} )( ",
        "", TAB_LEN,
        m_funcReturn, m_funcName
    );

    // Adding args.
    if (m_argCount > 0){
        if (m_funcArgs.length() >= 2)
            m_funcArgs.erase(m_funcArgs.length() - 2);
        m_cdefResult.append(m_funcArgs);
    } else {
        m_cdefResult.append("void");
    }
    m_cdefResult.append(" );\n");

    // Func. address cast
    m_bindResult += std::format(
        "local __{0} = ffi.cast( '{0}', 0x{1:X}ULL )\n",
        m_funcName,
        reinterpret_cast<uintptr_t>(m_funcPtr)
    );

    // TablePath to func.
    if (m_funcPath.empty()){
        m_funcPath.append("_G.");
    } else {
        if (m_funcPath.back() != '.')
            m_funcPath.append(".");
    }
    // Cast part
    m_bindResult += std::format(
        "{0}{1} = __{1}\n",
        m_funcPath, m_funcName
    );
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
    m_funcPtr = directPtr;
    m_argCount = 0;
    m_funcReturn = "void";
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

    m_funcArgs.append(type)
        .append(" ")
        .append(name)
        .append(", ");

    m_argCount++;

    return *this;
}

funcBuilder& funcBuilder::commitAll(){
    if (m_isFuncStarted)
        endFunc();

    return *this;
}