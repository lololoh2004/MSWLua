#include "dll_agent.hpp"

#include <iostream>
#include <ranges>

namespace dlib{

void log(const char* msg, const char* arg){
#ifdef DLL_AGENT_LOGS
    std::cout << msg << arg << std::endl;
#endif
}
void log(const char* msg, std::string_view arg){
#ifdef DLL_AGENT_LOGS
    std::cout << msg << arg << std::endl;
#endif
}

void print_all_libs(){
    for (const auto& key : all_libs | std::views::keys){
        std::cout << key << std::endl;
    }
}

}
