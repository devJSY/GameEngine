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
	// 1. FocusedUI Ȯ��
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
	{
		return; // FocusedUI ���� ��� ����
	}

	// 2. FocusedUI ������, �θ� UI ����, �ڽ� UI �� �� ���� Ÿ���� �� UI �� �����´�.
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	bool bLbtnAway = KEY_AWAY(KEY::LBTN);
	bool bLbtnTap = KEY_TAP(KEY::LBTN);


	// Ÿ���õ� UI�� ���� ���
	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn(); // ���� UI�� ���콺�� �ö��ִ�

		if (bLbtnTap)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pTargetUI->MouseLbtnUp();

			if (pTargetUI->m_bLbtnDown)	// ������ �����־��� �̹��� ������� Ŭ���Ȱ����� ó��
			{
				pTargetUI->MouseLbtnClicked();
			}

			// ���ʹ�ư ����, ���Ǵ� üũ�� �ٽ� �����Ѵ�.
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

	// ���� ��Ŀ�� UI�� �޾� �ΰ� ����Ǿ����� Ȯ���Ѵ�.
	CUI* pFocusedUI = m_pFocusedUI;

	// ��Ŀ�� ���� �̺�Ʈ�� �߻��������� ��� ����
	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	// ���ʹ�ư TAP �� �߻��ߴٴ� ������
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)(*iter))->IsMouseOn())
		{
			targetiter = iter; // ���� UI���� ���콺�� �ö��ִٸ� ����
		}
	}

	// �̹��� Focus �� UI �� ����.
	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	// ���� ������ �� �ڷ� ���� ��ü
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// 1. �θ� UI ����, ��� �ڽĵ��� �˻� �Ѵ�.
	CUI* pTargetUI = nullptr;

	static list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// ť���� ������ �ϳ� ������
		CUI* pUI = queue.front();
		queue.pop_front();

		// ť���� ������ UI �� TargetUI ���� Ȯ��
		// 2. Ÿ�� UI �� ��, �� �켱������ ���� ������ �� ���� ������ �ڽ� UI	
		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);	// ������ �����ִ� Ÿ�� UI �� ����
			}

			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);	// ������ �����ִ� Ÿ�� UI �� ����
		}

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);	// ���� UI�� �ڽ� UI �� queue �� �ִ´�
		}
	}

	// ���ʹ�ư ����, ���Ǵ� üũ�� �ٽ� �����Ѵ�.
	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	return pTargetUI;
}
