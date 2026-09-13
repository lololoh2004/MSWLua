#pragma once

typedef enum {
    NoCDefStarted = 0,
    CDefHasStarted,
} cdefStateEnum ;
typedef enum {
    ObjectNotStarted = 0,
    ObjectStarted,
    ObjectEnded
} curObjectStateEnum;

inline void createCDefStart(std::string& str, cdefStateEnum& cdefState){
    if (cdefState == CDefHasStarted) return;

    str += "ffi.cdef[[\n";
    cdefState = CDefHasStarted;
}
