// CrashDummy.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "CrashDummy.h"
#include <string>

#define ID_CRASHBTN 1
#define ID_HANGBTN 2
#define ID_LOADDBGBTN 3

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CRASHDUMMY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CRASHDUMMY));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CRASHDUMMY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CRASHDUMMY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 400, 300, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hwndCrashButton;
    static HWND hwndHangButton;
    static HWND hwndLoadDbgButton;
    switch (message)
    {
    case WM_CREATE:
        {
            hwndCrashButton = CreateWindow(
                L"BUTTON",  // Predefined class; Unicode assumed 
                L"Crash",      // Button text 
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
                10,         // x position 
                10,         // y position 
                100,        // Button width
                50,        // Button height
                hWnd,     // Parent window
                (HMENU)ID_CRASHBTN,       // No menu.
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);      // Pointer not needed.
            hwndHangButton = CreateWindow(
                L"BUTTON",  // Predefined class; Unicode assumed 
                L"Hang",      // Button text 
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
                210,         // x position 
                10,         // y position 
                100,        // Button width
                50,        // Button height
                hWnd,     // Parent window
                (HMENU)ID_HANGBTN,       // No menu.
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);      // Pointer not needed.
            hwndLoadDbgButton = CreateWindow(
                L"BUTTON",  // Predefined class; Unicode assumed 
                L"Load Debugger",      // Button text 
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
                120,         // x position 
                100,         // y position 
                120,        // Button width
                50,        // Button height
                hWnd,     // Parent window
                (HMENU)ID_LOADDBGBTN,       // No menu.
                (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                NULL);      // Pointer not needed.
        }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_CRASHBTN:
            {
                //DebugBreak();
                int* x = 0;
                *x = 1;
            }
                break;
            case ID_HANGBTN:
            {
                //DebugBreak();
                while (1) continue;
            }
                break;
            case ID_LOADDBGBTN:
            {
                HANDLE hLocalProc = GetCurrentProcess();
                HANDLE hGlobalProc;
                WCHAR procPath[] = L"D:/nightfall/NightFall/CrashReporter/Release/CrashReporter.exe";

                if (!DuplicateHandle(hLocalProc,
                    hLocalProc,
                    hLocalProc,
                    &hGlobalProc,
                    0,
                    TRUE,
                    DUPLICATE_SAME_ACCESS))
                {
                    int msgboxID = MessageBox(
                        NULL,
                        (L"DuplicateHandle failed: " + std::to_wstring(GetLastError())).c_str(),
                        L"Error",
                        MB_ICONERROR | MB_OK
                    );
                    break;
                }

                STARTUPINFO si;
                PROCESS_INFORMATION pi;

                ZeroMemory(&si, sizeof(si));
                si.cb = sizeof(si);
                ZeroMemory(&pi, sizeof(pi));

                WCHAR cmdline[2048];
                DWORD pollDelay = 5000, hungDelay = 30000;
                wsprintf(cmdline, L"%s %p %u %u", procPath, hGlobalProc, pollDelay, hungDelay);
                if (!CreateProcess(NULL,   // No module name (use command line)
                    cmdline,        // Command line
                    NULL,           // Process handle not inheritable
                    NULL,           // Thread handle not inheritable
                    TRUE,          // Set handle inheritance to FALSE
                    0,              // No creation flags
                    NULL,           // Use parent's environment block
                    NULL,           // Use parent's starting directory 
                    &si,            // Pointer to STARTUPINFO structure
                    &pi)           // Pointer to PROCESS_INFORMATION structure
                    )
                {
                    int msgboxID = MessageBox(
                        NULL,
                        (L"CreateProcess failed: " + std::to_wstring(GetLastError())).c_str(),
                        L"Error",
                        MB_ICONERROR | MB_OK
                    );
                    break;
                }
                else
                {
                    int msgboxID = MessageBox(
                        NULL,
                        (L"CreateProcess success with cmdline: " + std::wstring(cmdline) + L"\nParent PID: " + std::to_wstring(GetCurrentProcessId())).c_str(),
                        L"Info",
                        MB_OK
                    );
                }
            }
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
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
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

// Message handler for about box.
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
