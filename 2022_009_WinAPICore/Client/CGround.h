#pragma once
#include "CObject.h"

class CGround :
    public CObject
{
private:

public:
	void start() override;
	void update() override;

public:
	void OnCollisionEnter(CCollider* _pOther) override;
	void OnCollision(CCollider* _pOther) override;
	void OnCollisionExit(CCollider* _pOther) override;

public:
	CGround();
	~CGround() override;
	CLONE(CGround)
};

