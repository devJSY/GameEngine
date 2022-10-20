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

void FScanf(char* _pOutBuff, FILE* _pFile)
{
	int i = 0;
	while (true)
	{
		char c = (char)getc(_pFile);	// 파일로부터 한글자씩 잘라온다
		if (c == '\n')					// 개행 문자였다면 널문자로 만든뒤 break
		{
			_pOutBuff[i++] = '\0';
			break;
		}

		_pOutBuff[i++] = c;
	}
}
