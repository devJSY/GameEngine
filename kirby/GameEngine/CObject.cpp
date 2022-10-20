#include "global.h"

#include "CCore.h"
#include "CObject.h"
#include "CComponent.h"
#include "CCollider.h"
#include "CAnimator.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

CObject::CObject()
	: m_bAlive(true)
	, arr_Components{}
{
}

CObject::CObject(const CObject& _origin)
	: vPos(_origin.vPos)
	, vScale(_origin.vScale)
	, m_strName(_origin.m_strName)
	, arr_Components{}
	, m_bAlive(true)
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
	// 기본 업데이트 없음
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
}

void CObject::render(HDC _dc)
{
	// 기본 렌더 없음
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
}

CComponent* CObject::GetComponents(Component_TYPE _etype)
{
	if (nullptr == arr_Components[(UINT)_etype])
	{
		return nullptr;
	}

	return arr_Components[(UINT)_etype];
}
