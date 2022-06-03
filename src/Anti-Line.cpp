#include <Windows.h>
#include <gdiplus.h>
#include <string>
#include <iostream>
#include "game/points/StartPoint.h"
#include "GameData.h"

//constant for timer
static const int MOVING_REDRAW_TIMER = 12;

static const int STARTING_WIDTH = 960, STARTING_HEIGHT = 540;

LRESULT CALLBACK windowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
//These methods are used for drawing separate objects to not clutter the WM_PAINT call
inline void drawScoreString(Gdiplus::Graphics& graphics);
inline void drawStartAndEndPoints(Gdiplus::Graphics& graphics);
inline void drawPlayer(Gdiplus::Graphics& graphics);

int main() {
    //Initilzing Gdi+
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	//initizalie wc
	WNDCLASSW wc = { 0 };
	wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
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
    HWND hwnd = CreateWindowW(wc.lpszClassName, wc.lpszMenuName, WS_OVERLAPPEDWINDOW | WS_VISIBLE, screen.right / 2 - STARTING_WIDTH / 2, screen.bottom / 2 - STARTING_HEIGHT / 2, STARTING_WIDTH, STARTING_HEIGHT, nullptr, nullptr, wc.hInstance, nullptr);

    //Set a timer to redraw every 33 ms (30 fps) to handle the player moving
    SetTimer(hwnd, MOVING_REDRAW_TIMER, 33, (TIMERPROC)NULL);

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
        case WM_TIMER:
        {
            switch (wparam) {
                //happens every 33 ms
                case MOVING_REDRAW_TIMER:
                {
                    //redraw window
                    InvalidateRect(hwnd, nullptr, true);
                    break;
                }
            }
            break;
        }
        case WM_SIZE:
        {
            int width = LOWORD(lparam);
            int height = HIWORD(lparam);
            Pos::update(width, height);
            //redraw window after resizing
            RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE);
            break;
        }
        case WM_ERASEBKGND:
        {
            //don't handle WM_ERASEBKGND to prevent flickering
            return 1;
        }
        case WM_PAINT:
        {
            //initalize ps and hdc
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            //get dimensions of coordinates
            RECT client;
            GetClientRect(hwnd, &client);
            int width = client.right - client.left;
            int height = client.bottom - client.top;

            //create a separate hdc for double buffering to prevent flicker
            HDC memDC = CreateCompatibleDC(hdc);
            HBITMAP hBM = CreateCompatibleBitmap(hdc, width, height);
            SelectObject(memDC, hBM);

            //Fill
            RECT r;
            SetRect(&r, 0, 0, width, height);
            FillRect(memDC, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));

            //make graphics
            Gdiplus::Graphics graphics(memDC);

            //only draw game objects if in a round
            if (GameData::inRound) {
                drawStartAndEndPoints(graphics);
                drawPlayer(graphics);
                drawScoreString(graphics);
            }

            //paint on window
            BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);

            //free up to prevent resource leak
            DeleteObject(hBM);
            DeleteDC(memDC);
            //stop painting
            EndPaint(hwnd, &ps);
        }
        case WM_KEYDOWN:
        {
            //only detect key inputs if in a round
            if (GameData::inRound) {
                //read key inputs
                //no break; in the if statements so we can use multiple keys at once
                
                //up arrow OR W key
                if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(0x57) & 0x8000) {
                    GameData::currentRound.player.moveUp();  
                }
                //down arrow OR S key
                if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState(0x53) & 0x8000) {
                    GameData::currentRound.player.moveDown();
                }
                //left arrow OR A key
                if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState(0x41) & 0x8000) {
                    GameData::currentRound.player.moveLeft();
                }
                //right arrow OR D key
                if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState(0x44) & 0x8000) {
                    GameData::currentRound.player.moveRight();
                }
            }
            break;
        }
        default:break;
    }
    return DefWindowProcW(hwnd, msg, wparam, lparam);
}

inline void drawScoreString(Gdiplus::Graphics& graphics) {
    std::wstring scoreString(L"Score: ");
    scoreString += std::to_wstring(GameData::score);
    Gdiplus::Font font(L"Segeo UI", Pos::scaledFontSize(48));
    Gdiplus::SolidBrush scoreBrush(Gdiplus::Color(132, 135, 135));

    graphics.DrawString(scoreString.c_str(), -1, &font, Gdiplus::PointF(0, 0), &scoreBrush);
}

inline void drawStartAndEndPoints(Gdiplus::Graphics& graphics) {
    Gdiplus::SolidBrush startingPointBrush(Gdiplus::Color(0, 255, 0));
    graphics.FillRectangle(&startingPointBrush, GameData::currentRound.startPoint.pos.scaledX, GameData::currentRound.startPoint.pos.scaledY, 
                                                GameData::currentRound.startPoint.pos.scaledWidth, GameData::currentRound.startPoint.pos.scaledHeight);

    Gdiplus::SolidBrush endingPointBrush(Gdiplus::Color(255, 0, 0));
    graphics.FillRectangle(&endingPointBrush, GameData::currentRound.endPoint.pos.scaledX, GameData::currentRound.endPoint.pos.scaledY,
                                              GameData::currentRound.endPoint.pos.scaledWidth, GameData::currentRound.endPoint.pos.scaledHeight);
}

inline void drawPlayer(Gdiplus::Graphics& graphics) {
    Gdiplus::SolidBrush playerBrush(Gdiplus::Color(52, 103, 207));
    graphics.FillRectangle(&playerBrush, GameData::currentRound.player.pos.scaledX, GameData::currentRound.player.pos.scaledY,
                                         GameData::currentRound.player.pos.scaledWidth, GameData::currentRound.player.pos.scaledHeight);
    
}