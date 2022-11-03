#pragma once
#include "CComponent.h"

class CObject;

class CRigidBody :
    public CComponent
{
public:
    CObject*        m_pOwner;
    Vec2            m_vForce;       // 크기, 방향
    Vec2            m_vAccel;       // 가속도
    Vec2            m_vAccelA;      // 추가 가속도
    Vec2            m_vVelocity;    // 속도 ( 크기 : 속력, 방향 )
    Vec2            m_vMaxVelocity; // 최대속도

    float           m_fMass;        // 질량
    float           m_fFricCoeff;   // 마찰 계수

    // F = M * A;
    // V += A * DT

public:
    virtual void Component_update();
    virtual void Component_render(HDC _dc) {};

public:
    void AddForce(Vec2 _vF) { m_vForce += _vF; }
    void SetMass(float _fMass) { m_fMass = _fMass; }
    float GetMass() { return m_fMass; }
    float GetSpeed() { return m_vVelocity.Length(); }
    Vec2 GetVelocity() { return m_vVelocity; }

    void SetVelocity(Vec2 _v) { m_vVelocity = _v; }
    void AddVelocity(Vec2 _v) { m_vVelocity += _v; }
    void SetMaxVelocity(Vec2 _v) { m_vMaxVelocity = _v; }
    void SetAccelAlpha(Vec2 _vAccel) { m_vAccelA = _vAccel; }

    CLONE(CRigidBody);

private:
    void Move();
   
public:
    CRigidBody();
    ~CRigidBody();

    friend class CObject;

};

