#include "lo_utils/cxx_wrap/term.hpp"

#include "mswlua.hpp"
#include <filesystem>

#include "mswlua/ffi/build_func_cdef.hpp"
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
    term::msg("Hello World!", "MAIN_C", COLOR_GRAY);

    luaState state;
    state.openLibs(BaseLuaLib);

    structBuilder cdefStructs;
    cdefStructs
    .createStruct("vec3")
        .var("float", "x")
        .var("float", "y")
        .var("float", "z")
    .createStruct("rgba_c")
        .var("char", "r")
        .var("char", "g")
        .var("char", "b")
        .var("char", "a")
    .commitAll();

    printf("%s", cdefStructs.getCDefContent().c_str());

    // funcBuilder funcStructs;
    // funcStructs
    // .createFunc("foo")
    //     ->returnVal("void")
    //     ->arg("float", "x")
    //     ->arg("float", "y")
    //     ->arg("float", "z")
    // ->createFunc("foosttt")
    // ->commitFunc()
    //     ->returnVal("void")
    //     ->arg("int", "x")
    // ->commitFunc();
    //
    // funcStructs.endBuilding();
    //
    // printf("%s", funcStructs.getCDefContent().c_str());
    return 0;
}