#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "globals.hpp"

class Board {
private: 
    std::vector<std::vector<int>> board;
public:
    sf::RectangleShape outline; 
    std::vector<sf::RectangleShape> grid; 

    Board();
    void updateBoard();
};