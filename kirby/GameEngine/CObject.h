#pragma once

#include "CCamera.h"

enum class Component_TYPE
{
    Collider,
    Animator,
    END,
};

class CComponent;
class CCollider;
class CAnimator;

class CObject :
    public CRoot
{
private:
    Vec2                 vPos;
    Vec2                 vScale;
    wstring              m_strName;

    CComponent*         arr_Components[(UINT)Component_TYPE::END];

    bool                m_bAlive; // Dead Check

public:
    virtual void update();
    virtual void Component_update() final;
    virtual void render(HDC _dc);
    virtual void Component_render(HDC _dc) final;
    virtual void start() = 0; // Scene Enter() Afert Call Func

    virtual void OnCollision(CCollider* _pOther) {};
    virtual void OnCollisionEnter(CCollider* _pOther) {};
    virtual void OnCollisionExit(CCollider* _pOther) {};

public:
    void SetPos(Vec2 _vPos) { vPos = _vPos; }
    Vec2 GetPos() { return vPos; }

    void SetScale(Vec2 _vScale) { vScale = _vScale; }
    Vec2 GetScale()  { return vScale; }

    void SetName(const wstring& _strName) { m_strName = _strName; }
    wstring& GetName() { return m_strName; }

    bool IsDead() { return !m_bAlive; }

public:
    void CreateComponents(Component_TYPE _etype);
    CComponent* GetComponents(Component_TYPE _etype);

public:
    virtual CObject* Clone() = 0;

private:
    void SetDead() { m_bAlive = false; }

    friend class CEventMgr;

public:
    CObject();
    CObject(const CObject& _origin);
    ~CObject();
};

