#include <sstream>
#include <cstdlib>

#include "GameBoard.hpp"

using namespace snake;

int snake::GameBoard::resize(int w, int h)
{
	std::stringstream s;
	s << "resize -s";
	s << " " << h;
	s << " " << w * 2;

	return std::system(s.str().c_str());
}

int snake::GameBoard::clear()
{
	return std::system("clear");
}
