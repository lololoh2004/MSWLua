#include <lo_utils/c11/term/term_sys_wrap.h>
#include <lo_utils/cxx_wrap/term.hpp>

#include "mswlua.hpp"

#include "mswlua/ffi/build_func_cdef.hpp"
#include "mswlua/ffi/build_struct_cdef.hpp"
#include "mswlua/funcCall/funcCall.hpp"

#define PI 3.14

void debug_func(int intStd){
    term::msg(intStd, "LUA_SCRIPT", COLOR_CYAN);
}

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
    .createFunc("debug_func")
        .cPtr(reinterpret_cast<void*>(debug_func))
        .returnType("void")
        .arg("int", "intStd")
    .commitAll();

    std::string totalCDef =
        std::string("local ffi = require(\"ffi\")\n") +
        "ffi.cdef[[\n" +
        funcStructs.getCDefContent() +
        "]]\n" +
        funcStructs.getBindContent();

    printf("%s", totalCDef.c_str());
    state.doScriptStr(totalCDef);

    state.doScriptStr("debug_func(800)");
    state.doScriptPath("./example/lua/autorun.lua");

    auto printNumCall = funcCall(state.getRawState(), "api.print_val");
    // lfor(105){
    //     printNumCall.arg(1).exec();
    // }

    return 0;
}