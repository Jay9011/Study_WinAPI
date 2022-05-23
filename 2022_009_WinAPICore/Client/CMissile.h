#pragma once
#include "CObject.h"

class CMissile :
    public CObject
{
public:
    CMissile();
    ~CMissile() override;
    CLONE(CMissile)

    void update() override;
    void render(HDC _dc) override;

    void OnCollisionEnter(CCollider* _pOther) override;

    void SetDir(float _fTheta)  { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir)     { m_vDir = _vDir; m_vDir.Normalize(); }

private:
    float   m_fTheta;   // �̵����� ��Ÿ
    Vec2    m_vDir;     // �̵����� ����
    
};

