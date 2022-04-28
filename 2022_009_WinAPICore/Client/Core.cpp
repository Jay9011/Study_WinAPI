#include "pch.h"
#include "Core.h"

Core::Core()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hdc(0)
{
}

Core::~Core()
{
	ReleaseDC(m_hWnd, m_hdc);
}

int Core::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hdc = GetDC(m_hWnd);

	return S_OK;
}

void Core::progress()
{
	// 그리기
	Rectangle(m_hdc, 10, 10, 110, 110);
}
