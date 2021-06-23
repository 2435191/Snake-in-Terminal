#include "GameBoard.hpp"

using namespace snake;

int main()
{
	GameBoard board = GameBoard(20, 20, 10, 10, N, 250, 0);
	board.run();
	return 0;
}