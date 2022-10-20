#include "global.h"
#include "CSceneMgr.h"

#include "CScene.h"
#include "CScene_Start.h"

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
	m_arrScene[(UINT)SCENE_TYPE::START] = StartScene;

	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];

	m_pCurScene->Enter();
	m_pCurScene->Exit();
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
