#include "global.h"

#include "CCore.h"
#include "CObject.h"
#include "CComponent.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CGravity.h"
#include "CAnimator.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "SelectGDI.h"

CObject::CObject()
	: m_bAlive(true)
	, arr_Components{}
	, m_MidPoint(false)
{
}

CObject::CObject(const CObject& _origin)
	: vPos(_origin.vPos)
	, vScale(_origin.vScale)
	, m_strName(_origin.m_strName)
	, arr_Components{}
	, m_bAlive(true)
	, m_MidPoint(false)
{
	CComponent* pComponent = nullptr;

	for (int i = 0; i < (int)Component_TYPE::END; ++i)
	{
		if (nullptr != _origin.arr_Components[(UINT)i])
		{
			CreateComponents(Component_TYPE(i));
		}
	}

	// ====================
	// 각 컴포넌트 예외 처리 
	// ====================

	// 기존에 콜라이더 갖고있었던 경우에만 콜라이더 생성
	if (nullptr != arr_Components[(UINT)Component_TYPE::Collider])
	{
		CCollider* pCollider = (CCollider*)GetComponents(Component_TYPE::Collider);
		pCollider->SetScale(pCollider->GetScale());
		pCollider->SetOffsetPos(pCollider->GetOffsetPos());
	}
}

CObject::~CObject()
{
	for (size_t i = 0; i < (UINT)Component_TYPE::END; ++i)
	{
		if (nullptr != arr_Components[i])
		{
			delete arr_Components[i];
		}
	}
}

void CObject::update()
{
	m_vPrevPos = vPos;
}

void CObject::Component_update()
{
	for (size_t i = 0; i < (UINT)Component_TYPE::END; ++i)
	{
		if (nullptr != arr_Components[i])
		{
			arr_Components[i]->Component_update();
		}		
	}

	// 오브젝트 중점 활성화
	if (KEY_TAP(KEY::Q))
	{
		SetMidPoint();
	}
}

void CObject::render(HDC _dc)
{
	// 기본 렌더링 없음
}

void CObject::Component_render(HDC _dc)
{
	for (size_t i = 0; i < (UINT)Component_TYPE::END; ++i)
	{
		if (nullptr != arr_Components[i])
		{
			arr_Components[i]->Component_render(_dc);
		}
	}

	if (m_MidPoint)
	{
		SelectGDI select(_dc, PEN_TYPE::RED);
		SelectGDI select1(_dc, BRUSH_TYPE::RED);

		Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

		Ellipse(_dc, (int)vPos.x - 3, (int)vPos.y - 3, (int)vPos.x + 3, (int)vPos.y + 3);
	}
}

void CObject::CreateComponents(Component_TYPE _etype)
{
	if (Component_TYPE::Collider == _etype)
	{
		CCollider* pCollider = new CCollider;
		pCollider->m_pOwner = this;

		arr_Components[(UINT)Component_TYPE::Collider] = pCollider;
	}
	else if (Component_TYPE::Animator == _etype)
	{
		CAnimator* pAnimator = new CAnimator;
		pAnimator->m_pOwner = this;

		arr_Components[(UINT)Component_TYPE::Animator] = pAnimator;
	}
	else if (Component_TYPE::RigidBody == _etype)
	{
		CRigidBody* pRigidBody = new CRigidBody;
		pRigidBody->m_pOwner = this;

		arr_Components[(UINT)Component_TYPE::RigidBody] = pRigidBody;
	}
	else if (Component_TYPE::Gravity == _etype)
	{
		CGravity* pGravity = new CGravity;
		pGravity->m_pOwner = this;

		arr_Components[(UINT)Component_TYPE::Gravity] = pGravity;
	}
}

CComponent* CObject::GetComponents(Component_TYPE _etype)
{
	if (nullptr == arr_Components[(UINT)_etype])
	{
		return nullptr;
	}

	return arr_Components[(UINT)_etype];
}
