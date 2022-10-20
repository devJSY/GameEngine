#include "global.h"
#include "CMonster.h"

#include "CCore.h"
#include "CCollider.h"
#include "CTexture.h"

#include "CResMgr.h"

CMonster::CMonster()
{
	CreateComponents(Component_TYPE::Collider);
	m_pTex = CResMgr::GetInst()->LoadTexture(L"MonTex", L"\\Texture\\Player1.bmp");
}

CMonster::~CMonster()
{	
}

void CMonster::update()
{
}

void CMonster::render(HDC _dc)
{
	int iWidth = m_pTex->Width();
	int iHeight = m_pTex->Height();

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	TransparentBlt(_dc
		, int(vPos.x - (float)(iWidth / 2))
		, int(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

	Component_render(_dc);
}


void CMonster::start()
{
	CCollider* pCollider = ((CCollider*)GetComponents(Component_TYPE::Collider));
	pCollider->SetScale(Vec2(50.f, 50.f));
}