#pragma once
#include "CState.h"
class CIdleState :
    public CState
{
private:

	
public:
	// CState을(를) 통해 상속됨
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void update() override;

public:
	CIdleState();
	~CIdleState() override;

};

