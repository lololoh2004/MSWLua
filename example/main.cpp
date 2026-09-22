#include <lo_utils/c11/term.h>

#include "mswlua.hpp"

#include "mswlua/ffi/build_func_cdef.hpp"
#include "mswlua/ffi/build_struct_cdef.hpp"

#define PI 3.14

int main(){
    termSetupEnv();

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
    // .createFunc("foo")
    //     .path("api")
    //     .returnType("void")
    //     .arg("float", "x")
    //     .arg("float", "y")
    //     .arg("float", "z")
    // .createFunc("foosttt")
    //     .returnType("void")
    .createFunc("Beep")
        .returnType("int")
        .arg("unsigned long", "dwFreq")
        .arg("unsigned long", "dwDuration")
    .commitAll();

    std::string totalCDef =
        std::string("local ffi = require(\"ffi\")\n") +
        "ffi.cdef[[\n" +
        funcStructs.getCDefContent() +
        "]]\n" +
        funcStructs.getBindContent();

    printf("%s", totalCDef.c_str());
    state.doScriptStr(totalCDef);
    state.doScriptStr("Beep(800, 500)");

    state.regValDefine(PI);
    state.doScriptStr("print(PI)");

    state.doScriptPath("./example/lua/autorun.lua");
    state.doFunc("api.debug.func");

    state.addTempFunc("print_val").addTempArg(1).callFunc();

    return 0;
}