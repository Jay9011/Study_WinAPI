#pragma once
#include "CObject.h"
class CMonster :
    public CObject
{
public:
    CMonster();
    ~CMonster() override;

    void update() override;

    float GetSpeed() const { return m_fSpeed; }
    void  SetSpeed(float _f) { m_fSpeed = _f; }

    void  SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
    void  SetMoveDistance(float _f) { m_fMaxDistance = _f; }

private:
    Vec2    m_vCenterPos;
    float   m_fSpeed;
    float   m_fMaxDistance;
    int     m_iDir;



};

