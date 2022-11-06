#include "global.h"
#include "Kirby.h"

#include "CCore.h"
#include "CCollider.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CGravity.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CColliderMgr.h"

Kirby::Kirby()
	: m_iDir(1)
	, m_iPrevDir(m_iDir)
	, m_eCurState(KIRBY_STATE::IDLE)
	, m_eStockState(KIRBY_STATE::IDLE)
	, m_fAccTime(0.f)
{	
	// ================
	// Collider Create
	// ================ 
	CreateComponents(Component_TYPE::Collider);
	// = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"Texture\\Player1.bmp");
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link.0.bmp");


	// ================
	// Animator Create
	// ================ 
	CreateComponents(Component_TYPE::Animator);
	CAnimator* pAnimator = (CAnimator*)GetComponents(Component_TYPE::Animator);
	pAnimator->SetIgnoreRGB({ 72, 104, 112 });

	pAnimator->LoadAnimation(L"animation\\Kirby\\IDLE\\IDLE_Left.anim");
	pAnimator->LoadAnimation(L"animation\\Kirby\\IDLE\\IDLE_Right.anim");

	pAnimator->LoadAnimation(L"animation\\Kirby\\JUMP\\JUMP_Left.anim");
	pAnimator->LoadAnimation(L"animation\\Kirby\\JUMP\\JUMP_Right.anim");

	pAnimator->LoadAnimation(L"animation\\Kirby\\RUN\\RUN_Left.anim");
	pAnimator->LoadAnimation(L"animation\\Kirby\\RUN\\RUN_Right.anim");

	pAnimator->LoadAnimation(L"animation\\Kirby\\WALK\\WALK_Left.anim");
	pAnimator->LoadAnimation(L"animation\\Kirby\\WALK\\WALK_Right.anim");

	pAnimator->Play(L"IDLE_Right", true, false);

	// ================
	// Rigidbody Create
	// ================ 
	CreateComponents(Component_TYPE::RigidBody);


	// ================
	// Gravity Create
	// ================ 
	CreateComponents(Component_TYPE::Gravity);
}

Kirby::~Kirby()
{
}

void Kirby::update()
{
	CObject::update();
	update_state();
	update_move();
	update_animation();
	update_gravity();

	if (KEY_TAP(KEY::ENTER))
	{
		SetPos(Vec2(640.f, 384.f));
	}
}

void Kirby::render(HDC _dc)
{
	// 텍스쳐 렌더링
	/*int iWidth = m_pTex->Width();
	int iHeight = m_pTex->Height();

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	
	TransparentBlt(_dc
		, int(vPos.x - (float)(iWidth / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));*/

	Component_render(_dc);
}

