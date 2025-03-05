#pragma once

#include <vector>

#include "globals.hpp" 
#include "block.hpp"

class Tetromino {
private:
    
    std::vector<std::vector<bool>> layout; 

    sf::Vector2f position; 
    bool visible; 
    Color color; 
public:
std::vector<Block> blocks;  
    Tetromino(TetrominoShape s, Color c, sf::Vector2f position);
    Tetromino(std::vector<std::vector<bool>> layout, Color c, sf::Vector2f position);

    void update();
    void rotate(int deg);
    void hFlip(); 
    void vFlip(); 
    void draw(sf::RenderWindow& r); 

    void toggleVisibility(); 
};


