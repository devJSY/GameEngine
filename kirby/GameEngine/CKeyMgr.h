#pragma once

enum class KEY_STATE
{
    NONE,   // 이전에 눌려 있지 않았고 지금도 눌려있지 않음
    TAP,    // 이전에 눌려 있지 않았고 지금 눌림
    HOLD,   // 이전에도 눌려있고 지금도 눌려져있음
    AWAY,   // 이전에 눌려있었고 지금은 눌려있지 않음
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

