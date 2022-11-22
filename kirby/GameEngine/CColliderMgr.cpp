#include "global.h"
#include "CColliderMgr.h"

#include "CObject.h"
#include "CScene.h"
#include "CCollider.h"

#include "CSceneMgr.h"

CColliderMgr::CColliderMgr()
	: m_arrCheck{}
{
}

CColliderMgr::~CColliderMgr()
{
}

void CColliderMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			// ��Ʈ�� On �Ǿ��ִ��� Ȯ��
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}

}
void CColliderMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// �� (�׻� ������ ����)
	UINT iRow = (UINT)_eLeft;

	// �� (�׻� �ຸ�� ŭ)
	UINT iCol = (UINT)_eRight;

	if (iRow > iCol)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	// ���� ���ڰ��� üũ�ڽ� üũ
	if (m_arrCheck[iRow] & (1 << iCol))
	{
		// üũ �Ǿ��ִ°�� üũ ����
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		// 1�� iCol ��ŭ bit Shift �Ѱ��� üũ ��Ʈ üũ
		m_arrCheck[iRow] |= (1 << iCol);
	}
}


void CColliderMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;


	for (int i = 0; i < vecLeft.size(); ++i)
	{
		// �ݶ��̴��� ������� ��ŵ
		if(nullptr == vecLeft[i]->GetComponents(Component_TYPE::Collider))
		{
			continue;
		}

		for (int j = 0; j < vecRight.size(); ++j)
		{
			// �ݶ��̴��� ���ų� �ڱ� �ڽŰ��� �浹 üũ�� ��� ��ŵ
			if (nullptr == vecRight[j]->GetComponents(Component_TYPE::Collider)
				|| vecLeft[i] == vecRight[j])
			{
				continue;
			}

			CCollider* pLeftCol = (CCollider*)vecLeft[i]->GetComponents(Component_TYPE::Collider);
			CCollider* pRightCol = (CCollider*)vecRight[j]->GetComponents(Component_TYPE::Collider);

			COLLIDER_ID ID;
			ID.iLeft_id = pLeftCol->GetID();
			ID.iRight_id = pRightCol->GetID();

			// �浹ü���� ���� ID ����
			iter = m_mapColInfo.find(ID.ID);

			// �浹 ���� �̵���� ��� ���
			if (iter == m_mapColInfo.end())
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			// =========
			// �浹 üũ
			// =========

			// ���� �浹 ���̴�
			if (IsCollision(pLeftCol, pRightCol))
			{
				// ���� �������� �浹 ���̾���
				if (iter->second) 
				{
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						// ���������ӿ� �浹���̴�
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}

				// ���� �������� �浹���� �ƴϾ���
				else
				{					
					if (!(vecLeft[i]->IsDead() && vecRight[j]->IsDead()))
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}

			// ���� �浹 ���� �ƴϴ�
			else
			{
				if (iter->second)
				{
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CColliderMgr::IsCollision(CCollider* _eLeft, CCollider* _eRight)
{
	Vec2 LeftPos = _eLeft->GetFinalPos();
	Vec2 LeftScale = _eLeft->GetScale();

	Vec2 RightPos = _eRight->GetFinalPos();
	Vec2 RightScale = _eRight->GetScale();

	// �� �浹ü�� ��ǥ�ν��� ���̰��� �� �浹ü�� ������� �����ٸ� �浹���̴�
	if (abs(LeftPos.x - RightPos.x) <= (LeftScale.x + RightScale.x) / 2.f
		&& abs(LeftPos.y - RightPos.y) <= (LeftScale.y + RightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}


COLLIDER_DIR CColliderMgr::CollisionDIR(CCollider* _Check, CCollider* _Target)
{
	// �浿 �� ���°� �ƴ϶�� ����
	if (!IsCollision(_Check , _Target))
	{
		return COLLIDER_DIR{};
	}

	Vec2 CheckPos = _Check->GetFinalPos();
	Vec2 CheckScale = _Check->GetScale();

	Vec2 TargetPos = _Target->GetFinalPos();
	Vec2 TargetScale = _Target->GetScale();

	COLLIDER_DIR Check_Dir = {};

	// ������ġ ����
	if (CheckPos.x > TargetPos.x)
	{
		Check_Dir.LEFT = true;
	}
	else if(CheckPos.x < TargetPos.x)
	{
		Check_Dir.RIGHT = true;
	}

	if (CheckPos.y > TargetPos.y)
	{
		Check_Dir.TOP = true;
	}
	else if (CheckPos.y < TargetPos.y)
	{
		Check_Dir.BOTTOM = true;
	}

	// �浹�� ������ŭ�� ��ġ���� �����ͼ� ���밪���� ��
	Vec2 vDiff = ((CheckScale + TargetScale) / 2.f) - (CheckPos - TargetPos).Vec2_abs();
	Vec2 vDiff1 = ((CheckScale + TargetScale) / 2.f);
	Vec2 vDiff2 = (CheckPos - TargetPos).Vec2_abs();

	if (abs(vDiff.x) > abs(vDiff.y))
	{
		Check_Dir.LEFT = false;
		Check_Dir.RIGHT = false;
	}
	else
	{
		Check_Dir.TOP = false;
		Check_Dir.BOTTOM = false;

	}
	
	return Check_Dir;
}