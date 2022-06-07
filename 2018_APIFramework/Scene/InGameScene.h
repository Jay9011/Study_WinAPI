#pragma once
#include "CScene.h"
class CInGameScene :
    public CScene
{
public:
    virtual bool Init() override;

private:
    CInGameScene();
    virtual ~CInGameScene() override;

    friend class CSceneManager;
};

