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

#include "CResMgr.h"
#include "CTexture.h"

Core::Core()
	: m_hWnd(nullptr)
	, m_ptResolution{}
	, m_hdc(nullptr)
	, m_arrBrush{}
	, m_arrPen{}
{
}

Core::~Core()
{
	ReleaseDC(m_hWnd, m_hdc);

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

	// 이중 버퍼링 용도의 텍스처 한 장을 만든다.
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);

	// 자주 사용 할 펜 및 브러쉬 설정
	CreateBrushPen();

	// Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CCamera::GetInst()->init();
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
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	BitBlt(m_hdc
		, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_pMemTex->GetDC()
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