void Kirby::update_state()
{
	CRigidBody* pRigid = (CRigidBody*)GetComponents(Component_TYPE::RigidBody);

	// 입력 체크
	if (KEY_TAP(KEY::RIGHT))
	{
		m_iDir = (UINT)KIRBY_DIR::RIGHT;
	}

	if (KEY_TAP(KEY::LEFT))
	{
		m_iDir = (UINT)KIRBY_DIR::LEFT;
	}

	// 예외처리 키가 눌린상태에서 반대쪽키가 떼졌다면 눌려있는 키로 방향설정
	if (KEY_HOLD(KEY::RIGHT) || KEY_HOLD(KEY::LEFT))
	{
		// HOLD 중이지 않은 반대키의 AWAY여부를 확인하여 방향 설정
		if (KEY_AWAY(KEY::RIGHT))
		{
			m_iDir = (UINT)KIRBY_DIR::LEFT;
		}
		else if (KEY_AWAY(KEY::LEFT))
		{
			m_iDir = (UINT)KIRBY_DIR::RIGHT;
		}
	}

	switch (m_eCurState)
	{
	case KIRBY_STATE::IDLE:
	{
		State_Execute();

		if (KEY_HOLD(KEY::RIGHT) || KEY_HOLD(KEY::LEFT))
		{
			State_Exit();
			m_eCurState = KIRBY_STATE::WALK;
			State_Enter();
		}

		if (KEY_TAP(KEY::SPACE) || (pRigid->GetVelocity().y != 0.f))
		{
			State_Exit();
			m_eStockState = m_eCurState;
			m_eCurState = KIRBY_STATE::JUMP;
			State_Enter();
		}
	}
	break;

	case KIRBY_STATE::WALK:
	{
		State_Execute();

		m_fAccTime += fDT;

		// 동일한 키입력이 2번되었을때 RUN상태로 변환
		if ((KEY_TAP(KEY::RIGHT) || KEY_TAP(KEY::LEFT)) && m_iPrevDir == m_iDir)
		{
			State_Exit();
			m_eCurState = KIRBY_STATE::RUN;
			State_Enter();
			m_fAccTime = 0.f;
		}

		// 추가입력 시간 확보
		if (m_fAccTime > 0.3f)
		{
			if (!(KEY_HOLD(KEY::LEFT) || KEY_HOLD(KEY::RIGHT)))
			{
				State_Exit();
				m_eCurState = KIRBY_STATE::IDLE;
				State_Enter();
				m_fAccTime = 0.f;
			}
		}

		if (KEY_TAP(KEY::SPACE) || (pRigid->GetVelocity().y != 0.f))
		{
			State_Exit();
			m_eStockState = KIRBY_STATE::IDLE; // 설정 시간 딜레이 제거를 위해서 IDLE상태로 변경
			m_eCurState = KIRBY_STATE::JUMP;
			State_Enter();
			m_fAccTime = 0.f;
		}
	}
	break;

	case KIRBY_STATE::RUN:
	{
		State_Execute();

		// 키입력이 없을경우 상태변경
		if (!((KEY_HOLD(KEY::RIGHT)) || (KEY_HOLD(KEY::LEFT))))
		{
			State_Exit();
			m_eCurState = KIRBY_STATE::IDLE;
			State_Enter();
		}

		if (KEY_TAP(KEY::SPACE) || (pRigid->GetVelocity().y != 0.f))
		{
			State_Exit();
			m_eStockState = m_eCurState;
			m_eCurState = KIRBY_STATE::JUMP;
			State_Enter();
		}
	}
	break;

	case KIRBY_STATE::JUMP:
	{
		State_Execute();

		if (pRigid->GetVelocity().y == 0.f && ((CGravity*)GetComponents(Component_TYPE::Gravity))->IsGround())
		{
			State_Exit();
			m_eCurState = m_eStockState;
			State_Enter();
		}
	}
	break;

	case KIRBY_STATE::DEAD:
		break;
	}

	// 이전 상태정보 저장
	m_iPrevDir = m_iDir;	
}

void Kirby::update_move()
{
	CRigidBody* pRigid = (CRigidBody*)GetComponents(Component_TYPE::RigidBody);


	switch (m_eCurState)
	{
	case KIRBY_STATE::IDLE:
	{
	}
	break;

	case KIRBY_STATE::WALK:
	{
		if ((UINT)KIRBY_DIR::RIGHT == m_iDir)
		{
			if (KEY_HOLD(KEY::RIGHT))
			{
				pRigid->SetVelocity(Vec2(100.f, pRigid->GetVelocity().y));
			}
		}
		else if ((UINT)KIRBY_DIR::LEFT == m_iDir)
		{
			if (KEY_HOLD(KEY::LEFT))
			{
				pRigid->SetVelocity(Vec2(-100.f, pRigid->GetVelocity().y));
			}
		}
	}
	break;

	case KIRBY_STATE::RUN:
	{
		if ((UINT)KIRBY_DIR::RIGHT == m_iDir)
		{
			if (KEY_HOLD(KEY::RIGHT))
			{
				pRigid->SetVelocity(Vec2(300.f, pRigid->GetVelocity().y));
			}
		}
		else if ((UINT)KIRBY_DIR::LEFT == m_iDir)
		{
			if (KEY_HOLD(KEY::LEFT))
			{
				pRigid->SetVelocity(Vec2(-300.f, pRigid->GetVelocity().y));
			}
		}
	}
	break;

	case KIRBY_STATE::JUMP:
	{
		if ((UINT)KIRBY_DIR::RIGHT == m_iDir)
		{
			if (KEY_HOLD(KEY::RIGHT))
			{
				pRigid->SetVelocity(Vec2(100.f, pRigid->GetVelocity().y));
			}
		}
		else if ((UINT)KIRBY_DIR::LEFT == m_iDir)
		{
			if (KEY_HOLD(KEY::LEFT))
			{
				pRigid->SetVelocity(Vec2(-100.f, pRigid->GetVelocity().y));
			}
		}
	}
	break;

	case KIRBY_STATE::DEAD:
		break;
	}
}

