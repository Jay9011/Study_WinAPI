#pragma once
#include "CState.h"

class CTraceState
	:	public CState
{
private:

public:
	// CState을(를) 통해 상속됨
	virtual void update() override;
	virtual void Enter() override;
	virtual void Exit() override;

	
public:
	CTraceState();
	~CTraceState() override;

};

