#ifdef _WIN32
#include <windows.h>
#endif


#include "mswlua/common/defines.hpp"
#include "mswlua/c_api/doScript_funcs.hpp"
#include "mswlua/c_api/getVal_funcs.hpp"
#include "mswlua/c_api/init.hpp"
#include "mswlua/c_api/openLib_funcs.hpp"
#include "mswlua/c_api/regVal_funcs.hpp"

#include "mswlua/ffi/build_func_cdef.hpp"
#include "mswlua/ffi/build_struct_cdef.hpp"
#include "mswlua/funcCall/funcCall.hpp"

// Small setup section
#ifdef _WIN32
#   define EXPORT_MACRO __declspec(dllexport)
#else
#   define EXPORT_MACRO __attribute__((visibility("default")))
#endif

#define PI 3.14

#define COLOR_DEFLT   "\033[38;2;192;192;192m"
#define COLOR_BLACK   "\033[38;2;0;0;0m"
#define COLOR_RED     "\033[38;2;255;0;0m"
#define COLOR_GREEN   "\033[38;2;0;255;0m"
#define COLOR_YELLOW  "\033[38;2;255;255;0m"
#define COLOR_BLUE    "\033[38;2;0;0;255m"
#define COLOR_MAGENTA "\033[38;2;255;0;255m"
#define COLOR_CYAN    "\033[38;2;0;255;255m"
#define COLOR_WHITE   "\033[38;2;255;255;255m"
#define COLOR_GRAY    "\033[38;2;128;128;128m"

void mvLine(int i = 1){
    for (int c = 0; c < i; ++c) {
        std::printf("");
    }
}


// Functions from examples
EXPORT_MACRO void debug_mangled_func(){
    printf(COLOR_CYAN "[LUA_SCRIPT] : MANGLE IS OOOOVER\n" COLOR_DEFLT);
}

void debug_func(int intVal){
    printf(COLOR_CYAN "[LUA_SCRIPT] : %i\n" COLOR_DEFLT, intVal);
}

// Main
int main(){
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (hOut != INVALID_HANDLE_VALUE && GetConsoleMode(hOut, &dwMode)) {
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }
#endif

    lua_State* state = getLuaState();
    openLibs(state, BaseLuaLib);


    mvLine(2);
    printf(COLOR_GREEN "[MAIN_CXX] : REG ( funcs & structs ) TEST\n" COLOR_DEFLT);

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
        .luaPath("debug")
        .cPtr(FN_TO_PTR(debug_func))
        .returnType("void")
        .arg("int", "intVal")
    .createFunc("debug_mangled_func")
        .mangling(GNU_CXX)
        .luaPath("debug")
        .returnType("void")
    .commitAll();

    std::string luaCDef =
        std::string("local ffi = require(\"ffi\")\n") +
        "ffi.cdef[[\n" +
        structBind.getCDefContent() +
        funcBind.getCDefContent() +
        "]]\n" +
        structBind.getBindContent() +
        funcBind.getBindContent();
    // std::string termCDef = std::format(
    //     "local ffi = require(\"ffi\")\n"
    //     COLOR_CYAN "ffi.cdef[[\n" COLOR_DEFLT
    //     "{}{}"
    //     COLOR_CYAN "]]\n" COLOR_DEFLT
    //     "{}{}",
    //     structBind.getCDefContent(), funcBind.getCDefContent(),
    //     structBind.getBindContent(), funcBind.getBindContent()
    // );

    mvLine();
    printf("%s", luaCDef.c_str());
    doScriptStr(state, luaCDef);


    mvLine();
    printf(COLOR_GREEN "[MAIN_CXX] : DO & CALL TEST\n" COLOR_DEFLT);
    doScriptStr(state, "debug.debug_mangled_func()");
    doScriptStr(state, "debug.func(800)");
    doScriptPath(state, "./example/lua/autorun.lua");

    auto printNumCall = funcCall(state, "api.print_val");
    printNumCall.arg(728).exec();


    mvLine();
    printf(COLOR_GREEN "[MAIN_CXX] : REG ( values & defines ) TEST\n" COLOR_DEFLT);

    regValDef(state, PI);
    regVal(state, 24, "debug.num.real_num");
    int testVal1_1;
    getVal(state, testVal1_1, "debug.num.real_num");
    printf("debug.num.real_num : %i\n", testVal1_1);


    mvLine();
    printf("[MAIN_CXX] : GETTER TEST");


    int testVal2_1 = 0;
    getVal(state, testVal2_1, "api.debug.val1.");
    printf("api.debug.val1. : %i\n", testVal2_1);

    float testVal2_2 = 0.0f;
    getVal(state, testVal2_2, "api.debug.val2");
    printf("api.debug.val2 : %f\n", testVal2_2);

    std::string testVal2_3;
    getVal(state, testVal2_3, "api.debug.dir.val3");
    printf("api.debug.dir.val3 : %s\n", testVal2_3.c_str());


    // RETURN 0 SECTION ( VERY DANGEROUS )
    return 0;
}