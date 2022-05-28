#include "pch.h"
#include "Core.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"

Core::Core()
	: m_hWnd(nullptr)
	, m_ptResolution{}
	, m_hdc(nullptr)
	, m_hBit(nullptr)
	, m_memDC(nullptr)
	, m_arrBrush{}
	, m_arrPen{}
{
}

Core::~Core()
{
	ReleaseDC(m_hWnd, m_hdc);
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	for (UINT i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
	}
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

	// 이중 버퍼링 용도의 비트맵과 DC를 만든다.
	m_hBit = CreateCompatibleBitmap(m_hdc, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hdc);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);	// memDC가 가지고 있던 1pixel짜리 더미 Bitmap을 삭제

	// 자주 사용 할 펜 및 브러쉬 설정
	CreateBrushPen();

	// Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();
	
	return S_OK;
}

void Core::progress()
{
	// === === === ===
	// Manager Update
	// === === === ===
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();
	
	
	// === === === ===
	//  Scene Update
	// === === === ===
	CSceneMgr::GetInst()->update();
	CCollisionMgr::GetInst()->update();	// 충돌 체크
	CUIMgr::GetInst()->update();		// UI 이벤트 체크


	// === === === ===
	//    Rendering
	// === === === ===
	// 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC);

	BitBlt(m_hdc
		, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC
		, 0, 0
		, SRCCOPY
	);

	CTimeMgr::GetInst()->render();	// 원도우 창에 FPS와 DT 표시


	// === === === ===
	// 이벤트 지연처리
	// === === === ===
	CEventMgr::GetInst()->update();
}

void Core::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	// pen
	m_arrPen[(UINT)PEN_TYPE::RED]   = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE]  = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}
