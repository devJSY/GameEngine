#include "global.h"
#include "CMonster.h"

#include "CCore.h"
#include "CCollider.h"

CMonster::CMonster()
{
	CreateCollider();
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

	Component_render(_dc);
}


void CMonster::start()
{
	GetCollider()->SetScale(Vec2(25.f, 25.f));
}