#pragma once

// �浹ü���� ���� ID ������ union
union COLLIDER_ID
{
    struct {
        UINT iLeft_id;
        UINT iRight_id;
    };
    ULONGLONG ID;
};

struct COLLIDER_DIR
{
    bool LEFT = false;
    bool RIGHT = false;
    bool TOP = false;
    bool BOTTOM = false;
};

class CCollider;

class CColliderMgr :
    public CRoot
{
    SINGLE(CColliderMgr);

private:
    map<ULONGLONG, bool> m_mapColInfo; // �浹ü���� ���� ID ���� �� map

    UINT m_arrCheck[(UINT)GROUP_TYPE::END]; // �浹 üũ �� �迭

public:
    void update();
    void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
    void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }

    COLLIDER_DIR CollisionDIR(CCollider* _Check, CCollider* _Target);

private:
    void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
    bool IsCollision(CCollider* _eLeft, CCollider* _eRight);

};