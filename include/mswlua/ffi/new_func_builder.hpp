#pragma once

#include <string>
#include <string_view>
#include <vector>


struct strSizeView{
public:
    strSizeView();

    strSizeView(size_t offset, size_t len)
     : offset(offset), len(len) {}

    [[nodiscard]] std::string_view toStrView(const std::string& strPool) const{
        if (len == 0) return {};
        return { strPool.data() + offset, len };
    }
private:
    size_t offset, len;
};

enum funcMangling{
    StandardC = 0,
    GNU_CXX
};

struct funcArg{
    strSizeView type, name;
};

class funcBuilder;



[[nodiscard]]
inline strSizeView appendToPool(std::string& strBuf, std::string_view text) {
    strBuf.append(text);
    size_t strSize = text.size();
    return {strBuf.size() - strSize, strSize};
}


class singleFuncCtx{
public:
    // TOMORROW ME : in the constructor u need a funcBuilder& and a way to store it
    // U can get &globalStrBuf from funcBuilder&
    // Just delete this shii
    singleFuncCtx(std::string_view name, std::string& globalStrBuf)
     : m_strBuf(globalStrBuf) {
        cName(name);
    }

    // C / CXX info
    singleFuncCtx& retrn(std::string_view type){
        m_funcCName = appendToPool(m_strBuf, type);
        return *this;
    }
    singleFuncCtx& cName(std::string_view name){
        m_funcCName = appendToPool(m_strBuf, name);
        return *this;
    }
    singleFuncCtx& arg(std::string_view type, std::string_view name){
        strSizeView typeStrView = appendToPool(m_strBuf, type);
        strSizeView nameStrView = appendToPool(m_strBuf, name);

        m_funcArgs.emplace_back(typeStrView, nameStrView);

        return *this;
    }
    // Lua info
    singleFuncCtx& luaName();

    funcBuilder& commitFunc();
private:
    std::string& m_strBuf;

    strSizeView m_funcReturn {0,0};
    strSizeView m_funcCName  {0,0};
    strSizeView m_funcLuaName{0,0};
    std::vector<funcArg> m_funcArgs;
};

class funcBuilder{
public:
    friend class singleFuncCtx;
    funcBuilder();
    ~funcBuilder() = default;

    // Ctx options
    funcBuilder& cxxNamespace(std::string_view ns){
        m_ns = appendToPool(m_strBuf, ns);
        return *this;
    }
    funcBuilder& luaPath(std::string_view path){
        m_ns = appendToPool(m_strBuf, path);
        return *this;
    }

    // TOMORROW ME : read text above
    // in class singleFuncCtx
    singleFuncCtx func(std::string_view cName){
        return {cName, m_strBuf};
    }

    std::string_view getCDefResult(){ return m_cdefResult; }
    std::string_view getBindResult(){ return m_bindResult; }
private:
    std::string m_strBuf;

    strSizeView m_ns;
    strSizeView m_luaPath;

    std::string m_cdefResult;
    std::string m_bindResult;
};