#pragma once

class Core
{
	SINGLE(Core);
private:
	HWND	m_hWnd;			// 메인 윈도우 핸들
	POINT	m_ptResolution;	// 메인 윈도우 해상도
	HDC		m_hdc;			// 메인 윈도우에 Draw 할 DC

	HBITMAP	m_hBit;
	HDC		m_memDC;

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

public:
	HWND GetMainHWnd() { return m_hWnd; }
};

