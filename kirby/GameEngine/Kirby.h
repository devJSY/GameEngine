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

enum class KIRBY_DIR
{
    RIGHT = 0,
    LEFT = 1,
};

class CTexture;

class Kirby :
    public CObject
{
    CTexture*       m_pTex;

    UINT            m_iDir;         // �÷��̾� ���� ���� 
    UINT            m_iPrevDir;     // �÷��̾� ���� ���� ����
    KIRBY_STATE     m_eCurState;    // ���� ����
    KIRBY_STATE     m_eStockState;  // ���� ����� ����

    float           m_fAccTime;     // Run Ű�Է� ������ �ð�
    float           m_fJumpTime;    // ü�� �ð� 

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

