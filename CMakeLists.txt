cmake_minimum_required(VERSION 4.1)
project(MSWLua)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY         "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}")


add_library(dll_agent STATIC
        lib/dll_agent/src/lib_tools.cpp
        lib/dll_agent/src/log.cpp
        lib/dll_agent/src/reg_logic.cpp
)
target_include_directories(dll_agent PUBLIC lib/dll_agent/src)

add_executable(MSWLua
        src/main.cpp
)

target_link_libraries(MSWLua PRIVATE dll_agent)