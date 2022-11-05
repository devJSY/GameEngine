#include "global.h"
#include "CGround.h"

#include "CObject.h"
#include "CComponent.h"
#include "CCollider.h"
#include "CGravity.h"
#include "CRigidBody.h"

#include "CColliderMgr.h"


CGround::CGround()
{
	CreateComponents(Component_TYPE::Collider);
}

CGround::~CGround()
{
}

void CGround::start()
{
	((CCollider*)GetComponents(Component_TYPE::Collider))->SetScale(Vec2(GetScale()));
}

void CGround::update()
{
}

void CGround::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	Rectangle(_dc
		, int(vRenderPos.x - vScale.x / 2.f)
		, int(vRenderPos.y - vScale.y / 2.f)
		, int(vRenderPos.x + vScale.x / 2.f)
		, int(vRenderPos.y + vScale.y / 2.f));
}

void CGround::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetOwner();
	CRigidBody* pRigid = (CRigidBody*)pOtherObj->GetComponents(Component_TYPE::RigidBody);

	if (pOtherObj->GetName() == L"Kirby")
	{
		((CGravity*)pOtherObj->GetComponents(Component_TYPE::Gravity))->SetGround(true);

		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = ((CCollider*)GetComponents(Component_TYPE::Collider))->GetFinalPos();
		Vec2 vScale = ((CCollider*)GetComponents(Component_TYPE::Collider))->GetScale();

		pOtherObj->SetPos(pOtherObj->GetPrevPos());		
	}
}

void CGround::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetOwner();
	CRigidBody* pRigid = (CRigidBody*)pOtherObj->GetComponents(Component_TYPE::RigidBody);

	if (pOtherObj->GetName() == L"Kirby")
	{
		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = ((CCollider*)GetComponents(Component_TYPE::Collider))->GetFinalPos();
		Vec2 vScale = ((CCollider*)GetComponents(Component_TYPE::Collider))->GetScale();

		pOtherObj->SetPos(pOtherObj->GetPrevPos());
	}
}


void CGround::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetOwner();
	if (pOtherObj->GetName() == L"Kirby")
	{
		((CGravity*)pOtherObj->GetComponents(Component_TYPE::Gravity))->SetGround(false);

		Vec2 vPos = pOtherObj->GetPos();
	}
}
