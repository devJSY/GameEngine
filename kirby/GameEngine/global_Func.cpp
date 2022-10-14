#include "global.h"

#include "CObject.h"
#include "CEventMgr.h"

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParm = (DWORD_PTR)_pObj;
	evn.wParm = (DWORD_PTR)_eGroup;

	CEventMgr::GetInst()->AddEvent(evn);
}

void DeleteObject(CObject* _pObj)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParm = (DWORD_PTR)_pObj;

	CEventMgr::GetInst()->AddEvent(evn);

}
void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CHANGE_SCENE;
	evn.lParm = (DWORD_PTR)_eNext;

	CEventMgr::GetInst()->AddEvent(evn);
}