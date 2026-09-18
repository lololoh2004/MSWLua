#pragma once

#include <string>


inline std::string createCDefStart() { return "ffi.cdef [[\n"; }
inline std::string createCDefEnd()   { return "]]\n\n"; }

inline void createCDefStart(std::string& str) { str += createCDefStart(); }
inline void createCDefEnd(std::string& str)   { str += createCDefEnd(); }