#include "game/Game.h"
#include <Windows.h>
#include <gdiplus.h>
#include <string>
#include <iostream>

//constant for timer's code
static const int UPDATE_TIMER = 12;

//this stores how many ticks its been showing a player wins/loses message
//used to time how long its going to be
static int fadeTime = 0;

LRESULT CALLBACK windowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
//These methods are used for drawing separate objects to not clutter the WM_PAINT call
inline void drawScoreString(Gdiplus::Graphics& graphics);
inline void drawStartAndEndPoints(Gdiplus::Graphics& graphics);
inline void drawPlayer(Gdiplus::Graphics& graphics);
inline void drawLines(Gdiplus::Graphics& graphics);

int main() {;
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
    HWND hwnd = CreateWindowW(wc.lpszClassName, wc.lpszMenuName, WS_OVERLAPPEDWINDOW | WS_VISIBLE, screen.right / 2 - Pos::BASE_WIDTH / 2, screen.bottom / 2 - Pos::BASE_HEIGHT / 2, Pos::BASE_WIDTH, Pos::BASE_HEIGHT, nullptr, nullptr, wc.hInstance, nullptr);

    //Set a timer to redraw every 33 ms (30 fps) to handle the player moving
    SetTimer(hwnd, UPDATE_TIMER, 33, (TIMERPROC)NULL);

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
                case UPDATE_TIMER:
                {
                    //update the round
                    Game::getInstance().update();
                    if (!Game::getInstance().inRound) {
                        fadeTime++;
                    } else {
                        fadeTime = 0;
                    }
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
            if (Game::getInstance().inRound) {
                drawStartAndEndPoints(graphics);
                drawPlayer(graphics);
                drawScoreString(graphics);
                drawLines(graphics);
            } else {
                // draw corrosponding message on the round status
                if (Game::getInstance().status == RoundStatus::WON) {

                } else if (Game::getInstance().status == RoundStatus::LOST) {

                }
                if (fadeTime == 2500 / 33) {
                    Game::getInstance().newRound();
                }
            }

            //paint on window
            BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);

            //free up to prevent resource leak
            DeleteObject(hBM);
            DeleteDC(memDC);
            //stop painting
            EndPaint(hwnd, &ps);
        }
        //WM_KEYUP instead of WM_KEYDOWN so it doesn't get faster when holding down after a few ticks
        case WM_KEYUP:
        {
            //only detect key inputs if in a round, not in ai mode, and if window is input focused
            if (Game::getInstance().inRound && !Game::getInstance().AIMode && hwnd == GetFocus()) {
                //read key inputs
                //no break; in the if statements so we can use multiple keys at once
                
                //up arrow OR W key
                if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(0x57) & 0x8000) {
                    Game::getInstance().currentRound.player.moveUp();  
                }
                //down arrow OR S key
                if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState(0x53) & 0x8000) {
                    Game::getInstance().currentRound.player.moveDown();
                }
                //left arrow OR A key
                if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState(0x41) & 0x8000) {
                    Game::getInstance().currentRound.player.moveLeft();
                }
                //right arrow OR D key
                if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState(0x44) & 0x8000) {
                    Game::getInstance().currentRound.player.moveRight(); 
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
    scoreString += std::to_wstring(Game::getInstance().score);
    Gdiplus::Font font(L"Arial", Pos::scaledFontSize(48));
    Gdiplus::SolidBrush scoreBrush(Gdiplus::Color(132, 135, 135));

    graphics.DrawString(scoreString.c_str(), -1, &font, Gdiplus::PointF(0, 0), &scoreBrush);
}

inline void drawStartAndEndPoints(Gdiplus::Graphics& graphics) {
    Gdiplus::SolidBrush startingPointBrush(Game::getInstance().currentRound.startPoint.getColor());
    graphics.FillRectangle(&startingPointBrush, Game::getInstance().currentRound.startPoint.pos.scaledX, Game::getInstance().currentRound.startPoint.pos.scaledY, 
                                                Game::getInstance().currentRound.startPoint.pos.scaledWidth, Game::getInstance().currentRound.startPoint.pos.scaledHeight);

    Gdiplus::SolidBrush endingPointBrush(Game::getInstance().currentRound.endPoint.getColor());
    graphics.FillRectangle(&endingPointBrush, Game::getInstance().currentRound.endPoint.pos.scaledX, Game::getInstance().currentRound.endPoint.pos.scaledY,
                                              Game::getInstance().currentRound.endPoint.pos.scaledWidth, Game::getInstance().currentRound.endPoint.pos.scaledHeight);
}

inline void drawPlayer(Gdiplus::Graphics& graphics) {
    Gdiplus::SolidBrush playerBrush(Game::getInstance().currentRound.player.getColor());
    graphics.FillRectangle(&playerBrush, Game::getInstance().currentRound.player.pos.scaledX, Game::getInstance().currentRound.player.pos.scaledY,
                                         Game::getInstance().currentRound.player.pos.scaledWidth, Game::getInstance().currentRound.player.pos.scaledHeight);
    
}

inline void drawLines(Gdiplus::Graphics& graphics) {
    //all lines have the same color so just the first line
    Gdiplus::Pen linePen(Game::getInstance().currentRound.lines.at(0)->getColor());

    for (const std::shared_ptr<Line> l : Game::getInstance().currentRound.lines) {
        graphics.DrawLine(&linePen, l->startPos.scaledX, l->startPos.scaledY, l->endPos.scaledX, l->endPos.scaledY);
    }

    //DON'T FORGET TO REMOVE THIS (USED FOR DEBUGGING)
    Gdiplus::Pen testPen(Gdiplus::Color(89, 14, 98),5);
    graphics.DrawRectangle(&testPen, Game::getInstance().currentRound.endPoint.pos.scaledX + Game::getInstance().currentRound.endPoint.pos.scaledWidth/2, Game::getInstance().currentRound.endPoint.pos.scaledY + Game::getInstance().currentRound.endPoint.pos.scaledHeight/2, 10, 10);
    for (const std::shared_ptr<Line> l : Game::getInstance().currentRound.path.lines) {
        graphics.DrawLine(&testPen, l->startPos.scaledX, l->startPos.scaledY, l->endPos.scaledX, l->endPos.scaledY);
    
    }
}