#pragma once
#include "CRoot.h"

class CObject :
    public CRoot
{
private:
    Vec2        vPos;
    Vec2        vScale;
    wstring     m_strName;

    bool        m_bAlive; // Dead üũ

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    void SetPos(Vec2 _vPos) { vPos = _vPos; }
    Vec2 GetPos() { return vPos; }

    void SetScale(Vec2 _vScale) { vScale = _vScale; }
    Vec2 GetScale()  { return vScale; }

    void SetName(const wstring& _strName) { m_strName = _strName; }
    wstring& GetName() { return m_strName; }

    bool IsDead() { return !m_bAlive; }

private:
    void SetDead() { m_bAlive = false; }

    friend class CEventMgr;

public:
    CObject();
    ~CObject();
};

