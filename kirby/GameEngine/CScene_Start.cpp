#include "global.h"
#include "CScene_Start.h"

#include "CCore.h"
#include "CObject.h"
#include "Kirby.h"
#include "CMonster.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

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
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CUI* PanelUI = new CPanelUI;
	PanelUI->SetName(L"PanelUI");
	PanelUI->SetScale(Vec2(500.f, 500.f));
	PanelUI->SetPos(Vec2(vResolution / 2.f - PanelUI->GetScale() / 2.f));

	CUI* BtnUI = new CBtnUI;
	BtnUI->SetName(L"BtnUI");
	BtnUI->SetScale(Vec2(200.f, 200.f));
	BtnUI->SetPos(PanelUI->GetScale() / 2.f - BtnUI->GetScale() / 2.f);

	PanelUI->AddChild(BtnUI);

	EnterAddObject(PanelUI, GROUP_TYPE::UI);

	//CCamera::GetInst()->SetLookAt(vResolution / 2.f);
	
	start();
}

void CScene_Start::Exit()
{
	DeleteAll();
}
