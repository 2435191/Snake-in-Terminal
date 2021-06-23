
#include "GameBoard.hpp"
#include <vector>

#include <unordered_set>

using namespace snake;

bool GameBoard::isOutOfBounds(Point &point)
{
	return (
		point[0] < 0 ||
		point[1] < 0 ||
		point[0] >= boardWidth ||
		point[1] >= boardHeight);
}

bool snake::GameBoard::isInSelf(Point &point)
{
	for (Point &p : snakePos)
		if (point == p)
			return true;
	return false;
}

void snake::GameBoard::putFood()
{
	std::vector<Point> validPoints;
	std::unordered_set<Point, Point> invalidPoints;

	for (Point &i : snakePos)
		invalidPoints.insert(i);

	for (int r = 0; r < boardHeight; r++)
	{
		for (int c = 0; c < boardWidth; c++)
			if (invalidPoints.find({c, r}) == invalidPoints.end())
				validPoints.push_back({c, r});
	}

	this->foodCoords = validPoints[rng() % validPoints.size()];
}

GAMESTATE snake::GameBoard::updateSnake()
{
	Point newPoint = DIR_TO_POINT.at(facing) + snakePos.front();

	if (isOutOfBounds(newPoint))
	{
		return COLLISION_WALL_LOSE;
	}

	if (isInSelf(newPoint))
	{
		return COLLISION_SNAKE_LOSE;
	}

	snakePos.insert(snakePos.begin(), newPoint);
	snakePos.erase(snakePos.end()-1);

	if (newPoint == foodCoords)
	{
		addToSnake();
		if (snakePos.size() == boardWidth * boardHeight)
			return WIN;
		putFood();
	}


	return STILL_PLAYING;
}

bool snake::GameBoard::addToSnake()
{
	Point *tail = &snakePos.back();
	if (snakePos.size() == 1)
	{
		Point newPoint = *tail - DIR_TO_POINT.at(facing);
		if (!isOutOfBounds(newPoint))
		{
			snakePos.push_back(newPoint);
			return true;
		}

		for (int i = 0; i < 4; i++)
		{
			DIRECTION d = static_cast<DIRECTION>(i);
			newPoint = *tail - DIR_TO_POINT.at(d);
			if (isOutOfBounds(newPoint))
				continue;
			snakePos.push_back(newPoint);

			return true;
		}
		return false;
	}
	Point *penultimate = &snakePos[snakePos.size() - 2];
	Point towardBackOfSnake = *tail - *penultimate;

	Point newPoint = *tail + towardBackOfSnake;
	if (!isOutOfBounds(newPoint))
	{
		snakePos.push_back(newPoint);
		return true;
	}
	for (int i = 0; i < 4; i++)
	{
		DIRECTION d = static_cast<DIRECTION>(i);
		newPoint = *tail - DIR_TO_POINT.at(d);
		if (isOutOfBounds(newPoint))
			continue;
		snakePos.push_back(newPoint);

		return true;
	}
	return false;
}