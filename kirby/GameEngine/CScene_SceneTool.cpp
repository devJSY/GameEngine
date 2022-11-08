#include "global.h"
#include "CScene_SceneTool.h"

#include "CCore.h"
#include "CKeyMgr.h"

void CScene_SceneTool::update()
{
	CScene::update();

	if (KEY_AWAY(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}

void CScene_SceneTool::render(HDC _dc)
{
}

void CScene_SceneTool::Enter()
{
	CCore::GetInst()->DockMenu();
}

void CScene_SceneTool::Exit()
{
}

CScene_SceneTool::CScene_SceneTool()
{
}

CScene_SceneTool::~CScene_SceneTool()
{
}
