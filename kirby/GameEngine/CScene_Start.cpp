#include "global.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "Kirby.h"
#include "CCore.h"

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


	CreateObject(gObj, GROUP_TYPE::PLAYER);
	
}

void CScene_Start::Exit()
{
}
