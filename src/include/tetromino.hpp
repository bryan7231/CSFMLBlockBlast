#pragma once

#include <vector>

#include "globals.hpp" 
#include "block.hpp"

class Tetromino {
private:
    std::vector<Block> blocks;      
    std::vector<std::vector<bool>> layout; 

    sf::Vector2f position; 
    sf::Vector2f hitbox; 
    sf::Vector2f initialOffset; 
    sf::Vector2f initialPos; 
    bool visible; 
    bool clicked;
    bool validPos; 
    Color color; 
    int id; 

    bool checkCollisions(sf::Vector2f pos); 
public:
    Tetromino(TetrominoShape s, Color c, sf::Vector2f position);
    Tetromino(std::vector<std::vector<bool>> layout, Color c, sf::Vector2f position);

    sf::Vector2f getSize(); 

    void setPosition(sf::Vector2f pos); 
    std::vector<std::vector<bool>>& getLayout(); 

    void update(sf::RenderWindow& window, std::vector<std::vector<int>>& board);
    void draw(sf::RenderWindow& r); 

    void rotate(int deg);
    void hFlip(); 
    void vFlip(); 

    void shiftLayout(); 

    void toggleVisibility(); 

    bool isVisible();
};


