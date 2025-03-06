#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "block.hpp"
#include "globals.hpp"

class Board {
private: 
    std::vector<std::vector<sf::RectangleShape>> grid; 
public:
    sf::RectangleShape outline; 
    std::vector<std::vector<int>> board;

    Board();
    void updateBoard();
    void draw(sf::RenderWindow& window);
};