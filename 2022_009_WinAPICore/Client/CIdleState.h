#pragma once
#include "CState.h"
class CIdleState :
    public CState
{
private:

	
public:
	// CState��(��) ���� ��ӵ�
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void update() override;

public:
	CIdleState();
	~CIdleState() override;

};

