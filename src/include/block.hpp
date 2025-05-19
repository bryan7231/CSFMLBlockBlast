#pragma once

#include <SFML/Graphics.hpp>
#include "globals.hpp"

class Block {
private:
    sf::RectangleShape rect; 
    sf::Vector2i tetroCoords; 
public:
    Block();
    Block(Color color);
    Block(sf::Vector2f pos);
    Block(Color color, sf::Vector2f pos);

    // Returns the position of the block
    sf::Vector2f getPosition();

    // Sets the position of the block
    void setPosition(sf::Vector2f pos);

    // Sets the position of the block given x and y 
    void setPosition(float x, float y);

    // Returns the position of the block relative to its tetromino (0, 0) to (5, 5)
    sf::Vector2i getTetroPos();

    // Sets the position of the block relative to its parent tetromino
    void setTetroPos(sf::Vector2i pos);

    // Returns a reference to the sf:RectangleShape of the block. 
    sf::RectangleShape& shape();
};
