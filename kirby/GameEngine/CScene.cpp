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
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->update();

				m_arrObj[i][j]->Component_update();
			}
		}
	}
}

void CScene::render(HDC _dc)
{
	for (int i = 0; i < (int)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->render(_dc);

				m_arrObj[i][j]->Component_render(_dc);
			}			
		}
	}
}

void CScene::DeadObjectErase()
{
	for (int i = 0; i < (int)GROUP_TYPE::END; ++i)
	{
		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end();)
		{
			if ((*iter)->IsDead())
			{
				// 삭제 될경우 다음 순번을 iter에 넣음
				iter = m_arrObj[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}
