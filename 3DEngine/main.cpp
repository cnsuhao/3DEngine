// 3DEngine.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "3DEngine.h"
#include "resource.h"

#define MAX_LOADSTRING 100

C3DEngine* pEngine = nullptr;
int nWindowWidth = 800;
int nWindowHeight = 600;

HINSTANCE g_hInstance = NULL;

void InitCube(CVerticesData& tData)
{
    float fEdgeLength = 4.0f;
    std::vector<CWorldCoordinate> pos;
    // 近
    pos.push_back(CWorldCoordinate(-fEdgeLength, fEdgeLength, fEdgeLength) );    // 左上
    pos.push_back(CWorldCoordinate(-fEdgeLength,-fEdgeLength, fEdgeLength) );    // 左下
    pos.push_back(CWorldCoordinate( fEdgeLength,-fEdgeLength, fEdgeLength) );    // 右下
    pos.push_back(CWorldCoordinate( fEdgeLength,-fEdgeLength, fEdgeLength) );    // 右下
    pos.push_back(CWorldCoordinate( fEdgeLength, fEdgeLength, fEdgeLength) );    // 右上
    pos.push_back(CWorldCoordinate(-fEdgeLength, fEdgeLength, fEdgeLength) );
    // 远
    pos.push_back(CWorldCoordinate( fEdgeLength, fEdgeLength,-fEdgeLength) );
    pos.push_back(CWorldCoordinate( fEdgeLength,-fEdgeLength,-fEdgeLength) );
    pos.push_back(CWorldCoordinate(-fEdgeLength,-fEdgeLength,-fEdgeLength) );
    pos.push_back(CWorldCoordinate(-fEdgeLength,-fEdgeLength,-fEdgeLength) );
    pos.push_back(CWorldCoordinate(-fEdgeLength, fEdgeLength,-fEdgeLength) );
    pos.push_back(CWorldCoordinate( fEdgeLength, fEdgeLength,-fEdgeLength) );
    // 左
    pos.push_back(CWorldCoordinate( fEdgeLength, fEdgeLength,-fEdgeLength) );
    pos.push_back(CWorldCoordinate( fEdgeLength,-fEdgeLength,-fEdgeLength) );
    pos.push_back(CWorldCoordinate( fEdgeLength,-fEdgeLength, fEdgeLength) );
    pos.push_back(CWorldCoordinate( fEdgeLength,-fEdgeLength, fEdgeLength) );
    pos.push_back(CWorldCoordinate( fEdgeLength, fEdgeLength, fEdgeLength) );
    pos.push_back(CWorldCoordinate( fEdgeLength, fEdgeLength,-fEdgeLength) );
    // 右
    pos.push_back(CWorldCoordinate(-fEdgeLength, fEdgeLength, fEdgeLength) );
    pos.push_back(CWorldCoordinate(-fEdgeLength,-fEdgeLength, fEdgeLength) );
    pos.push_back(CWorldCoordinate(-fEdgeLength,-fEdgeLength,-fEdgeLength) );
    pos.push_back(CWorldCoordinate(-fEdgeLength,-fEdgeLength,-fEdgeLength) );
    pos.push_back(CWorldCoordinate(-fEdgeLength, fEdgeLength,-fEdgeLength) );
    pos.push_back(CWorldCoordinate(-fEdgeLength, fEdgeLength, fEdgeLength) );

    // 上
    pos.push_back(CWorldCoordinate(-fEdgeLength, fEdgeLength,-fEdgeLength) );
    pos.push_back(CWorldCoordinate(-fEdgeLength, fEdgeLength, fEdgeLength) );
    pos.push_back(CWorldCoordinate( fEdgeLength, fEdgeLength, fEdgeLength) );
    pos.push_back(CWorldCoordinate( fEdgeLength, fEdgeLength, fEdgeLength) );
    pos.push_back(CWorldCoordinate( fEdgeLength, fEdgeLength,-fEdgeLength) );
    pos.push_back(CWorldCoordinate(-fEdgeLength, fEdgeLength,-fEdgeLength) );

    // 下
    pos.push_back(CWorldCoordinate(-fEdgeLength,-fEdgeLength, fEdgeLength) );
    pos.push_back(CWorldCoordinate(-fEdgeLength,-fEdgeLength,-fEdgeLength) );
    pos.push_back(CWorldCoordinate( fEdgeLength,-fEdgeLength,-fEdgeLength) );
    pos.push_back(CWorldCoordinate( fEdgeLength,-fEdgeLength,-fEdgeLength) );
    pos.push_back(CWorldCoordinate( fEdgeLength,-fEdgeLength, fEdgeLength) );
    pos.push_back(CWorldCoordinate(-fEdgeLength,-fEdgeLength, fEdgeLength) );

    std::vector<CColor> color(pos.size(), CColor(100, 100, 100));
    tData.SetPosVec(pos);
    tData.SetColorVec(color);

    // 添加法线
    std::vector<CWorldCoordinate> tmpNormal;
    tmpNormal.reserve(6);
    tmpNormal.push_back(  CWorldCoordinate( 0.0f, 0.0f, 1.0f) );
    tmpNormal.push_back(  CWorldCoordinate( 0.0f, 0.0f,-1.0f) );
    tmpNormal.push_back(  CWorldCoordinate(-1.0f, 0.0f, 0.0f) );
    tmpNormal.push_back(  CWorldCoordinate( 1.0f, 0.0f, 0.0f) );
    tmpNormal.push_back(  CWorldCoordinate( 0.0f, 1.0f, 0.0f) );
    tmpNormal.push_back(  CWorldCoordinate( 0.0f,-1.0f, 0.0f) );

    std::vector<CWorldCoordinate> normalVec;
    for (int i=0; i<6; ++i)
    {
        for (int j=0; j<6; ++j)
        {
            normalVec.push_back( tmpNormal[i] );
        }
    }
    tData.SetNormalVec(normalVec);

    // 添加纹理坐标
    std::vector<CTexCoordinate> texVec;
    texVec.resize(pos.size());
    for (int i=0; i<pos.size()/6; ++i)
    {
        int j=i*6;
        texVec[j++] = CTexCoordinate(0, 1);
        texVec[j++] = CTexCoordinate(0, 0);
        texVec[j++] = CTexCoordinate(1, 0);
        texVec[j++] = CTexCoordinate(1, 0);
        texVec[j++] = CTexCoordinate(1, 1);
        texVec[j++] = CTexCoordinate(0, 1);
    }
    tData.SetTexVec(texVec);
}

