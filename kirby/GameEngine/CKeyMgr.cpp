#include "global.h"
#include "CKeyMgr.h"
#include "CCore.h"

// enum class KEY 에 대응되는 배열
int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,//LEFT,
	VK_RIGHT,//RIGHT,
	VK_UP,//UP,
	VK_DOWN,//DOWN,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',

	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',

	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',

	VK_LBUTTON,
	VK_RBUTTON,

	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,

	//LAST, // 끝을 알리는 용도로 지정할 필요가없음
};

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::init()
{
	// 모든 키의 초기화 vector 
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_veckey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::update()
{
	// 현재 포커싱 된 윈도우 핸들
	HWND hWnd = GetFocus();

	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			// 현재 Key가 눌려 있는지
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_veckey[i].bPrevPush)
				{
					// 이전에도 눌려있었다
					m_veckey[i].key_state = KEY_STATE::HOLD;
				}
				else
				{
					// 이전에 눌려있지 않았다
					m_veckey[i].key_state = KEY_STATE::TAP;
				}

				m_veckey[i].bPrevPush = true;
			}

			// 이번 프레임에 눌려있지 않았다
			else
			{
				if (m_veckey[i].bPrevPush)
				{
					// 이전에도 눌려있었다
					m_veckey[i].key_state = KEY_STATE::AWAY;
				}
				else
				{
					// 이전에 눌려있지 않았다
					m_veckey[i].key_state = KEY_STATE::NONE;
				}

				m_veckey[i].bPrevPush = false;
			}
		}
	}

	// 포커싱된 윈도우가 없다
	else
	{
		// 포커싱 해제
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_veckey[i].bPrevPush = false;

			if (KEY_STATE::TAP == m_veckey[i].key_state || KEY_STATE::HOLD == m_veckey[i].key_state)
			{
				m_veckey[i].key_state = KEY_STATE::AWAY;
			}

			else if (KEY_STATE::AWAY == m_veckey[i].key_state)
			{
				m_veckey[i].key_state = KEY_STATE::NONE;

			}
		}
	}


	POINT MousePos = {};
	// 현재 마우스 Pos 를 받아온다
	GetCursorPos(&MousePos);
	// 마우스 Pos 를 스크린 좌표에서 특정 클라이언트 좌표로 바꿔준다
	ScreenToClient(MainHwnd, &MousePos);
	m_vCurMousePos = MousePos;
}
