#pragma once

union COLLIDER_ID
{
    struct {
        UINT iLeft_id;
        UINT iRight_id;
    };
    ULONGLONG ID;
};

class CCollider;

class CColliderMgr :
    public CRoot
{
    SINGLE(CColliderMgr);

private:
    map<ULONGLONG, bool> m_mapColInfo; // �浹ü ID �� �浹 ����

    UINT m_arrCheck[(UINT)GROUP_TYPE::END]; // �浹 üũ �� �迭

public:
    void upadte();
    void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
    void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }

private:
    void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
    bool IsCollision(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);

};