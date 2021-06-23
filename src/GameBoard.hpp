#ifndef GameBoard_hpp
#define GameBoard_hpp

#include "Point.cpp"

#include <unordered_map>
#include <mutex>
#include <string>
#include <random>
#include <vector>

namespace snake
{
	enum DIRECTION
	{
		N,
		S,
		E,
		W
	};

	static const std::unordered_map<DIRECTION, Point> DIR_TO_POINT{
		{N, {0, -1}},
		{S, {0, 1}},
		{E, {1, 0}},
		{W, {-1, 0}},
	};

	enum GAMESTATE
	{
		COLLISION_WALL_LOSE,
		COLLISION_SNAKE_LOSE,
		WIN,
		STILL_PLAYING
	};

	class GameBoard
	{
	public:
		// GameBoard.cpp
		GameBoard(const int, const int, const int, const int, const DIRECTION, const int, const int);
		void run();

		// printing.cpp
		operator std::string();
		void print();

		

	private:
		// input_processing.cpp
		void getInput(std::atomic_bool&);
		
		// printing.cpp
		std::string to_string();
		std::string to_string(const std::string&, const std::string&, const std::string&);

		// snake_movement.cpp
		void putFood();
		GAMESTATE updateSnake();
		bool addToSnake();
		bool isOutOfBounds(Point &);
		bool isInSelf(Point &);

		// utilities.cpp
		static int resize(int, int);
		static int clear();

		std::random_device rng;
		DIRECTION facing;
		std::mutex facing_mutex; // protect this->facing
		std::vector<Point> snakePos; // FIXME: use ordered set
		Point foodCoords;


		const int dt; // msec
		const int boardWidth;
		const int boardHeight;
		const int endBackgroundChars;
		int turns = 0;

		
	};
};

#include "snake_movement.cpp"
#include "utilities.cpp"
#include "printing.cpp"
#include "user_input.cpp"
#include "GameBoard.cpp"

#endif