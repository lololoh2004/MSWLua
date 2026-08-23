#include "mswlua/ffi/scan_src_headers.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <lo_utils/term.h>

namespace fs = std::filesystem;

std::string buildCDefPart(fs::path path){
    std::string result;
    std::ifstream file(path);
    if (!file.is_open()){
        termMsgC("Cant open file; skip","CDEF_PARSE",COLOR_RED);
        return result;
    }
    std::string fileContent = std::string(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());

    std::string activeApiMacro =
#ifdef _WIN32
    "__declspec(dllexport)";
#else
    "__attribute__((visibility("default")))";
#endif
    size_t firstMacroUsagePos = fileContent.find(activeApiMacro);
    size_t lineStartPos = fileContent.rfind('\n', firstMacroUsagePos);
    size_t defineStartPos = fileContent.rfind("#define", firstMacroUsagePos);
    if (defineStartPos != std::string::npos && defineStartPos >= lineStartPos){
        size_t defineEndPos  = defineStartPos + 7;

        size_t macroStartPos = fileContent.find_first_not_of(" \t", defineEndPos);
        size_t macroEndPos   = fileContent.find_last_not_of (" \t", firstMacroUsagePos - 1);
        size_t macroLength   = (macroEndPos - macroStartPos) + 1;

        activeApiMacro = fileContent.substr(macroStartPos, macroLength);
    }

    // дорогой я из будущего
    // мне кароче лень доделывать парсинг функций
    // сделаешь завтра как только проснешься
    // код полное говно так что развяжи его потом на несколько мелких функций
    // чмоооошнииик

    // кстати готовый алгоритм снизу ваще не работает и не будет
    std::stringstream fileStream(fileContent);
    std::string curLine;

    while (std::getline(fileStream, curLine)){
        if (curLine.find(activeApiMacro) != std::string::npos){
            size_t funcEndPos = curLine.find(';');
            if (funcEndPos != std::string::npos){
                result += curLine.substr(0, curLine.size() - funcEndPos);
            }
        }

    }

    // if (firstApiUsagePos == std::string::npos)


    return result;
}

std::string buildCDefStr(fs::path path, std::vector<fs::path> firstFilePaths){
    std::string result;
    for (const auto& filePath : firstFilePaths){
        if (fs::is_regular_file(filePath)){
            buildCDefPart(filePath);
            continue;
        }
        termMsgC(
            "Unable to parse the important file; the path must point to a file",
            "CDEF_PARSE",
            COLOR_RED);
    }
    return result;
}