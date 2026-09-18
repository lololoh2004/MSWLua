#include "mswlua/ffi/build_func_cdef.hpp"


funcBuilder& funcBuilder::createFunc(std::string_view name, void* directPtr){


    return *this;
}

funcBuilder& funcBuilder::returnType(std::string_view type){


    return *this;
}

funcBuilder& funcBuilder::arg(std::string_view type, std::string_view name){


    return *this;
}

funcBuilder& funcBuilder::commitAll(){


    return *this;
}