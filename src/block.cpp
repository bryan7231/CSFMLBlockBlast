#include "include/block.hpp"

std::vector<sf::Color> Block::Colors = {
    sf::Color(218, 98, 98), // RED
    sf::Color(222, 137, 53), // ORANGE
    sf::Color(244, 239, 149), // YELLOW
    sf::Color(51, 158, 72), // GREEN
    sf::Color(122, 205, 255), // TEAL
    sf::Color(34, 69, 150), // BLUE
    sf::Color(168, 153, 199) // PURPLE
};

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

sf::RectangleShape Block::shape() {
    return rect; 
}