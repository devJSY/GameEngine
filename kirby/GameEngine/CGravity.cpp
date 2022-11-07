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
}

void CGravity::Component_update()
{
	if (!m_bGround)
	{
		((CRigidBody*)m_pOwner->GetComponents(Component_TYPE::RigidBody))->SetAccelAlpha(Vec2(0.f, 800.f));
	}
}
