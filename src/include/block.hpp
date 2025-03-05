#pragma once

#include <SFML/Graphics.hpp>
#include "globals.hpp"

class Block {
private:
    sf::RectangleShape rect; 
    sf::Vector2i tetroCoords; 
public:

    static std::vector<sf::Color> Colors;
    Block();
    Block(Color color);
    Block(sf::Vector2f pos);
    Block(Color color, sf::Vector2f pos);

    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f pos);
    void setPosition(float x, float y);

    sf::Vector2i getTetroPos();
    void setTetroPos(sf::Vector2i pos);

    sf::RectangleShape shape();
};
