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

sf::Vector2f Block::getPosition() {
    return rect.getPosition();
}

sf::Vector2i Block::getTetroPos() {
    return this->tetroCoords; 
}
void Block::setTetroPos(sf::Vector2i pos) {
    this->tetroCoords = pos; 
}

void Block::setPosition(sf::Vector2f pos) {
    rect.setPosition(pos);
}

void Block::setPosition(float x, float y) {
    rect.setPosition({x, y});
}

sf::RectangleShape& Block::shape() {
    return rect; 
}