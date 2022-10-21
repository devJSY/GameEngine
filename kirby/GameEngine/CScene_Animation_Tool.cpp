#include "global.h"
#include "CScene_Animation_Tool.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CCore.h"
#include "Kirby.h"

#include "SelectGDI.h"
#include "CTexture.h"
#include "CTimeMgr.h"


CScene_Animation_Tool::CScene_Animation_Tool()
	: m_CurTex(nullptr)
	, m_DragTrig(false)
{
}

CScene_Animation_Tool::~CScene_Animation_Tool()
{
}

void CScene_Animation_Tool::update()
{
	CScene::update();

	if (KEY_TAP(KEY::LBTN))
	{
		m_vTapPos = MOUSE_POS;
		m_DragTrig = true;
	}

	if (KEY_AWAY(KEY::LBTN))
	{
		m_vAwayPos = MOUSE_POS;
		m_DragTrig = false;
	}

	Vec2 AddLookAt = Vec2(0.f, 0.f);

	if (KEY_HOLD(KEY::W))
		AddLookAt.y -= 800.f * fDT;
	if (KEY_HOLD(KEY::S))
		AddLookAt.y += 800.f * fDT;
	if (KEY_HOLD(KEY::A))
		AddLookAt.x -= 800.f * fDT;
	if (KEY_HOLD(KEY::D))
		AddLookAt.x += 800.f * fDT;

	CCamera::GetInst()->AddAccLookAt(AddLookAt);
}

void CScene_Animation_Tool::render(HDC _dc)
{
	int iWidth = m_CurTex->Width();
	int iHeight = m_CurTex->Height();


	Vec2 LookAt = CCamera::GetInst()->GetLookAt();

	BitBlt(_dc
		, (int)LookAt.x
		, (int)LookAt.y
		, (int)(iWidth - LookAt.x)
		, (int)(iHeight - LookAt.y)
		, m_CurTex->GetDC()
		, 0, 0, SRCCOPY); 

	Vec2 vMousePos = MOUSE_POS;
		
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI p(_dc, PEN_TYPE::GREEN);

	if (m_DragTrig)
	{
		Rectangle(_dc
			, (int)m_vTapPos.x
			, (int)m_vTapPos.y
			, (int)vMousePos.x
			, (int)vMousePos.y);
	}

	CScene::render(_dc);
}

void CScene_Animation_Tool::Enter()
{
	m_CurTex = CResMgr::GetInst()->LoadTexture(L"AnimTex", L"Texture\\KirbyRight.bmp");

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(Vec2(0.f , 0.f));
}

void CScene_Animation_Tool::Exit()
{
}
