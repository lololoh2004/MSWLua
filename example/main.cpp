#include "lo_utils/term.h"

#include "mswlua.hpp"
#include "mswlua/ffi/scan_headers_legacy.hpp"
#include <filesystem>

namespace fs = std::filesystem;

void runFolder(const fs::path& path, luaState& state){
    for (const auto& entry : fs::directory_iterator(path)){
        if (entry.is_regular_file()){
            state.doScript(entry.path().string(), ScriptSrc::FilePath);
        }
    }
}
void scanAndRun(luaState& state){
    fs::path luaPath =
        fs::current_path() / "example" / "lua";

    runFolder(luaPath / "autorun", state);
    runFolder(luaPath / "autorun/sv", state);
    runFolder(luaPath / "autorun/cl", state);
}

int main(){
    termSetupEnv();
    termMsg("Hello World!", "MAIN_C", COLOR_GRAY);

    luaState state;
    state.openLibs(mswlua::lib::base);

    state.doScript(R"(print("Hello from internal init script!"))", ScriptSrc::RawText);
    scanAndRun(state);

    //buildCDefStr("./example", "TEST_API");

    termWait();
    return 0;
}