#include "PredeterminedPath.h"


PredeterminedPath::PredeterminedPath(const Pos& start, const Pos& end) {
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
		const Pos& PREVIOUS_LINE_END = lines.at(lines.size() - 1)->endPos;

		//basically the same thing as above but we do it each time to account for the randomness
		float x_distance_to_end = std::abs(end.getX() + end.getWidth() / 2 - PREVIOUS_LINE_END.getX());
		float y_distance_to_end = std::abs(end.getY() + end.getHeight() / 2 - PREVIOUS_LINE_END.getY());
		//angle from the end of the first line to the end point's middle
		float angle_to_end = std::atan(y_distance_to_end / x_distance_to_end);

		//fill out the other side lengths of the triangle with an initial longer first line
		float triangle_adjacent_length = LINE_LENGTH * std::cos(angle_to_end);
		float triangle_opposite_length = LINE_LENGTH * std::sin(angle_to_end);

		//the distnace from the previous line to the end
		Pos translatedEndPos(end.getX() + end.getWidth() / 2,end.getY() + end.getHeight() / 2);
		float distance = PREVIOUS_LINE_END.getDistanceTo(translatedEndPos);

		//the maximum randomness the line can get and this gets the smaller the closer to the end it gets
		float maxRandomDistance = (distance / DISTANCE_TO_END) * 25;

		//create a random distance using the max above
		float randomiziedLength = Util::random(0,maxRandomDistance);

		//right now the line only goes up so if the previous line is below the end go up and go down if not
		int sign = PREVIOUS_LINE_END.getY() < end.getY() ? 1 : -1;

		//add the line to the vector
		lines.push_back(std::make_shared<Line>(PREVIOUS_LINE_END.getX(), PREVIOUS_LINE_END.getY(), PREVIOUS_LINE_END.getX() + triangle_adjacent_length, PREVIOUS_LINE_END.getY() + triangle_opposite_length * sign + randomiziedLength* sign));

		//in case the line somehow misses, just break early before any memory overflow
		if (lines.size() >= DISTANCE_TO_END/LINE_LENGTH) {
			break;
		}
	}
}

bool PredeterminedPath::isLineNear(const Line& line, int distance) const {
	//the positions of the line
	const Pos& LINE_START = line.startPos;
	const Pos& LINE_END = line.endPos;
	//do a check for every line in the path
	for (const std::shared_ptr<Line>& l : lines) {
		if (l->endPos.getDistanceTo(LINE_START) <= distance || l->endPos.getDistanceTo(LINE_END) <= distance) {
			return true;
		}
		//its definitely near if the line goes through the path
		if (l->doLinesIntersect(line)) {
			return true;
		}

	}

	return false;
}