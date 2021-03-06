#include "pch.h"
#include "CTile.h"

#include "CTexture.h"

CTile::CTile()
    : m_pTileTex(nullptr)
    , m_iImgIdx(0)
{
    SetScale(Vec2((float)TILE_SIZE, (float)TILE_SIZE));
}

CTile::~CTile() = default;

void CTile::update()
{
}

void CTile::render(HDC _dc)
{
    if (nullptr == m_pTileTex || -1 == m_iImgIdx)
        return;

    UINT iWidth  = m_pTileTex-> Width();
    UINT iHeight = m_pTileTex-> Height();

    UINT iMaxCol = iWidth / TILE_SIZE;
    UINT iMaxRow = iHeight / TILE_SIZE;

    UINT iCurCol = (UINT)m_iImgIdx % iMaxCol;
    UINT iCurRow = (UINT)m_iImgIdx / iMaxCol;

    // 이미지 범위를 벗어난 인덱스에 접근하려는 경우
    if (iMaxRow <= iCurRow)
        assert(nullptr);

    Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
    Vec2 vScale = GetScale();
    
    BitBlt(_dc
        , (int)(vRenderPos.x)
        , (int)(vRenderPos.y)
        , (int)(vScale.x)
        , (int)(vScale.y)
        , m_pTileTex-> GetDC()
        , iCurCol * TILE_SIZE
        , iCurRow * TILE_SIZE
        , SRCCOPY
        );

}

void CTile::Save(FILE* _pFile)
{
    fwrite(&m_iImgIdx, sizeof(m_iImgIdx), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
    fread(&m_iImgIdx, sizeof(m_iImgIdx), 1, _pFile);
}
