#pragma once

#include <string>
#include <string_view>
#include <filesystem>

#ifdef _WIN32
#define DEFLT_API_MACRO "__declspec(dllexport)"
#else
#define DEFLT_API_MACRO R"(__attribute__((visibility("default"))))"
#endif

std::string buildCDefStr(const std::filesystem::path& includePath, std::string_view apiMacroName = DEFLT_API_MACRO);
