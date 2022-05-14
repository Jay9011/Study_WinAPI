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

    void SetDir(bool _bUp) 
    {
        if (_bUp)
            m_fDir = -1.f;
        else
            m_fDir = 1.f;
    }

private:
    float m_fDir;

};

