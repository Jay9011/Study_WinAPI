#pragma once
#include "CScene.h"

class CScene_Tool : public CScene
{
public:
	CScene_Tool();
	~CScene_Tool() override;

	void update() override;
	void Enter() override;
	void Exit() override;


};
