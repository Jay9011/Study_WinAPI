#pragma once

class Core
{
	SINGLE(Core);
private:
	Core();
	~Core();

private:
	HWND	m_hWnd;			// ���� ������ �ڵ�
	POINT	m_ptResolution;	// ���� ������ �ػ�

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

};

