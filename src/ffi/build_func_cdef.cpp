#include "mswlua/ffi/build_func_cdef.hpp"

#include <cassert>
#include <format>

constexpr std::string_view TAB = "    ";


void funcBuilder::_addArgs(){
    if (m_argCount > 0){
        if (m_funcArgs.length() >= 2)
            m_funcArgs.resize(m_funcArgs.length() - 2);

        m_cdefResult.append(m_funcArgs);
    } else {
        m_cdefResult.append("void");
    }
    m_cdefResult.append(" );\n");
}

std::string funcBuilder::_getLuaPath(){
    if (m_funcPath.empty()){
        return "_G.";
    }
    if (m_funcPath.back() != '.'){
        return m_funcPath + ".";
    }
    return m_funcPath;
}

std::string funcBuilder::_getMangledName(){
    std::string mangled = std::format("_Z{}{}", m_funcName.length(), m_funcName);

    if (m_funcMangledArgs.empty()){
        mangled.append("v");
    } else{
        mangled.append(m_funcMangledArgs);
    }
    return mangled;

}
std::string funcBuilder::_getMangledType(std::string_view type) const{
    // Only GNU
    if (type == "int")         return "i";
    if (type == "float")       return "f";
    if (type == "double")      return "d";
    if (type == "char")        return "c";
    if (type == "void")        return "v";
    if (type == "char*")       return "Pc";
    if (type == "const char*") return "PKc";

    return "";
}

void funcBuilder::_endFuncCDef(){
    switch (m_mangling){
        case GNU_CXX:
            m_cdefResult += std::format(
                "{}{} {} ( ",
                TAB, m_funcReturn, _getMangledName()
            );
            // Adding args.
            _addArgs();

            m_bindResult += std::format(
                "{0}{1} = ffi.C.{2}\n",
                _getLuaPath(), m_funcName, _getMangledName()
            );
            break;
        default:
            m_cdefResult += std::format(
                "{}{} {} ( ",
                TAB, m_funcReturn, m_funcName
            );
            // Adding args.
            _addArgs();

            m_bindResult += std::format(
                "{0}{1} = ffi.C.{1}\n",
                _getLuaPath(), m_funcName
            );
            break;
    }
}
void funcBuilder::_endFuncCast(){
    m_cdefResult += std::format(
    "{}typedef {} ( *{} )( ",
        TAB,
        m_funcReturn, m_funcName
    );

    // Adding args.
    _addArgs();

    // Func. address cast
    m_bindResult += std::format(
        "local __{0} = ffi.cast( '{0}', 0x{1:X}ULL )\n",
        m_funcName,
        reinterpret_cast<uintptr_t>(m_funcPtr)
    );

    // Cast part
    m_bindResult += std::format(
        "{0}{1} = __{1}\n",
        _getLuaPath(), m_funcName
    );
}

void funcBuilder::endFunc(){
    if (m_funcPtr != nullptr){
        _endFuncCast();
    } else {
        _endFuncCDef();
    }
    // Reset class buf.
    m_funcMangledArgs.clear();
    m_funcArgs.clear();
    m_funcReturn.clear();
    m_funcPtr = nullptr;
    m_argCount = 0;
    m_isFuncStarted = false;
}

funcBuilder& funcBuilder::createFunc(std::string_view name){
    if (m_isFuncStarted)
        endFunc();

    m_funcName = name;
    m_argCount = 0;
    m_funcReturn = "void";
    m_isFuncStarted = true;

    return *this;
}
funcBuilder& funcBuilder::returnType(std::string_view type){
    assert(m_isFuncStarted && "MSWLUA GEN ERROR : returnType() call before createFunc()!");

    m_funcReturn = type;


    return *this;
}
funcBuilder& funcBuilder::arg(std::string_view type, std::string_view name){
    assert(m_isFuncStarted && "MSWLUA GEN ERROR : arg() call before createFunc()!");

    m_funcArgs.append(type)
        .append(" ")
        .append(name)
        .append(", ");
    m_argCount++;

    if (m_mangling != StandardC){
        m_funcMangledArgs.append(_getMangledType(type));
    }

    return *this;
}

funcBuilder& funcBuilder::commitAll(){
    if (m_isFuncStarted){
        endFunc();
    }

    return *this;
}