void Kirby::update_animation()
{
	CAnimator* pAnimator = (CAnimator*)GetComponents(Component_TYPE::Animator);

	switch (m_eCurState)
	{
	case KIRBY_STATE::IDLE:
	{
		if ((UINT)KIRBY_DIR::LEFT == m_iDir)
		{
			pAnimator->Play(L"IDLE_Left", true, false);
		}
		else
		{
			pAnimator->Play(L"IDLE_Right", true, false);
		}
	}
	break;

	case KIRBY_STATE::WALK:
	{
		if ((UINT)KIRBY_DIR::LEFT == m_iDir)
		{
			pAnimator->Play(L"WALK_Left", true, false);
		}
		else
		{
			pAnimator->Play(L"WALK_Right", true, false);
		}
	}

		break;

	case KIRBY_STATE::RUN:
	{
		if ((UINT)KIRBY_DIR::LEFT == m_iDir)
		{
			pAnimator->Play(L"RUN_Left", true, false);
		}
		else
		{
			pAnimator->Play(L"RUN_Right", true, false);
		}
	}

		break;

	case KIRBY_STATE::JUMP:
	{
		if ((UINT)KIRBY_DIR::LEFT == m_iDir)
		{
			pAnimator->Play(L"JUMP_Left", true, false);
		}
		else
		{
			pAnimator->Play(L"JUMP_Right", true, false);
		}
	}
	break;

	case KIRBY_STATE::DEAD:
		break;
	}
}

void Kirby::update_gravity()
{
	switch (m_eCurState)
	{
	case KIRBY_STATE::IDLE:
		break;
	case KIRBY_STATE::WALK:
		break;
	case KIRBY_STATE::RUN:
		break;
	case KIRBY_STATE::JUMP:
		break;
	case KIRBY_STATE::DEAD:
		break;
	default:
		break;
	}
}

void Kirby::State_Enter()
{
	CRigidBody* pRigid = (CRigidBody*)GetComponents(Component_TYPE::RigidBody);

	switch (m_eCurState)
	{
	case KIRBY_STATE::IDLE:
		break;
	case KIRBY_STATE::WALK:
	{
		if ((UINT)KIRBY_DIR::RIGHT == m_iDir)
		{
			pRigid->SetVelocity(Vec2(100.f, pRigid->GetVelocity().y));
		}
		else if ((UINT)KIRBY_DIR::LEFT == m_iDir)
		{
			pRigid->SetVelocity(Vec2(-100.f, pRigid->GetVelocity().y));
		}
	}
	break;
	case KIRBY_STATE::RUN:
	{
		if ((UINT)KIRBY_DIR::RIGHT == m_iDir)
		{
			pRigid->SetVelocity(Vec2(200.f, pRigid->GetVelocity().y));
		}
		else if ((UINT)KIRBY_DIR::LEFT == m_iDir)
		{
			pRigid->SetVelocity(Vec2(-200.f, pRigid->GetVelocity().y));
		}
	}
	break;
	case KIRBY_STATE::JUMP:
	{
		// 점프키를 누러 진입한 경우 추가 속도
		if (KEY_TAP(KEY::SPACE))
		{
			pRigid->SetVelocity(Vec2(pRigid->GetVelocity().x, -500.f));
		}	
	}
	break;
	case KIRBY_STATE::DEAD:
		break;
	default:
		break;
	}
}

void Kirby::State_Execute()
{
	CRigidBody* pRigid = (CRigidBody*)GetComponents(Component_TYPE::RigidBody);

	switch (m_eCurState)
	{
	case KIRBY_STATE::IDLE:
		break;
	case KIRBY_STATE::WALK:
		break;
	case KIRBY_STATE::RUN:
		break;
	case KIRBY_STATE::JUMP:
	{
		if (KEY_TAP(KEY::SPACE))
		{
			pRigid->SetVelocity(Vec2(0.f, -300.f));
		}		
	}
		break;
	case KIRBY_STATE::DEAD:
		break;
	default:
		break;
	}
}

void Kirby::State_Exit()
{
	CRigidBody* pRigid = (CRigidBody*)GetComponents(Component_TYPE::RigidBody);

	switch (m_eCurState)
	{
	case KIRBY_STATE::IDLE:
		break;
	case KIRBY_STATE::WALK:
		break;
	case KIRBY_STATE::RUN:
		break;
	case KIRBY_STATE::JUMP:
		break;
	case KIRBY_STATE::DEAD:
		break;
	default:
		break;
	}

}


void Kirby::OnCollision(CCollider* _pOther)
{
}

void Kirby::OnCollisionEnter(CCollider* _pOther)
{
}

void Kirby::OnCollisionExit(CCollider* _pOther)
{
}

void Kirby::start()
{
	CCollider* pCollider = ((CCollider*)GetComponents(Component_TYPE::Collider));
	pCollider->SetScale(Vec2(50.f, 50.f));
}