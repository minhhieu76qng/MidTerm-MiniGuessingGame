// MiniGuessingGame.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MiniGuessingGame.h"

#include <windowsx.h>
#include <CommCtrl.h>
#include <gdiplus.h>

#pragma comment (lib, "gdiplus")
using namespace Gdiplus;
#pragma comment(lib, "comctl32.lib")

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

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


BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnPaint(HWND hwnd);
void OnDestroy(HWND hwnd);

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
    LoadStringW(hInstance, IDC_MINIGUESSINGGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MINIGUESSINGGAME));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINIGUESSINGGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_BTNFACE+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MINIGUESSINGGAME);
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
      CW_USEDEFAULT, 0, 700, 500, nullptr, nullptr, hInstance, nullptr);

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
	InitCommonControls();
    switch (message)
    {
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);

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


// ======================= MY VARIABLES =========================
RECT client_Rect;

HWND panel_Play, panel_Info;

HWND btnStart, btnReset;

HWND hImageLabel;

HWND hButtonSubmit1, hButtonSubmit2;

// ======================= MY FUNCTIONS =========================



BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	// lay kich thuoc man hinh
	GetClientRect(hwnd, &client_Rect);

	// tao title cho chuong trinh
	HWND title = CreateWindowEx(NULL, L"STATIC", L"LEARNING ENGLISH", WS_CHILD | WS_VISIBLE
		| SS_CENTER, (client_Rect.right-500)/2 , 10, 500, 40, hwnd, NULL, hInst, NULL);
	
	HFONT fontTitle = CreateFont(30, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	SetWindowFont(title, fontTitle, TRUE);


	#pragma region Panel Game Play

	// panel 1
	panel_Play = CreateWindowEx(NULL, L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER
		| SS_CENTER, 0, 50, client_Rect.right * 0.65, client_Rect.bottom - 50, hwnd, NULL, hInst, NULL);
	RECT panel_Play_rect;
	GetClientRect(panel_Play, &panel_Play_rect);

	
	#pragma region Question
	// question
	HWND hQuestion = CreateWindowEx(NULL, L"STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER
		, 20, 20, panel_Play_rect.right - 40, 70, panel_Play, NULL, hInst, NULL);
		 
	#pragma endregion


	#pragma region Label Image
	// image 1
	hImageLabel = CreateWindowEx(NULL, L"STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER
		| SS_BITMAP, (panel_Play_rect.right - 230) / 2, 130, 230, 130, panel_Play, NULL, hInst, NULL);
	#pragma endregion

	#pragma region Button 1
	// button 1
	hButtonSubmit1 = CreateWindowEx(NULL, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		130, 300, 80, 30, panel_Play, (HMENU)IDC_BTN_CHOOSE1, hInst, NULL);

	hButtonSubmit2 = CreateWindowEx(NULL, L"BUTTON", L"", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		230, 300, 80, 30, panel_Play, (HMENU)IDC_BTN_CHOOSE2, hInst, NULL);

	#pragma endregion

	#pragma region Button 2
	// button 2


	#pragma endregion

	#pragma endregion

	

	#pragma region PanelInfo

	panel_Info = CreateWindowEx(NULL, L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER
		| SS_CENTER, client_Rect.right * 0.65, 50, client_Rect.right * 0.35,
		client_Rect.bottom - 50, hwnd, NULL, hInst, NULL);

	RECT panelInfo_Rect;
	GetClientRect(panel_Info, &panelInfo_Rect);


		#pragma region Panel Timer

		HWND panel_Timer = CreateWindowEx(NULL, L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER
			| SS_CENTER, 10, 10, panelInfo_Rect.right - 20,
			70, panel_Info, NULL, hInst, NULL);
		RECT panel_Timer_Rect;
		GetClientRect(panel_Timer, &panel_Timer_Rect);

		// minute
		HWND lbMinute = CreateWindowEx(NULL, L"STATIC", L"00", WS_CHILD | WS_VISIBLE,
			50, (panel_Timer_Rect.bottom - 25) / 2, 30, 50, panel_Timer, NULL, hInst, NULL);

		SetWindowFont(lbMinute, fontTitle, true);

		// colon
		HWND lbColon = CreateWindowEx(NULL, L"STATIC", L":", WS_CHILD | WS_VISIBLE| SS_CENTER,
			90, (panel_Timer_Rect.bottom - 25) / 2 - 2, 30, 50, panel_Timer, NULL, hInst, NULL);

		SetWindowFont(lbColon, fontTitle, true);

		// second
		HWND lbSecond = CreateWindowEx(NULL, L"STATIC", L"00", WS_CHILD | WS_VISIBLE,
			130, (panel_Timer_Rect.bottom - 25) / 2, 30, 50, panel_Timer, NULL, hInst, NULL);

		SetWindowFont(lbSecond, fontTitle, true);

		#pragma endregion



		#pragma region Panel Show info Game Play

		HWND panel_ShowInFoGame = CreateWindowEx(NULL, L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER
			| SS_CENTER, 10, 90, panelInfo_Rect.right - 20,
			180, panel_Info, NULL, hInst, NULL);

		// show round
		HWND lbRound = CreateWindowEx(NULL, L"STATIC", L"Round:", WS_CHILD | WS_VISIBLE, 10, 10,
			70, 40, panel_ShowInFoGame, NULL, hInst, NULL);

		SetWindowFont(lbRound, hFont, true);

		HWND txbRound = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | SS_CENTER,
			90, 5, 110, 20, panel_ShowInFoGame, (HMENU)IDC_EDIT_ROUND, hInst, NULL);
		SetWindowFont(txbRound, hFont, true);

		EnableWindow(txbRound, false);

		// show score
		HWND lbScore = CreateWindowEx(NULL, L"STATIC", L"Score:", WS_CHILD | WS_VISIBLE, 10, 50,
			70, 30, panel_ShowInFoGame, NULL, hInst, NULL);

		SetWindowFont(lbScore, hFont, true);

		HWND txbScore = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | SS_CENTER,
			90, 45, 110, 20, panel_ShowInFoGame, (HMENU)IDC_EDIT_SCORE, hInst, NULL);
		SetWindowFont(txbScore, hFont, true);
		EnableWindow(txbScore, false);

		// show player
		HWND lbPlayer = CreateWindowEx(NULL, L"STATIC", L"Player:", WS_CHILD | WS_VISIBLE, 10, 90,
			70, 30, panel_ShowInFoGame, NULL, hInst, NULL);

		SetWindowFont(lbPlayer, hFont, true);

		HWND txbPlayer = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | SS_CENTER,
			90, 85, 110, 20, panel_ShowInFoGame, (HMENU)IDC_EDIT_PLAYER, hInst, NULL);
		SetWindowFont(txbPlayer, hFont, true);
		EnableWindow(txbPlayer, false);

		// show highest score
		HWND lbHightest = CreateWindowEx(NULL, L"STATIC", L"Highest Score:", WS_CHILD | WS_VISIBLE, 10, 130,
			70, 30, panel_ShowInFoGame, NULL, hInst, NULL);

		SetWindowFont(lbHightest, hFont, true);

		HWND txbHighest = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | SS_CENTER,
			90, 125, 110, 20, panel_ShowInFoGame, (HMENU)IDC_EDIT_HIGHEST, hInst, NULL);
		SetWindowFont(txbHighest, hFont, true);
		EnableWindow(txbHighest, false);
		#pragma endregion



		#pragma region Panel Button Controls
		HWND panel_ButtonControl = CreateWindowEx(NULL, L"STATIC", L"", WS_CHILD | WS_VISIBLE | WS_BORDER
			| SS_CENTER, 10, 280, panelInfo_Rect.right - 20,
			panelInfo_Rect.bottom - 10 - 280, panel_Info, NULL, hInst, NULL);

		RECT panel_ButtonControl_Rect;
		GetClientRect(panel_ButtonControl, &panel_ButtonControl_Rect);

		btnStart = CreateWindowEx(NULL, L"BUTTON", L"Start", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10, 10, 60, 30, panel_ButtonControl, (HMENU)IDC_BTN_START, hInst, NULL);

		SetWindowFont(btnStart, hFont, TRUE);

		btnReset = CreateWindowEx(NULL, L"BUTTON", L"Reset", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			80, 10, 60, 30, panel_ButtonControl, (HMENU)IDC_BTN_RESET, hInst, NULL);

		SetWindowFont(btnReset, hFont, TRUE);
		#pragma endregion


#pragma endregion

	return TRUE;
}
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{

}

bool drawFrame = false;

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);


	EndPaint(hwnd, &ps);
}
void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}