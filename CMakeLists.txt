cmake_minimum_required(VERSION 4.1)
project(MSWLua LANGUAGES C CXX)

# Shit
cmake_policy(SET CMP0169 OLD)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY         "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}")


# === My UtilsLib from FetchContent ===
include(FetchContent)
FetchContent_Declare(
        LolohUtilsPack_raw
        GIT_REPOSITORY "https://github.com/lololoh2004/LolohUtilsPack.git"
        GIT_TAG        main
)
FetchContent_Populate(LolohUtilsPack_raw)
set(Utils_SRC_DIR "${lolohutilspack_raw_SOURCE_DIR}")


# === Utils Auto Build ===
file(GLOB_RECURSE UTILS_SOURCES
        "${Utils_SRC_DIR}/src/*.c"
        "${Utils_SRC_DIR}/src/*.h"
)
add_library(LolohUtils STATIC ${UTILS_SOURCES})
target_include_directories(LolohUtils PUBLIC
        "${Utils_SRC_DIR}/src"
        "${Utils_SRC_DIR}/src/_include"
)


# === OpenResty LuaJIT 2 ===
add_library(LuaJIT_lib INTERFACE)

target_include_directories(LuaJIT_lib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/lib/luajit2/include")

if(WIN32)
    set(LUA_SHARED_FILE "${CMAKE_CURRENT_SOURCE_DIR}/lib/luajit2/win64/lua51.dll")
    target_link_libraries(LuaJIT_lib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/lib/luajit2/win64/lua51.dll.a")
else()
    set(LUA_SHARED_FILE "${CMAKE_CURRENT_SOURCE_DIR}/lib/luajit2/lin64/libluajit-5.1.so.2")
    target_link_libraries(LuaJIT_lib INTERFACE "${LUA_SHARED_FILE}")
endif()


# === MSWLua Wrapper ===
file(GLOB_RECURSE WRAPPER_SOURCES "src/*.cpp" "src/*.hpp")
add_library(MSWLua_lib STATIC ${WRAPPER_SOURCES}
        src/_include/init_lua.hpp
        src/_include/state_class.hpp
        src/classes/state_init.cpp)

target_include_directories(MSWLua_lib PUBLIC src)

target_link_libraries(MSWLua_lib PUBLIC LolohUtils LuaJIT_lib)


# === Example with CXX ===
add_executable(MSWLua_example
        example/main.cpp
)
target_link_libraries(MSWLua_example PRIVATE MSWLua_lib)


# === Custom Cmds ===
target_link_options(MSWLua_example PRIVATE "-Wl,-rpath,$ORIGIN")
add_custom_command(TARGET MSWLua_example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${LUA_SHARED_FILE}"
        "$<TARGET_FILE_DIR:MSWLua_example>"
)