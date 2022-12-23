#include "global.h"
#include "CMonster.h"

#include "CCore.h"
#include "CCollider.h"
#include "CTexture.h"
#include "AI.h"
#include "CAnimation.h"
#include "CAnimator.h"

#include "SelectGDI.h"
#include "CResMgr.h"

CMonster::CMonster()
	: m_tInfo{}
{
	// ================
	// Collider Create
	// ================ 
	CreateComponents(Component_TYPE::Collider);
	((CCollider*)GetComponents(Component_TYPE::Collider))->SetOffsetPos(Vec2(5.f, 30.f));

	// ================
	// Animator Create
	// ================ 
	CreateComponents(Component_TYPE::Animator);
	CAnimator* pAnimator = (CAnimator*)GetComponents(Component_TYPE::Animator);
	pAnimator->SetIgnoreRGB({ 0, 72, 80 });

	pAnimator->LoadAnimation(L"animation\\Monster\\NormalMonster\\Grizzo\\RUN_Left.anim");
	pAnimator->LoadAnimation(L"animation\\Monster\\NormalMonster\\Grizzo\\RUN_Right.anim");

	pAnimator->Play(L"RUN_Right", true, false);

	// ================
	// Rigidbody Create
	// ================ 
	CreateComponents(Component_TYPE::RigidBody);


	// ================
	// Gravity Create
	// ================ 
	CreateComponents(Component_TYPE::Gravity);
}

CMonster::~CMonster()
{	
	if (nullptr != m_pAI)
		delete m_pAI;
}

void CMonster::update()
{
	if (nullptr != m_pAI)
		m_pAI->update();
}

void CMonster::render(HDC _dc)
{
	Component_render(_dc);
	
	SelectGDI select(_dc, PEN_TYPE::RED);
	SelectGDI select1(_dc, BRUSH_TYPE::RED);

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	Ellipse(_dc, (int)vPos.x - 3, (int)vPos.y - 3, (int)vPos.x + 3, (int)vPos.y + 3);
}

void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
}

void CMonster::start()
{
	CCollider* pCollider = ((CCollider*)GetComponents(Component_TYPE::Collider));
	pCollider->SetScale(GetScale());
}