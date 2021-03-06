#pragma once

class AI;
class CMonster;

class CState
{
private:
	AI*       m_pAI;
	MON_STATE m_eState;

public:
	AI*       GetAI() const      { return m_pAI; }
	MON_STATE GetType() const    { return m_eState; }
	CMonster* GetMonster() const;

public:
	virtual void update() = 0;
	virtual void Enter()  = 0;
	virtual void Exit()   = 0;
	
public:
	CState(MON_STATE _eState);
	virtual ~CState();
	
	friend class AI;
};

