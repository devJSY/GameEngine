#pragma once
#include "CObject.h"

enum class PLAYER_STATE
{
    IDLE,
    WALK,
    RUN,
    JUMP,
    DEAD,
};

enum class PLAYER_ATTACK_STATE
{
    NORMAL_ATT_1,
    NORMAL_ATT_2,
    NORMAL_ATT_3,
    NORMAL_ATT_4,
    SKILL_ATT_1,
};

class CTexture;

class Kirby :
    public CObject
{
    CTexture*       m_pTex;
    int             m_iDir; // �÷��̾� ���� ����
    int             m_iPrevDir;
    PLAYER_STATE    m_eCurState; // ���� ����
    PLAYER_STATE    m_ePreveState; // ���� ����

    int             m_iState;
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

