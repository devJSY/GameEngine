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
		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = ((CCollider*)GetComponents(Component_TYPE::Collider))->GetFinalPos();
		Vec2 vScale = ((CCollider*)GetComponents(Component_TYPE::Collider))->GetScale();

		COLLIDER_DIR ColDir = CColliderMgr::GetInst()->CollisionDIR(((CCollider*)pOtherObj->GetComponents(Component_TYPE::Collider)), ((CCollider*)GetComponents(Component_TYPE::Collider)));
	
		if (ColDir.TOP)
		{
			float diffPos = abs(vObjPos.y - vPos.y);
			float diffScale = abs(vObjScale.y / 2.f + vScale.y / 2.f);

			Vec2 vSetPos = pOtherObj->GetPos();

			vSetPos.y -= (diffScale - diffPos);

			pOtherObj->SetPos(vSetPos);
		}
		else if (ColDir.BOTTOM)
		{
			((CGravity*)pOtherObj->GetComponents(Component_TYPE::Gravity))->SetGround(true);

			float diffPos = abs(vObjPos.y - vPos.y);
			float diffScale = abs(vObjScale.y / 2.f + vScale.y / 2.f);

			Vec2 vSetPos = pOtherObj->GetPos();

			vSetPos.y += (diffScale - diffPos) + 1;

			pOtherObj->SetPos(vSetPos);
		}
		else if (ColDir.LEFT)
		{
			float diffPos = abs(vObjPos.x - vPos.x);
			float diffScale = abs(vObjScale.x / 2.f + vScale.x / 2.f);

			Vec2 vSetPos = pOtherObj->GetPos();

			vSetPos.x += (diffScale - diffPos);

			pOtherObj->SetPos(vSetPos);
		}
		else if (ColDir.RIGHT)
		{
			float diffPos = abs(vObjPos.x - vPos.x);
			float diffScale = abs(vObjScale.x / 2.f + vScale.x / 2.f);

			Vec2 vSetPos = pOtherObj->GetPos();

			vSetPos.x -= (diffScale - diffPos);

			pOtherObj->SetPos(vSetPos);
		}	
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

		COLLIDER_DIR ColDir = CColliderMgr::GetInst()->CollisionDIR(((CCollider*)pOtherObj->GetComponents(Component_TYPE::Collider)), ((CCollider*)GetComponents(Component_TYPE::Collider)));

		if (ColDir.TOP)
		{
			float diffPos = abs(vObjPos.y - vPos.y);
			float diffScale = abs(vObjScale.y / 2.f + vScale.y / 2.f);

			Vec2 vSetPos = pOtherObj->GetPos();

			vSetPos.y += (diffScale - diffPos);

			pOtherObj->SetPos(vSetPos);
		}
		else if (ColDir.BOTTOM)
		{
			((CGravity*)pOtherObj->GetComponents(Component_TYPE::Gravity))->SetGround(true);

			float diffPos = abs(vObjPos.y - vPos.y);
			float diffScale = abs(vObjScale.y / 2.f + vScale.y / 2.f);

			Vec2 vSetPos = pOtherObj->GetPos();

			vSetPos.y -= (diffScale - diffPos) + 1;

			pOtherObj->SetPos(vSetPos);
		}
		else if (ColDir.LEFT)
		{
			float diffPos = abs(vObjPos.x - vPos.x);
			float diffScale = abs(vObjScale.x / 2.f + vScale.x / 2.f);

			Vec2 vSetPos = pOtherObj->GetPos();

			vSetPos.x += (diffScale - diffPos);

			pOtherObj->SetPos(vSetPos);
		}
		else if (ColDir.RIGHT)
		{
			float diffPos = abs(vObjPos.x - vPos.x);
			float diffScale = abs(vObjScale.x / 2.f + vScale.x / 2.f);

			Vec2 vSetPos = pOtherObj->GetPos();

			vSetPos.x -= (diffScale - diffPos);

			pOtherObj->SetPos(vSetPos);
		}
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
