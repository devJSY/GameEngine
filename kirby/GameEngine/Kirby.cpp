#include "global.h"
#include "Kirby.h"

#include "CCore.h"
#include "CCollider.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

Kirby::Kirby()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(50.f, 50.f));
	GetCollider()->SetOffsetPos(Vec2(500.f, 0.f));
}

Kirby::~Kirby()
{
}

void Kirby::update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::LEFT))
	{
		vPos.x -= 500 * fDT;
	}

	if (KEY_HOLD(KEY::RIGHT))
	{
		vPos.x += 500 * fDT;
	}

	if (KEY_HOLD(KEY::DOWN))
	{
		vPos.y += 500 * fDT;
	}

	if (KEY_HOLD(KEY::UP))
	{
		vPos.y -= 500 * fDT;
	}

	SetPos(vPos);
}

void Kirby::render(HDC _dc)
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
