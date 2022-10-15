#include "global.h"

#include "CObject.h"
#include "CScene.h"

#include "CEventMgr.h"
#include "CSceneMgr.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::update()
{
	// Dead �޼��� ����
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}

	m_vecDead.clear();

	// �̺�Ʈ ó��
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}

	m_vecEvent.clear();
}

void CEventMgr::AddEvent(const tEvent& _eve)
{
	m_vecEvent.push_back(_eve);
}

void CEventMgr::Excute(const tEvent& _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParm : Object Adsress
		// wParm : Group Type
		CObject* pNewObj = (CObject*)_eve.lParm;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParm;

		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
	break;

	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParm : Object Adsress
		CObject* pDeadObj = (CObject*)_eve.lParm;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
	break;

	case EVENT_TYPE::CHANGE_SCENE:
	{
		// lParm : SCENE_TYPE
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParm);
		//CUIMgr::GetInst()->SetFocusedUI(nullptr);
	}
	break;

	case EVENT_TYPE::CHANGE_KIRBY_STATE:
	{
	}
	break;
	}

}