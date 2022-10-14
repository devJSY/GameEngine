#include "global.h"
#include "CObject.h"

#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CObject::CObject()
	: m_bAlive(true)
{
}

CObject::~CObject()
{
}

void CObject::update()
{
}

void CObject::render(HDC _dc)
{
}
