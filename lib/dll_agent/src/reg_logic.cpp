#include "dll_agent.hpp"

namespace dlib{

FARPROC reg_func_body(const char* name, const char* func_name){
    std::string full_name = std::string(name) + TYPE;

    DL_HANDLE h_inst = nullptr;
    auto it = all_libs.find(full_name);

    if (it == all_libs.end()){
        std::string path = "./" + full_name;
        h_inst = DL_OPEN(path.c_str());
        if (h_inst){
            all_libs[full_name] = h_inst;
        }
    } else {
        h_inst = it->second;
    }

    if (!h_inst){
        log("Could not load lib : ", full_name);
        return nullptr;
    }

    auto func_ptr = reinterpret_cast<FARPROC>(DL_GET_PTR(h_inst, func_name));
    if (!func_ptr){
        log("Could not locate the func : ", func_name);
        return nullptr;
    }

    return func_ptr;
}

}