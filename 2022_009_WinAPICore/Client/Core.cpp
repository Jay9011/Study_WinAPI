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

	// �ػ󵵿� �°� ������ ũ�� ����

	return S_OK;
}

void Core::progress()
{
}
