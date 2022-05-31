#pragma once
#include "CScene.h"

class CScene_Tool : public CScene
{
private:
	CUI* m_pUI;

public:
	void update() override;
	void Enter() override;
	void Exit() override;

	void SetTileIdx();
	void SaveTileData();
	void SaveTile(const wstring& _strFilePath);
	void LoadTileData();

public:
	CScene_Tool();
	~CScene_Tool() override;

};
