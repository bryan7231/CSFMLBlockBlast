#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/tetromino.hpp"
#include "include/board.hpp"
#include "include/globals.hpp"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Block Blast");
    window.setFramerateLimit(144);

    Board board;

    Tetromino line(TetrominoShape::Rectangle, Color::TEAL, toGlobalCoords({0, 0})); 

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            } 
            if (event->is<sf::Event::MouseButtonPressed>()) 
            {
                // std::cout << sf::Mouse::getPosition().x - window.getPosition().x << ", " << sf::Mouse::getPosition().y - window.getPosition().y << "\n";
                mouseHeld = true; 
            }
            if (event->is<sf::Event::MouseButtonReleased>()) 
            {
                mouseHeld = false; 
            }
        }

        line.update(window, board.board);

        board.updateBoard();

        window.clear(BACKGROUND_COLOR);
        
        board.draw(window);

        line.draw(window);

        window.display();
    }
}
