#pragma once
#include "CScene.h"

class CScene_Tool : public CScene
{
private:


public:
	void update() override;
	void Enter() override;
	void Exit() override;

	void SetTileIdx();

public:
	CScene_Tool();
	~CScene_Tool() override;

};
