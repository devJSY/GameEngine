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


CScene_Start::CScene_Start()
{
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
	CScene::render(_dc);
}

void CScene_Start::Enter()
{
	

	//CUI* PanelUI = new CPanelUI;
	//PanelUI->SetName(L"PanelUI");
	//PanelUI->SetScale(Vec2(500.f, 500.f));
	//PanelUI->SetPos(Vec2(vResolution / 2.f - PanelUI->GetScale() / 2.f));

	//CUI* BtnUI = new CBtnUI;
	//BtnUI->SetName(L"BtnUI");
	//BtnUI->SetScale(Vec2(200.f, 200.f));
	//BtnUI->SetPos(PanelUI->GetScale() / 2.f - BtnUI->GetScale() / 2.f);

	//PanelUI->AddChild(BtnUI);

	//EnterAddObject(PanelUI, GROUP_TYPE::UI);

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	CObject* pKirby = new Kirby;
	pKirby->SetName(L"Kirby");
	pKirby->SetPos(Vec2(640.f, 384.f));
	pKirby->SetScale(Vec2(100.f, 100.f));

	EnterAddObject(pKirby, GROUP_TYPE::PLAYER);

	CGround* pGround = new CGround;
	pGround->SetName(L"Ground");
	pGround->SetPos(Vec2(640.f, 584.f));
	pGround->SetScale(Vec2(800.f, 60.f));

	EnterAddObject(pGround, GROUP_TYPE::GROUND);

	CColliderMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);

	
	start();
}

void CScene_Start::Exit()
{
	DeleteAll();
}
