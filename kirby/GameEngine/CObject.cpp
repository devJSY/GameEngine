#include "global.h"
#include "CObject.h"

#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CObject::CObject()
{
}

CObject::~CObject()
{
}

void CObject::update()
{
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
}

void CObject::render(HDC _dc)
{
	Rectangle(MemoryDC
		, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f)
	);
}
