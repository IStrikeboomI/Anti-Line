#pragma once
#include <vector>
#include <iostream>
class Pos {
private:
	static std::vector<Pos*> instances;
	//used for scaling the dimensions
	static int screenWidth, screenHeight;
	//"real" coordinates
	//this one should be used for moving around
	int x = 0, y = 0, width = 0, height = 0;
public:
	//scaled version of the coordinates
	//this one should be the one used for drawing
	int scaledX = 0, scaledY = 0, scaledWidth = 0, scaledHeight = 0;

	Pos(int x, int y, int width = 0, int height = 0);
	//called when resizing
	static void update(int width = screenWidth, int height = screenHeight);
	//separate functions so we can update after setting
	//sets real coordinates but also does scale
	void setX(int x);
	void setY(int Y);
	void setWidth(int width);
	void setHeight(int height);

	friend std::ostream& operator<<(std::ostream& os, const Pos& pos);
};

