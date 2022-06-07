#pragma once
#include "../Game.h"

class CScene
{
public:
	virtual bool Init();

protected:
	CScene();
	virtual ~CScene() = 0;

	friend class CSceneManager;
};

