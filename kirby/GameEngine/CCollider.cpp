#include "CCollider.h"

#include "CObject.h"

// CCollider 고유 ID
UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_iID(g_iNextID++)
	, m_iCol(0)
{
}

CCollider::CCollider(const CCollider& _origin)
	: m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++)
	, m_iCol(_origin.m_iCol)
{
}

CCollider::~CCollider()
{
}

void CCollider::Component_update()
{
	Vec2 vPos = GetOwner()->GetPos();
	m_vFinalPos = vPos + m_vOffsetPos;

	// 충돌횟수 오류 체크
	assert(0 <= m_iCol);
}

void CCollider::Component_render(HDC _dc)
{
	Rectangle(_dc
		, int(m_vFinalPos.x - m_vScale.x / 2.f)
		, int(m_vFinalPos.y - m_vScale.y / 2.f)
		, int(m_vFinalPos.x + m_vScale.x / 2.f)
		, int(m_vFinalPos.y + m_vScale.y / 2.f)
	);
}

void CCollider::OnCollision(CCollider* _pOther)
{
	GetOwner()->OnCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	++m_iCol;
	GetOwner()->OnCollisionEnter(_pOther);
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--m_iCol;
	GetOwner()->OnCollisionExit(_pOther);
}
