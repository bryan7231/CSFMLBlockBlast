#include "include/block.hpp"

Block::Block(): Block(Color::TEAL) {}


Block::Block(Color color): Block(color, {0, 0}) {}

Block::Block(sf::Vector2f pos): Block(Color::TEAL, pos) {}


Block::Block(Color color, sf::Vector2f pos) {
    rect.setSize({BLOCK_SIZE, BLOCK_SIZE});
    rect.setFillColor(Colors[color]);
    
    rect.setOutlineThickness(-OUTLINE_WIDTH);
    rect.setOutlineColor(BACKGROUND_COLOR);

    rect.setPosition(pos);
}

// Returns the position of the block
sf::Vector2f Block::getPosition() {
    return rect.getPosition();
}

// Returns the position of the block relative to its tetromino (0, 0) to (5, 5)
sf::Vector2i Block::getTetroPos() {
    return this->tetroCoords; 
}

// Sets the position of the block relative to its parent tetromino
void Block::setTetroPos(sf::Vector2i pos) {
    this->tetroCoords = pos; 
}

// Sets the position of the block
void Block::setPosition(sf::Vector2f pos) {
    rect.setPosition(pos);
}

// Sets the position of the block given x and y 
void Block::setPosition(float x, float y) {
    rect.setPosition({x, y});
}

// Returns a read-write reference to the sf:RectangleShape of the block. 
sf::RectangleShape& Block::shape() {
    return rect; 
}