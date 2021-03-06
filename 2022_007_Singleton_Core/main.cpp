// main.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "main.h"
#include <vector>
using std::vector;

#define MAX_LOADSTRING 100

struct ObjInfo
{
    POINT objectPos = { 500, 300 };
    POINT objectScale = { 100, 100 };
};
vector<ObjInfo> vecInfo;

bool lBtnDown = false;
POINT LeftTop;
POINT RightBottom;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND  g_hWnd;
POINT mousePoint;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY2022007SINGLETONCORE, szWindowClass, MAX_LOADSTRING);
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

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2022007SINGLETONCORE));

    MSG msg;

    // Peek 메시지 루프
    /*
    *   Peek : (재빨리) 훔쳐보다.
    *   메시지 유무와 관계없이 항상 반환.
    *   메시지큐에서 메시지를 확인한 경우 true, 메시지큐에 메시지가 없는 경우 false를 반환한다.
    */
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            // 단축키가 눌렸는지에 대한 정보를 TranslateAccelerator()로 확인한다.
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg); // 메시지를 해석한 후
                DispatchMessage(&msg);  // 해당 윈도우의 처리기에 메시지를 전달한다.
            }
        }
        // 메시지가 발생하지 않는 대부분의 시간
        else
        {
            // Game 코드 수행

        }
    }

    return (int) msg.wParam;
}


//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2022007SINGLETONCORE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY2022007SINGLETONCORE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

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

            // Device Context 를 만들어서 ID를 반환
            HDC hdc = BeginPaint(hWnd, &ps);    // Device Context ( 그리기 작업을 수행하기 위해 필요한 Data들의 집합 )
            // DC의 목적지는 hWnd
            // DC의 기본 펜은 Black
            // DC의 기본 브러쉬는 White

            // 직접 펜을 만들어서 DC에 지급
            HPEN hRenPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 128));
            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRenPen);    // 기존 Object를 type casting 해서 받아둠
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 128, 255));
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

            for (size_t i = 0; i < vecInfo.size(); i++)
            {
                Rectangle(hdc
                    , vecInfo[i].objectPos.x - vecInfo[i].objectScale.x / 2
                    , vecInfo[i].objectPos.y - vecInfo[i].objectScale.y / 2
                    , vecInfo[i].objectPos.x + vecInfo[i].objectScale.x / 2
                    , vecInfo[i].objectPos.y + vecInfo[i].objectScale.y / 2
                );
            }

            if (lBtnDown)
            {
                Rectangle(hdc
                    , LeftTop.x, LeftTop.y
                    , RightBottom.x, RightBottom.y);
            }

            // 원래 Object로 되돌려줌
            SelectObject(hdc, hDefaultPen);
            SelectObject(hdc, hDefaultBrush);

            // 다 쓴 Object 삭제 요청
            DeleteObject(hRenPen);  // Kernel ID를 직접 지울 수 없기 때문에, 함수로 요청해야 한다.
            DeleteObject(hBlueBrush);

            // 그리기 종료
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_KEYDOWN:
        {
            switch (wParam)
            {
            case VK_UP:
                //objectPos.y -= 10;
                InvalidateRect(hWnd, nullptr, true);   // 강제로 무효화 영역이 발생했다고 알림
                break;
            case VK_DOWN:
                //objectPos.y += 10;
                InvalidateRect(hWnd, nullptr, true);   // 강제로 무효화 영역이 발생했다고 알림
                break;
            case VK_LEFT:
                //objectPos.x -= 10;
                InvalidateRect(hWnd, nullptr, true);   // 강제로 무효화 영역이 발생했다고 알림
                break;
            case VK_RIGHT:
                //objectPos.x += 10;
                InvalidateRect(hWnd, nullptr, true);   // 강제로 무효화 영역이 발생했다고 알림
                break;
            case 'W':
                break;
            default:
                break;
            }
        }
        break;
    case WM_LBUTTONDOWN:
        {
            lBtnDown = true;
            LeftTop.x = LOWORD(lParam);
            LeftTop.y = HIWORD(lParam);
        }
        break;
    case WM_MOUSEMOVE:
        {
            if (lBtnDown)
            {
                RightBottom.x = LOWORD(lParam);
                RightBottom.y = HIWORD(lParam);
            }
            InvalidateRect(hWnd, nullptr, true);   // 강제로 무효화 영역이 발생했다고 알림
        }
        break;
    case WM_LBUTTONUP:
        {
            ObjInfo info = {};
            info.objectPos.x = (LeftTop.x + RightBottom.x) / 2;
            info.objectPos.y = (LeftTop.y + RightBottom.y) / 2;

            info.objectScale.x = abs(LeftTop.x - RightBottom.x);
            info.objectScale.y = abs(LeftTop.y - RightBottom.y);

            vecInfo.push_back(info);

            lBtnDown = false;
            InvalidateRect(hWnd, nullptr, true);   // 강제로 무효화 영역이 발생했다고 알림
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
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
