#pragma once

class CTexture;

enum class CAM_EFFECT
{
    FADE_IN,
    FADE_OUT,
    NONE,
};

struct tCamEffect
{
    CAM_EFFECT	eEffect;
    float		fDuration;
    float		fCurTime;
};

class CCamera :
    public CRoot
{
    SINGLE(CCamera);

private:
    Vec2             m_vLookAt;
    Vec2             m_vPrevLookAt;
    Vec2             m_vCurLookAt;

    CObject*         m_pTargetObj;
    Vec2             m_vDiff;

    float             m_fTime;
    float             m_fSpeed;
    float             m_fAccTime;

    list<tCamEffect>  m_listCamEffect;
    CTexture*         m_pVeilTex;

public:
    void init();
    void update();
    void render(HDC _dc);   

    void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
    void ReleaseTarget() { m_pTargetObj = nullptr; }

    void SetLookAt(Vec2 _vLook)
    {
        m_vLookAt = _vLook;
        float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length(); // 이전 위치부터 설정한 위치까지의 거리값
        m_fSpeed = fMoveDist / m_fTime;
        m_fAccTime = 0.f;
    }

    // 카메라와 반대로 이동해야함으로 -
    Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }
    Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }
    Vec2 GetLookAt() { return m_vCurLookAt; }

public:
    void fadeIn(float _fDuration)
    {
        tCamEffect ef = {};
        ef.eEffect = CAM_EFFECT::FADE_IN;
        ef.fDuration = _fDuration;
        ef.fCurTime = 0.f;

        m_listCamEffect.push_back(ef);
    }

    void fadeOut(float _fDuration)
    {
        tCamEffect ef = {};
        ef.eEffect = CAM_EFFECT::FADE_OUT;
        ef.fDuration = _fDuration;
        ef.fCurTime = 0.f;

        m_listCamEffect.push_back(ef);
    }

private:
    void CalDiff();
};

