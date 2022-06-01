#include "pch.h"
#include "CTexture.h"

#include "Core.h"

CTexture::CTexture()
	: m_dc(nullptr)
	, m_hBit(nullptr)
	, m_bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	// 파일로부터 로딩한 데이터를 비트맵으로 생성
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str()
								, IMAGE_BITMAP
								, 0, 0
								, LR_CREATEDIBSECTION | LR_LOADFROMFILE
								);
	assert(m_hBit);

	// 비트맵과 연결할 DC 생성
	m_dc = CreateCompatibleDC(Core::GetInst()->GetMainDC());

	// 비트맵과 DC 연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	// 비트맵(Object) 정보
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
	
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC maindc = Core::GetInst()->GetMainDC();
	
	// 비트맵 생성
	m_hBit = CreateCompatibleBitmap(maindc, _iWidth, _iHeight);
	// 비트맵과 연결할 DC 생성
	m_dc = CreateCompatibleDC(maindc);

	// 비트맵과 DC 연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	// 비트맵(Object) 정보
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}
