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
{
	CreateComponents(Component_TYPE::Collider);
	// = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"Texture\\Player1.bmp");
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link.0.bmp");

	CreateComponents(Component_TYPE::Animator);
	CAnimator* pAnimator = (CAnimator*)GetComponents(Component_TYPE::Animator);

	//pAnimator->CreateAnimation(L"WALK_LEFT", m_pTex, Vec2(0.f, 325.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);
	//pAnimator->CreateAnimation(L"WALK_RIGHT", m_pTex, Vec2(0.f, 455.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.1f, 10);

	//pAnimator->CreateAnimation(L"IDLE_LEFT", m_pTex, Vec2(0.f, 65.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.3f, 3);
	//pAnimator->CreateAnimation(L"IDLE_RIGHT", m_pTex, Vec2(0.f, 195.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.3f, 3);


	//pAnimator->FindAnimation(L"WALK_LEFT")->Save(L"animation\\player_walk_left.anim");
	//pAnimator->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\player_walk_right.anim");

	//pAnimator->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\player_idle_left.anim");
	//pAnimator->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\player_idle_right.anim");	

	pAnimator->LoadAnimation(L"animation\\player_walk_left.anim");
	pAnimator->LoadAnimation(L"animation\\player_walk_right.anim");
	pAnimator->LoadAnimation(L"animation\\player_idle_left.anim");
	pAnimator->LoadAnimation(L"animation\\player_idle_right.anim");
	pAnimator->LoadAnimation(L"animation\\Test.anim");

	pAnimator->Play(L"Test", true);
}

Kirby::~Kirby()
{
}

void Kirby::update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::LEFT))
	{
		vPos.x -= 500 * fDT;
	}

	if (KEY_HOLD(KEY::RIGHT))
	{
		vPos.x += 500 * fDT;
	}

	if (KEY_HOLD(KEY::DOWN))
	{
		vPos.y += 500 * fDT;
	}

	if (KEY_HOLD(KEY::UP))
	{
		vPos.y -= 500 * fDT;
	}

	SetPos(vPos);
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

void Kirby::OnCollision(CCollider* _pOther)
{
}

void Kirby::OnCollisionEnter(CCollider* _pOther)
{
	if (L"CopyKirby" == GetName())
	{
		DeleteObject(this);
	}
}

void Kirby::OnCollisionExit(CCollider* _pOther)
{

}

void Kirby::start()
{
	CCollider* pCollider = ((CCollider*)GetComponents(Component_TYPE::Collider));
	pCollider->SetScale(Vec2(50.f, 50.f));
}