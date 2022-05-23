#pragma once

// Singleton 매크로
#define SINGLE(type)	public:\
							static type* GetInst()\
							{\
								static type mgr;\
								return &mgr;\
							}\
						private:\
							type();\
							~type();

// Delta Time
#define DT	CTimeMgr::GetInst()->GetDT()
#define fDT	CTimeMgr::GetInst()->GetfDT()

#define CLONE(type)	type* Clone() { return new type(*this); }

// KeyMgr 매크로
#define KEY_CHECK(key, state)	CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key)			KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key)			KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key)			KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key)			KEY_CHECK(key, KEY_STATE::NONE)

// Math
constexpr float PI = 3.1415926536f;

// Type Definition
enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MONSTER,
	PROJ_PLAYER,
	PROJ_MONSTER,

	END = 32
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END
};

enum class BRUSH_TYPE
{
	HOLLOW,
	
	END
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	END
};