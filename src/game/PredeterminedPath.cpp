#include "PredeterminedPath.h"

PredeterminedPath::PredeterminedPath(Pos start, Pos end) : start(start), end(end) {
	//these three booleans are used for seeing if the point is on the top half to bias the random angle direction
	const bool START_ON_TOP_HALF = start.getY() < Pos::BASE_HEIGHT/2;
	const bool END_ON_TOP_HALF = end.getY() < Pos::BASE_HEIGHT / 2;
	//this is done so the angle from the start to the corner is adjusted for which is higher
	const bool START_ABOVE_END = start.getY() < end.getY();

	//the start point of the line should be in the on the far east in the middle of the start point
	const int X_START = start.getX() + start.getWidth();
	const int Y_START = start.getY() + start.getHeight() / 2;

	//angle from the end of the first line to the end point's middle
	const float ANGLE_TO_END = std::atan(std::abs((float)(end.getY() + end.getHeight()/2 - Y_START) / std::abs(end.getX() + end.getWidth() / 2 - X_START)));

	//fill out the other side lengths of the triangle with an initial longer first line
	const float TRIANGLE_ADJACENT_LENGTH = LINE_LENGTH * std::cos(ANGLE_TO_END);
	const float TRIANGLE_OPPOSITE_LENGTH = LINE_LENGTH * std::sin(ANGLE_TO_END);

	//so far the line only goes up so we need a variable to make the line go down if end is below start
	const int SIGN = START_ABOVE_END ? 1 : -1;

	//the first line jutting out from the start point
	lines.push_back(std::make_shared<Line>(X_START, Y_START, X_START + TRIANGLE_ADJACENT_LENGTH, Y_START + TRIANGLE_OPPOSITE_LENGTH * SIGN));

	while (!lines.at(lines.size() - 1)->endPos.isCollided(end)) {

		//the ending of the previous line
		Pos previousLineEnd = lines.at(lines.size() - 1)->endPos;

		lines.push_back(std::make_shared<Line>(previousLineEnd.getX(), previousLineEnd.getY(), previousLineEnd.getX() + TRIANGLE_ADJACENT_LENGTH, previousLineEnd.getY() + TRIANGLE_OPPOSITE_LENGTH * SIGN));

	}
}

