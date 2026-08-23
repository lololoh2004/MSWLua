#pragma once

#include <string>
#include <string_view>
#include <filesystem>
#include <vector>


std::string buildCDefStr(std::filesystem::path path, std::vector<std::filesystem::path> firstFilePaths);
