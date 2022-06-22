#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
//This class is used for positioning in the top left
class Pos {
private:
	static std::vector<Pos*> instances;
	//used for scaling the dimensions
	static int screenWidth, screenHeight;
	//These two floats are used for scaling the pos
	//a scale factor of 1 on each is for a 960x540 window
	static float scaleFactorX, scaleFactorY;
	//"real" coordinates
	//this one should be used for moving around
	int x = 0, y = 0, width = BASE_WIDTH, height = BASE_HEIGHT;
public:
	const static int BASE_WIDTH = 960, BASE_HEIGHT = 540;
	//scaled version of the coordinates
	//this one should be the one used for drawing
	int scaledX = 0, scaledY = 0, scaledWidth = 0, scaledHeight = 0;

	//unscaled version
	Pos(int x, int y, int width = 0, int height = 0);
	//copy constructor
	Pos(const Pos& p) = default;
	//called to remove the pos from the vector when deleted
	~Pos();
	//called when resizing
	static void update(int width = screenWidth, int height = screenHeight);
	//helper function used to scale font size
	static float scaledFontSize(int size);
	//used for removing all the Pos in the vector
	//used during round changes
	static void clearInstances();
	//separate functions so we can update after setting
	//sets real coordinates but also does scale
	void setX(int x);
	void setY(int Y);
	void setWidth(int width);
	void setHeight(int height);
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;

	bool isCollided(const Pos& pos, int extraSpace = 0) const;
	float getDistanceTo(const Pos& pos) const;

	Pos& operator=(const Pos& p) = default;
	friend std::ostream& operator<<(std::ostream& os, const Pos& pos);
	friend bool operator==(const Pos& pos1, const Pos& pos2);
	friend bool operator!=(const Pos& pos1, const Pos& pos2);

	//Note: these operator overloads DO NOT effect the height and width (it will only use the Pos1 if two Pos are provided)
	//Adds 2 positions together
	friend Pos operator+(const Pos& pos1, const Pos& pos2);
	//Subtracts 2 positions together
	friend Pos operator-(const Pos& pos1, const Pos& pos2);
	Pos& operator+=(const Pos& pos2);
	Pos& operator-=(const Pos& pos2);
};

