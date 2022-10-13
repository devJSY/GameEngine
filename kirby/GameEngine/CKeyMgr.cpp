#include "global.h"
#include "CKeyMgr.h"
#include "CCore.h"

// enum class KEY �� �����Ǵ� �迭
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

	//LAST, // ���� �˸��� �뵵�� ������ �ʿ䰡����
};

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::init()
{
	// ��� Ű�� �ʱ�ȭ vector 
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_veckey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::update()
{
	// ���� ��Ŀ�� �� ������ �ڵ�
	HWND hWnd = GetFocus();

	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			// ���� Key�� ���� �ִ���
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_veckey[i].bPrevPush)
				{
					// �������� �����־���
					m_veckey[i].key_state = KEY_STATE::HOLD;
				}
				else
				{
					// ������ �������� �ʾҴ�
					m_veckey[i].key_state = KEY_STATE::TAP;
				}

				m_veckey[i].bPrevPush = true;
			}

			// �̹� �����ӿ� �������� �ʾҴ�
			else
			{
				if (m_veckey[i].bPrevPush)
				{
					// �������� �����־���
					m_veckey[i].key_state = KEY_STATE::AWAY;
				}
				else
				{
					// ������ �������� �ʾҴ�
					m_veckey[i].key_state = KEY_STATE::NONE;
				}

				m_veckey[i].bPrevPush = false;
			}
		}
	}

	// ��Ŀ�̵� �����찡 ����
	else
	{
		// ��Ŀ�� ����
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
	// ���� ���콺 Pos �� �޾ƿ´�
	GetCursorPos(&MousePos);
	// ���콺 Pos �� ��ũ�� ��ǥ���� Ư�� Ŭ���̾�Ʈ ��ǥ�� �ٲ��ش�
	ScreenToClient(MainHwnd, &MousePos);
	m_vCurMousePos = MousePos;
}
