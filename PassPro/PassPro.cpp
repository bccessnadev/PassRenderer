// PassPro.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "PassPro.h"

#include "RenderManager/RenderManager.h"
#include "ObjectManager/ObjectManager.h"

#include "ObjectManager/Object.h"
#include "Components/RenderingComponent.h"

#define MAX_LOADSTRING 100
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

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
    LoadStringW(hInstance, IDC_PASSPRO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PASSPRO));

    MSG msg;

    RenderManager* Renderer = RenderManager::Get();
    ObjectManager* World = new ObjectManager();

    Object* TriangleObject = new Object();
    CRenderingComponent* TriangleRenderComponent = new CRenderingComponent(TriangleObject, RMesh::Triangle({ 0.f, 0.5f }, { 0.5f, -0.5f }, { -0.5f, -0.5f }, {1.f, 0.f, 0.f, 1.f}));
    TriangleObject->AddComponent(TriangleRenderComponent);
    World->AddObject(TriangleObject);

    float Rotation = 0.f;
    float PositionVal = 0.f;

    // Main message loop:
    while (true) // Want rt update loop, not wait for message // GetMessage(&msg, nullptr, 0, 0))
    {
        PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);

        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (msg.message == WM_QUIT)
        {
            break;
        }

        // Make Debug Lines
        Matrix2D DebugMatrix(Vector2(cosf(PositionVal) * 0.5f, sinf(PositionVal) * 0.5f), Rotation);
        Vector2 XAxis(DebugMatrix.M[0][0], DebugMatrix.M[0][1]);
        Vector2 YAxis(DebugMatrix.M[1][0], DebugMatrix.M[1][1]);
        Vector2 Position(DebugMatrix.M[0][2], DebugMatrix.M[1][2]);
        XAxis = XAxis + Position;
        YAxis = YAxis + Position;
        Renderer->DrawDebugLine(Position, XAxis, Vector4(1.f, 1.f, 1.f, 1.f));
        Renderer->DrawDebugLine(Position, YAxis, Vector4(1.f, 1.f, 1.f, 1.f));

        Vector2 LocalVector1(0.25f, 0.25f);
        Vector2 GlobalVector1 = DebugMatrix * LocalVector1;
        Vector2 LocalVector2(0.5f, 0.5f);
        Vector2 GlobalVector2 = DebugMatrix * LocalVector2;

        Renderer->DrawDebugLine(GlobalVector1, GlobalVector2, Vector4(0.f, 1.f, 0.f, 1.f));

        Rotation += 0.01f;
        PositionVal += 0.01f;

        World->Update();
        Renderer->PreRender();
        World->Render();
        Renderer->PresentRender();
    }

    delete World;
    delete Renderer;

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PASSPRO));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PASSPRO);
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
      CW_USEDEFAULT, 0, WINDOW_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
    
   // Render manager init
   RenderManager::Initialize(hWnd);
  
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
    switch (message)
    {
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
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    //case WM_PAINT:
    //    {
    //        PAINTSTRUCT ps;
    //        HDC hdc = BeginPaint(hWnd, &ps);
    //        // TODO: Add any drawing code that uses hdc here...
    //        EndPaint(hWnd, &ps);
    //    }
    //    break;
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
