#pragma once

class Core
{
	SINGLE(Core);
private:
	HWND	m_hWnd;			// ���� ������ �ڵ�
	POINT	m_ptResolution;	// ���� ������ �ػ�
	HDC		m_hdc;			// ���� �����쿡 Draw �� DC

	HBITMAP	m_hBit;
	HDC		m_memDC;

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

public:
	HWND GetMainHWnd() { return m_hWnd; }
};

