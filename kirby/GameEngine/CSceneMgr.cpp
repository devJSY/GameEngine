#include "global.h"
#include "CSceneMgr.h"

#include "CScene.h"
#include "CScene_Start.h"
#include "CScene_Stage.h"
#include "CScene_AnimTool.h"
#include "CScene_SceneTool.h"


CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
	for (int i = 0; i < (int)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}			
	}
}

void CSceneMgr::init()
{
	// Scene »ý¼º
	CScene* StartScene = new CScene_Start;
	StartScene->SetName(L"StartScene");
	m_arrScene[(UINT)SCENE_TYPE::START] = StartScene;

	CScene* Animation_Tool = new CScene_AnimTool;
	Animation_Tool->SetName(L"Animation_Tool");
	m_arrScene[(UINT)SCENE_TYPE::Animation_Tool] = Animation_Tool;

	CScene* Scene_Tool = new CScene_SceneTool;
	Scene_Tool->SetName(L"Scene_Tool");
	m_arrScene[(UINT)SCENE_TYPE::Scene_Tool] = Scene_Tool;

	CScene* Stage_01 = new CScene_Stage;
	m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = Stage_01;

	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];

	m_pCurScene->Enter();
}

void CSceneMgr::update()
{
	m_pCurScene->update();

	m_pCurScene->Component_update();
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}

void CSceneMgr::DeadObjectErase()
{
	m_pCurScene->DeadObjectErase();
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)_eNext];
	m_pCurScene->Enter();
}
