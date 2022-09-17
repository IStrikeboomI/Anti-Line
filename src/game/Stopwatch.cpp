#include "Stopwatch.h"
#include "Game.h"
class Game;
Stopwatch::Stopwatch() {
}

void Stopwatch::draw(Gdiplus::Graphics& g) const {
	int minutes = (elapsedTicks / Game::FPS) / 60;
	//this includes the seconds and miliseconds
	double seconds = std::fmod(((double)elapsedTicks / Game::FPS),60);
	std::wstringstream  wstringStream;
	wstringStream << minutes << ":" 
		//format string to 2 decimal places and the seconds
		<< std::format("{:.2f}",seconds).c_str();
	Gdiplus::Font font(L"Arial", Pos::scaledFontSize(48));
	Gdiplus::SolidBrush brush(Gdiplus::Color(132, 135, 135));
	//TODO find a way to center the stopwatch
	g.DrawString(wstringStream.str().c_str(), -1, &font, Gdiplus::PointF(600, 1), &brush);
}

void Stopwatch::update() {
	//only update counter if in round/can draw
	if (canDraw()) {
		elapsedTicks++;
	}
}
