#pragma once

// Singleton
#define SINGLE(type) public: \
				static type* GetInst()\
				{\
						static type inst;\
						return &inst;\
				}\
				private:\
					type();\
					~type();\

#define DT CTimeMgr::GetInst()->GetDT()
#define fDT CTimeMgr::GetInst()->GetfDT()

#define CLONE(type) type* Clone() { return new type(*this); }

#define MainHwnd CCore::GetInst()->GetMainHwnd()
#define MainDC CCore::GetInst()->GetMainDC()
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()



#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state 
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

#define TILE_SIZE 32


enum class GROUP_TYPE
{
	BackGround,
	ForeGround,
	PLAYER,
	MONSTER,
	UI,
	GROUND,
	TILE,

	END = 32,
};

enum class SCENE_TYPE
{
	START,
	STAGE_01,
	STAGE_02,
	STAGE_03,
	Animation_Tool,
	Scene_Tool,

	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	CHANGE_SCENE,
	CHANGE_KIRBY_STATE,
	CHANGE_AI_STATE,


	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	YELLOW,
	PURPLE,
	PINK,
	BLACK,

	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	BLACK,
	WHITE,
	RED,

	END,
};

enum class MON_STATE
{
	IDLE,
	PATROL,
	TRACE,
	ATTACK,
	RUN,
	DEAD,
};