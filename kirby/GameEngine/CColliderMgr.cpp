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
			// 비트가 On 되어있는지 확인
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}

}
void CColliderMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 행 (항상 열보다 작음)
	UINT iRow = (UINT)_eLeft;

	// 열 (항상 행보다 큼)
	UINT iCol = (UINT)_eRight;

	if (iRow > iCol)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	// 들어온 인자값의 체크박스 체크
	if (m_arrCheck[iRow] & (1 << iCol))
	{
		// 체크 되어있는경우 체크 해제
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		// 1을 iCol 만큼 bit Shift 한값에 체크 비트 체크
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
		// 콜라이더가 없을경우 스킵
		if(nullptr == vecLeft[i]->GetComponents(Component_TYPE::Collider))
		{
			continue;
		}

		for (int j = 0; j < vecRight.size(); ++j)
		{
			// 콜라이더가 없거나 자기 자신과의 충돌 체크인 경우 스킵
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

			// 충돌체간의 조합 ID 생성
			iter = m_mapColInfo.find(ID.ID);

			// 충돌 정보 미등록인 경우 등록
			if (iter == m_mapColInfo.end())
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			// =========
			// 충돌 체크
			// =========

			// 현재 충돌 중이다
			if (IsCollision(pLeftCol, pRightCol))
			{
				// 이전 프레임이 충돌 중이었다
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
						// 이전프레임에 충돌중이다
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}

				// 이전 프레임이 충돌중이 아니었다
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

			// 현재 충돌 중이 아니다
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

	// 두 충돌체의 좌표로써의 차이값이 두 충돌체의 사이즈보다 가깝다면 충돌중이다
	if (abs(LeftPos.x - RightPos.x) <= (LeftScale.x + RightScale.x) / 2.f
		&& abs(LeftPos.y - RightPos.y) <= (LeftScale.y + RightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}


COLLIDER_DIR CColliderMgr::CollisionDIR(CCollider* _Check, CCollider* _Target)
{
	// 충동 된 상태가 아니라면 리턴
	if (!IsCollision(_Check , _Target))
	{
		return COLLIDER_DIR{};
	}

	Vec2 CheckPos = _Check->GetFinalPos();
	Vec2 CheckScale = _Check->GetScale();

	Vec2 TargetPos = _Target->GetFinalPos();
	Vec2 TargetScale = _Target->GetScale();

	COLLIDER_DIR Check_Dir = {};

	// 접촉위치 선별
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

	// 충돌된 부위만큼의 위치값을 가져와서 절대값으로 비교
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