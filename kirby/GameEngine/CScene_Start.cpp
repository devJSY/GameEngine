#include "global.h"
#include "CScene_Start.h"

#include "CCore.h"
#include "CObject.h"
#include "Kirby.h"
#include "CMonster.h"

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

	CColliderMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);

	//CCamera::GetInst()->SetLookAt(vResolution / 2.f);
	CCamera::GetInst()->SetTarget(gObj);
	
	start();
}

void CScene_Start::Exit()
{
}
