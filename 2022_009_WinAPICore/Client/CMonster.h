#pragma once
#include "CObject.h"

struct tMonInfo
{
    float fHP;         // ü��
    float fSpeed;      // �ӵ�
    float fRecogRange; // �ν� ����
    float fAttRange;   // ���� ����
    float fAtt;        // ���ݷ�
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

