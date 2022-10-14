#include "global.h"
#include "CScene.h"

#include "CObject.h"

CScene::CScene()
{
}

CScene::~CScene()
{
	for (int i = 0; i < (int)GROUP_TYPE::END; ++i)
	{
		Safe_Delete_Vec(m_arrObj[i]);
	}	
}

void CScene::update()
{
	for (int i = 0; i < (int)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->update();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (int i = 0; i < (int)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->render(_dc);
		}
	}
}
