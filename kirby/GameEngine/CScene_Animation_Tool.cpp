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
		vAccPos = Vec2(0.f, 0.f);
	}

	if (KEY_AWAY(KEY::LBTN))
	{
		m_vAwayPos = MOUSE_POS;
		m_DragTrig = false;


		// 마우스 좌표에 따른 지정한 범위의 프레임 데이터 벡터에 저장
		AnimFrmData p = {};

		p.vLT = CCamera::GetInst()->GetRealPos(m_vTapPos);
		p.vRB = (m_vTapPos - m_vAwayPos) + CCamera::GetInst()->GetRealPos(vPos);

		frameData.push_back(p);
	}

	//Vec2 AddLookAt = Vec2(0.f, 0.f);

	if (KEY_HOLD(KEY::W))
	{
		vPos.y += 800.f * fDT;
		vAccPos.y += 800.f * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y -= 800.f * fDT;
		vAccPos.y -= 800.f * fDT;
	}

	if (KEY_HOLD(KEY::A))
	{
		vPos.x += 800.f * fDT;
		vAccPos.x += 800.f * fDT;
	}

	if (KEY_HOLD(KEY::D))
	{
		vPos.x -= 800.f * fDT;
		vAccPos.x -= 800.f * fDT;
	}


	//CCamera::GetInst()->AddAccLookAt(AddLookAt);
}

void CScene_Animation_Tool::render(HDC _dc)
{
	// 텍스쳐 렌더링
	if (nullptr != m_CurTex)
	{
		int iWidth = m_CurTex->Width();
		int iHeight = m_CurTex->Height();

		Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(vPos);

		BitBlt(_dc
			, (int)vRenderPos.x
			, (int)vRenderPos.y
			, (int)iWidth
			, (int)iHeight
			, m_CurTex->GetDC()
			, 0, 0, SRCCOPY);
	}

	Vec2 vMousePos = MOUSE_POS;
		
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI p(_dc, PEN_TYPE::GREEN);

	Vec2 vTagPos = CCamera::GetInst()->GetRenderPos(m_vTapPos);
	vTagPos += vAccPos;

	if (m_DragTrig)
	{
		Rectangle(_dc
			, (int)vTagPos.x
			, (int)vTagPos.y
			, (int)vMousePos.x
			, (int)vMousePos.y);
	}

	CScene::render(_dc);
}

void CScene_Animation_Tool::Enter()
{
	m_CurTex = CResMgr::GetInst()->LoadTexture(L"AnimTex", L"Texture\\KirbyRight.bmp");

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(Vec2(vResolution /2.f ));
}

void CScene_Animation_Tool::Exit()
{
}
