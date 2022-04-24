#pragma once

class Core
{
	SINGLE(Core);
private:
	Core();
	~Core();

private:
	HWND	m_hWnd;			// 메인 윈도우 핸들
	POINT	m_ptResolution;	// 메인 윈도우 해상도

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

};

