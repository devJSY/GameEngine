#pragma once
#include "CComponent.h"

class CCollider :
    public CComponent
{
private:
    static	UINT g_iNextID; // 정적 고유 ID 용 변수

    Vec2    m_vFinalPos;
    Vec2    m_vOffsetPos;
    Vec2    m_vScale;

    UINT    m_iID;
    int     m_iCol;

public:
   virtual void Component_update();
   virtual void Component_render(HDC _dc);

public:
    UINT GetID() { return m_iID; }

    Vec2 GetFinalPos() { return m_vFinalPos; }
    Vec2 GetOffsetPos() { return m_vOffsetPos; }
    Vec2 GetScale() { return m_vScale; }

    void SetOffsetPos(Vec2 _vOffsetPos) { m_vOffsetPos = _vOffsetPos; }
    void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

public:
    void OnCollision(CCollider* _pOther);
    void OnCollisionEnter(CCollider* _pOther);
    void OnCollisionExit(CCollider* _pOther);

    // = 삭제 
    CCollider& operator = (CCollider& _origin) = delete;

    CLONE(CCollider);

public:
    CCollider();
    CCollider(const CCollider& _origin);
    virtual ~CCollider();

};

