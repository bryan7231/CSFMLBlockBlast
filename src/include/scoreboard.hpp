#include "globals.hpp"
#include <SFML/Graphics.hpp>

class Scoreboard {
private:
    sf::Font font; 
    sf::Text text; 
    sf::Text restartText;
public:
    Scoreboard(std::string font); 

    // Sets the font size of the score board
    void setFontSize(int fontSize); 

    // Sets the text of the scoreboard
    void setText(std::string text);

    // Sets what style the text is in the scoreboard, bold, underline...
    void setStyle(uint32_t t); 

    // Sets the color of text of the scoreboard
    void setColor(sf::Color c); 

    // Sets the position of the scoreboard
    void setPosition(sf::Vector2f v); 

    // Updates the scoreboard
    void update();

    // Draws the scoreboard to a window
    void draw(sf::RenderWindow& window);

    // Draws the scoreboard to a texture
    void draw(sf::RenderTexture& window);

    // Resets the scoreboard
    void reset(); 
};
