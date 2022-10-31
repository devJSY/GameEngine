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
    int             m_iDir; // 플레이어 방향 정보
    int             m_iPrevDir;
    PLAYER_STATE    m_eCurState; // 현재 상태
    PLAYER_STATE    m_ePreveState; // 이전 상태

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
    void update_state();        // 상태 체크
    void update_move();         // 이동 적용
    void update_animation();    // 애니메이션 설정
    void update_gravity();      // 중력 적용

    CLONE(Kirby);

public:
    Kirby();
    virtual ~Kirby();
};

