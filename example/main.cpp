#include "lo_utils/term.h"

#include "mswlua.hpp"
#include <filesystem>

#include "mswlua/ffi/build_struct_cdef.hpp"

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
    state.openLibs(BaseLuaLib);

    structBuilder cdefStructs;
    cdefStructs.createStruct("Vector3")
        ->var("float", "x")
        ->var("float", "y")
        ->var("float", "z")
    ->commitStruct();

    cdefStructs.endBuilding();

    printf("%s", cdefStructs.getCDefContent().c_str());
    // termWait();
    return 0;
}