#include "global.h"
#include "CUIMgr.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"

#include "CUI.h"
#include "CScene.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{}

CUIMgr::~CUIMgr()
{}

void CUIMgr::update()
{
	// 1. FocusedUI 확인
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
	{
		return; // FocusedUI 없는 경우 종료
	}

	// 2. FocusedUI 내에서, 부모 UI 포함, 자식 UI 둘 중 실제 타겟팅 된 UI 를 가져온다.
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	bool bLbtnAway = KEY_AWAY(KEY::LBTN);
	bool bLbtnTap = KEY_TAP(KEY::LBTN);


	// 타겟팅된 UI가 있을 경우
	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn(); // 현재 UI에 마우스가 올라가있다

		if (bLbtnTap)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown)	// 이전에 눌려있었고 이번에 떼진경우 클릭된것으로 처리
			{
				pTargetUI->MouseLbtnClicked();
			}

			// 왼쪽버튼 떼면, 눌렷던 체크를 다시 해제한다.
			pTargetUI->m_bLbtnDown = false;
		}
	}
}

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
}

CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// 기존 포커싱 UI를 받아 두고 변경되었는지 확인한다.
	CUI* pFocusedUI = m_pFocusedUI;

	// 포커싱 변경 이벤트가 발생하지않은 경우 리턴
	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	// 왼쪽버튼 TAP 이 발생했다는 전제하
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)(*iter))->IsMouseOn())
		{
			targetiter = iter; // 현재 UI위에 마우스가 올라가있다면 변경
		}
	}

	// 이번에 Focus 된 UI 가 없다.
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	// 백터 내에서 맨 뒤로 순번 교체
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// 1. 부모 UI 포한, 모든 자식들을 검사 한다.
	CUI* pTargetUI = nullptr;

	static list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// 큐에서 데이터 하나 꺼내기
		CUI* pUI = queue.front();
		queue.pop_front();

		// 큐에서 꺼내온 UI 가 TargetUI 인지 확인
		// 2. 타겟 UI 들 중, 더 우선순위가 높은 기준은 더 낮은 계층의 자식 UI	
		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);	// 기존에 갖고있던 타겟 UI 는 해제
			}

			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);	// 기존에 갖고있던 타겟 UI 는 해제
		}

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);	// 현재 UI의 자식 UI 를 queue 에 넣는다
		}
	}

	// 왼쪽버튼 떼면, 눌렷던 체크를 다시 해제한다.
	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	return pTargetUI;
}
