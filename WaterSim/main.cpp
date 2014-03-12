// WaterSim.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "WaterSim.h"
#include "Tungsten\ServiceLocator.h"
#include "Tungsten\Services\D3DRenderer.h"
#include "Tungsten\Services\ConfigManager.h"
#include "Tungsten\Game.h"
#include "Tungsten\DebugWriter.h"
#include "Tungsten\Services\AssetLoader.h"
#include "MainState.h"

#include "Tungsten\States\SpriteString.h"

#define MAX_LOADSTRING 100

HWND g_mainWindow;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				RegisterWindowClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);


using namespace Tungsten;


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	MSG msg;

	Services.SetConfig(new ConfigManager());
	Services.Config()->Load(L"config.cfg");
	


	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WATERSIM, szWindowClass, MAX_LOADSTRING);
	RegisterWindowClass(hInstance);


	

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	Services.SetInput(new InputService());
	Services.SetGraphics(new D3DRenderer(g_mainWindow));
	Services.Input()->Initialise(g_mainWindow);
	Services.SetImporter(new AssetLoader);
	
	

	Game game;
	game.Push(new MainState());
	//Services.Graphics()->Present();
	// Main message loop:
	while (true)
	{
		
		game.RunFrame(0);
		



		Services.Input()->Refresh();
		while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
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
ATOM RegisterWindowClass(HINSTANCE hInstance)
{
	Tungsten::ConfigurationState state = Services.Config()->Get();
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WATERSIM));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	/*wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+4);*/
	if (state.windowed == state.no)
		wcex.hbrBackground = (HBRUSH)0;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
	HWND hWnd = 0;
	Tungsten::ConfigurationState state = Services.Config()->Get();


	// Set the window's style.
	if (state.windowed == state.no)
	{
		//SetWindowLong( hWnd, GWL_STYLE, WS_POPUP );
		RECT rectangle = { 0, 0, state.resolution.width, state.resolution.height };
		AdjustWindowRect(&rectangle, WS_POPUP, false);
		//  HBRUSH brush = (HBRUSH)0;
		// SetClassLongPtr(g_mainWindow, GCLP_HBRBACKGROUND, (LONG)brush);
		hWnd = CreateWindow(szWindowClass, szTitle, WS_POPUP,
			200, 200, rectangle.right, rectangle.bottom, NULL, NULL, hInstance, NULL);
	}
	if (state.windowed == state.borderless)
	{
		//SetWindowLong( hWnd, GWL_STYLE, WS_POPUP );
		RECT rectangle = { 0, 0, state.resolution.width, state.resolution.height };
		//AdjustWindowRect(&rectangle,WS_POPUP,false);
		hWnd = CreateWindow(szWindowClass, szTitle, WS_POPUP,
			0, 0, rectangle.right, rectangle.bottom, NULL, NULL, hInstance, NULL);
	}
	if (state.windowed == state.yes)
	{
		//SetWindowLong( hWnd, GWL_STYLE, WS_POPUP );
		RECT rectangle = { 0, 0, state.resolution.width, state.resolution.height };
		AdjustWindowRect(&rectangle, WS_POPUP, false);
		hWnd = CreateWindow(szWindowClass, szTitle, WS_CAPTION,
			200, 200, rectangle.right, rectangle.bottom, NULL, NULL, hInstance, NULL);
	}
	if (!hWnd)
	{
		return FALSE;
	}
	// Maximize the window.
	ShowWindow(hWnd, 10);


	UpdateWindow(hWnd);
	g_mainWindow = hWnd;

	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_INPUT:
		Services.Input()->HandleInputEvent(lParam);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


