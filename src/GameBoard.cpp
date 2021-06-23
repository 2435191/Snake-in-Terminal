#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <mutex>
#include <future>
#include <string>
#include "GameBoard.hpp"

using namespace snake;
using std::string;

const string DEATH_HEAD = "💀";
const string DEATH_BODY = "🦴";
const string DEATH_BKGD = "👻";

const string WIN_HEAD = "😀";
const string WIN_BODY = "O";
const string WIN_BKGD = "🐍";

GameBoard::GameBoard(
	const int boardWidth, const int boardHeight,
	const int startX, const int startY,
	const DIRECTION facing, const int dt, const int endBackgroundChars)
	: boardWidth(boardWidth), boardHeight(boardHeight), facing(facing), dt(dt), endBackgroundChars(endBackgroundChars)
{

	snakePos.push_back({startX, startY});

	resize(boardWidth, boardHeight + 3);
	clear();
	putFood();

	std::system("stty raw");
}

void GameBoard::run()
{
	std::atomic_bool exitFlag = false;
	auto future = std::async(std::launch::async, &GameBoard::getInput, this, std::ref(exitFlag));

	std::string end_screen;
	std::string end_message;
	while (!exitFlag)
	{

		std::this_thread::sleep_for(std::chrono::milliseconds(dt));

		this->turns++;

		std::system("clear");

		const auto lock = new std::lock_guard<std::mutex>(facing_mutex);
		GAMESTATE state = this->updateSnake();
		this->print();
		std::cout << "\n";
		delete lock;

		switch (state)
		{
		case STILL_PLAYING:
			break;

		case COLLISION_WALL_LOSE:
			exitFlag = true;
			end_message = "Ran into a wall!";
			end_screen = to_string(DEATH_HEAD, DEATH_BODY, DEATH_BKGD);
			break;
		case COLLISION_SNAKE_LOSE:
			exitFlag = true;
			end_screen = to_string(DEATH_HEAD, DEATH_BODY, DEATH_BKGD);
			end_message = "Ran into yourself!";
			break;
		case WIN:
			exitFlag = true;
			end_screen = to_string(WIN_HEAD, WIN_BODY, WIN_BKGD);
			end_message = "You beat the game!";
		}
	}

	

	std::system("stty cooked");
	std::system("clear");

	std::cout << end_screen << end_message;
	std::cout << " You scored " << snakePos.size();
	std::cout << " and lasted " << turns << " turns.";
}

