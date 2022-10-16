#include "global.h"
#include "CScene_Start.h"

#include "CCore.h"
#include "CObject.h"
#include "Kirby.h"
#include "CMonster.h"

#include "CColliderMgr.h"
#include "CSceneMgr.h"


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

	CObject* gObj = new Kirby;
	gObj->SetPos(Vec2(vResolution.x / 2.f, vResolution.y / 2.f));
	gObj->SetScale(Vec2(100.f, 100.f));
	gObj->SetName(L"Kirby");
	EnterAddObject(gObj, GROUP_TYPE::PLAYER);

	CObject* gMonObj = new CMonster;
	gMonObj->SetPos(Vec2(vResolution.x / 2.f, vResolution.y / 2.f - 300.f));
	gMonObj->SetScale(Vec2(50.f, 50.f));
	gMonObj->SetName(L"Monster");
	EnterAddObject(gMonObj, GROUP_TYPE::MONSTER);


	CObject* LeftgObj = gObj->Clone();
	LeftgObj->SetPos(gObj->GetPos() + Vec2(200.f, 0.f));
	LeftgObj->SetScale(Vec2(30.f, 30.f));
	LeftgObj->SetName(L"LeftgObj");
	EnterAddObject(LeftgObj, GROUP_TYPE::PLAYER);

	CObject* RightgObj = gObj->Clone();
	RightgObj->SetPos(gObj->GetPos() + Vec2(-200.f, 0.f));
	RightgObj->SetScale(Vec2(30.f, 30.f));
	RightgObj->SetName(L"RightgObj");
	EnterAddObject(RightgObj, GROUP_TYPE::PLAYER);


	CColliderMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);

	start();
}

void CScene_Start::Exit()
{
}
