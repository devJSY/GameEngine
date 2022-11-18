#include "global.h"
#include "CScene.h"
#include "CCore.h"
#include "CCamera.h"

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
			}
		}
	}
}

void CScene::Component_update()
{
	for (int i = 0; i < (int)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (!m_arrObj[i][j]->IsDead())
			{
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
			if (!m_arrObj[i][j]->IsDead() && IsRenderArea(m_arrObj[i][j]))
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

void CScene::start()
{
	for (int i = 0; i < (int)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->start();
			}
		}
	}
}

void CScene::DeleteAll()
{
	for (size_t i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	Safe_Delete_Vec(m_arrObj[(UINT)_eTarget]);
}

bool CScene::IsRenderArea(CObject* _pobj)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(_pobj->GetPos());
	Vec2 vScale = _pobj->GetScale();
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	
	if (vRenderPos.x > 0.f && (vRenderPos.x + (vScale.x / 2.f)) - TILE_SIZE < vResolution.x
		&& vRenderPos.y > 0.f && (vRenderPos.y + (vScale.y / 2.f)) - TILE_SIZE < vResolution.y)
	{
		return true;
	}

	return false;	
}
