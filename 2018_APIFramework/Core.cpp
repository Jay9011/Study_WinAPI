#include "Core.h"
#include "Scene/CSceneManager.h"
#include "Core/Timer.h"

CCore* CCore::instance = nullptr;
bool   CCore::m_bLoop  = true;

CCore::CCore()
    : m_hInst(nullptr)
    , m_hWnd(nullptr)
    , m_tRS{}
{
}

CCore::~CCore()
{
    DESTROY_SINGLE(CSceneManager);
    DESTROY_SINGLE(CTimer);
}

bool CCore::Init(HINSTANCE hInst)
{
	m_hInst = hInst;
    MyRegisterClass();
	
	// 해상도 설정
    m_tRS.iW = 1280;
	m_tRS.iH = 720;

    // 윈도우 생성
    if (!Create())
        return false;

    // 화면 DC를 만들어 준다.
    m_hDC = GetDC(m_hWnd);

    // 타이머 초기화
    if (!GET_SINGLE(CTimer)->Init())
        return false;

	// 장면 관리자 초기화
    if (!GET_SINGLE(CSceneManager)->Init())
        return false;

	return true;
}

int CCore::Run()
{
    MSG msg{};

    // PeekMessage는 메시지가 메시지큐에 없어도 바로 빠져나온다.
    // 메시지가 있을 경우 true, 없을 경우 false가 된다.
    // 메시지가 없는 시간이 윈도우의 데드타임이다.
    while (m_bLoop)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        // 메시지가 없을 때 (데드타임인 경우) 들어온다.
        else
        {
            Logic();
        }
    }
	
    return (int)msg.wParam;
}

void CCore::Logic()
{
	// 타이머 갱신
	GET_SINGLE(CTimer)->Update();
	
	float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();

    Input(fDeltaTime);
	Update(fDeltaTime);
    LateUpdate(fDeltaTime);
    Collision(fDeltaTime);
	Render(fDeltaTime);
	
}

void CCore::Input(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->Input(fDeltaTime);
}

int CCore::Update(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->Update(fDeltaTime);
    return 0;
}

int CCore::LateUpdate(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->LateUpdate(fDeltaTime);
    return 0;
}

void CCore::Collision(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->Collision(fDeltaTime);
}

void CCore::Render(float fDeltaTime)
{
    GET_SINGLE(CSceneManager)->Render(m_hDC, fDeltaTime);
}

LRESULT CCore::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    // 키가 눌렸을 때 들어오는 메시지
    case WM_KEYDOWN:
        // 이 메시지가 들어올 경우 wParam에 어떤 키를 눌렀는지가 들어온다.
        switch (wParam)
        {
        case VK_ESCAPE:
            m_bLoop = false;
            DestroyWindow(hWnd);
            break;
        default:
            break;
        }
        break;
    case WM_DESTROY:
        m_bLoop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

ATOM CCore::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style         = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc   = CCore::WndProc;
    wcex.cbClsExtra    = 0;
    wcex.cbWndExtra    = 0;
    wcex.hInstance     = m_hInst;
    wcex.hIcon         = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_MY2018APIFRAMEWORK));
    wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName  = nullptr;
    wcex.lpszClassName = L"AF18";
    wcex.hIconSm       = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL CCore::Create()
{
    m_hWnd = CreateWindowW(L"AF18", L"AF18", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)
    {
        return FALSE;
    }
    
	// 실제 윈도우 타이틀바나 메뉴를 포함한 윈도우의 크기를 구해준다.
    RECT rc = { 0, 0, m_tRS.iW, m_tRS.iH };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    // 위에서 구한 크기로 윈도우 클라이언트 영역의 크기를 원하는 크기로 맞춘다.
	SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    return TRUE;
}
