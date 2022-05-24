#pragma once
#include "CObject.h"

class CTexture;

class CPlayer : public CObject
{
public:
	CPlayer();
	~CPlayer() override;
	CLONE(CPlayer)

public:
	void update() override;
	void render(HDC _dc) override;

private:
	void CreateMissile();
};

