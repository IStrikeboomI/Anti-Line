#include <Windows.h>
#include <gdiplus.h>
#include <string>
#include <iostream>
#include "game/points/StartPoint.h"

namespace GameData {
    StartPoint startPoint;
    static const int STARTING_WIDTH = 960, STARTING_HEIGHT = 540;
}

LRESULT CALLBACK windowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

int main() {
    //Initilzing Gdi+
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	//initizalie wc
	WNDCLASSW wc = { 0 };
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszClassName = L"anti-line";
	wc.lpfnWndProc = windowProcedure;
	wc.lpszMenuName = L"Anti-Line";
	//Adds icon in corner (117 is icon)
	//wc.hIcon = (HICON)LoadImageW(wc.hInstance, MAKEINTRESOURCEW(117), IMAGE_ICON, 256, 191, LR_DEFAULTSIZE | LR_SHARED);
	
    if (!RegisterClassW(&wc)) {
        return -1;
    }

    //Gets screen to center window
    RECT screen;
    GetWindowRect(GetDesktopWindow(), &screen);

    //Creates Window
    CreateWindowW(wc.lpszClassName, wc.lpszMenuName, WS_OVERLAPPEDWINDOW | WS_VISIBLE, screen.right / 2 - GameData::STARTING_WIDTH / 2, screen.bottom / 2 - GameData::STARTING_HEIGHT / 2, GameData::STARTING_WIDTH, GameData::STARTING_HEIGHT, nullptr, nullptr, wc.hInstance, nullptr);

    MSG msg = { nullptr };

    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    //Shutdown Gdi+
    Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}

LRESULT CALLBACK windowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

    switch (msg) {
        case WM_DESTROY: 
        {
            //default destroy message
            PostQuitMessage(0);
            break;
		}
        case WM_SIZING:
        {
            RECT* screen = (RECT*)lparam;
            Pos::update(screen->right - screen->left, screen->bottom - screen->top);
            InvalidateRect(hwnd, 0, TRUE);
            break;
        }
        case WM_PAINT:
        {
            //initalize ps and hdc
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            //make graphics
            Gdiplus::Graphics graphics(hdc);
            
            //Used for drawing starting point
            Gdiplus::SolidBrush startingPointBrush(Gdiplus::Color(0,255,0));
            graphics.FillRectangle(&startingPointBrush,GameData::startPoint.pos.scaledX, GameData::startPoint.pos.scaledY, GameData::startPoint.pos.scaledWidth, GameData::startPoint.pos.scaledHeight);
            //stop painting
            EndPaint(hwnd, &ps);
        }
        default:break;
    }
    return DefWindowProcW(hwnd, msg, wparam, lparam);
}
