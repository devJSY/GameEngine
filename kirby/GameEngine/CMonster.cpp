#include "global.h"
#include "CMonster.h"

#include "CCore.h"
#include "CCollider.h"

CMonster::CMonster()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(50.f, 50.f));
	GetCollider()->SetOffsetPos(Vec2(500.f, 0.f));
}

CMonster::~CMonster()
{
}

void CMonster::update()
{
}

void CMonster::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Rectangle(MemoryDC
		, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f)
	);
}
