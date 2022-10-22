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


		// ���콺 ��ǥ�� ���� ������ ������ ������ ������ ���Ϳ� ����
		AnimFrmData p = {};

		// �»�� ���밪 ����
		p.vLT = CCamera::GetInst()->GetRealPos(m_vTapPos + vAccPos);
		p.vLT.Vec2_abs();

		// ���ϴ� ���밪 ����
		p.vRB = (m_vTapPos - m_vAwayPos) + vAccPos;
		p.vRB.Vec2_abs();

		frameData.push_back(p);
	}

	float Cam_fSpeed = CCamera::GetInst()->GetMoveSpeed();

	// Ŭ���� ī�޶� �̵��� ����
	if (KEY_HOLD(KEY::W))
		vAccPos.y += Cam_fSpeed * fDT;
	if (KEY_HOLD(KEY::S))
		vAccPos.y -= Cam_fSpeed * fDT;
	if (KEY_HOLD(KEY::A))
		vAccPos.x += Cam_fSpeed * fDT;
	if (KEY_HOLD(KEY::D))
		vAccPos.x -= Cam_fSpeed * fDT;

	//CCamera::GetInst()->AddAccLookAt(AddLookAt);
}

void CScene_Animation_Tool::render(HDC _dc)
{
	// �ؽ��� ������
	if (nullptr != m_CurTex)
	{
		int iWidth = m_CurTex->Width();
		int iHeight = m_CurTex->Height();

		Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(Vec2(0.f, 0.f));	// ( 0 , 0 ) ���� �ؽ��� ������

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

	if (m_DragTrig)
	{
		Rectangle(_dc
			, (int)(m_vTapPos.x + vAccPos.x)	// Ŭ���� ���� ���� ī�޶� ���� ����
			, (int)(m_vTapPos.y + vAccPos.y)	// Ŭ���� ���� ���� ī�޶� ���� ����
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
	CCamera::GetInst()->SetMovsSpeed(800.f);
}

void CScene_Animation_Tool::Exit()
{
}
