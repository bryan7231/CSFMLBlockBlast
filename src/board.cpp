#include "include/board.hpp"
#include "include/globals.hpp"

Board::Board() {
    board.assign(BOARD_SIZE, std::vector<bool>(BOARD_SIZE, 0));
}
