#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{
public:
    CScene_Start();
    ~CScene_Start() override;

    void update() override;
    void Enter() override;
    void Exit()  override;

};

