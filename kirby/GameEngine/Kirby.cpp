#include "global.h"
#include "Kirby.h"

#include "CCore.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

Kirby::Kirby()
{
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
}
