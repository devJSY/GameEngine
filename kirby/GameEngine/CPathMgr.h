#pragma once
#include "CRoot.h"
class CPathMgr :
    public CRoot
{
    SINGLE(CPathMgr)
private:
    wchar_t m_szContentPath[256];

public:
    void init();

public:
    const wchar_t* GetContentPath() { return m_szContentPath; }
    wstring GetRelativePath(const wchar_t* _filepath);
};

