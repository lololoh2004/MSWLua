#pragma once


#define FN_TO_PTR(fn) reinterpret_cast<void*>(fn)
#define regValDef(L, val) regVal(L, val, "")