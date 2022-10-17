#include "global.h"
#include "Kirby.h"

#include "CCore.h"
#include "CCollider.h"
#include "CTexture.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"

Kirby::Kirby()
{
	CreateCollider();
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"\\Texture\\Player1.bmp");
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

void Kirby::OnCollision(CCollider* _pOther)
{
}

void Kirby::OnCollisionEnter(CCollider* _pOther)
{
	if (L"CopyKirby" == GetName())
	{
		DeleteObject(this);
	}
}

void Kirby::OnCollisionExit(CCollider* _pOther)
{

}

void Kirby::start()
{
	GetCollider()->SetScale(Vec2(50.f, 50.f));
}