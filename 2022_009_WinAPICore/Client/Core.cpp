#include "pch.h"
#include "Core.h"
#include "resource.h"

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

#include "SelectGDI.h"

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

	DestroyMenu(m_hMenu);
}

int Core::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// �ػ󵵿� �°� ������ ũ�� ����
	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);

	// �޴��� ����
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));
	


	
	m_hdc = GetDC(m_hWnd);

	// ���� ���۸� �뵵�� �ؽ�ó �� ���� �����.
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);

	// ���� ��� �� �� �� �귯�� ����
	CreateBrushPen();

	// Manager �ʱ�ȭ
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
	CCollisionMgr::GetInst()->update();	// �浹 üũ
	CUIMgr::GetInst()->update();		// UI �̺�Ʈ üũ


	// === === === ===
	//    Rendering
	// === === === ===
	// ȭ�� Clear
	Clear();

	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	BitBlt(m_hdc
		, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_pMemTex->GetDC()
		, 0, 0
		, SRCCOPY
	);

	CTimeMgr::GetInst()->render();	// ������ â�� FPS�� DT ǥ��


	// === === === ===
	// �̺�Ʈ ����ó��
	// === === === ===
	CEventMgr::GetInst()->update();
}

void Core::DockingMenu()
{
	SetMenu(m_hWnd, m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void Core::DividieMenu()
{
	SetMenu(m_hWnd, nullptr);
	ChangeWindowSize(GetResolution(), false);
}

void Core::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	RECT rt = { 0, 0, (int)_vResolution.x, (int)_vResolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
}

void Core::Clear()
{
	SelectGDI gdi(m_pMemTex->GetDC(), BRUSH_TYPE::BLACK);
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}

void Core::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK]  = (HBRUSH)GetStockObject(BLACK_BRUSH);

	// pen
	m_arrPen[(UINT)PEN_TYPE::RED]   = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE]  = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}