void SetVerticesData(C3DEngine* pEngine)
{
    CVerticesData tData;
    //std::vector<CWorldCoordinate> pos;
    //pos.push_back(CWorldCoordinate( 0.0f, 1.0f, 0.0f));
    //pos.push_back(CWorldCoordinate( 0.0f,-1.0f, 0.0f));
    //pos.push_back(CWorldCoordinate( 1.0f, 0.0f, 0.0f));
    //tData.SetPosVec(pos);

    //std::vector<CColor> color;
    //color.push_back(CColor(255, 0, 0));
    //color.push_back(CColor(255, 255, 255));
    //color.push_back(CColor(255, 255, 255));
    //tData.SetColorVec(color);

    InitCube(tData);
    tData.SetPrimitiveType(CVerticesData::PT_TRIANGLES);
    pEngine->SetVerticesData(tData);
}

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY3DENGINE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3DENGINE));

	// Main message loop:
    SetVerticesData(pEngine);
	while (GetMessage(&msg, NULL, 0, 0))
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
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style			= CS_HREDRAW | CS_VREDRAW;
    //wcex.style          = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3DENGINE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY3DENGINE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    //WNDCLASSEX wcex;
    //memset(&wcex, 0, sizeof(WNDCLASSEX));
    //wcex.cbSize = sizeof(WNDCLASSEX);
    //wcex.style			= CS_HREDRAW | CS_VREDRAW;
    //wcex.lpfnWndProc = (WNDPROC)WndProc;
    //wcex.hInstance = hInstance;
    //wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    //wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    //wcex.lpszClassName = szWindowClass;
	return RegisterClassEx(&wcex);
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
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, nWindowWidth, nWindowHeight, NULL, NULL, hInstance, NULL);
   
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   pEngine = new C3DEngine(hWnd, nWindowWidth, nWindowHeight);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
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
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
        if ( pEngine )
        {
            pEngine->Draw();
        }
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_MOUSEMOVE:
    case WM_MOUSEWHEEL:
        pEngine->MouseEvent(message, wParam, lParam);
        pEngine->Draw();
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
