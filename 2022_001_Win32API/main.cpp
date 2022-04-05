#include "framework.h"
#include "main.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름

// 함수 전방 선언:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// SAL ( 소스코드 주석 )
int APIENTRY wWinMain(_In_      HINSTANCE hInstance,     // 프로세스가 시작되는 메모리 주소
                      _In_opt_  HINSTANCE hPrevInstance, // 이전 프로세스의 시작 주소...였으나 현재는 가상메모리를 사용하면서 쓰이지 않게 되었다.
                      _In_      LPWSTR    lpCmdLine,     // CMD로 추가적인 명령어를 받음.
                      _In_      int       nCmdShow)      // 윈도우가 처음 실행될 때 어떻게 보여질지 설정을 받아온다. (기본, 최대화, 최소화)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 리소스의 String Table에, 저장된 ID의 문자열로 초기화 한다. (Resource.h에 ID값과 #define이 저장되어 있다.)
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY2022001WIN32API, szWindowClass, MAX_LOADSTRING);

    /*
    *   Process =/= Window
    *   프로세스와 윈도우는 같은 개념이 아니다 !!
    *   쉬운 예로 백그라운드 프로그램 같은 경우 Process는 할당 받지만 Window를 생성하지는 않는다.
    */
    
    // 윈도우 기본 정보 등록 (어떤 형태로 윈도우를 띄울지에 대한 정보를 생성한다)
    MyRegisterClass(hInstance);
    
    // 윈도우 생성 (상호작용을 위한 UI를 생성)
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 단축키 정보. 리소스의 Accelerator에 단축키 정보가 들어있다.
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2022001WIN32API));

    MSG msg;

    // 기본 메시지 루프
    /*
    *   GetMessage
    *   Message Queue 에 메시지가 없으면 메시지를 받을 때까지 대기한다.
    *   ( false를 반환하면 프로그램이 종료되기 때문에,
    *     msg.message == WM_QUIT 을 받을때 false를 반환하여 프로그램을 종료시킨다. )
    */
    // 발생한 Message Queue에서 Message를 꺼내 본인 Message Queue에 저장한다.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        // 단축키가 눌렸는지에 대한 정보를 TranslateAccelerator()로 확인한다.
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg); // 메시지를 해석한 후
            DispatchMessage(&msg);  // 해당 윈도우의 처리기에 메시지를 전달한다.
        }
    }

    return (int) msg.wParam;
}



//
//  창 클래스 구조체를 채운 뒤 RegisterClassExW(&WNDCLASSEXW)를 통해 창 정보를 등록한다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;          // 메시지 발생시 처리할 함수를 함수 포인터에 저장.
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2022001WIN32API));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY2022001WIN32API);
    wcex.lpszClassName  = szWindowClass;    // 정보를 찾을 Key를 szWindowClass 리소스로 만든다.
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다. (UI 창을 만들고 사용자에게 보여준다)
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // CreateWindowW()시 szWindowClass 리소스로 윈도우 정보를 찾아온다.
   // 올바른 정보를 찾은 후 CreateWindowW()로 윈도우를 생성한다.
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   // 윈도우 만들기에 실패하면 FALSE를 리턴
   if (!hWnd)
   {
      return FALSE;
   }

   // 윈도우를 보여주고 업데이트한다.
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            Rectangle(hdc, 10, 10, 1920, 1024);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        // 처리하지 못한 메시지는 DefWindowProc()로 기본 윈도우 프로시저에서 처리한다.
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
