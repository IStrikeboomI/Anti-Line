#include <Windows.h>
#include <gdiplus.h>
#include <string>
#include <iostream>
#include "game/points/StartPoint.h"
#include "GameData.h"

static const int STARTING_WIDTH = 960, STARTING_HEIGHT = 540;

LRESULT CALLBACK windowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
//These methods are used for drawing separate objects to not clutter the WM_PAINT call
void drawScoreString(Gdiplus::Graphics& graphics);
void drawStartAndEndPoints(Gdiplus::Graphics& graphics);
void drawPlayer(Gdiplus::Graphics& graphics);

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
    CreateWindowW(wc.lpszClassName, wc.lpszMenuName, WS_OVERLAPPEDWINDOW | WS_VISIBLE, screen.right / 2 - STARTING_WIDTH / 2, screen.bottom / 2 - STARTING_HEIGHT / 2, STARTING_WIDTH, STARTING_HEIGHT, nullptr, nullptr, wc.hInstance, nullptr);

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
        case WM_SIZE:
        {
            int width = LOWORD(lparam);
            int height = HIWORD(lparam);
            Pos::update(width, height);
            //repaint on update
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

            if (GameData::inRound) {
                drawScoreString(graphics);
                drawStartAndEndPoints(graphics);
                drawPlayer(graphics);
            }

            //stop painting
            EndPaint(hwnd, &ps);
        }
        case WM_KEYDOWN:
        {
            GameData::currentRound.player.handleKeyboardInput(wparam);
            break;
        }
        default:break;
    }
    return DefWindowProcW(hwnd, msg, wparam, lparam);
}

void drawScoreString(Gdiplus::Graphics& graphics) {
    std::wstring scoreString(L"Score: ");
    scoreString += std::to_wstring(GameData::score);
    Gdiplus::Font font(L"Arial", Pos::scaledFontSize(48));
    Gdiplus::SolidBrush scoreBrush(Gdiplus::Color(132, 135, 135));

    graphics.DrawString(scoreString.c_str(), -1, &font, Gdiplus::PointF(0, 0), &scoreBrush);
}

void drawStartAndEndPoints(Gdiplus::Graphics& graphics) {
    Gdiplus::SolidBrush startingPointBrush(Gdiplus::Color(0, 255, 0));
    graphics.FillRectangle(&startingPointBrush, GameData::currentRound.startPoint.pos.scaledX, GameData::currentRound.startPoint.pos.scaledY, 
                                                GameData::currentRound.startPoint.pos.scaledWidth, GameData::currentRound.startPoint.pos.scaledHeight);

    Gdiplus::SolidBrush endingPointBrush(Gdiplus::Color(255, 0, 0));
    graphics.FillRectangle(&endingPointBrush, GameData::currentRound.endPoint.pos.scaledX, GameData::currentRound.endPoint.pos.scaledY,
                                              GameData::currentRound.endPoint.pos.scaledWidth, GameData::currentRound.endPoint.pos.scaledHeight);
}

void drawPlayer(Gdiplus::Graphics& graphics) {
    Gdiplus::SolidBrush playerBrush(Gdiplus::Color(52, 103, 207));
    graphics.FillRectangle(&playerBrush, GameData::currentRound.player.pos.scaledX, GameData::currentRound.player.pos.scaledY,
                                         GameData::currentRound.player.pos.scaledWidth, GameData::currentRound.player.pos.scaledHeight);

}
