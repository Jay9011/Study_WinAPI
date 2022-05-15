#pragma once
#include "CRes.h"

class CTexture : public CRes
{
public:
	CTexture();
	~CTexture() override;

	void Load(const wstring& _strFilePath);

private:
	HDC		m_dc;
	HBITMAP	m_hBit;

};

