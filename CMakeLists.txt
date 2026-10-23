cmake_minimum_required(VERSION 4.1)
project(MSWLua LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
option(NO_DL_COPY "Disable auto-copy of dynamic lua lib" OFF)


# === My UtilsLib from FetchContent ===
if(NOT TARGET LolohUtilsPack AND NOT TARGET LolohUtilsPack_cxx)
    add_subdirectory(lib/LoUtils)
endif()


# === LuaJIT ===
add_library(LuaJIT_lib INTERFACE)
target_include_directories(LuaJIT_lib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/lib/luajit2/include")

if(WIN32)
    target_link_libraries(LuaJIT_lib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/lib/luajit2/win64/lua51.lib")
else()
    target_link_libraries(LuaJIT_lib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/lib/luajit2/lin64/lua51.so")
endif()


# === MSWLua Wrapper ===
add_library(MSWLua_lib STATIC
        # INCLUDE
        include/mswlua/funcCall/funcCall.hpp
        include/mswlua/ffi/build_struct_cdef.hpp
        include/mswlua/ffi/build_func_cdef.hpp
        include/mswlua/ffi/cdef_common.hpp
        include/mswlua/c_api/regVal_funcs.hpp
        include/mswlua/common/defines.hpp
        include/mswlua/c_api/getVal_funcs.hpp
        include/mswlua/c_api/doScript_funcs.hpp
        include/mswlua/c_api/report_funcs.hpp
        include/mswlua/c_api/openLib_funcs.hpp
        include/mswlua/c_api/init.hpp
        include/mswlua/c_api/path_funcs.hpp
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
        src/c_api/openLib_funcs.cpp
        src/c_api/path_funcs/find_by_path.cpp
)

target_include_directories(MSWLua_lib
        PUBLIC
        include

        PRIVATE
        src
)

target_link_libraries(MSWLua_lib
        PUBLIC
        LolohUtilsPack_cxx
        LuaJIT_lib
)


# === Example with CXX ===
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_executable(MSWLua_example
            example/main.cpp
    )
    target_link_libraries(MSWLua_example PRIVATE LolohUtilsPack_cxx MSWLua_lib)

    if(UNIX AND NOT APPLE)
        target_link_options(MSWLua_example PRIVATE "-Wl,-rpath,$ORIGIN")
    endif()
endif()