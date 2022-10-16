#include "global.h"

#include "CCore.h"
#include "CObject.h"
#include "CComponent.h"
#include "CCollider.h"

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
	// 예외처리 추가 기존에 콜라이더 갖고있었던 경우에만 콜라이더 생성
	if (nullptr != _origin.arr_Components[(UINT)Component_TYPE::CCollider])
	{
		CreateCollider();
		GetCollider()->SetScale(Vec2(50.f, 50.f));
		GetCollider()->SetOffsetPos(Vec2(500.f, 0.f));
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


void CObject::CreateCollider()
{
	CCollider* pCollider = new CCollider;
	pCollider->m_pOwner = this;

	arr_Components[(UINT)Component_TYPE::CCollider] = pCollider;
}

CCollider* CObject::GetCollider()
{
	if (nullptr == arr_Components[(UINT)Component_TYPE::CCollider])
	{
		return nullptr;
	}

	return (CCollider*)arr_Components[(UINT)Component_TYPE::CCollider];
}