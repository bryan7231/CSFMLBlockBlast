#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/tetromino.hpp"
#include "include/board.hpp"
#include "include/globals.hpp"
#include "include/bag.hpp"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Block Blast");
    window.setFramerateLimit(144);

    Board board;

    // Tetromino line(TetrominoShape::L3, Color::TEAL, {TILE_START_X, TILE_START_Y}); 

    Bag bag(3); 

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

        // line.update(window, board.board);

        if (gameOver) {
            std::cout << "Game over!" << "\n"; 
            continue; 
        }

        bag.update(window, board.board); 

        board.updateBoard();

        window.clear(BACKGROUND_COLOR);
        
        board.draw(window);

        bag.draw(window);

        // line.draw(window);

        window.display();
    }
}
