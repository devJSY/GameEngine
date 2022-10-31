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
    map<wstring, CAnimation*>   m_mapAnim;  // ��� Animation
    CAnimation*                 m_pCurAnim; // ���� Animation
    bool                        m_bRepeat;  // �ݺ� ��� ����
    bool				        m_pRealRender;	// ���� ��ǥ, ������ ��ǥ ���� 0 �̸� ���� ��ǥ
    CTexture*                   m_pTex;     // ���� ������� �ؽ���
    IgnoreRGB		        	m_IgnoreRGB;	// �⺻�� ����Ÿ ����

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

