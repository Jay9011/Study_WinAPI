#pragma once
#include "CObject.h"

struct tMonInfo
{
    float fHP;         // 체력
    float fSpeed;      // 속도
    float fRecogRange; // 인식 범위
    float fAttRange;   // 공격 범위
    float fAtt;        // 공격력
};

class AI;
class CMonster :
    public CObject
{
private:
	AI*      m_pAI;
    tMonInfo m_tInfo;
    
public:
    void update() override;

    float GetSpeed() const   { return m_tInfo.fSpeed; }
    void  SetSpeed(float _f) { m_tInfo.fSpeed = _f; }
	
    void  SetAI(AI* _pAI);

	const tMonInfo& GetInfo() const { return m_tInfo; }

private:
    void SetMonInfo(const tMonInfo& _info) { m_tInfo = _info; }

public:
    void  OnCollisionEnter(CCollider* _pOther) override;
	
public:
    CMonster();
    ~CMonster() override;
    CLONE(CMonster)

    friend class CMonFactory;
};

