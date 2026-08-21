#include "mswlua.hpp"

extern "C"{
#include "common.h"
#include "term.h"
}

#include <cstdio>
#include <string>

int main(){
    termSetupEnv();
    termMsgC("Hello World!\n", "MAIN_C", COLOR_GRAY);

    luaState svState;
    luaState clState;

    if (svState.getRawState() && clState.getRawState()) {
        termMsgC("Both Lua states initialized successfully!\n", "MAIN_C", COLOR_GREEN);
    }
    svState.openLibs(mswlua::lib::base);

    std::string returnVal;
    svState.runStrScript(R"(return "hell")", false, &returnVal);
    printf("returnVal = %s\n", returnVal.c_str());

    return 0;
}
