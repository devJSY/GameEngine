#pragma once
#include "CObject.h"

enum class KIRBY_STATE
{
    IDLE,
    WALK,
    RUN,
    JUMP,
    DEAD,
};

class CTexture;

class Kirby :
    public CObject
{
    CTexture*      m_pTex;

    int            m_iDir;      // �÷��̾� ���� ���� 0 ���� / 1 ����
    KIRBY_STATE    m_eCurState; // ���� ����

    int             m_iDashTrig;
    float           m_fAccTime;

public:
    virtual void update();
    virtual void render(HDC _dc);
    virtual void start();

    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

public:
    void update_state();        // ���� üũ
    void update_move();         // �̵� ����
    void update_animation();    // �ִϸ��̼� ����
    void update_gravity();      // �߷� ����

    CLONE(Kirby);

public:
    Kirby();
    virtual ~Kirby();
};

