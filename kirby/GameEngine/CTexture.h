#pragma once
#include "CRes.h"

class CTexture :
    public CRes
{
private:
    HDC         m_dc;          // ���� ���۸��� ��Ʈ��
    HBITMAP     m_hBit;        // ���� ���۸��� DC
    BITMAP      m_bitInfo;     // ������ ��Ʈ�� ����

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

