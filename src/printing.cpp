
#include "GameBoard.hpp"

#include <string>
#include <sstream>
#include <iostream>

using namespace snake;
using std::string;

void snake::GameBoard::print()
{
	system("stty cooked");
	std::cout << (std::string) *this;
	system("stty raw");
}

GameBoard::operator std::string() {
	return to_string();
}
std::string GameBoard::to_string()
{
	char matrix[boardHeight][boardWidth];
	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			matrix[i][j] = '.';
		}
	}

	for (Point &point : snakePos)
	{
		matrix[point[1]][point[0]] = 'O';
	}

	auto head = snakePos[0];
	char headChar;

	switch (this->facing)
	{
	case N:
		headChar = '^';
		break;
	case S:
		headChar = 'V';
		break;
	case E:
		headChar = '>';
		break;
	case W:
		headChar = '<';
		break;
	}
	matrix[head[1]][head[0]] = headChar;
	matrix[foodCoords[1]][foodCoords[0]] = '*';

	std::stringstream s;
	for (int r = 0; r < boardHeight; r++)
	{
		for (int c = 0; c < boardWidth; c++)
		{
			s << matrix[r][c] << " ";
		}
		s << "\n";
	}

	return s.str();
}

string GameBoard::to_string(const string& headChar, const string& bodyChar, const string& backgroundChar) // for death/win conditions
{
	string matrix[boardHeight][boardWidth];
	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			matrix[i][j] = ".";
		}
	}

	for (int i = 0; i < endBackgroundChars; i++) {
		matrix[rng() % boardHeight][rng() % boardWidth] = backgroundChar;
	}

	for (Point &point : snakePos)
	{
		matrix[point[1]][point[0]] = bodyChar;
	}

	auto head = snakePos[0];
	matrix[head[1]][head[0]] = headChar;

	std::stringstream ss;
	for (int r = 0; r < boardHeight; r++)
	{
		for (int c = 0; c < boardWidth; c++)
		{
			string s = matrix[r][c];
			ss << s << (s.size() == 1 ? " " : "");
		}
		ss << "\n";
	}

	return ss.str();
}

