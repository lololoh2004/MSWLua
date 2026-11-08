#include "mswlua/log_hook.hpp"

#include <cstdarg>
#include <cstdio>
#include <string>


void defltMSWLuaHook(std::string_view text, const char* entry){
    printf("[%s] : %.*s", entry, static_cast<int>(text.size()), text.data());
}

void MSWLuaLog(const char* entry, const char* fmt, ...){
    if (!curLogHook) return;

    va_list args;

    va_start(args, fmt);
    int size = vsnprintf(nullptr, 0, fmt, args);
    va_end(args);
    if (size <= 0) return;

    std::string buf;

    va_start(args, fmt);
    buf.resize(size + 1);
    vsnprintf(buf.data(), buf.size(), fmt, args);
    va_end(args);

    curLogHook(std::string_view(buf.c_str(), size), entry);
}
