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

    // Returns the size of the tetromino, in global coordinates; the smallest size that can fit all blocks in the tetromino
    sf::Vector2f getSize(); 

    // Sets the position of the tetromino, updating position of all blocks, as well as hitbox
    void setPosition(sf::Vector2f pos); 

    // Gets the layout of the tetromino, in terms of a 5x5 matrix, where true is a location of a block
    std::vector<std::vector<bool>>& getLayout(); 

    // Updates and checks for collisions of tetromino, returns true if tetromino was placed during this frame
    bool update(sf::RenderWindow& window, std::vector<std::vector<int>>& board);

    // Draws the tetromino to a window
    void draw(sf::RenderWindow& r); 

    // Draws the tetromino to a texture
    void draw(sf::RenderTexture& r); 

    // Rotates the tetromino by a multiple of 90 degrees, only valid ones are, (90, 180, 270), shifting layout after
    void rotate(int deg);

    // Flips the layout of a tetromino horizontally, and shifts layout.
    void hFlip(); 

    // Flips the layout of a tetromino vertically, and shifts layout. 
    void vFlip(); 

    // Shifts the layout of the tetromino, moving it to the top left corner of the matrix. Ensures that position of each tetromino is correct. 
    void shiftLayout(); 

    // Toggles the visibility of the tetromino
    void toggleVisibility(); 

    // Returns true if the tetromino is visible, false otherwise 
    bool isVisible();
};


