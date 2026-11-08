#pragma once

#include <string_view>

typedef void (*MSWLuaLogHook)(std::string_view text, const char* entry);

void defltMSWLuaHook(std::string_view text, const char* entry);
inline MSWLuaLogHook curLogHook = defltMSWLuaHook;

inline void setMSWLuaLogHook(MSWLuaLogHook hookFunc){
    curLogHook = hookFunc;
}

#ifdef __GNUC__
__attribute__((format(printf, 2, 3)))
#endif
void MSWLuaLog(const char* entry, const char* fmt, ...);