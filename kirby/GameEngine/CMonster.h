#pragma once
#include "CObject.h"

struct tMonInfo
{
    float   fSpeed;       // �ӵ�    
    float   fHP;          // ü��
    float   fRecogRange;  // ���� ����
    float   fAttRange;    // ���� ����
    float   fAtt;         // ���ݷ�
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

