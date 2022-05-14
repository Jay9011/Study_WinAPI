#pragma once
#include "CObject.h"

class CPlayer : public CObject
{
public:
	void update() override;

private:
	void CreateMissile();
};

