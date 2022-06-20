#include "PredeterminedPath.h"

PredeterminedPath::PredeterminedPath(Pos start, Pos end) : start(start), end(end) {
	//the start point of the line should be in the on the far east in the middle of the start point
	const int X_START = start.getX() + start.getWidth();
	const int Y_START = start.getY() + start.getHeight() / 2;

	//these only apply for the first line
	const float X_DISTANCE_TO_END = std::abs(end.getX() + end.getWidth() / 2 - X_START);
	const float Y_DISTANCE_TO_END = std::abs(end.getY() + end.getHeight() / 2 - Y_START);
	const float DISTANCE_TO_END = std::sqrt(X_DISTANCE_TO_END* X_DISTANCE_TO_END + Y_DISTANCE_TO_END* Y_DISTANCE_TO_END);

	//just make a straight line so the while loop has something to base it off of
	lines.push_back(std::make_shared<Line>(X_START,Y_START, X_START + LINE_LENGTH, Y_START));

	//keep running until the line in the front hits the end
	while (!lines.at(lines.size() - 1)->endPos.isCollided(end)) {

		//the ending of the previous line
		Pos previousLineEnd = lines.at(lines.size() - 1)->endPos;

		//basically the same thing as above but we do it each time to account for the randomness
		float x_distance_to_end = std::abs(end.getX() + end.getWidth() / 2 - previousLineEnd.getX());
		float y_distance_to_end = std::abs(end.getY() + end.getHeight() / 2 - previousLineEnd.getY());
		//angle from the end of the first line to the end point's middle
		float angle_to_end = std::atan(y_distance_to_end / x_distance_to_end);

		//fill out the other side lengths of the triangle with an initial longer first line
		float triangle_adjacent_length = LINE_LENGTH * std::cos(angle_to_end);
		float triangle_opposite_length = LINE_LENGTH * std::sin(angle_to_end);

		//the distnace from the previous line to the end
		float xDistance = std::abs(end.getX() + end.getWidth() / 2 - previousLineEnd.getX());
		float yDistance = std::abs(end.getY() + end.getHeight() / 2 - previousLineEnd.getY());
		float distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);

		//the maximum randomness the line can get and this gets the smaller the closer to the end it gets
		float maxRandomDistance = (distance / DISTANCE_TO_END) * 25;

		//create a random distance using the max above
		float randomiziedLength = Util::random(0,maxRandomDistance);

		//right now the line only goes up so if the previous line is below the end go up and go down if not
		int sign = previousLineEnd.getY() < end.getY() ? 1 : -1;

		//add the line to the vector
		lines.push_back(std::make_shared<Line>(previousLineEnd.getX(), previousLineEnd.getY(), previousLineEnd.getX() + triangle_adjacent_length, previousLineEnd.getY() + triangle_opposite_length * sign + randomiziedLength* sign));

		//in case the line somehow misses, just break early before any memory overflow
		if (lines.size() >= DISTANCE_TO_END/LINE_LENGTH) {
			break;
		}
	}
}

