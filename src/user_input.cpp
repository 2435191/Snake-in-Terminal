#include "GameBoard.hpp"

using namespace snake;
void GameBoard::getInput(std::atomic_bool& shutdown_flag) {
    while (!shutdown_flag) {
        char c = getchar();
        
        DIRECTION d;
        switch (c) {
            case 'w': d = N; break;
            case 'a': d = W; break;
            case 's': d = S; break;
            case 'd': d = E; break;
        }
        const std::lock_guard<std::mutex> lock(facing_mutex);
        this->facing = d;
    }
}