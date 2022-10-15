#include "global.h"

#include "CObject.h"
#include "CComponent.h"

#include "CCore.h"
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
	for (size_t i = 0; i < vComponent.size(); ++i)
	{
		vComponent[i] = _origin.vComponent[i]->Clone();
	}
}

CObject::~CObject()
{
	Safe_Delete_Vec(vComponent);
}

void CObject::update()
{
}

void CObject::Component_update()
{
	for (size_t i = 0; i < vComponent.size(); ++i)
	{
		vComponent[i]->Component_update();
	}
}

void CObject::render(HDC _dc)
{
}

void CObject::Component_render(HDC _dc)
{
	for (size_t i = 0; i < vComponent.size(); ++i)
	{
		vComponent[i]->Component_render(_dc);
	}
}
