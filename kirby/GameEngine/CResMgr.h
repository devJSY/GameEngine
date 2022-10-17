#pragma once

class CRes;
class CTexture;

class CResMgr :
    public CRoot
{
    SINGLE(CResMgr);
private:
    map<wstring, CRes*>  m_mapTex;

public:
    CTexture* LoadTexture(const wstring& _strkey, const wstring& _RelativePath);
    CTexture* FindTexture(const wstring& _strkey);
    CTexture* CreateTexture(const wstring& _strkey, UINT _iWidth, UINT _iHeight); // Alpha Blend 

};

