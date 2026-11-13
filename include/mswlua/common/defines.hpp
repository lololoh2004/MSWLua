#pragma once


#define FN_TO_PTR(fn) reinterpret_cast<void*>(fn)
#define setValDef(L, val) setVal(L, val, "")