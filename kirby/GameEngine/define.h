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
#define MemoryDC CCore::GetInst()->GetMemoryDC()
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()



#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state 
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)


enum class GROUP_TYPE
{
	NON_DEFINE,
	PLAYER,
	MONSTER,

	END = 32,
};

enum class SCENE_TYPE
{
	START,
	STAGE_01,
	STAGE_02,
	STAGE_03,

	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	CHANGE_SCENE,
	CHANGE_KIRBY_STATE,


	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	BLACK,

	END,
};