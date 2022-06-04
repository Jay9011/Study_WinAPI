#pragma once
#include "CObject.h"

enum class PLAYER_STATE
{
	IDLE,
	WALK,
	ATTCK,
	JUMP,
	DEAD,
};

enum class PLAYER_DIRECTION
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

enum class PLAYER_ATTACK_STATE
{
	NORMAL_ATT_1,
	NORMAL_ATT_2,
	NORMAL_ATT_3,

	SKILL_ATT_1,
	// ...
};

class CTexture;
class CPlayer : public CObject
{
private:
	vector<CObject*> m_vecColObj;
	
	PLAYER_STATE     m_eCurState;
	PLAYER_STATE     m_ePrevState;
	PLAYER_DIRECTION m_iDir;
	PLAYER_DIRECTION m_iPrevDir;
	
public:
	void update() override;
	void render(HDC _dc) override;

private:
	void CreateMissile();
	void update_state();
	void update_move();
	void update_animation();
	void update_gravity();
	
public:
	CPlayer();
	~CPlayer() override;
	CLONE(CPlayer)
};

