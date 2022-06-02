#include "pch.h"
#include "CMonFactory.h"

#include "CMonster.h"
#include "AI.h"

#include "CIdleState.h"
#include "CTraceState.h"


CMonster* CMonFactory::CreateMonster(MON_TYPE _eType, Vec2 _vPos)
{
	CMonster* pMon = nullptr;
	
	switch (_eType)
	{
	case MON_TYPE::NORMAL:
	{
		pMon = new CMonster;
		pMon->SetPos(_vPos);

		tMonInfo info = {};
		info.fHP = 100.f;
		info.fSpeed = 150.f;
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 300.f;

		pMon->SetMonInfo(info);

		AI* pAI = new AI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CTraceState);
		pAI->SetCurState(MON_STATE::IDLE);

		pMon->SetAI(pAI);
	}
		break;
	case MON_TYPE::RANGE:
		
		break;
	default:
		break;
	}
	
	assert(pMon);
	return pMon;
}