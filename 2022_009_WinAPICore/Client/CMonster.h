#pragma once
#include "CObject.h"
class AI;
class CMonster :
    public CObject
{
private:
	AI*     m_pAI;
	
    float   m_fSpeed;
    int     m_iHp;
    
public:
    void update() override;

    float GetSpeed() const   { return m_fSpeed; }
    void  SetSpeed(float _f) { m_fSpeed = _f; }
    void  SetAI(AI* _pAI)    { m_pAI = _pAI; m_pAI-> m_pOwner = this; }

public:
    void  OnCollisionEnter(CCollider* _pOther) override;
	
public:
    CMonster();
    ~CMonster() override;
    CLONE(CMonster)

};

