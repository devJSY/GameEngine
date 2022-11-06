#include "global.h"
#include "CGravity.h"

#include "CObject.h"
#include "CRigidBody.h"

CGravity::CGravity()
	: m_pOwner(nullptr)
	, m_bGround(false)
{
}

CGravity::~CGravity()
{
}

void CGravity::SetGround(bool _b)
{
	m_bGround = _b;
	if (m_bGround)
	{
		Vec2 vV = ((CRigidBody*)m_pOwner->GetComponents(Component_TYPE::RigidBody))->GetVelocity();
		((CRigidBody*)m_pOwner->GetComponents(Component_TYPE::RigidBody))->SetVelocity(Vec2(vV.x, 0.f)); // 땅에 닿아있는 상태라면 0속도를 0으로 셋팅
	}
}

void CGravity::Component_update()
{
	if (!m_bGround)
	{
		((CRigidBody*)m_pOwner->GetComponents(Component_TYPE::RigidBody))->SetAccelAlpha(Vec2(0.f, 800.f));
	}
}
