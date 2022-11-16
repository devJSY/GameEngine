#include "global.h"
#include "CTile.h"

#include "SelectGDI.h"
#include "CCamera.h"
#include "CCore.h"

CTile::CTile()
{
}

CTile::~CTile()
{
}

void CTile::update()
{
}

void CTile::render(HDC _dc)
{

	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);
	
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	Rectangle(_dc
		, int(vRenderPos.x - vScale.x / 2.f)
		, int(vRenderPos.y - vScale.y / 2.f)
		, int(vRenderPos.x + vScale.x / 2.f)
		, int(vRenderPos.y + vScale.y / 2.f));
}
