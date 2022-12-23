#include "global.h"
#include "CGround.h"

#include "CObject.h"
#include "Kirby.h"
#include "CComponent.h"
#include "CCollider.h"
#include "CGravity.h"
#include "CRigidBody.h"

#include "SelectGDI.h"
#include "CColliderMgr.h"

CGround::CGround()
{
	CreateComponents(Component_TYPE::Collider);
}

CGround::~CGround()
{
}

void CGround::update()
{
}

void CGround::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc
		, int(vRenderPos.x - vScale.x / 2.f)
		, int(vRenderPos.y - vScale.y / 2.f)
		, int(vRenderPos.x + vScale.x / 2.f)
		, int(vRenderPos.y + vScale.y / 2.f));

	Component_render(_dc);
}

void CGround::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetOwner();
	CRigidBody* pRigid = (CRigidBody*)pOtherObj->GetComponents(Component_TYPE::RigidBody);

	if (pOtherObj->GetName() == L"Kirby" || pOtherObj->GetName() == L"Monster")
	{
		// Collider �� FinalPos �δ� Ground �浹�� 2���̻� �߻��Ǿ����� Pos ������ ���� �����ӿ� �߻������� Pos �� ����
		Vec2 vObjPos = pOtherObj->GetPos();
		vObjPos += ((CCollider*)pOtherObj->GetComponents(Component_TYPE::Collider))->GetOffsetPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetPos();
		vPos += ((CCollider*)GetComponents(Component_TYPE::Collider))->GetOffsetPos();
		Vec2 vScale = ((CCollider*)GetComponents(Component_TYPE::Collider))->GetScale();

		COLLIDER_DIR ColDir = CColliderMgr::GetInst()->CollisionDIR(((CCollider*)pOtherObj->GetComponents(Component_TYPE::Collider)), ((CCollider*)GetComponents(Component_TYPE::Collider)));
	
		if (ColDir.TOP)
		{
			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			if (0.f < fValue)
			{
				vObjPos = pOtherObj->GetPos();
				vObjPos.y += (fValue);

				pOtherObj->SetPos(vObjPos);
			}
		}
		else if (ColDir.BOTTOM)
		{
			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

 			if (0.f < fValue)
			{
				vObjPos = pOtherObj->GetPos();
				vObjPos.y -= (fValue);

				pOtherObj->SetPos(vObjPos);
			}

			((CGravity*)pOtherObj->GetComponents(Component_TYPE::Gravity))->SetGround(true); // �浹 ���۽� �׶��� ���� ����

			pRigid->SetVelocity(Vec2(pRigid->GetVelocity().x, 0.f)); // ���� ����ִ� ���¶�� 0�ӵ��� 0���� ����
			pRigid->SetAccelAlpha(Vec2(0.f, 0.f)); // �߰����ӵ� ����
		}
		else if (ColDir.LEFT)
		{
			float fLen = abs(vObjPos.x - vPos.x);
			float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;

			if (0.f < fValue)
			{
				vObjPos = pOtherObj->GetPos();
				vObjPos.x += (fValue);

				pOtherObj->SetPos(vObjPos);
			}
		}
		else if (ColDir.RIGHT)
		{
			float fLen = abs(vObjPos.x - vPos.x);
			float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;

			if (0.f < fValue)
			{
				vObjPos = pOtherObj->GetPos();
				vObjPos.x -= (fValue);

				pOtherObj->SetPos(vObjPos);
			}
		}	
	}
}

void CGround::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetOwner();
	CRigidBody* pRigid = (CRigidBody*)pOtherObj->GetComponents(Component_TYPE::RigidBody);

	if (pOtherObj->GetName() == L"Kirby" || pOtherObj->GetName() == L"Monster")
	{
		// Collider �� FinalPos �δ� Ground �浹�� 2���̻� �߻��Ǿ����� Pos ������ ���� �����ӿ� �߻������� Pos �� ����
		Vec2 vObjPos = pOtherObj->GetPos();
		vObjPos += ((CCollider*)pOtherObj->GetComponents(Component_TYPE::Collider))->GetOffsetPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetPos();
		vPos += ((CCollider*)GetComponents(Component_TYPE::Collider))->GetOffsetPos();
		Vec2 vScale = ((CCollider*)GetComponents(Component_TYPE::Collider))->GetScale();

		COLLIDER_DIR ColDir = CColliderMgr::GetInst()->CollisionDIR(((CCollider*)pOtherObj->GetComponents(Component_TYPE::Collider)), ((CCollider*)GetComponents(Component_TYPE::Collider)));

		if (ColDir.TOP)
		{
			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			if (0.f < fValue)
			{
				vObjPos = pOtherObj->GetPos();
				vObjPos.y += (fValue);

				pOtherObj->SetPos(vObjPos);
			}
		}
		else if (ColDir.BOTTOM)
		{
			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			if (KIRBY_STATE::JUMP != ((Kirby*)pOtherObj)->GetCurStage())
			{
				if (0.f < fValue)
				{
					vObjPos = pOtherObj->GetPos();
					vObjPos.y -= (fValue);

					pOtherObj->SetPos(vObjPos);
				}
			}

			((CGravity*)pOtherObj->GetComponents(Component_TYPE::Gravity))->SetGround(true);

			pRigid->SetAccelAlpha(Vec2(0.f, 0.f)); // �߰����ӵ� ����
		}
		else if (ColDir.LEFT)
		{
			float fLen = abs(vObjPos.x - vPos.x);
			float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;

			if (0.f < fValue)
			{
				vObjPos = pOtherObj->GetPos();
				vObjPos.x += (fValue);

				pOtherObj->SetPos(vObjPos);
			}
		}
		else if (ColDir.RIGHT)
		{
			float fLen = abs(vObjPos.x - vPos.x);
			float fValue = (vObjScale.x / 2.f + vScale.x / 2.f) - fLen;

			if (0.f < fValue)
			{
				vObjPos = pOtherObj->GetPos();
				vObjPos.x -= (fValue);

				pOtherObj->SetPos(vObjPos);
			}
		}
	}
}


void CGround::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetOwner();
	if (pOtherObj->GetName() == L"Kirby" || pOtherObj->GetName() == L"Monster")
	{
		((CGravity*)pOtherObj->GetComponents(Component_TYPE::Gravity))->SetGround(false);
	}
}

void CGround::start()
{
	((CCollider*)GetComponents(Component_TYPE::Collider))->SetScale(Vec2(GetScale()));
}
