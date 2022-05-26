#include "pch.h"
#include "CScene_Tool.h"

#include "Core.h"
#include "CResMgr.h"
#include "CKeyMgr.h"

#include "CTile.h"

CScene_Tool::CScene_Tool() = default;

CScene_Tool::~CScene_Tool() = default;

void CScene_Tool::update()
{
	CScene::update();
}

void CScene_Tool::Enter()
{
	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\TILE.bmp");

	// 타일 생성
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			CTile* pTile = new CTile();
			pTile->SetPos(Vec2((float)j * TILE_SIZE, (float)i * TILE_SIZE));
			pTile->SetTexture(pTileTex);
			
			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}

	// Camera Look 지정
	Vec2 vResolution = Core::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(vResolution * .5f);
}

void CScene_Tool::Exit()
{
}
