#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "Core.h"

#include "CPathMgr.h"
#include "CTexture.h"

#include "CCollisionMgr.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCamera.h"

#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"

CScene_Start::CScene_Start() = default;

CScene_Start::~CScene_Start() = default;

void CScene_Start::update()
{
	CScene::update();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}
}

void CScene_Start::Enter()
{
	// Scene ����
	
	// Player �߰�
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	//CObject* pOtherPlayer = pObj->Clone();
	//pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);
	
	//CCamera::GetInst()->SetTarget(pObj);

	
	// ���� ��ġ
	int iMonCount = 1;
	float fObjScale = 50.f;
	
	Vec2 vResolution = Core::GetInst()->GetResolution();

	AI* pAI = new AI;
	pAI->AddState(new CIdleState);
	pAI->AddState(new CTraceState);

	CMonster* pMonsterObj = nullptr;
	for (int i = 0; i < iMonCount; ++i)
	{
		// Monster Object �߰�
		pMonsterObj = new CMonster;
		pMonsterObj->SetName(L"Monster");
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		pMonsterObj->SetPos(vResolution * .5f - Vec2(0.f, 300.f));
		
		pMonsterObj->SetAI(pAI);
		
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

	// Ÿ�� �ε�
	//LoadTile(L"Tile\\start.tile");

	// �浹 ����
	// Player �׷�� Monster �׷� ���� �浹 üũ
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	// Camera Look ����
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	// Camera ȿ�� ����
	CCamera::GetInst()->FadeOut(2.f);
	CCamera::GetInst()->FadeIn(2.f);
	CCamera::GetInst()->FadeOut(2.f);
	CCamera::GetInst()->FadeIn(2.f);
}

void CScene_Start::Exit()
{
	// Scene Ż��
	DeleteAll();
	
	CCollisionMgr::GetInst()->Reset();
}
