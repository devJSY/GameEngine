#pragma once

#include "CComponent.h"

class CTexture;
class CAnimation;

class CAnimator :
    public CComponent
{
private:
    map<wstring, CAnimation*>   m_mapAnim;  // ��� Animation
    CAnimation*                 m_pCurAnim; // ���� Animation
    bool                        m_bRepeat;  // �ݺ� ��� ����
    CTexture*                   m_pTex;     // ���� ������� �ؽ���

public:
    void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT
        , Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT iFrameCount);
    void LoadAnimation(const wstring& _strRelativePath);
    CAnimation* FindAnimation(const wstring& _strName);
    void Play(const wstring& _strName, bool _bRepeat);

    virtual void Component_update();
    virtual void Component_render(HDC _dc);

public:
    CLONE(CAnimator);

public:
    CAnimator();
    CAnimator(const CAnimator& _origin);
    ~CAnimator();

    friend class CObject;
};
