#include "globals.hpp"
#include <SFML/Graphics.hpp>

class Scoreboard {
private:
    sf::Font font; 
    sf::Text text; 
    sf::Text restartText;
public:
    Scoreboard(std::string font); 

    void setFontSize(int fontSize); 
    void setText(std::string text);
    void setStyle(uint32_t t); 
    void setColor(sf::Color c); 
    void setPosition(sf::Vector2f v); 

    void update();
    void draw(sf::RenderWindow& window);
    void draw(sf::RenderTexture& window);

    void reset(); 
};
