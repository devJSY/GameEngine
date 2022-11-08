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
    //CTexture*       m_pTex;

    UINT            m_iDir;         // 플레이어 방향 정보 
    UINT            m_iPrevDir;     // 플레이어 이전 방향 정보
    KIRBY_STATE     m_eCurState;    // 현재 상태
    KIRBY_STATE     m_eStockState;  // 상태 저장용 변수

    float           m_fAccTime;     // Run 키입력 딜레이 시간

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

public:
    void State_Enter();
    void State_Execute();
    void State_Exit();

    CLONE(Kirby);

public:
    Kirby();
    virtual ~Kirby();
};

