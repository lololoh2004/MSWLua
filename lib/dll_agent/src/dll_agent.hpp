#pragma once

// CHANGE THIS IF LOGS AREN'T NEEDED
#ifndef DLL_AGENT_LOGS
#define DLL_AGENT_LOGS
#endif

#if defined (_WIN32)
    #include <windows.h>
    #define DL_HANDLE HINSTANCE
    #define DL_OPEN(path) LoadLibraryA(path)
    #define DL_GET_PTR(handle, name) GetProcAddress(handle, name)
    #define TYPE ".dll"
#else
    #include <dlfcn.h>
    #define DL_HANDLE void*
    #define DL_OPEN(path) dlopen(path, RTLD_LAZY)
    #define DL_GET_PTR(handle, name) dlsym(handle, name)
    #define TYPE ".so"
    using FARPROC = void(*)();
#endif

#include <unordered_map>
#include <string_view>
#include <string>

namespace dlib{

inline std::unordered_map<std::string, DL_HANDLE> all_libs;

void log(const char* msg, const char* arg);
void log(const char* msg, std::string_view arg);

FARPROC reg_func_body(const char* name, const char* func_name);

template <typename T>
int reg_func(const char* name, const char* func_name, T& base_ptr){
    auto func_ptr = reg_func_body(name, func_name);
    if (!func_ptr) return EXIT_FAILURE;

    base_ptr = reinterpret_cast<T>(func_ptr);
    log("Registered function : ", func_name);

    return EXIT_SUCCESS;
}

void print_all_libs();
void free_all();

}