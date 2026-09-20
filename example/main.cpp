#include "mswlua.hpp"

#include "mswlua/ffi/build_func_cdef.hpp"
#include "mswlua/ffi/build_struct_cdef.hpp"

int main(){
    luaState state;
    state.openLibs(BaseLuaLib);

    // structBuilder cdefStructs;
    // cdefStructs
    // .createStruct("vec3")
    //     .var("float", "x")
    //     .var("float", "y")
    //     .var("float", "z")
    // .createStruct("rgba_c")
    //     .var("char", "r")
    //     .var("char", "g")
    //     .var("char", "b")
    //     .var("char", "a")
    // .commitAll();
    //
    // printf("%s", cdefStructs.getCDefContent().c_str());

    funcBuilder funcStructs;
    funcStructs
    .createFunc("foo")
        .path("api")
        .returnType("void")
        .arg("float", "x")
        .arg("float", "y")
        .arg("float", "z")
    .createFunc("foosttt")
        .returnType("void")
    .commitAll();

    printf("%s", funcStructs.getCDefContent().c_str());
    printf("%s", funcStructs.getBindContent().c_str());
    return 0;
}