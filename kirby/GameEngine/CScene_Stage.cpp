#include "global.h"
#include "CScene_Stage.h"

#include "CCore.h"
#include "Kirby.h"
#include "CGround.h"


#include "CCamera.h"
#include "CColliderMgr.h"
#include "CKeyMgr.h"


CScene_Stage::CScene_Stage()
{
}

CScene_Stage::~CScene_Stage()
{
}

void CScene_Stage::update()
{
	CScene::update();

	if (KEY_AWAY(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}

void CScene_Stage::render(HDC _dc)
{
	CScene::render(_dc);
}

void CScene_Stage::Enter()
{
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

	CGround* pGround2 = pGround->Clone();
	pGround2->SetName(L"Ground2");
	pGround2->SetPos(Vec2(900.f, 550.f));
	pGround2->SetScale(Vec2(200.f, 200.f));

	EnterAddObject(pGround2, GROUP_TYPE::GROUND);

	CGround* pGround3 = pGround2->Clone();
	pGround3->SetPos(Vec2(300.f, 250.f));

	EnterAddObject(pGround3, GROUP_TYPE::GROUND);

	CColliderMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);

	start();
}

void CScene_Stage::Exit()
{
	DeleteAll();
}