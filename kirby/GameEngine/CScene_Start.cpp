#include "global.h"
#include "CScene_Start.h"

#include "CCore.h"
#include "CObject.h"
#include "Kirby.h"
#include "CMonster.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CGround.h"

#include "CColliderMgr.h"
#include "CSceneMgr.h"
#include "CCamera.h"
#include "CResMgr.h"

CScene_Start::CScene_Start()
	: m_TexBackGround(nullptr)
{
	m_TexBackGround = CResMgr::GetInst()->LoadTexture(L"StartScene", L"Texture\\StartScene.bmp");

}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	CScene::update();
}

void CScene_Start::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(Vec2(0.f, 0.f));	// ( 0 , 0 ) 부터 텍스쳐 렌더링
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	BitBlt(_dc
		, (int)vRenderPos.x
		, (int)vRenderPos.y
		, (int)vResolution.x
		, (int)vResolution.y
		, m_TexBackGround->GetDC()
		, 0, 0 , SRCCOPY);

	CScene::render(_dc);
}

void CScene_Start::Enter()
{
	CCore::GetInst()->DividMenu();

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	CUI* PanelUI = new CPanelUI;
	PanelUI->SetName(L"PanelUI");
	PanelUI->SetScale(Vec2(500.f, 500.f));
	PanelUI->SetPos(Vec2(vResolution / 2.f - PanelUI->GetScale() / 2.f));

	CBtnUI* BtnUI = new CBtnUI;
	BtnUI->SetScale(Vec2(300.f, 50.f));


	CBtnUI* StageBtnUI = BtnUI->Clone();
	StageBtnUI->SetName(L"StageBtnUI");
	StageBtnUI->SetSceneType((UINT)SCENE_TYPE::STAGE_01);
	StageBtnUI->SetPos(Vec2(100.f, 100.f));

	CBtnUI* AnimToolBtnUI = BtnUI->Clone();
	AnimToolBtnUI->SetName(L"AnimToolBtnUI");
	AnimToolBtnUI->SetSceneType((UINT)SCENE_TYPE::Animation_Tool);
	AnimToolBtnUI->SetPos(Vec2(100.f, 200.f));

	CBtnUI* SceneToolBtnUI = BtnUI->Clone();
	SceneToolBtnUI->SetName(L"SceneToolBtnUI");
	SceneToolBtnUI->SetSceneType((UINT)SCENE_TYPE::Scene_Tool);
	SceneToolBtnUI->SetPos(Vec2(100.f, 300.f));


	PanelUI->AddChild(StageBtnUI);
	PanelUI->AddChild(AnimToolBtnUI);
	PanelUI->AddChild(SceneToolBtnUI);
	

	EnterAddObject(PanelUI, GROUP_TYPE::UI);

	delete BtnUI; // 기준 버튼 UI삭제

	start();
}

void CScene_Start::Exit()
{
	DeleteAll();
	CColliderMgr::GetInst()->Reset(); // 충돌체크 리셋
}
