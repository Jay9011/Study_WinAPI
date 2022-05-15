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
	// ���Ϸκ��� �ε��� �����͸� ��Ʈ������ ����
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str()
								, IMAGE_BITMAP
								, 0, 0
								, LR_CREATEDIBSECTION | LR_LOADFROMFILE
								);
	assert(m_hBit);

	// ��Ʈ�ʰ� ������ DC ����
	m_dc = CreateCompatibleDC(Core::GetInst()->GetMainDC());

	// ��Ʈ�ʰ� DC ����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	// ��Ʈ��(Object) ����
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
	
}
