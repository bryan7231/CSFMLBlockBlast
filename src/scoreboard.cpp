#include "include/scoreboard.hpp"
#include <iostream> 

Scoreboard::Scoreboard(std::string font): text(this->font), restartText(this->font) {
    if (!this->font.openFromFile("../fonts/" + font)) {
        std::cout << "No font found!" << "\n"; 
    } else {
        text.setFont(this->font); 
        setFontSize(60); 
        setColor(HIGHLIGHT_COLOR); 
        setText("Adding text..."); 
        setStyle(sf::Text::Bold);

        restartText.setFont(this->font); 
        restartText.setCharacterSize(120); 
        restartText.setFillColor(sf::Color::Red);
        restartText.setStyle(sf::Text::Bold); 
        restartText.setString("Press Space to restart");

        float xPos = (WINDOW_WIDTH / 2.f + (BLOCK_SIZE * BOARD_SIZE) / 8.f + WINDOW_WIDTH) / 2.f; 
        setPosition({xPos, WINDOW_HEIGHT/2.f - 60});
    }
}

// Sets the font size of the score board
void Scoreboard::setFontSize(int fontSize) {
    text.setCharacterSize(fontSize);
}

// Sets the text of the scoreboard
void Scoreboard::setText(std::string text) {
    this->text.setString(text); 
}

// Sets what style the text is in the scoreboard, bold, underline...
void Scoreboard::setStyle(uint32_t t) {
    this->text.setStyle(t); 
}

// Sets the color of text of the scoreboard
void Scoreboard::setColor(sf::Color c) {
    this->text.setFillColor(c);
}

// Sets the position of the scoreboard
void Scoreboard::setPosition(sf::Vector2f v) {
    this->text.setPosition(v); 
}

// Updates the scoreboard
void Scoreboard::update() {
    if (gameOver) {

        setFontSize(120); 
        setColor(sf::Color::Red); 
        setPosition({WINDOW_WIDTH / 2.f - 350.f, WINDOW_HEIGHT / 2.f - 200.f}); 
        setText(
            "GAME OVER!\nScore: " + 
            std::to_string((int)score) + 
            std::to_string(score - (int)score).substr(1, 3)
        ); 
        setStyle(sf::Text::Bold);

        restartText.setPosition({WINDOW_WIDTH / 2.f - 550.f, WINDOW_HEIGHT / 2.f + 200.f});
        return; 
    }

    setText("Score:\n" + std::to_string((int)score) + std::to_string(score - (int)score).substr(1, 3)); 
}

// Draws the scoreboard to a window
void Scoreboard::draw(sf::RenderWindow& window) {
    window.draw(text); 
    if (gameOver) window.draw(restartText); 
}

// Draws the scoreboard to a texture
void Scoreboard::draw(sf::RenderTexture& window) {
    window.draw(text); 
    if (gameOver) window.draw(restartText); 
}

// Resets the scoreboard
void Scoreboard::reset() {
    setFontSize(60); 
    setColor(HIGHLIGHT_COLOR); 
    setText("Adding text..."); 
    setStyle(sf::Text::Bold);

    float xPos = (WINDOW_WIDTH / 2.f + (BLOCK_SIZE * BOARD_SIZE) / 8.f + WINDOW_WIDTH) / 2.f; 
    setPosition({xPos, WINDOW_HEIGHT/2.f - 60});
} 