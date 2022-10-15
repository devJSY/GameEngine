#include "CComponent.h"


CComponent::CComponent()
	: m_pOwner(nullptr)
{
}

CComponent::CComponent(const CComponent& _origin)
	: m_pOwner(nullptr)
{
}

CComponent::~CComponent()
{
}
