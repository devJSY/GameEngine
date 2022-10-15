#include "global.h"

#include "CCore.h"
#include "CObject.h"
#include "CComponent.h"
#include "CCollider.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"



CObject::CObject()
	: m_bAlive(true)
{
}

CObject::CObject(const CObject& _origin)
	: vPos(_origin.vPos)
	, vScale(_origin.vScale)
	, m_strName(_origin.m_strName)
	, m_bAlive(true)
{
	map<wstring, CComponent*>::iterator iter = m_Component.begin();

	for (; iter != m_Component.end(); ++iter)
	{
		iter->second = iter->second->Clone();
	}
}

CObject::~CObject()
{
	Safe_Delete_Map(m_Component);
}

void CObject::update()
{
}

void CObject::Component_update()
{
	map<wstring, CComponent*>::iterator iter = m_Component.begin();

	for (; iter != m_Component.end(); ++iter)
	{
		iter->second->Component_update();
	}
}

void CObject::render(HDC _dc)
{
}

void CObject::Component_render(HDC _dc)
{
	map<wstring, CComponent*>::iterator iter = m_Component.begin();

	for (; iter != m_Component.end(); ++iter)
	{
		iter->second->Component_render(_dc);
	}
}


void CObject::CreateCollider()
{
	CCollider* pCollider = new CCollider;
	pCollider->m_pOwner = this;

	m_Component.insert(make_pair(L"Collider", pCollider));
}

CCollider* CObject::GetCollider()
{
	map<wstring, CComponent*>::iterator iter = m_Component.find(L"Collider");
	return (CCollider*)iter->second;
}