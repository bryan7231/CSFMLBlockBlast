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
    
    // Updates the board based on the board vector, clears completed rows and updates score
    void updateBoard();

    // Draws the board to a window
    void draw(sf::RenderWindow& window);

    // Draws the board to a texture
    void draw(sf::RenderTexture& window);

    // Clears the board, setting all tiles to empty
    void clear(); 
};