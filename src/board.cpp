#include "include/board.hpp"
#include "include/globals.hpp"

Board::Board() {
    board.assign(BOARD_SIZE, std::vector<int>(BOARD_SIZE, 0));

    outline.setSize({BOARD_SIZE*BLOCK_SIZE, BOARD_SIZE*BLOCK_SIZE});
    outline.setFillColor(BACKGROUND_COLOR);
    outline.setOutlineColor(sf::Color(255, 255, 255));
    outline.setOutlineThickness(OUTLINE_WIDTH*2);

    outline.setPosition({X_OFFSET, Y_OFFSET});
}
