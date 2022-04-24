#include "pch.h"
#include "Core.h"

Core::Core()
{
}

Core::~Core()
{
}

int Core::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정

	return S_OK;
}

void Core::progress()
{
}
