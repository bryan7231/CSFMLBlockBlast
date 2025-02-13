#include <SFML/Graphics.hpp>
#include "globals.hpp"

class Block {
private:
sf::RectangleShape rect; 
public:

    static std::vector<sf::Color> Colors;
    Block();
    Block(Color color);
    Block(sf::Vector2f pos);
    Block(Color color, sf::Vector2f pos);

    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f pos);
    void setPosition(float x, float y);

    sf::RectangleShape shape();
};
