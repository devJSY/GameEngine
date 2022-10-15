#pragma once
#include "CRoot.h"

class CComponent;
class CCollider;

class CObject :
    public CRoot
{
private:
    Vec2                 vPos;
    Vec2                 vScale;
    wstring              m_strName;

    map<wstring, CComponent*>  m_Component;

    bool        m_bAlive; // Dead 체크

public:
    virtual void update();
    virtual void Component_update() final;
    virtual void render(HDC _dc);
    virtual void Component_render(HDC _dc) final;

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
    void CreateCollider();
    CCollider* GetCollider();

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

