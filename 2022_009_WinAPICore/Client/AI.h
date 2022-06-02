#pragma once

class CMonster;
class CState;

class AI
{
private:
	// 유한 상태
	map<MON_STATE, CState*> m_mapState;
	
	CState*   m_pCurState;
	CMonster* m_pOwner;

public:
	void update();

public:
	void    AddState(CState* _pState);
	CState* GetState(MON_STATE _eState);
	void	SetCurState(MON_STATE _eState);
	
public:
	AI();
	virtual ~AI();

	friend class CMonster;
};

