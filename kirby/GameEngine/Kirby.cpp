#include "global.h"
#include "Kirby.h"

#include "CCore.h"
#include "CCollider.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"

Kirby::Kirby()
	: m_iDir(1)
	, m_iPrevDir(m_iDir)
	, m_eCurState(KIRBY_STATE::IDLE)
	, m_eStockState(KIRBY_STATE::IDLE)
	, m_fAccTime(0.f)
	, m_fJumpTime(0.f)

{
	CreateComponents(Component_TYPE::Collider);
	// = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"Texture\\Player1.bmp");
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link.0.bmp");

	CreateComponents(Component_TYPE::Animator);
	CAnimator* pAnimator = (CAnimator*)GetComponents(Component_TYPE::Animator);
	pAnimator->SetIgnoreRGB({ 72, 104, 112 });

	//pAnimator->CreateAnimation(L"WALK_LEFT", m_pTex, Vec2(0.f, 325.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);
	//pAnimator->CreateAnimation(L"WALK_RIGHT", m_pTex, Vec2(0.f, 455.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);

	//pAnimator->CreateAnimation(L"IDLE_LEFT", m_pTex, Vec2(0.f, 65.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.3f, 3);
	//pAnimator->CreateAnimation(L"IDLE_RIGHT", m_pTex, Vec2(0.f, 195.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.3f, 3);


	//pAnimator->FindAnimation(L"WALK_LEFT")->Save(L"animation\\player_walk_left.anim");
	//pAnimator->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\player_walk_right.anim");

	//pAnimator->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\player_idle_left.anim");
	//pAnimator->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\player_idle_right.anim");	

	pAnimator->LoadAnimation(L"animation\\Kirby\\IDLE\\IDLE_Left.anim");
	pAnimator->LoadAnimation(L"animation\\Kirby\\IDLE\\IDLE_Right.anim");

	pAnimator->LoadAnimation(L"animation\\Kirby\\JUMP\\JUMP_Left.anim");
	pAnimator->LoadAnimation(L"animation\\Kirby\\JUMP\\JUMP_Right.anim");

	pAnimator->LoadAnimation(L"animation\\Kirby\\RUN\\RUN_Left.anim");
	pAnimator->LoadAnimation(L"animation\\Kirby\\RUN\\RUN_Right.anim");

	pAnimator->LoadAnimation(L"animation\\Kirby\\WALK\\WALK_Left.anim");
	pAnimator->LoadAnimation(L"animation\\Kirby\\WALK\\WALK_Right.anim");

	pAnimator->Play(L"IDLE_Right", true, false);
}

Kirby::~Kirby()
{
}

void Kirby::update()
{
	update_state();
	update_move();
	update_animation();
	update_gravity();

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
		if ((UINT)KIRBY_DIR::RIGHT == m_iDir)
		{
			if (KEY_HOLD(KEY::RIGHT) || KEY_TAP(KEY::RIGHT))
			{
				m_eCurState = KIRBY_STATE::WALK;
			}
		}
		else if ((UINT)KIRBY_DIR::LEFT == m_iDir)
		{
			if (KEY_HOLD(KEY::LEFT) || KEY_TAP(KEY::LEFT))
			{
				m_eCurState = KIRBY_STATE::WALK;
			}
		}

		if (KEY_TAP(KEY::SPACE))
		{
			m_eStockState = m_eCurState;
			m_eCurState = KIRBY_STATE::JUMP;
		}
	}
	break;

	case KIRBY_STATE::WALK:
	{		
		m_fAccTime += fDT;

		if ((UINT)KIRBY_DIR::RIGHT == m_iDir)
		{
			if (KEY_TAP(KEY::RIGHT) && (UINT)KIRBY_DIR::RIGHT == m_iPrevDir)
			{
				m_eCurState = KIRBY_STATE::RUN;
				m_fAccTime = 0.f;
			}		
		}
		else if ((UINT)KIRBY_DIR::LEFT == m_iDir)
		{
			if (KEY_TAP(KEY::LEFT) && (UINT)KIRBY_DIR::LEFT == m_iPrevDir)
			{
				m_eCurState = KIRBY_STATE::RUN;
				m_fAccTime = 0.f;
			}
		}		

		// 추가입력 시간 확보
		if (m_fAccTime > 0.3f)
		{
			if (!(KEY_HOLD(KEY::LEFT) || KEY_HOLD(KEY::RIGHT)))
			{
				m_eCurState = KIRBY_STATE::IDLE;
				m_fAccTime = 0.f;
			}
		}

		if (KEY_TAP(KEY::SPACE))
		{
			m_eStockState = KIRBY_STATE::IDLE; // 설정 시간 딜레이 제거를 위해서 IDLE상태로 변경
			m_eCurState = KIRBY_STATE::JUMP;
			m_fAccTime = 0.f;
		}
	}
	break;

	case KIRBY_STATE::RUN:
	{
		if ((UINT)KIRBY_DIR::RIGHT == m_iDir)
		{
			// 키입력이없을경우 상태변경
			if (!(KEY_HOLD(KEY::RIGHT)))
			{
				// 예외처리 방향 바꿀때에는 RUN상태 유지
				if ((KEY_HOLD(KEY::LEFT)))
				{
					m_eCurState = KIRBY_STATE::RUN;
				}
				else
				{
					m_eCurState = KIRBY_STATE::IDLE;
				}				
			}
		}
		else if ((UINT)KIRBY_DIR::LEFT == m_iDir)
		{
			// 키입력이없을경우 상태변경
			if (!(KEY_HOLD(KEY::LEFT)))
			{
				// 예외처리 방향 바꿀때에는 RUN상태 유지
				if ((KEY_HOLD(KEY::RIGHT)))
				{
					m_eCurState = KIRBY_STATE::RUN;
				}
				else
				{
					m_eCurState = KIRBY_STATE::IDLE;
				}
			}
		}

		if (KEY_TAP(KEY::SPACE))
		{
			m_eStockState = m_eCurState;
			m_eCurState = KIRBY_STATE::JUMP;
		}
	}
	break;

	case KIRBY_STATE::JUMP:
	{
		m_fJumpTime += fDT;

		if (m_fJumpTime > 1.f)
		{
			m_fJumpTime = 0.f;
			m_eCurState = m_eStockState;
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
	Vec2 vPos = GetPos();


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
				vPos.x += 200 * fDT;
			}
		}
		else if ((UINT)KIRBY_DIR::LEFT == m_iDir)
		{
			if (KEY_HOLD(KEY::LEFT))
			{
				vPos.x -= 200 * fDT;
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
				vPos.x += 500 * fDT;
			}
		}
		else if ((UINT)KIRBY_DIR::LEFT == m_iDir)
		{
			if (KEY_HOLD(KEY::LEFT))
			{
				vPos.x -= 500 * fDT;
			}
		}
	}
	break;

	case KIRBY_STATE::JUMP:
	{
		//vPos.y -= 50 * fDT;
	}
	break;

	case KIRBY_STATE::DEAD:
		break;
	}


	SetPos(vPos);
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