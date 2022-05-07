#include "pch.h"
#include "Core.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
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

	// Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	

	g_obj.SetPos(Vec2(m_ptResolution.x / 2.f, m_ptResolution.y / 2.f));
	g_obj.SetScale(Vec2(100, 100));

	return S_OK;
}

void Core::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->update();

	update();	// 변경점 적용
	render();	// 그리기
}

void Core::update()
{
	Vec2 vPos = g_obj.GetPos();
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vPos.x -= 200.f * CTimeMgr::GetInst()->GetfDT();
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 200.f * CTimeMgr::GetInst()->GetfDT();
	}

	g_obj.SetPos(vPos);
}

void Core::render()
{
	// 그리기
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();
	Rectangle(m_hdc
		, vPos.x - vScale.x / 2.f
		, vPos.y - vScale.y / 2.f
		, vPos.x + vScale.x / 2.f
		, vPos.y + vScale.y / 2.f);
}
