cmake_minimum_required(VERSION 4.1)
project(MSWLua LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)


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
        include/mswlua/c_api/func_call.hpp
        include/mswlua/ffi/build_struct_cdef.hpp
        include/mswlua/ffi/build_func_cdef.hpp
        include/mswlua/c_api/set_to_table.hpp
        include/mswlua/common/defines.hpp
        include/mswlua/c_api/get_from_table.hpp
        include/mswlua/c_api/report_func.hpp.
        include/mswlua/c_api/open_libs.hpp
        include/mswlua/c_api/path_funcs.hpp
        # SOURCE
        src/lua_state_wrap/init.cpp
        src/ffi/build_struct_cdef.cpp
        src/ffi/build_func_cdef.cpp
        src/c_api/set_to_table.cpp
        src/c_api/report_func.cpp
        src/func_call/base.cpp
        src/func_call/exec.cpp
        src/c_api/get_from_table.cpp
        src/c_api/path_funcs/create_path.cpp
        src/c_api/open_libs.cpp
        src/c_api/path_funcs/find_by_path.cpp
        include/mswlua/log_hook.hpp
        src/log_hook.cpp
        include/mswlua/ffi/new_func_builder.hpp
        src/ffi/new_func_builder.cpp
        include/mswlua/c_api/run_str_script.hpp
        src/c_api/run_str_script/load.cpp
        src/c_api/run_str_script/push_overloads.cpp
        src/c_api/run_str_script/get_overloads.cpp
        include/mswlua/c_api/lua_state_wrap.hpp
)

target_include_directories(MSWLua_lib
        PUBLIC
        include

        PRIVATE
        src
)

target_link_libraries(MSWLua_lib
        PUBLIC
        LuaJIT_lib
)


# === Example with CXX ===
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_executable(MSWLua_example
            example/main.cpp
    )
    target_link_libraries(MSWLua_example PRIVATE MSWLua_lib)

    if(UNIX AND NOT APPLE)
        target_link_options(MSWLua_example PRIVATE "-Wl,-rpath,$ORIGIN")
    endif()
endif()