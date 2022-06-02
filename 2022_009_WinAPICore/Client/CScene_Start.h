#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{
private:
    Vec2  m_vForcePos;
    float m_fForceRadius;
    float m_fCurRadius;
    float m_fForce;
    bool  m_bUseForce;

public:
    void update() override;
    void render(HDC _dc) override;
    void Enter() override;
    void Exit() override;

public:
    void CreateForce();
	
public:
    CScene_Start();
    ~CScene_Start() override;
};

