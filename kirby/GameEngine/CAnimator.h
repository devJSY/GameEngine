#pragma once

#include "CComponent.h"

class CTexture;
class CAnimation;

struct IgnoreRGB
{
    BYTE R;
    BYTE G;
    BYTE B;
};


class CAnimator :
    public CComponent
{
private:
    map<wstring, CAnimation*>   m_mapAnim;  // 모든 Animation
    CAnimation*                 m_pCurAnim; // 현재 Animation
    bool                        m_bRepeat;  // 반복 재생 여부
    bool				        m_pRealRender;	// 실제 좌표, 렌더링 좌표 여부 0 이면 실제 좌표
    CTexture*                   m_pTex;     // 현재 사용중인 텍스쳐
    IgnoreRGB		        	m_IgnoreRGB;	// 기본값 마젠타 색상

public:
    void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT
        , Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT iFrameCount);
    void LoadAnimation(const wstring& _strRelativePath);
    CAnimation* FindAnimation(const wstring& _strName);
    void Play(const wstring& _strName, bool _bRepeat, bool _pRealRender);

    virtual void Component_update();
    virtual void Component_render(HDC _dc);

public:
    void SetIgnoreRGB(IgnoreRGB _IgnoreRGB) { m_IgnoreRGB = _IgnoreRGB; }
    IgnoreRGB GetIgnoreRGB() { return m_IgnoreRGB; }

public:
    CLONE(CAnimator);

public:
    CAnimator();
    CAnimator(const CAnimator& _origin);
    ~CAnimator();

    friend class CObject;
};

