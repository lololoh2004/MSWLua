cmake_minimum_required(VERSION 4.1)
project(MSWLua LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
option(NO_DL_COPY "Disable auto-copy of dynamic lua lib" OFF)


# === My UtilsLib from FetchContent ===
if(NOT TARGET LolohUtilsPack AND NOT TARGET LolohUtilsPack_cxx)
    include(FetchContent)
    FetchContent_Declare(
            LolohUtilsPack
            GIT_REPOSITORY "https://github.com/lololoh2004/LolohUtilsPack.git"
            GIT_TAG        main
    )
    FetchContent_MakeAvailable(LolohUtilsPack)
endif()


# === OpenResty LuaJIT 2 ===
add_library(LuaJIT_lib INTERFACE
        include/mswlua/c_api/path_funcs.hpp
        src/c_api/path_funcs/find_by_path.cpp
)

target_include_directories(LuaJIT_lib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/lib/luajit2/include")

if(WIN32)
    set(LUA_SHARED_FILE "${CMAKE_CURRENT_SOURCE_DIR}/lib/luajit2/win64/lua51.dll")
    target_link_libraries(LuaJIT_lib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/lib/luajit2/win64/lua51.lib")
else()
    set(LUA_SHARED_FILE "${CMAKE_CURRENT_SOURCE_DIR}/lib/luajit2/lin64/lua51.so")
    target_link_libraries(LuaJIT_lib INTERFACE "${LUA_SHARED_FILE}")
endif()


# === MSWLua Wrapper ===
file(GLOB_RECURSE WRAPPER_SOURCES "src/*.cpp" "src/*.hpp")
add_library(MSWLua_lib STATIC ${WRAPPER_SOURCES}
        # INCLUDE
        include/mswlua/funcCall/funcCall.hpp
        include/mswlua/ffi/build_struct_cdef.hpp
        include/mswlua/ffi/build_func_cdef.hpp
        include/mswlua/ffi/cdef_common.hpp
        # SOURCE
        src/luaState/init.cpp
        src/ffi/build_struct_cdef.cpp
        src/ffi/build_func_cdef.cpp
        src/c_api/regVal_funcs.cpp
        src/luaState/run_script.cpp
        src/c_api/report_funcs.cpp
        src/funcCall/base.cpp
        src/funcCall/exec.cpp
        src/c_api/getVal_funcs.cpp
        src/c_api/path_funcs/create_path.cpp
        include/mswlua/c_api/regVal_funcs.hpp
        include/mswlua/common/defines.hpp
        include/mswlua/c_api/getVal_funcs.hpp
        include/mswlua/c_api/doScript_funcs.hpp
        include/mswlua/c_api/report_funcs.hpp
        include/mswlua/c_api/openLib_funcs.hpp
        src/c_api/openLib_funcs.cpp
        include/mswlua/c_api/init.hpp
)

target_include_directories(MSWLua_lib PUBLIC
        src
        include
)

target_link_libraries(MSWLua_lib PUBLIC LolohUtilsPack_cxx LuaJIT_lib)


# === Example with CXX ===
add_executable(MSWLua_example
        example/main.cpp
)
target_link_libraries(MSWLua_example PRIVATE LolohUtilsPack_cxx MSWLua_lib)


# === Custom Cmds ===
if(NOT NO_DL_COPY)
    if(WIN32)
        add_custom_command(TARGET MSWLua_example POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${LUA_SHARED_FILE}"
                "$<TARGET_FILE_DIR:MSWLua_example>"
        )
    else()
        target_link_options(MSWLua_example PRIVATE "-Wl,-rpath,$ORIGIN")
        add_custom_command(TARGET MSWLua_example POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${LUA_SHARED_FILE}"
                "$<TARGET_FILE_DIR:MSWLua_example>"
        )
    endif()
endif()