#pragma once

enum class KEY_STATE
{
    NONE,   // ������ ���� ���� �ʾҰ� ���ݵ� �������� ����
    TAP,    // ������ ���� ���� �ʾҰ� ���� ����
    HOLD,   // �������� �����ְ� ���ݵ� ����������
    AWAY,   // ������ �����־��� ������ �������� ����
};

enum class KEY
{
    LEFT,
    RIGHT,
    UP,
    DOWN,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,

	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,

	Z,
	X,
	C,
	V,
	B,
	N,
	M,

	LBTN,
	RBTN,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LAST,
};

struct tKeyInfo
{
    KEY_STATE	key_state;
    bool		bPrevPush;
};


class CKeyMgr :
    public CRoot
{
    SINGLE(CKeyMgr);

private:
	vector<tKeyInfo>	 m_veckey;
	Vec2				 m_vCurMousePos;

public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_veckey[(int)_eKey].key_state; }
	Vec2 GetMousePos() { return m_vCurMousePos; }

};

