#pragma once
#include "CRes.h"

class CTexture :
    public CRes
{
private:
    HDC         m_dc;          // 이중 버퍼링용 비트맵
    HBITMAP     m_hBit;        // 이중 버퍼링용 DC
    BITMAP      m_bitInfo;     // 생성한 비트맵 정보

public:
    void Load(const wstring& _strRelativePath);
    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }
    HDC GetDC() { return m_dc; }

public:
    void Create(UINT _iWidth, UINT _iHeight);  // Alpha Blend 

private:
    CTexture();
    virtual ~CTexture();

    friend class CResMgr;
};

