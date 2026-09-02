#include "mswlua/ffi/scan_headers_legacy.hpp"

#include <filesystem>
#include <fstream>
#include <unordered_set>

#include <lo_utils/term.h>

namespace fs = std::filesystem;
std::unordered_set<fs::path> viewedFiles;


std::string buildCDefFile(const fs::path& filePath, std::string_view apiMacroName){
    termMsg("Building CDEF part from file..\n", "CDEF_PARSE");
    std::string result;
    std::ifstream file(filePath);
    if (!file.is_open()){
        termMsg("Cant open file; skip","CDEF_PARSE", COLOR_RED);
        return result;
    }
    if (viewedFiles.contains(filePath)){
        termMsg("This part has already been scanned; skip\n", "CDEF_PARSE");
        return "";
    }
    viewedFiles.insert(filePath);

    std::string fileContent = std::string((std::istreambuf_iterator<char>(file)),
                                           std::istreambuf_iterator<char>());

    // "Incl" is a short name for "include"
    size_t inclStartPos = fileContent.find("#include");
    while (inclStartPos != std::string::npos){
        size_t includeEndPos   = inclStartPos + 8;
        // Type position is a position of char "<" or '"' after "#include"
        size_t inclContetnStartPos  = fileContent.find_first_not_of(" \t", includeEndPos);

        if (inclContetnStartPos != std::string::npos && fileContent[inclContetnStartPos] == '"'){
            size_t inclContetnEndPos = fileContent.find('"', inclContetnStartPos + 1);
            if (inclContetnEndPos != std::string::npos){
                std::string inclContent = fileContent.substr(
                    inclContetnStartPos + 1, inclContetnEndPos - inclContetnStartPos - 1);
                auto inclPath = filePath.parent_path() / inclContent;
                result += buildCDefFile(inclPath, apiMacroName);
            }
        }
        inclStartPos = fileContent.find("#include", inclStartPos + 1);
    }

    size_t macroPos   = fileContent.find(apiMacroName);
    while (macroPos != std::string::npos){
        size_t lnStartPos = fileContent.rfind('\n', macroPos);
        if (lnStartPos == std::string::npos)
            lnStartPos = 0;
        else
            lnStartPos += 1;

        size_t lnEndPos   = fileContent.find (';' , macroPos);
        lnEndPos++; // Needed to capture the ";" char
        std::string func = fileContent.substr(lnStartPos, lnEndPos - lnStartPos);

        size_t funcMacroStart = func.find(apiMacroName);
        func = func.erase(funcMacroStart, apiMacroName.size());
        result += func + '\n';

        macroPos = fileContent.find(apiMacroName, lnEndPos + 1);
    }

    return result;
}

std::string buildCDefStr(const fs::path& includePath, std::string_view apiMacroName){
    std::string result;
    if (!fs::exists(includePath)){
        termMsg("Path doesnt exist", "CDEF_PARSE", COLOR_RED);
        return result;
    }

    if (apiMacroName == DEFLT_API_MACRO)
        termMsg("The export macro (API) was not specified as the second argument in "
                 "the \"buildCDefStr\" function; using the default", "CDEF_PARSE", COLOR_YELLOW);

    for (const auto& filePath : fs::recursive_directory_iterator(includePath)){
        auto ext = filePath.path().extension();
        if (fs::is_regular_file(filePath.path()) && (ext == ".h" || ext == ".hpp")){
            auto funcsStr = buildCDefFile(filePath, apiMacroName) + '\n';
            result += funcsStr;
            termMsg(funcsStr.c_str(), "CDEF_PARSE");
        }
    }
    return result;
}