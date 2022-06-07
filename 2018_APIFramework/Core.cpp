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
	
	// �ػ� ����
    m_tRS.iW = 1280;
	m_tRS.iH = 720;

    // ������ ����
    if (!Create())
        return false;

    // Ÿ�̸� �ʱ�ȭ
    if (!GET_SINGLE(CTimer)->Init())
        return false;

	// ��� ������ �ʱ�ȭ
    if (!GET_SINGLE(CSceneManager)->Init())
        return false;

	return true;
}

int CCore::Run()
{
    MSG msg{};

    // PeekMessage�� �޽����� �޽���ť�� ��� �ٷ� �������´�.
    // �޽����� ���� ��� true, ���� ��� false�� �ȴ�.
    // �޽����� ���� �ð��� �������� ����Ÿ���̴�.
    while (m_bLoop)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        // �޽����� ���� �� (����Ÿ���� ���) ���´�.
        else
        {
            Logic();
        }
    }
	
    return (int)msg.wParam;
}

void CCore::Logic()
{
	// Ÿ�̸� ����
	GET_SINGLE(CTimer)->Update();
	
	float fDeltaTime = GET_SINGLE(CTimer)->GetDeltaTime();
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
    // Ű�� ������ �� ������ �޽���
    case WM_KEYDOWN:
        // �� �޽����� ���� ��� wParam�� � Ű�� ���������� ���´�.
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
    
	// ���� ������ Ÿ��Ʋ�ٳ� �޴��� ������ �������� ũ�⸦ �����ش�.
    RECT rc = { 0, 0, m_tRS.iW, m_tRS.iH };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    // ������ ���� ũ��� ������ Ŭ���̾�Ʈ ������ ũ�⸦ ���ϴ� ũ��� �����.
	SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    return TRUE;
}
