#pragma once
#include "CObject.h"

class CMissile :
    public CObject
{
public:
    CMissile();
    ~CMissile() override;

    void update() override;
    void render(HDC _dc) override;

    void SetDir(float _fTheta) { m_fTheta = _fTheta; }

private:
    float m_fTheta; // 이동방향 세타

};

