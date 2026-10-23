#include <lo_utils/cxx_wrap/term.hpp>

#include "mswlua/common/defines.hpp"
#include "mswlua/c_api/doScript_funcs.hpp"
#include "mswlua/c_api/getVal_funcs.hpp"
#include "mswlua/c_api/init.hpp"
#include "mswlua/c_api/openLib_funcs.hpp"
#include "mswlua/c_api/regVal_funcs.hpp"

#include "mswlua/ffi/build_func_cdef.hpp"
#include "mswlua/ffi/build_struct_cdef.hpp"
#include "mswlua/funcCall/funcCall.hpp"

#define PI 3.14

void debug_func(int intVal){
    term::msg(intVal, "LUA_SCRIPT", COLOR_CYAN);
}

int main(){
    term::setup();

    lua_State* state = getLuaState();
    openLibs(state, BaseLuaLib);


    // REG ( funcs & structs ) TEST
    term::mvLine();
    term::mvLine();
    term::msg("REG ( funcs & structs ) TEST", "MAIN_CXX", COLOR_GREEN);

    structBuilder structBind;
    structBind
    .createStruct("vec3")
        .var("float", "x")
        .var("float", "y")
        .var("float", "z")
    // .createStruct("rgba_c")
    //     .var("char", "r")
    //     .var("char", "g")
    //     .var("char", "b")
    //     .var("char", "a")
    .commitAll();
    //
    // printf("%s", cdefStructs.getCDefContent().c_str());

    funcBuilder funcBind;
    funcBind
    .createFunc("func")
        .path("debug")
        .cPtr(FN_TO_PTR(debug_func))
        .returnType("void")
        .arg("int", "intVal")
    .commitAll();

    std::string totalCDef =
        std::string("local ffi = require(\"ffi\")\n") +
        "ffi.cdef[[\n" +
        structBind.getCDefContent() +
        funcBind.getCDefContent() +
        "]]\n" +
        structBind.getBindContent() +
        funcBind.getBindContent();

    term::mvLine();
    printf("%s", totalCDef.c_str());
    doScriptStr(state, totalCDef);


    // DO & CALL TEST
    term::mvLine();
    term::msg("DO & CALL TEST", "MAIN_CXX", COLOR_GREEN);
    doScriptStr(state, "debug.func(800)");
    doScriptPath(state, "./example/lua/autorun.lua");

    auto printNumCall = funcCall(state, "api.print_val");
    printNumCall.arg(728).exec();


    // REG ( values & defines ) TEST
    term::mvLine();
    term::msg("REG ( values & defines ) TEST", "MAIN_CXX", COLOR_GREEN);

    regValDef(state, PI);
    regVal(state, 24, "debug.num.real_num");
    int testVal1_1;
    getVal(state, testVal1_1, "debug.num.real_num");
    term::msg(testVal1_1, "debug.num.real_num", COLOR_WHITE);


    // GETTER TEST
    term::mvLine();
    term::msg("GETTER TEST", "MAIN_CXX", COLOR_GREEN);

    int testVal2_1 = 0;
    getVal(state, testVal2_1, "api.debug.val1.");
    term::msg(testVal2_1, "api.debug.val1.", COLOR_WHITE);

    float testVal2_2 = 0.0f;
    getVal(state, testVal2_2, "api.debug.val2");
    term::msg(testVal2_2, "api.debug.val2", COLOR_WHITE);

    std::string testVal2_3;
    getVal(state, testVal2_3, "api.debug.dir.val3");
    term::msg(testVal2_3.c_str(), "api.debug.dir.val3", COLOR_WHITE);


    // RETURN 0 SECTION ( VERY DANGEROUS )
    return 0;
}