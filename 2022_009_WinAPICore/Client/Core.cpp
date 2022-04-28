#include "pch.h"
#include "Core.h"
#include "CObject.h"

CObject g_obj;

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

	g_obj.m_ptPos = POINT{ m_ptResolution.x / 2, m_ptResolution.y / 2 };
	g_obj.m_ptScale = POINT{ 100, 100 };

	return S_OK;
}

void Core::progress()
{
	update();	// 변경점 적용
	render();	// 그리기
}

void Core::update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		g_obj.m_ptPos.x -= 1;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_obj.m_ptPos.x += 1;
	}
}

void Core::render()
{
	// 그리기
	Rectangle(m_hdc
		, g_obj.m_ptPos.x - g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2
		, g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2);
}
