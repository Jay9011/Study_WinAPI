#pragma once
#include "CObject.h"

class CTexture;

class CTile : public CObject
{
private:
    CTexture* m_pTileTex;
    int       m_iImgIdx;

public:
    virtual void Save(FILE* _pFile);
    virtual void Load(FILE* _pFile);

    void SetTexture(CTexture* _pTex)
    {
        m_pTileTex = _pTex;
    }

    void AddImgIdx()
    {
        ++m_iImgIdx;
    }


private:
    void update() override;
    void render(HDC _dc) override;

    CLONE(CTile)
public:
    CTile();
    ~CTile();
};

