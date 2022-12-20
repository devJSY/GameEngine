#pragma once
#include "CObject.h"

struct tMonInfo
{
    float   fSpeed;       // 속도    
    float   fHP;          // 체력
    float   fRecogRange;  // 인지 범위
    float   fAttRange;    // 공격 범위
    float   fAtt;         // 공격력
};

class AI;

class CMonster :
    public CObject
{
private:
    tMonInfo    m_tInfo;
    AI*         m_pAI;


public:
    virtual void update();
    virtual void render(HDC _dc);
    virtual void start();

    virtual void OnCollision(CCollider* _pOther) {};
    virtual void OnCollisionEnter(CCollider* _pOther) {};
    virtual void OnCollisionExit(CCollider* _pOther) {};

    CLONE(CMonster);

public:
    CMonster();
    virtual ~CMonster();
};

