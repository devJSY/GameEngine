#include "global.h"
#include "CScene_Animation_Tool.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CCore.h"
#include "CAnimation.h"

#include "Kirby.h"

#include "SelectGDI.h"
#include "CTexture.h"
#include "CTimeMgr.h"


CScene_Animation_Tool::CScene_Animation_Tool()
	: m_pTex(nullptr)
	, m_SaveAnim(nullptr)
	, m_DragTrig(false)
	, CurAinmData{}
{
}

CScene_Animation_Tool::~CScene_Animation_Tool()
{
	
}

void CScene_Animation_Tool::update()
{
	CScene::update();

	if (KEY_TAP(KEY::RBTN))
	{
		m_vTapPos = MOUSE_POS;
		m_DragTrig = true;
		vAccPos = CCamera::GetInst()->GetLookAt();	// 클릭 당시 위치 값 저장
	}

	if (KEY_AWAY(KEY::RBTN))
	{
		m_vAwayPos = MOUSE_POS;
		m_DragTrig = false;

		// 슬라이스 사이즈 저장
		CurAinmData.vSlice = (m_vTapPos - m_vAwayPos) - vCamDist;
		CurAinmData.vSlice.Vec2_abs();

		// 좌상단 절대값 저장
		CurAinmData.vLT = CCamera::GetInst()->GetRealPos(m_vTapPos - vCamDist);
		//CurAinmData.vLT.Vec2_abs();

		// 우하단 절대값 저장
		CurAinmData.vRB = CCamera::GetInst()->GetRealPos(m_vAwayPos);
		//CurAinmData.vRB.Vec2_abs();				
	}

	if (KEY_TAP(KEY::SPACE))
	{
		// 마우스 좌표에 따른 지정한 범위의 프레임 데이터 벡터에 저장
		frameData.push_back(CurAinmData);
		m_SaveAnim = new CAnimation;

		CurAinmData.vLT = CurAinmData.vLT.Vec2_abs();
		CurAinmData.vRB = CurAinmData.vRB.Vec2_abs();

		m_SaveAnim->Create(m_pTex, CurAinmData.vLT, Vec2(CurAinmData.vSlice.x / 5.f, CurAinmData.vSlice.y), Vec2(CurAinmData.vSlice.x / 5.f, 0.f), 0.3f, 5);
		m_SaveAnim->SetName(L"Test");
		m_SaveAnim->Save(L"animation\\Test.anim");
	}	

	// 클릭 당시 위치값과 현재 위치값의 차이, 즉 카메라 이동량을 구함
	vCamDist = CCamera::GetInst()->GetLookAt() - vAccPos;
}

void CScene_Animation_Tool::render(HDC _dc)
{
	// 텍스쳐 렌더링
	if (nullptr != m_pTex)
	{
		int iWidth = m_pTex->Width();
		int iHeight = m_pTex->Height();

		Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(Vec2(0.f, 0.f));	// ( 0 , 0 ) 부터 텍스쳐 렌더링

		BitBlt(_dc
			, (int)vRenderPos.x
			, (int)vRenderPos.y
			, (int)iWidth
			, (int)iHeight
			, m_pTex->GetDC()
			, 0, 0, SRCCOPY);
	}

	Vec2 vMousePos = MOUSE_POS;
		
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI p(_dc, PEN_TYPE::GREEN);	

	if (m_DragTrig)
	{
		Vec2 vTagPos = CCamera::GetInst()->GetRenderPos(m_vTapPos);

		Rectangle(_dc
			, (int)(m_vTapPos.x - vCamDist.x)	// 클릭한 순간 부터 카메라 영향 받음
			, (int)(m_vTapPos.y - vCamDist.y)	// 클릭한 순간 부터 카메라 영향 받음
			, (int)vMousePos.x
			, (int)vMousePos.y);
	}

	// 생성한 프레임 렌더링
	for (size_t i = 0; i < frameData.size(); ++i)
	{
		Vec2 vLT = CCamera::GetInst()->GetRenderPos(frameData[i].vLT);
		Vec2 vRB = CCamera::GetInst()->GetRenderPos(frameData[i].vRB);

		Rectangle(_dc
			, (int)vLT.x	// 클릭한 순간 부터 카메라 영향 받음
			, (int)vLT.y	// 클릭한 순간 부터 카메라 영향 받음
			, (int)vRB.x
			, (int)vRB.y);
	}
	

	CScene::render(_dc);
}

void CScene_Animation_Tool::Enter()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"AnimTex", L"Texture\\KirbyRight.bmp");

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(Vec2(vResolution /2.f ));
	CCamera::GetInst()->SetMovsSpeed(800.f);

	CObject* mObj = new Kirby;
	mObj->SetName(L"Obj");
	mObj->SetScale(Vec2(300, 300));
	mObj->SetPos(vResolution / 2.f);

	EnterAddObject(mObj, GROUP_TYPE::PLAYER);
}

void CScene_Animation_Tool::Exit()
{
}
