#include <string>
#include "mswlua.hpp"

extern "C"{
// Utils
#include "common.h"
#include "term.h"
}

int main(){
    termSetupEnv();
    termMsgC("Hello World!\n", "MAIN_C", COLOR_GRAY);

    lua_State* svState = nullptr;
    lua_State* clState = nullptr;

    initLuaStates(&svState, &clState);

    if (svState && clState) {
        termMsgC("Both Lua states initialized successfully!\n", "MAIN_C", COLOR_GREEN);
    }

    return 0;
}
