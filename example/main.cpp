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
        .cPtr(FN_TO_PTR(debug_func))
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
    printNumCall.arg(728).exec();
    // lfor(105){
    //     printNumCall.arg(1).exec();
    // }


    // REG TEST
    state.regValDef(PI);

    state.regVal();


    // GETTER TEST
    int testVal1 = 0;
    state.getVal(testVal1, "api.debug.val1.");
    term::msg(testVal1, "api.debug.val1.", COLOR_WHITE);

    float testVal2 = 0.0f;
    state.getVal(testVal2, "api.debug.val2");
    term::msg(testVal2, "api.debug.val2", COLOR_WHITE);

    std::string testVal3;
    state.getVal(testVal3, "api.debug.dir.val3");
    term::msg(testVal3.c_str(), "api.debug.dir.val3", COLOR_WHITE);


    // RETURN 0 SECTION ( VERY DANGEROUS )
    return 0;
}