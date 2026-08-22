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

    svState.doScript(R"(print("Hello from Lua!"))", ScriptSrc::RawText);

    termWait("stopped\n");
    return 0;
}
